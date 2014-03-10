#ifndef header_CCF1F1A11CC1
#define header_CCF1F1A11CC1

namespace SG
{
    template <typename T>
    class Group : public Rt::Observable<>
    {
    public:
        typedef std::set<T> Items;
    
    private:
        Items items;

    public:
        void add(T item) {
            auto result = items.insert(item);
            if (!result.second) Rt::error(0x384A8FEA);
            notify(this);
        }
        
        void remove(T item) {
            auto iter = items.find(item);
            if (iter != items.end()) {
                items.erase(iter);
                notify(this);
            }
        }
        
        void clear() {
            items.clear();
            notify(this);
        }
        
        const Items& getItems() const {
            return items;
        }

        std::list<T> sort(const std::shared_ptr<ObjectsOrder>& order) const {
            return order->sort(items);
        }
    };
}

#endif
