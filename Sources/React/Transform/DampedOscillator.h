#ifndef header_6cdd7547e1ca
#define header_6cdd7547e1ca

namespace React
{
    class DampedOscillator : public Animation<float, DampedOscillator>
    {
    private:
        enum class Behaviour {
            under,
            critical,
            over
        };

    private:
        float m, k, c, g;
        float x0, v0;
        float discriminant, coeff[3], l[2];
        Behaviour behaviour;
        bool firstRun;

    private:
        static Behaviour determineSystemBehaviour(float c, float m, float k, float& discriminant) {
            discriminant = c * c - 4 * m * k;
            if (discriminant < 0.0f) return Behaviour::under;
            else
                if (discriminant == 0.0f)
                    return Behaviour::critical;
                else
                    return Behaviour::over;
        }

        static void calcParameters(float m, float k, float c, float g, float x0, float v0,
                                   float& discriminant, Behaviour& behaviour, float coeff[3], float l[2])
        {
/*
            zeta = c / (2 * std::sqrt(k * m));
            omega0 = std::sqrt(k / m);
*/
            behaviour = determineSystemBehaviour(c, m, k, discriminant);

            switch (behaviour) {
                case Behaviour::under: {
                    auto alpha = -c / (2 * m);
                    auto beta = std::sqrt(-discriminant) / (2 * m);
                    auto tmp = alpha * alpha + beta * beta;
                    l[0] = alpha;
                    l[1] = beta;
                    coeff[0] = (x0 * k + 2.0f * alpha * v0 * m + v0 * c + g)/(m * tmp);
                    coeff[1] = (-x0 * alpha * k - alpha * alpha * v0 * m - alpha * v0 * c - alpha * g + v0 * beta * beta * m) / (beta * m * tmp);
                    coeff[2] = (x0 * alpha * alpha * m + x0 * beta * beta * m - x0 * k - 2.0f * alpha * v0 * m - v0 * c - g) / (m * tmp);
                }
                break;

                case Behaviour::critical: {
                    l[0] = l[1] = -c / (2.0f * m);
                    coeff[0] = v0 / l[0];
                    auto tmp = l[0] * l[0] * m;
                    auto tmp1 = -v0 * c - g - x0 * k;
                    coeff[1] = (tmp1 - v0 * l[0] * m) / tmp;
                    coeff[2] = (tmp1 - 2 * v0 * l[0] * m + x0 * tmp) / tmp;
                }
                break;

                case Behaviour::over: {
                    l[0] = (-c - std::sqrt(discriminant)) / (2.0f * m);
                    l[1] = (-c + std::sqrt(discriminant)) / (2.0f * m);
                    coeff[0] = - (x0 * (c + l[1] * m) + v0 + g) / (l[0] * m * (l[0] - l[1]));
                    coeff[1] = - (x0 * (c + l[0] * m) + v0 + g) / (l[1] * m * (l[1] - l[0]));
                    coeff[2] = - (x0 * (c + m * (l[0] + l[1])) + v0 * (1.0f - l[0] * l[1] * m) + g) / (l[0] * l[1] * m);
                }
                break;
            }
        }

    protected:
        virtual void evaluate(Rt::u8 t) {
            double dt = 0.0, x;

            auto iter = this->timePoints.begin();
            if (iter != this->timePoints.end())
                dt = double(t - *iter);
            else {
                this->timePoints.push_front(t);
                dt = 0;
            }

            static double last_dt = 0.0;
            //printf("%f\n", dt - last_dt);
            last_dt = dt;
            dt /= 100000000.0;

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

            output[0]->set(x);
            output[0]->commit();

//            if (firstRun) {
                output[1]->set(coeff[2]);
//                firstRun = false;
//            }
            output[1]->commit();
        }

    public:
        DampedOscillator(float m, float k, float c, float g, float x0, float v0) {
            this->m = m;
            this->k = k;
            this->c = c;
            this->g = g;
            this->x0 = x0;
            this->v0 = v0;
            this->firstRun = true;
            calcParameters(m, k, c, g, x0, v0, discriminant, behaviour, coeff, l);
        }

        void reset() {
            this->timePoints.clear();
        }
    };
}

#endif
