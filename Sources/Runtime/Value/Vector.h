#ifndef header_90A40BDEB717
#define header_90A40BDEB717

namespace Rt
{
    namespace Value
    {
        class Vector : public Container<std::vector<std::shared_ptr<Trait>>>
        {
        public:
            Vector();
            virtual ~Vector();

            Rt::u4 getSize();
            std::shared_ptr<Trait> get(Rt::u4 index);
            void set(Rt::u4 index, std::shared_ptr<Trait> value);

            virtual void traverseTree(std::function<void (std::shared_ptr<Trait>)> f);
        };
    }
}

#endif
