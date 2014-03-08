#ifndef header_377428102FA0
#define header_377428102FA0

#include <boost/format.hpp>

namespace Rt
{
    namespace Type
    {
        template <typename T = u4, typename I = u4>
        class Atom : public Trait<T, I>
        {
        private:
            T size;

        public:
            Atom(T size) {
                this->kind = Trait<T, I>::Kind::Atom;
                this->size = size;
            }

            virtual Trait<T, I>* at(const char* pathComponent) {
                Rt::error(0x30FBA399);
                return 0;
            }

            virtual T getSize() {
                return size;
            }

            void setSize(T size) {
                this->size = size;
            }

            virtual std::string toString() const {
                return str(boost::format("%u") % size);
            }

            virtual Trait<T, I>* copyRecursively() {
                auto retval = new Atom(size);
                if (!retval) Rt::error(0xC00A7862);

                this->copyAttributesTo(retval);

                return retval;
            }
        };
    }
}

#endif
