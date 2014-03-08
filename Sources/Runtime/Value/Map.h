#ifndef header_467FFD2AE90B
#define header_467FFD2AE90B

namespace Rt
{
    namespace Value
    {
        class Map : public Container<std::map<std::string, std::shared_ptr<Trait>>>
        {
        public:
            typedef const char* PropertyName;

        public:
            Map();
            Map(const Map&);
            virtual ~Map();

            virtual Map operator+(const Map&) const;
            virtual Map& operator+=(const Map&);

            Rt::u4 getCount(PropertyName) const;
            Option<std::shared_ptr<Trait>> get(PropertyName) const;
            void set(PropertyName, std::shared_ptr<Trait> value);
            void erase(PropertyName);

            virtual void traverseTree(std::function<void (std::shared_ptr<Trait>)> f);

            template <typename T>
            Option<T> getScalar(PropertyName) const;

            template <typename T>
            void setScalar(PropertyName, Option<T>);

            template <typename T>
            void setScalar(PropertyName, T);
        };
    }
}

#include <Runtime/Value/MapDefinition.h>

#endif
