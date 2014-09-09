#ifndef header_3643B86B2B78
#define header_3643B86B2B78

namespace Math
{
    namespace Geometry
    {
        template <typename D, typename I>
        class SourceElementsProvider
        {
            virtual I getSourceElement(D, I) = 0;
            virtual std::vector<I> getSourceElements(D) = 0;
        };

        template <typename D, typename I>
        class DefaultSourceElementsProvider : public SourceElementsProvider<D, I>
        {
        protected:
            std::shared_ptr<Topology<D, I>> topology;

        public:
            virtual I getSourceElement(D, I index) override {
                return index;
            }

            virtual std::vector<I> getSourceElements(D dim) override {
                I count = topology->getCount(dim);
                std::vector<I> retval(count);

                for (I i  = 0; i < count; i++)
                    retval[i] = i;

                return retval;
            }
        };
    }
}

#endif
