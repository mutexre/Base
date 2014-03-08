#ifndef header_9a4feae6ad3c
#define header_9a4feae6ad3c

namespace React
{
    template <typename T, class This>
    class Animation : public Transform<T, This>
    {
    protected:
        ValuePtr<Rt::u8> timeSource;
        std::deque<Rt::u8> timePoints;

    protected:
        virtual void evaluate() {
            evaluate(timeSource->get(0));
        }

        virtual void evaluate(Rt::u8) = 0;

    public:
        ValuePtr<Rt::u8> getTimeSource() {
            return timeSource;
        }

        void setTimeSource(ValuePtr<Rt::u8> timeSource) {
            if (timeSource.get()) {
                // TODO: disconnect from old time source
            }
            this->timeSource = timeSource;
            this->observeInput(timeSource);
        }

        std::deque<Rt::u8>& getTimePoints() {
            return timePoints;
        }
    };

    template <typename T>
    class LambdaAnimation : public Animation<T, LambdaAnimation<T>>
    {
    protected:
        std::function<void(Rt::u8, LambdaAnimation&)> f;

    protected:
        virtual void evaluate(Rt::u8 t) {
            f(t, *this);
        }

    public:
        LambdaAnimation(std::function<void(Rt::u8, LambdaAnimation&)> f) {
            this->f = f;
        }
    };
}

#endif
