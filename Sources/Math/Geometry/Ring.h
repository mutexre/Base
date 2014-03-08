#ifndef header_65572337E110
#define header_65572337E110

namespace Math
{
    namespace Geometry
    {
        namespace Ring
        {
            template <typename D = Rt::u1, typename I = Rt::u4>
            class Topology : public Geometry::Topology<D, I>
            {
            private:
                I n;

            public:
                Topology() {}

                Topology(I n) {
                    this->n = n;
                }

                virtual ~Topology() {}

                I getN() const { return n; }
                void setN(I n) { this->n = n; }

                virtual I getCount(D dim) override {
                    if (dim == 0 || dim == 1) return n;
                    return 0;
                };

                virtual I getCount(I, D dim, D elementsDim) override {
                    if ((dim == 0 && elementsDim == 1) || (dim == 1 && elementsDim == 0)) return 2;
                    return 0;
                }

                virtual bool isElementsCountUniform(D, D elementDim) override {
                    return true;
                }

                virtual std::vector<I> getElements(I id, D dim, D elementsDim) override {
                    std::vector<I> retval;
                    switch (dim) {
                        case 0:
                            if (elementsDim == 1) {
                                retval.push_back(id == 0 ? n - 1 : id);
                                retval.push_back(id);
                            }
                            else
                                retval.push_back(id);
                        break;

                        case 1:
                            if (elementsDim == 0) {
                                retval.push_back(id);
                                retval.push_back(id == n - 1 ? 0 : id + 1);
                            }
                            else
                                retval.push_back(id);
                        break;
                    };

                    return retval;
                }
            };
/*
            template <typename D = Rt::u1, typename I = Rt::u4>
            class Topology2 : public Geometry::Topology<D, I>
            {
            private:
                std::vector<I> dimensions;

            public:
                Topology2() {}

                Topology2(const std::vector<I>& dimensions) {
                    this->dimensions = dimensions;
                }

                Topology2(I n) {
                    dimensions.push_back(n);
                }

                virtual ~Topology2() {}

                const std::vector<I>& getDimensions() const {
                    return dimensions;
                }

                void setDimensions(const std::vector<I>& dimensions) {
                    this->dimensions = dimensions;
                }

                virtual I getCount(D dim) override {
                    if (dim == 0 || dim == 1) return n;
                    return 0;
                };

                virtual I getCount(I, D dim, D elementsDim) override {
                    if ((dim == 0 && elementsDim == 1) || (dim == 1 && elementsDim == 0)) return 2;
                    return 0;
                }

                virtual bool isElementsCountUniform(D, D) override {
                    return true;
                }

                virtual std::vector<I> getElements(I id, D dim, D elementsDim) override {
                    std::vector<I> retval;
                    switch (dim) {
                        case 0:
                            if (elementsDim == 1) {
                                retval.push_back(id == 0 ? n - 1 : id);
                                retval.push_back(id);
                            }
                            else
                                retval.push_back(id);
                        break;

                        case 1:
                            if (elementsDim == 0) {
                                retval.push_back(id);
                                retval.push_back(id == n - 1 ? 0 : id + 1);
                            }
                            else
                                retval.push_back(id);
                        break;
                    };

                    return retval;
                }
            };
*/
        }
    }
}

#endif

