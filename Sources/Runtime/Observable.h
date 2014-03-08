#ifndef header_B4F80D95184F
#define header_B4F80D95184F

namespace Rt
{
    template <unsigned char N_SIGNALS = 1, typename IntType = Rt::u4>
    class Observable
    {
    public:
        typedef boost::signals2::signal<void (void*)> Signal;

    private:
        Signal signals[N_SIGNALS];

    public:
        boost::signals2::connection addObserver(Rt::u1 signalIndex, const typename Signal::slot_type& observer) {
            return signals[signalIndex].connect(observer);
        }

        boost::signals2::connection addObserver(const typename Signal::slot_type& observer) {
            return addObserver(0, observer);
        }

        void notify(Rt::u1 signalIndex, void* data) {
            signals[signalIndex](data);
        }

        void notify(void* data) {
            notify(0, data);
        }
    };
}

#endif
