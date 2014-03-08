#ifndef header_945DAA370412
#define header_945DAA370412

#include <functional>

namespace Rt
{
    template <typename T>
    class Option
    {
    public:
        bool defined;
        T value;

        Option() : defined(false) {}
        Option(T val) : defined(true), value(val) {}

        void define(T value) {
            defined = true;
            this->value = value;
        }

        void undefine() {
            defined = false;
        }

        T get() const {
            return value;
        }

        T getOrElse(T defaultValue) {
            return defined ? value : defaultValue;
        }

        T getOrExecute(std::function<void()> f) {
            if (!defined) f();
            return value;
        }

        T getOrThrow() {
            if (!defined) error(0xE17432AC);
            return value;
        }

        T operator->() const {
            return value;
        }
    };
}

#endif
