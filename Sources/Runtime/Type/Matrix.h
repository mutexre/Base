#ifndef header_CA3127E13585
#define header_CA3127E13585

#include <boost/format.hpp>

namespace Rt
{
    namespace Type
    {
        template <typename T = u4, typename I = u4>
        class Matrix : public Trait<T, I>
        {
        private:
            Trait<T, I>* type;
            I numberOfElements;
            std::vector<I> dimensions;

            I calcNumberOfElements() {
                return std::accumulate(dimensions.begin(), dimensions.end(), 1, std::multiplies<I>());
            }

        public:
            Matrix() {
                this->kind = Trait<T, I>::Kind::Matrix;
            }

            virtual ~Matrix() {
                delete type;
            }

            Matrix(Trait<T, I>* type, std::vector<I> dimensions) {
                this->kind = Trait<T, I>::Kind::Matrix;
                this->type = type;
                type->setParent(Option<Trait<T, I>*>(this));
                this->dimensions = dimensions;
                this->numberOfElements = calcNumberOfElements();
            }

            Matrix(Trait<T, I>* type, I numberOfElements) {
                this->kind = Trait<T, I>::Kind::Matrix;
                this->type = type;
                type->setParent(Option<Trait<T, I>*>(this));
                this->dimensions.push_back(numberOfElements);
                this->numberOfElements = numberOfElements;
            }

            virtual void traverseTree(std::function<void (Trait<T, I>*)> f) {
                type->traverseTree(f);
                Trait<T, I>::traverseTree(f);
            }

            virtual Trait<T, I>* at(const char* pathComponent) {
                auto name = type->getName();
                if (name.defined && !strcmp(pathComponent, name.value.c_str()))
                    return type;

                return 0;
            }

            virtual T getSize() {
                return type->getRoundedSize() * numberOfElements;
            }

            Trait<T, I>* getNestedType() const { return type; }

            I getNumberOfElements() const { return numberOfElements; }

            void setDimension(u2 dimIndex, I value) {
                dimensions[dimIndex] = value;
                numberOfElements = calcNumberOfElements();
            }

            void setDimensions(std::vector<I> dimensions) {
                this->dimensions = dimensions;
                numberOfElements = calcNumberOfElements();
            }
            
            virtual std::string toString() const {
                std::string retval = type->toString();

                auto iter = dimensions.begin();
                while (iter != dimensions.end()) {
                    if (iter == dimensions.begin()) retval += std::string(" x ");
                    retval += str(boost::format("%u") % *iter);
                    iter++;
                    if (iter != dimensions.end()) retval += std::string(" x ");
                }

                return retval;
            }

            virtual Trait<T, I>* copyRecursively() {
                auto retval = new Matrix();
                if (!retval) Rt::error(0xBBF14271);

                retval->type = type->copyRecursively();
                if (!retval->type) Rt::error(0x74B78660);

                retval->numberOfElements = numberOfElements;
                retval->dimensions = dimensions;

                this->copyAttributesTo(retval);

                return retval;
            }
        };
    }
}

#endif
