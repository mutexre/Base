#ifndef header_06FA4404FA48
#define header_06FA4404FA48

namespace Rt
{
    namespace Memory
    {
        template <typename Size>
        class CommonRequirements
        {
        public:
            static Value::Map pack(Option<Size> size = Option<Size>(), Option<Size> alignment = Option<Size>()) {
                Value::Map requirements;

                requirements.setScalar("size", size);
                requirements.setScalar("alignment", alignment);

                return requirements;
            }

            static Value::Map pack(Size size, Option<Size> alignment = Option<Size>()) {
                return pack(Option<Size>(size), alignment);
            }

            static Value::Map pack(Size size, Size alignment) {
                return pack(Option<Size>(size), Option<Size>(alignment));
            }

            static void unpack(const Value::Map& requirements,
                               Option<Size>& size,
                               Option<Size>& alignment)
            {
                size = requirements.getScalar<Size>("size");
                alignment = requirements.getScalar<Size>("alignment");
            }
        };
    }
}

#endif
