#ifndef header_E0EB936B780D
#define header_E0EB936B780D

namespace Rt
{
    namespace Value
    {
        class Uuid : public Trait
        {
        private:
            Rt::uuid value;

        public:
            Uuid();
            Uuid(Rt::uuid value);

            void get(Rt::uuid& value);
            void set(Rt::uuid value);

            void generate();
        };
    }
}

#endif
