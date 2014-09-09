#ifndef header_C42229FFF6AF
#define header_C42229FFF6AF

namespace SG
{
    template <typename T>
    class Order : public React::Observable<1>
    {
    private:
        std::list<Rt::Either<T, std::shared_ptr<Order>>> children;

    public:
        template <typename T2>
        void add(T2 item) {
            children.push_back(Rt::Either<T, std::shared_ptr<Order>>(item));
            notify(this);
        }

        std::list<ObjectPtr>
        sort(const std::set<T>& objects) const {
            std::list<ObjectPtr> orderedObjects;
            for (auto& child : children) {
                if (child.state.defined) {
                    if (child.state.get() == 0) {
                        auto object = child.a;
                        if (objects.find(object) != objects.end())
                            orderedObjects.push_back(object);
                    }
                    else
                        orderedObjects.merge(child.b->sort(objects));
                }
            }
            return orderedObjects;
        }
    };
}

#endif
