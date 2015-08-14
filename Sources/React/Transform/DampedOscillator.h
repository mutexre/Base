#ifndef header_6cdd7547e1ca
#define header_6cdd7547e1ca

namespace React
{
    template <typename T, typename F>
    class DampedOscillator : public Transform<DampedOscillator<T, F>>
    {
        DF_IN(ScalarPtr<T>, timeSource, getTimeSource, setTimeSource, &DampedOscillator::invalidateTimeDependants)
        DF_IN(ScalarPtr<F>, m, getM, setM, &DampedOscillator::invalidateOthers)
        DF_IN(ScalarPtr<F>, k, getK, setK, &DampedOscillator::invalidateOthers)
        DF_IN(ScalarPtr<F>, c, getC, setC, &DampedOscillator::invalidateOthers)
        DF_IN(ScalarPtr<F>, g, getG, setG, &DampedOscillator::invalidateOthers)
        DF_IN(ScalarPtr<F>, x0, getX0, setX0, &DampedOscillator::invalidateOthers)
        DF_IN(ScalarPtr<F>, v0, getV0, setV0, &DampedOscillator::invalidateOthers)
        DF_OUT(ScalarPtr<F>, x, getX, setX, &DampedOscillator::evaluateTimeDependants)
        DF_OUT(ScalarPtr<F>, finalDisplacement, getFinalDisplacement, setFinalDisplacement, &DampedOscillator::evaluateOthers)

    public:
        enum class Behaviour {
            under,
            critical,
            over
        };

        DF_OUT(ScalarPtr<Behaviour>, behaviour, getBehaviour, setBehaviour, &DampedOscillator::evaluateOthers)

    private:
        F discriminant, coeff[3], l[2];
        std::deque<T> timePoints;

    private:
        static Behaviour determineSystemBehaviour(F c, F m, F k, F& discriminant) {
            discriminant = c * c - F(4) * m * k;
            if (discriminant < F(0)) return Behaviour::under;
            else
                if (discriminant == F(0))
                    return Behaviour::critical;
                else
                    return Behaviour::over;
        }

        static void calcParameters(F m, F k, F c, F g, F x0, F v0,
                                   F& discriminant, Behaviour& behaviour, F coeff[3], F l[2])
        {
/*
            zeta = c / (2 * std::sqrt(k * m));
            omega0 = std::sqrt(k / m);
*/
            behaviour = determineSystemBehaviour(c, m, k, discriminant);

            switch (behaviour) {
                case Behaviour::under: {
                    auto alpha = -c / (F(2) * m);
                    auto beta = std::sqrt(-discriminant) / (F(2) * m);
                    auto tmp = alpha * alpha + beta * beta;
                    l[0] = alpha;
                    l[1] = beta;
                    coeff[0] = (x0 * k + F(2) * alpha * v0 * m + v0 * c + g)/(m * tmp);
                    coeff[1] = (-x0 * alpha * k - alpha * alpha * v0 * m - alpha * v0 * c - alpha * g + v0 * beta * beta * m) / (beta * m * tmp);
                    coeff[2] = (x0 * alpha * alpha * m + x0 * beta * beta * m - x0 * k - F(2) * alpha * v0 * m - v0 * c - g) / (m * tmp);
                }
                break;

                case Behaviour::critical: {
                    l[0] = l[1] = -c / (F(2) * m);
                    coeff[0] = v0 / l[0];
                    auto tmp = l[0] * l[0] * m;
                    auto tmp1 = -v0 * c - g - x0 * k;
                    coeff[1] = (tmp1 - v0 * l[0] * m) / tmp;
                    coeff[2] = (tmp1 - F(2) * v0 * l[0] * m + x0 * tmp) / tmp;
                }
                break;

                case Behaviour::over: {
                    l[0] = (-c - std::sqrt(discriminant)) / (F(2) * m);
                    l[1] = (-c + std::sqrt(discriminant)) / (F(2) * m);
                    coeff[0] = - (x0 * (c + l[1] * m) + v0 + g) / (l[0] * m * (l[0] - l[1]));
                    coeff[1] = - (x0 * (c + l[0] * m) + v0 + g) / (l[1] * m * (l[1] - l[0]));
                    coeff[2] = - (x0 * (c + m * (l[0] + l[1])) + v0 * (F(1) - l[0] * l[1] * m) + g) / (l[0] * l[1] * m);
                }
                break;
            }
        }

    protected:
        void evaluateTimeDependants() {
            F dt, x;

            auto t = timeSource->get();
            auto iter = this->timePoints.begin();
            if (iter != this->timePoints.end())
                dt = F(double(t - *iter) / 100000000.0);
            else {
                this->timePoints.push_front(t);
                dt = F(0);
            }

            switch (behaviour) {
                case Behaviour::under:
                    x = std::exp(l[0] * dt) * (coeff[0] * std::cos(l[1] * dt) + coeff[1] * std::sin(l[1] * dt)) + coeff[2];
                break;

                case Behaviour::critical:
                    x = (coeff[0] + coeff[1] * (l[0] * dt - 1.0f)) * std::exp(l[0] * dt) + coeff[2];
                break;

                case Behaviour::over:
                    x = coeff[0] * std::exp(l[0] * dt) + coeff[1] * std::exp(l[1] * dt) + coeff[2];
                break;
            }

            this->x->set(x);
            this->x->commit(false);

/*//            if (firstRun) {
                finalDisplacement->set(coeff[2]);
//                firstRun = false;
//            }
            finalDisplacement->commit(false);*/
        }

        void evaluateOthers() {
            calcParameters(m->get(), k->get(), c->get(), g->get(), x0->get(), v0->get(),
                           discriminant, behaviour->get(), coeff, l);

            behaviour->commit(false);
            finalDisplacement->set(coeff[2]);
            finalDisplacement->commit(false);
        }

        void invalidateTimeDependants() {
            if (x.get())
                x->invalidate();
        }

        void invalidateOthers() {
            if (x.get())
                x->invalidate();

            if (behaviour.get())
                behaviour->invalidate();

            if (finalDisplacement.get())
                finalDisplacement->invalidate();
        }

    public:
/*        DampedOscillator(F m, F k, F c, F g, F x0, F v0) {
            this->m = m;
            this->k = k;
            this->c = c;
            this->g = g;
            this->x0 = x0;
            this->v0 = v0;
            this->firstRun = true;
            calcParameters(m, k, c, g, x0, v0, discriminant, behaviour, coeff, l);
        }*/

        void reset() {
            this->timePoints.clear();
        }
    };
}

#endif
