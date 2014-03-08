#ifndef header_BA5B0F225B02
#define header_BA5B0F225B02

namespace Rt {
    namespace Memory {
        namespace Traits
        {
            template <typename Id>
            class Info
            {
            public:
                virtual Value::Map getInfo() { return Value::Map(); }
                virtual Value::Map getAllocationInfo(Id) { return Value::Map(); }
            };
        }
    }
}

#endif
