#ifndef header_1CC569137D05
#define header_1CC569137D05

namespace Rt {
    namespace Memory {
        namespace Traits
        {
            template <typename Id>
            class Alloc
            {
            public:
                class BadAlloc : std::exception
                {
                public:
                    BadAlloc();

                    virtual const char* what() const throw() {
                        return "bad alloc";
                    }
                };

            protected:
                Value::Map defaultRequirements;

            protected:
                virtual Id inheritedAlloc(Value::Map) = 0;

            public:
                Alloc() {}
                Alloc(Value::Map defaultRequirements);
                virtual ~Alloc() {}

                virtual Value::Map getDefaultRequirements();
                virtual void setDefaultRequirements(Value::Map);

                virtual Id alloc();
                virtual Id alloc(Value::Map);

                virtual void free(Id) = 0;
            };

            #include <Runtime/Memory/Traits/AllocDefinition.h>
        }
    }
}

#endif
