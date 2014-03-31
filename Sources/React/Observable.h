#ifndef header_B4F80D95184F
#define header_B4F80D95184F

namespace React
{
    template <int N = 1>
    class Observable
    {
    public:
        using Signal = boost::signals2::signal<void (void*)>;
        using Observer = Signal::slot_type;
        using Connection = boost::signals2::connection;

    protected:
        Signal signals[N];

    public:
        Connection addObserver(Rt::u1 index, const Observer& observer) {
            return signals[index].connect(observer);
        }

        Connection addObserver(const Observer& observer) {
            return addObserver(0, observer);
        }

        void notify(Rt::u1 index, void* data) {
            signals[index](data);
        }

        void notify(void* data) {
            notify(0, data);
        }
    };
}

#endif
