#ifndef header_7D4A81C8E38C
#define header_7D4A81C8E38C

namespace Math
{
    namespace Geometry
    {
/*
        template <typename T, typename D = Rt::u1, typename I = Rt::u4>
        class VertexData
        {
        public:
            D dim;
            std::vector<T> coords;
        };

        template <typename T, typename D = Rt::u1, typename I = Rt::u4>
        class Model
        {
        public:
            D dim;
            std::vector<T> vertices;
            std::shared_ptr<Topology<D, I>> topology;

        public:
            Model(D dim) {
                this->dim = dim;
            }

            virtual ~Model() {}
        };

        template <typename T, typename D = Rt::u1, typename I = Rt::u4>
        class MixedModel : public Model<T, D, I>
        {
        private:
            D sourceDim;
            std::vector<std::vector<T>> sources;

        public:
            MixedModel(D sourceDim, D numberOfSources, std::shared_ptr<Topology<D, I>> topology) : Model<T, D, I>(numberOfSources * sourceDim)
            {
                this->sourceDim = sourceDim;
                this->topology = topology;
                sources.resize(numberOfSources);
                this->vertices.resize(topology->getCount(0) * this->dim);
            }

            virtual ~MixedModel() {}

            std::vector<T>& getSource(D index) {
                return sources[index];
            }

            void setSourceVertices(D sourceIndex, std::vector<T> source) {
                sources[sourceIndex] = source;
            }

            void gather()
            {
                auto srcVertexDataSize = sourceDim * sizeof(T);
                for (D source = 0; source < sources.size(); source++) {
                    Rt::stridedCopy((Rt::u1*)sources[source].data(), srcVertexDataSize,
                                    (Rt::u1*)(this->vertices.data() + source * sourceDim), this->dim * sizeof(T),
                                    srcVertexDataSize, this->topology->getCount(0));
                }
            }
        };
*/
        template <typename T = float, typename D = Rt::u1, typename I = Rt::u4>
        std::vector<T> gather(const std::vector<std::vector<T>>& sources, D srcAttrSize, I count)
        {
            auto srcAttrSizeInBytes = srcAttrSize * sizeof(T);
            auto dstAttrSize = srcAttrSize * sources.size();
            auto dstAttrSizeInBytes = dstAttrSize * sizeof(T);
            std::vector<T> dest(count * dstAttrSize);

            for (D source = 0; source < sources.size(); source++)
                Rt::stridedCopy(reinterpret_cast<const Rt::u1*>(sources[source].data()), srcAttrSizeInBytes,
                                reinterpret_cast<Rt::u1*>(dest.data()) + source * srcAttrSizeInBytes, dstAttrSizeInBytes,
                                srcAttrSizeInBytes, count);

            return dest;
        }
    }
}

#endif
