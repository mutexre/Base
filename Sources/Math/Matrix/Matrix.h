#ifndef header_62F5AAF3E3DD
#define header_62F5AAF3E3DD

#include <stdio.h>
#include <xmmintrin.h>

namespace Math
{
    template <typename T, typename I, std::size_t Alignment>
    class Matrix;

    template <typename T, typename I, std::size_t Alignment>
    Matrix<T, I, Alignment> makeScalar();

    template <typename T, typename I, std::size_t Alignment>
    Matrix<T, I, Alignment> makeScalar(T value);

    template <typename T, typename I, std::size_t Alignment>
    Matrix<T, I, Alignment> makeVector(std::vector<T, Rt::AlignedAllocator<T, Alignment>> data);

    template <typename T, typename I, std::size_t Alignment>
    Matrix<T, I, Alignment> makeVector(const T* data, I size);

    template <typename T, typename I, std::size_t Alignment>
    Matrix<T, I, Alignment> makeVector(T x, T y);

    template <typename T, typename I, std::size_t Alignment>
    Matrix<T, I, Alignment> makeVector(T x, T y, T z);

    template <typename T, typename I, std::size_t Alignment>
    Matrix<T, I, Alignment> makeVector(T x, T y, T z, T w);

//    template <typename T, typename I, std::size_t Alignment>
//    Matrix<T, I, Alignment> makeMatrix(I size = 4, bool loadIdentity = true);

    template <typename T, typename I, std::size_t Alignment>
    Matrix<T, I, Alignment> makeMatrix(T size, const std::vector<T, Rt::AlignedAllocator<T, Alignment>>& data,
                                       Rt::Option<std::vector<Rt::u1>> layout = Rt::Option<std::vector<Rt::u1>>());

    template <typename T = float, typename I = Rt::u1, std::size_t Alignment = 32>
    class Matrix
    {
    public:
        class NonConformable : public std::exception {
            virtual const char* what() const throw() {
                return "non comformable multidimensional matrices";
            }
        };

        using Ref = typename std::vector<T, Rt::AlignedAllocator<T, Alignment>>::reference;
        using ConstRef = typename std::vector<T, Rt::AlignedAllocator<T, Alignment>>::const_reference;

    protected:
        std::vector<I> dims;
        std::vector<T, Rt::AlignedAllocator<T, Alignment>> data;
        Rt::u1 dim, actualDim;
        bool areAllDimensionsEqual;
        Rt::u4 numberOfElements;

        // Describes the way N-dimensional matrix is mapped into 1-dimensional linear address space
        struct Layout
        {
        public:
            std::vector<Rt::u1> permutation; // The order of dimensions in which the data is layd out.
                                             // Let's assume that N-dimensional matrix is the vector of (N-1)-dimensional matrices.
                                             // The order in which two elements of this vector are layd out in memory is the same as the order of these elements in a vector.
                                             // This field defines the order in which N-dimensional matrix is recursively splitted into vectors to form a tree structure (branching).

            std::vector<Rt::u4> partialProducts; // partial products used in computation of an offset of an element based on its indices

        public:
            void init(const std::vector<Rt::u1>& permutation, const std::vector<I>& dims) {
                this->permutation = permutation;
                calcPartialProducts(dims);
            }

            void calcPartialProducts(const std::vector<I>& dims) {
                auto dim = dims.size();

                partialProducts.resize(std::max<Rt::u1>(dim, 1));
                if (dim > 0) {
                    std::vector<I> rearrangedDims(dim);
                    std::vector<Rt::u4> partialProductsTmp(std::max<Rt::u1>(dim, 1));

                    Rt::rearrange(permutation.begin(), permutation.end(), dims.begin(), rearrangedDims.begin());

                    partialProductsTmp[0] = 1;
                    std::partial_sum(rearrangedDims.rbegin(), --rearrangedDims.rend(), ++partialProductsTmp.begin(), std::multiplies<Rt::u4>());
                    std::reverse(partialProductsTmp.begin(), partialProductsTmp.end());

                    Rt::rearrange(permutation.begin(), permutation.end(), partialProductsTmp.begin(), partialProducts.begin());
                }
                else
                    partialProducts[0] = 1;
            }

            static std::vector<Rt::u1> createDefaultPermutation(Rt::u1 dim) {
                std::vector<Rt::u1> result(dim);
                if (dim > 0) {
                    Rt::u1 i = 0;
                    std::generate_n(result.begin(), dim, [&i]() -> Rt::u1 { return i++; });
                }
                return result;
            }

            static Rt::u4 getIndex(const std::vector<I>& indices, const std::vector<Rt::u4>& partialProducts) {
                Rt::u4 retval = 0;

                for (Rt::u1 i = 0; i < indices.size(); i++)
                    retval += indices[i] * partialProducts[i];

                return retval;
            }

            static Rt::u4 getIndex(I i, const std::vector<Rt::u4>& partialProducts, Rt::u1 dim = 0) {
                return i * partialProducts[dim];
            }

            static Rt::u4 getIndex2(I i, I j, const std::vector<Rt::u4>& partialProducts, Rt::u1 dim0 = 0, Rt::u1 dim1 = 1) {
                return i * partialProducts[dim0] + j * partialProducts[dim1];
            }

            static Rt::u4 getIndex3(I i, I j, I k, const std::vector<Rt::u4>& partialProducts, Rt::u1 dim0 = 0, Rt::u1 dim1 = 1, Rt::u1 dim2 = 2) {
                return i * partialProducts[dim0] + j * partialProducts[dim1] + k * partialProducts[dim2];
            }

            Rt::u4 getIndex(const std::vector<I>& indices) const {
                return getIndex(indices, partialProducts);
            }

            Rt::u4 getIndex(I i, Rt::u1 dim = 0) const {
                return getIndex(i, partialProducts, dim);
            }

            Rt::u4 getIndex2(I i, I j, Rt::u1 dim0 = 0, Rt::u1 dim1 = 1) const {
                return getIndex2(i, j, partialProducts, dim0, dim1);
            }

            Rt::u4 getIndex3(I i, I j, I k, Rt::u1 dim0 = 0, Rt::u1 dim1 = 1, Rt::u1 dim2 = 2) const {
                return getIndex3(i, j, k, partialProducts, dim0, dim1, dim2);
            }
        }
        layout;

    private:
        static Rt::u4 calcNumberOfElements(const std::vector<I>& dims) {
            if (dims.size() > 0)
                return std::accumulate(dims.begin(), dims.end(), 1, [](Rt::u4 acc, I x) -> Rt::u4 {
                    return acc * x;
                });

            return 1;
        }

        static Rt::u1 calcActualDimensionality(const std::vector<I>& dims) {
            return Rt::u1(std::count_if(dims.begin(), dims.end(), [](I x) -> bool {
                return x > 1;
            }));
        }

        void update() {
            dim = dims.size();
            actualDim = calcActualDimensionality(dims);
            numberOfElements = calcNumberOfElements(dims);
            areAllDimensionsEqual = (dim <= 1 ? true : std::find_if(dims.begin()++, dims.end(), [&](I x) -> bool {
                return x != dims[0];
            }) == dims.end());
        }

        void resize() {
            data.resize(numberOfElements);
        }

    public:
        Matrix() {}

        Matrix(I size) : Matrix(size, size)
        {}

        Matrix(I size0, I size1) {
            initMatrix(size0, size1);
            update();
            resize();
        }

        Matrix(const std::vector<I>& dims,
               const std::vector<T, Rt::AlignedAllocator<T, Alignment>>& data,
               Rt::Option<std::vector<Rt::u1>> layout = Rt::Option<std::vector<Rt::u1>>())
        {
            init(dims, layout);
            this->data = data;
        }

        virtual ~Matrix() {}

        void init(const std::vector<I>& dims, Rt::Option<std::vector<Rt::u1>> layout = Rt::Option<std::vector<Rt::u1>>())
        {
            this->dims = dims;
            this->layout.init(layout.defined ? layout.get() : Layout::createDefaultPermutation(dims.size()), dims);
            update();
        }

        void initScalar() {
            update();
            resize();
        }

        void initVector(I size, Rt::Option<std::vector<Rt::u1>> layout = Rt::Option<std::vector<Rt::u1>>()) {
            std::vector<I> dims;
            dims.push_back(size);
            this->init(dims, layout);
        }

        void initMatrix(I size0, I size1, Rt::Option<std::vector<Rt::u1>> layout = Rt::Option<std::vector<Rt::u1>>()) {
            std::vector<I> dims;
            dims.push_back(size0);
            dims.push_back(size1);
            this->init(dims, layout);
        }

        void initSquareMatrix(I size, Rt::Option<std::vector<Rt::u1>> layout = Rt::Option<std::vector<Rt::u1>>()) {
            this->initMatrix(size, size, layout);
        }

        bool empty() const {
            return data.empty();
        }

        bool operator==(const Matrix<T, I>& that) {
            return (dims == that.dims && data == that.data);
        }

        static bool areConformableForElementToElementOperations(const Matrix<T, I>& a, const Matrix<T, I>& b) {
            return simplify(a.dims) == simplify(b.dims);
        }

        void elementToElementOperation(const Matrix<T, I>& that, const std::function<void (T&, T)>& op) {
            switch (dim) {
                case 0:
                    op(data[0], that.data[0]);
                break;

                case 1:
                    for (auto i = 0; i < dims[0]; i++)
                        op(data[i], that.data[i]);
                break;

                case 2:
                    for (auto i = 0; i < dims[0]; i++)
                        for (auto j = 0; j < dims[1]; j++)
                            op(data[layout.getIndex2(i, j)], that.data[that.layout.getIndex2(i, j)]);
                break;

                case 3:
                    for (auto i = 0; i < dims[0]; i++)
                        for (auto j = 0; j < dims[1]; j++)
                            for (auto k = 0; k < dims[2]; k++)
                                op(data[layout.getIndex3(i, j, k)], that.data[that.layout.getIndex3(i, j, k)]);
                break;

                default: {
                    std::vector<I> indices(dims.size(), 0);
                    for (Rt::u4 i = 0; i < numberOfElements; i++) {
                        op(data[layout.getIndex(indices)], that.data[that.layout.getIndex(indices)]);
                        for (Rt::u1 j = 0; j < dims.size(); j++) {
                            indices[j]++;
                            if (indices[j] < dims[j]) break;
                            else indices[j] = 0;
                        }
                    }
                }
                break;
            }
        }

        void iterate(std::function<void (T&)> op) {
            switch (dim) {
                case 0:
                    op(data[0]);
                break;

                case 1:
                    for (auto i = 0; i < dims[0]; i++)
                        op(data[i]);
                break;

                case 2:
                    for (auto i = 0; i < dims[0]; i++)
                        for (auto j = 0; j < dims[1]; j++)
                            op(data[layout.getIndex2(i, j)]);
                break;

                case 3:
                    for (auto i = 0; i < dims[0]; i++)
                        for (auto j = 0; j < dims[1]; j++)
                            for (auto k = 0; k < dims[2]; k++)
                                op(data[layout.getIndex3(i, j, k)]);
                break;

                default: {
                    std::vector<I> indices(dim, 0);
                    for (Rt::u4 i = 0; i < numberOfElements; i++) {
                        op(data[layout.getIndex(indices)]);
                        for (Rt::u1 j = 0; j < dims.size(); j++) {
                            indices[j]++;
                            if (indices[j] < dims[j]) break;
                            else indices[j] = 0;
                        }
                    }
                }
                break;
            }
        }

        static void iterate(const std::vector<I>& startIndices, const std::vector<I>& sizes, const std::function<void(const std::vector<I>&)>& op) {
            auto indices = startIndices;
            auto numberOfElementsToIterate = std::accumulate(sizes.begin(), sizes.end(), Rt::u4(1), std::multiplies<Rt::u4>());
            auto dim = indices.size();
            for (Rt::u4 i = 0; i < numberOfElementsToIterate; i++) {
                op(indices);
                for (Rt::u1 j = 0; j < dim; j++) {
                    indices[j]++;
                    if (indices[j] < startIndices[j] + sizes[j]) break;
                    else indices[j] = startIndices[j];
                }
            }
        }

        void iterateIndices(const std::function<void(const std::vector<I>&)>& op) {
            std::vector<I> indices(dim, 0);
            for (Rt::u4 i = 0; i < numberOfElements; i++) {
                op(indices);
                for (Rt::u1 j = 0; j < dim; j++) {
                    indices[j]++;
                    if (indices[j] < dims[j]) break;
                    else indices[j] = 0;
                }
            }
        }

        Matrix<T, I>& operator+=(const Matrix<T, I>& that) {
            if (areConformableForElementToElementOperations(*this, that))
                elementToElementOperation(that, [](T& a, T b) {
                    a += b;
                });
            else
                throw new NonConformable();

            return *this;
        }

        Matrix<T, I> operator+(const Matrix<T, I>& that) {
            auto result = *this;
            result += that;
            return result;
        }

        Matrix<T, I>& operator-=(const Matrix<T, I>& that) {
            if (areConformableForElementToElementOperations(*this, that))
                elementToElementOperation(that, [](T& a, T b) { a -= b; });
            else
                throw new NonConformable();

            return *this;
        }

        Matrix<T, I> operator-(const Matrix<T, I>& that) {
            auto result = *this;
            result -= that;
            return result;
        }

        Matrix<T, I>& operator*=(T coeff) {
            iterate([=](T& a) { a *= coeff; });
            return *this;
        }

        Matrix<T, I>& multiplyByScalar(T a) {
            *this *= a;
            return *this;
        }

        Matrix<T, I>& hadamardProduct(const Matrix<T, I>& that) {
            elementToElementOperation(that, [](T& a, T b) { a *= b; });
            return *this;
        }

        static bool areConformableForScalarByScalarMultiplication(const Matrix<T, I>& a, const Matrix<T, I>& b) {
            return a.actualDim == 0 && b.actualDim == 0;
        }

        void scalarByScalarMultiplication(const Matrix<T, I>& that) {
            data[0] *= that.data[0];
        }

        static bool areConformableForDotProduct(const Matrix<T, I>& a, const Matrix<T, I>& b) {
            return a.actualDim == 1 && b.actualDim == 1 && a.numberOfElements == b.numberOfElements;
        }

        void dotProduct(const Matrix<T, I>& that) { 
            T product = 0;
            for (I i = 0; i < numberOfElements; i++)
                product += that.data[i] * data[i];

            dims.clear();
            layout.permutation.clear();
            layout.calcPartialProducts(dims);
            update();
            resize();

            data[0] = product;
        }

        static std::vector<I> expandIntoHigherDimensions(const std::vector<I>& dims, Rt::u1 nDims) {
            auto result = dims;
            for (auto i = 0; i < nDims; i++) result.push_back(1);
            return result;
        }

        static bool areConformableForMultiplication(const Matrix<T, I>& a, const Matrix<T, I>& b, Rt::u1 dim0 = 0, Rt::u2 dim1 = 1) {
            auto maxDim = std::max(a.dim, b.dim);

            auto aDimsExpanded = maxDim - a.dim == 0 ? a.dims : expandIntoHigherDimensions(a.dims, maxDim - a.dim);
            auto bDimsExpanded = maxDim - b.dim == 0 ? b.dims : expandIntoHigherDimensions(b.dims, maxDim - b.dim);

            if (aDimsExpanded[dim1] == bDimsExpanded[dim0])
            {
                bool equal = true;
                for (auto i = 0; i < maxDim; i++)
                    if (i != dim0 && i != dim1 && a.dims[i] != b.dims[i]) {
                        equal = false;
                        break;
                    }

                return equal;
            }

            return false;
        }

        static Rt::u1 getSimplifiedDim(const std::vector<I>& dims) {
            auto result = Rt::u1(dims.size());
            if (result)
                for (Rt::s1 i = dims.size() - 1; i >= 0 && dims[i] == 1; i--)
                    result--;

            return result;
        }

        static std::vector<I> simplify(const std::vector<I>& dims) {
            auto result = dims;
            auto simplifiedSize = getSimplifiedDim(dims);
            if (simplifiedSize < dims.size()) result.resize(simplifiedSize);
            return result;
        }

        bool simplify() {
            auto simplifiedSize = getSimplifiedDim(dims);
            if (simplifiedSize < dims.size()) {
                dims.resize(simplifiedSize);
                layout.permutation.resize(simplifiedSize);
                layout.calcPartialProducts(dims);
                return true;
            }
            return false;
        }

        void multiply(const Matrix<T, I>& that, Rt::u1 dim0 = 0, Rt::u1 dim1 = 1, bool simplifyResult = true) {
            switch (actualDim)
            {
                case 1: {
                    switch (that.actualDim) {
                        case 1: {
                            if (dims[dim1] == 1) {
                                T x = 0;
                                for (I i = 0; i < dims[dim0]; i++)
                                    x += that.data[i] * data[i];

                                dims[dim0] = 1;
                                update();
                                resize();

                                data[0] = x;
                            }
                            else {
                                auto savedData = data;
                                    
                                auto maxDim = std::max(dim0, dim1);
                                if (dim <= maxDim) grow(maxDim + 1, Rt::Option<std::function<void()>>([&]() {
                                    dims[dim0] = that.dims[dim0];
                                }));
                                    
                                for (I i = 0; i < that.dims[dim0]; i++)
                                    for (I j = 0; j < dims[dim1]; j++)
                                        data[layout.getIndex2(i, j, dim0, dim1)] = savedData[i] * that.data[j];
                            }
                        }
                        break;

                        case 2:
                            for (I i = 0; i < that.dims[dim0]; i++) {
                                T x = 0;
                                for (I k = 0; k < dims[dim0]; k++)
                                    x += that.data[that.layout.getIndex2(i, k, dim0, dim1)] * data[k];
                                data[i] = x;
                            }
                        break;
                    }
                }
                break;

                case 2: {
                    switch (that.actualDim) {
                        case 1: {
                            struct {
                                std::vector<T, Rt::AlignedAllocator<T, Alignment>> data;
                                std::vector<Rt::u4> partialProducts;
                            }
                            saved;

                            saved.data = data;
                            saved.partialProducts = layout.partialProducts;

                            dims[dim0] = 1;
                            update();
                            resize();

                            for (I i = 0; i < dims[dim1]; i++) {
                                T x = 0;
                                for (I k = 0; k < dims[dim0]; k++)
                                    x += that.data[k] * saved.data[Layout::getIndex2(k, i, saved.partialProducts, dim0, dim1)];
                                data[i] = x;
                            }
                        }
                        break;

                        case 2: {
                            struct {
                                std::vector<T, Rt::AlignedAllocator<T, Alignment>> data;
                                std::vector<Rt::u4> partialProducts;
                            }
                            saved;

                            saved.data = data;
                            saved.partialProducts = layout.partialProducts;

                            auto maxDim = std::max(dim0, dim1);
                            if (dim <= maxDim) grow(maxDim + 1, Rt::Option<std::function<void()>>([&]() { 
                                dims[dim0] = that.dims[dim0];
                            }));

                            for (I i = 0; i < that.dims[dim0]; i++) {
                                for (I j = 0; j < dims[dim1]; j++) {
                                    T x = 0;
                                    for (I k = 0; k < dims[dim0]; k++)
                                        x += that.data[that.layout.getIndex2(i, k, dim0, dim1)] * saved.data[Layout::getIndex2(k, j, saved.partialProducts, dim0, dim1)];
                                    data[layout.getIndex2(i, j, dim0, dim1)] = x;
                                }
                            }
                        }
                        break;

                        default: break;
                    }
                }
                break;

                default: break;
            }

            if (simplifyResult) simplify();
        }

        Matrix<T, I>& operator*=(const Matrix<T, I>& that) {
            if (areConformableForScalarByScalarMultiplication(*this, that))
                scalarByScalarMultiplication(that);
            else {
                if (areConformableForDotProduct(*this, that))
                    dotProduct(that);
                else {
                    if (areConformableForMultiplication(*this, that))
                        multiply(that, 0, 1);
                    else
                        throw new NonConformable();
                }
            }

            return *this;
        }

        Matrix<T, I>& crop(const std::vector<I>& startIndices, const std::vector<I>& sizes) {
            struct {
                std::vector<T, Rt::AlignedAllocator<T, Alignment>> data;
                std::vector<Rt::u4> partialProducts;
            }
            saved;

            saved.data = std::move(data);
            saved.partialProducts = std::move(layout.partialProducts);

            dims = sizes;
            update();
            resize();
            layout.calcPartialProducts(dims);

            iterate(startIndices, sizes, [&](const std::vector<I>& indices) {
                std::vector<I> localIndices(dim);

                for (auto i = 0; i < dim; i++)
                    localIndices[i] = indices[i] - startIndices[i];

                set(localIndices, saved.data[Layout::getIndex(indices, saved.partialProducts)]);
            });

            return *this;
        }

        Matrix<T, I>& crop(I size, I offset = 0) {
            std::vector<I> startIndices(dim, offset), sizes(dim, size);
            return crop(startIndices, sizes);
        }

        Matrix<T, I> getSubMatrix(const std::vector<I>& offset, const std::vector<I>& size) const {
            auto copy = *this;
            return copy.crop(offset, size);
        }

        Matrix<T, I> getSubMatrix(I size, I offset = 0) const {
            auto copy = *this;
            return copy.crop(size, offset);
        }

        Ref operator*() {
            return data[0];
        }

        ConstRef operator*() const {
            return data[0];
        }

        Ref operator[](I i) {
            return data[i];
        }

        ConstRef operator[](I i) const {
            return data[i];
        }

        Ref operator[](const std::vector<I>& indices) {
            return data[layout.getIndex(indices)];
        }

        ConstRef operator[](const std::vector<I>& indices) const {
            return data[layout.getIndex(indices)];
        }

        Ref get() {
            return data[0];
        }

        ConstRef get() const {
            return data[0];
        }

        Ref get(I i) {
            return data[i];
        }

        ConstRef get(I i) const {
            return data[i];
        }

        Ref get(I i, I j) {
            return data[layout.getIndex2(i, j)];
        }

        ConstRef get(I i, I j) const {
            return data[layout.getIndex2(i, j)];
        }

        Ref get(I i, I j, I k) {
            return data[layout.getIndex3(i, j, k)];
        }

        ConstRef get(I i, I j, I k) const {
            return data[layout.getIndex3(i, j, k)];
        }

        Ref get(const std::vector<I>& indices) {
            return data[layout.getIndex(indices)];
        }

        ConstRef get(const std::vector<I>& indices) const {
            return data[layout.getIndex(indices)];
        }

        virtual void set(T value) {
            data[0] = value;
        }

        virtual void set(I i, T value) {
            data[i] = value;
        }

        virtual void set(I i, I j, T value) {
            data[layout.getIndex2(i, j)] = value;
        }

        virtual void set(I i, I j, I k, T value) {
            data[layout.getIndex3(i, j, k)] = value;
        }

        virtual void set(const std::vector<I>& indices, T value) {
            data[layout.getIndex(indices)] = value;
        }

        const std::vector<T, Rt::AlignedAllocator<T, Alignment>>& getData() const {
            return data;
        }

        std::vector<T, Rt::AlignedAllocator<T, Alignment>>& getData() {
            return data;
        }

        Rt::Option<T> calcDet() const {
            if (areAllDimensionsEqual && dim == 2 && actualDim == 2) {
                switch (dims[0]) {
                    case 1: return Rt::Option<T>(data[0]);

                    case 2: return Rt::Option<T>(get(0, 0) * get(1, 1) - get(0, 1) * get(1, 0));

                    case 3: return Rt::Option<T>(get(0, 0) * (get(1, 1) * get(2, 2) - get(1, 2) * get(2, 1)) +
                                                 get(0, 1) * (get(1, 2) * get(2, 0) - get(1, 0) * get(2, 2)) +
                                                 get(0, 2) * (get(1, 0) * get(2, 1) - get(1, 1) * get(2, 0)));

                    case 4: return Rt::Option<T>(1);
                }
            }
            return Rt::Option<T>();
        }

        static Rt::Option<Matrix<T, I>> getInversed(const Matrix<T, I, Alignment>& m, Rt::u1 dim0 = 0, Rt::u1 dim1 = 1) {
            if (m.actualDim == 0)
                return Rt::Option<Matrix<T, I>>(makeScalar<T, I, Alignment>(T(1) / m.data[0]));

            if (m.actualDim == 2 && m.dims[dim0] == m.dims[dim1]) {
                switch (m.dims[0])
                {
                    case 1: {
                        Matrix<T, I> result(m);
                        result.data[0] = T(1) / m.data[0];
                        return Rt::Option<Matrix<T, I>>(result);
                    }
                    break;

                    case 2: {
                        auto det = m.calcDet();
                        if (det.defined && std::abs(det.get()) > std::numeric_limits<T>::epsilon()) {
                            Matrix<T, I> result(m);
                            T inv_det = T(1) / det.get();

                            result.set(0, 0, +inv_det * m.get(1, 1));
                            result.set(0, 1, -inv_det * m.get(0, 1));
                            result.set(1, 0, -inv_det * m.get(1, 0));
                            result.set(1, 1, +inv_det * m.get(0, 0));

                            return Rt::Option<Matrix<T, I>>(result);
                        }
                    }
                    break;

                    case 3: {
                        auto det = m.calcDet();

                        if (det.defined && std::abs(det.get()) > std::numeric_limits<T>::epsilon())
                        {
                            Matrix<T, I> result(m);
                            T inv_det = T(1) / det.get();

                            result.set(0, 0, +inv_det * (m.get(2, 2) * m.get(1, 1) - m.get(2, 1) * m.get(1, 2)));
                            result.set(0, 1, -inv_det * (m.get(2, 2) * m.get(0, 1) - m.get(2, 1) * m.get(0, 2)));
                            result.set(0, 2, +inv_det * (m.get(1, 2) * m.get(0, 1) - m.get(1, 1) * m.get(0, 2)));

                            result.set(1, 0, -inv_det * (m.get(2, 2) * m.get(1, 0) - m.get(2, 0) * m.get(1, 2)));
                            result.set(1, 1, +inv_det * (m.get(2, 2) * m.get(0, 0) - m.get(2, 0) * m.get(0, 2)));
                            result.set(1, 2, -inv_det * (m.get(1, 2) * m.get(0, 0) - m.get(1, 0) * m.get(0, 2)));

                            result.set(2, 0, +inv_det * (m.get(2, 1) * m.get(1, 0) - m.get(2, 0) * m.get(1, 1)));
                            result.set(2, 1, -inv_det * (m.get(2, 1) * m.get(0, 0) - m.get(2, 0) * m.get(0, 1)));
                            result.set(2, 2, +inv_det * (m.get(1, 1) * m.get(0, 0) - m.get(1, 0) * m.get(0, 1)));

                            return Rt::Option<Matrix<T, I>>(result);
                        }
                    }
                    break;

                    case 4: {
                        #pragma warning(push)
                        #pragma warning( disable : 4700 )

                        __m128 tmp = _mm_setr_ps(0.0f, 0.0f, 0.0f, 0.0f);
                        tmp = _mm_loadh_pi(_mm_loadl_pi(tmp, (__m64*)m.data.data()), (__m64*)(m.data.data() + 4));

                        __m128 row1 = _mm_setr_ps(0.0f, 0.0f, 0.0f, 0.0f);
                        row1 = _mm_loadh_pi(_mm_loadl_pi(row1, (__m64*)(m.data.data() + 8)), (__m64*)(m.data.data() + 12));

                        __m128 row0 = _mm_setr_ps(0.0f, 0.0f, 0.0f, 0.0f);
                        row0 = _mm_shuffle_ps(tmp, row1, 0x88);
                        row1 = _mm_shuffle_ps(row1, tmp, 0xDD);
                        tmp = _mm_loadh_pi(_mm_loadl_pi(tmp, (__m64*)(m.data.data() + 2)), (__m64*)(m.data.data() + 6));

                        __m128 row3 = _mm_setr_ps(0.0f, 0.0f, 0.0f, 0.0f);
                        row3 = _mm_loadh_pi(_mm_loadl_pi(row3, (__m64*)(m.data.data() + 10)), (__m64*)(m.data.data() + 14));

                        __m128 row2 = _mm_setr_ps(0.0f, 0.0f, 0.0f, 0.0f);
                        row2 = _mm_shuffle_ps(tmp, row3, 0x88);
                        row3 = _mm_shuffle_ps(row3, tmp, 0xDD);
                        #pragma warning(pop)

                        tmp = _mm_mul_ps(row2, row3);
                        tmp = _mm_shuffle_ps(tmp, tmp, 0xb1);

                        __m128 minor0 = _mm_setr_ps(0.0f, 0.0f, 0.0f, 0.0f);
                        minor0 = _mm_mul_ps(row1, tmp);

                        __m128 minor1 = _mm_setr_ps(0.0f, 0.0f, 0.0f, 0.0f);
                        minor1 = _mm_mul_ps(row0, tmp);
                        tmp = _mm_shuffle_ps(tmp, tmp, 0x4e);
                        minor0 = _mm_sub_ps(_mm_mul_ps(row1, tmp), minor0);
                        minor1 = _mm_sub_ps(_mm_mul_ps(row0, tmp), minor1);
                        minor1 = _mm_shuffle_ps(minor1, minor1, 0x4e);

                        tmp = _mm_mul_ps(row1, row2);
                        tmp = _mm_shuffle_ps(tmp, tmp, 0xB1);
                        minor0 = _mm_add_ps(_mm_mul_ps(row3, tmp), minor0);

                        __m128 minor3 = _mm_setr_ps(0.0f, 0.0f, 0.0f, 0.0f);
                        minor3 = _mm_mul_ps(row0, tmp);
                        tmp = _mm_shuffle_ps(tmp, tmp, 0x4E);
                        minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row3, tmp));
                        minor3 = _mm_sub_ps(_mm_mul_ps(row0, tmp), minor3);
                        minor3 = _mm_shuffle_ps(minor3, minor3, 0x4E);

                        tmp = _mm_mul_ps(_mm_shuffle_ps(row1, row1, 0x4E), row3);
                        tmp = _mm_shuffle_ps(tmp, tmp, 0xB1);
                        row2 = _mm_shuffle_ps(row2, row2, 0x4E);
                        minor0 = _mm_add_ps(_mm_mul_ps(row2, tmp), minor0);

                        __m128 minor2 = _mm_setr_ps(0.0f, 0.0f, 0.0f, 0.0f);
                        minor2 = _mm_mul_ps(row0, tmp);
                        tmp = _mm_shuffle_ps(tmp, tmp, 0x4E);
                        minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row2, tmp));
                        minor2 = _mm_sub_ps(_mm_mul_ps(row0, tmp), minor2);
                        minor2 = _mm_shuffle_ps(minor2, minor2, 0x4E);

                        tmp = _mm_mul_ps(row0, row1);
                        tmp = _mm_shuffle_ps(tmp, tmp, 0xB1);
                        minor2 = _mm_add_ps(_mm_mul_ps(row3, tmp), minor2);
                        minor3 = _mm_sub_ps(_mm_mul_ps(row2, tmp), minor3);
                        tmp = _mm_shuffle_ps(tmp, tmp, 0x4E);
                        minor2 = _mm_sub_ps(_mm_mul_ps(row3, tmp), minor2);
                        minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row2, tmp));

                        tmp = _mm_mul_ps(row0, row3);
                        tmp = _mm_shuffle_ps(tmp, tmp, 0xB1);
                        minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row2, tmp));
                        minor2 = _mm_add_ps(_mm_mul_ps(row1, tmp), minor2);
                        tmp = _mm_shuffle_ps(tmp, tmp, 0x4E);
                        minor1 = _mm_add_ps(_mm_mul_ps(row2, tmp), minor1);
                        minor2 = _mm_sub_ps(minor2, _mm_mul_ps(row1, tmp));

                        tmp = _mm_mul_ps(row0, row2);
                        tmp = _mm_shuffle_ps(tmp, tmp, 0xB1);
                        minor1 = _mm_add_ps(_mm_mul_ps(row3, tmp), minor1);
                        minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row1, tmp));
                        tmp = _mm_shuffle_ps(tmp, tmp, 0x4E);
                        minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row3, tmp));
                        minor3 = _mm_add_ps(_mm_mul_ps(row1, tmp), minor3);

                        __m128 det = _mm_mul_ps(row0, minor0);
                        det = _mm_add_ps(_mm_shuffle_ps(det, det, 0x4E), det);
                        det = _mm_add_ss(_mm_shuffle_ps(det, det, 0xB1), det);
                        tmp = _mm_rcp_ss(det);

                        det = _mm_sub_ss(_mm_add_ss(tmp, tmp), _mm_mul_ss(det, _mm_mul_ss(tmp, tmp)));
                        det = _mm_shuffle_ps(det, det, 0x00);

                        minor0 = _mm_mul_ps(det, minor0);
                        minor1 = _mm_mul_ps(det, minor1);
                        minor2 = _mm_mul_ps(det, minor2);
                        minor3 = _mm_mul_ps(det, minor3);

                        Matrix<T, I> result(m);

                        if (m.layout.permutation[0] == 0) {
                            _mm_store_ps(result.data.data(), minor0);
                            _mm_store_ps(result.data.data() + 4, minor1);
                            _mm_store_ps(result.data.data() + 8, minor2);
                            _mm_store_ps(result.data.data() + 12, minor3);
                        }
                        else {
                            //alignas(16) float tmp[16];
                        #if defined _MSC_VER
                            __declspec(align(16))
                        #endif
                            T tmp[4 * 4]
                        #if defined __GNUC__ || defined __clang__
                            __attribute__((aligned(16)))
                        #endif
                            ;

                            _mm_store_ps(tmp, minor0);
                            _mm_store_ps(tmp + 4, minor1);
                            _mm_store_ps(tmp + 8, minor2);
                            _mm_store_ps(tmp + 12, minor3);

                            for (auto i = 0; i < 4; i++)
                                for (auto j = 0; j < 4; j++)
                                    result.set(i, j, tmp[4 * i + j]);
                        }

                        return Rt::Option<Matrix<T, I>>(result);
                    }
                }
            }

            return Rt::Option<Matrix<T, I>>();
        }

        bool inverse(Rt::u1 dim0 = 0, Rt::u1 dim1 = 1) {
            auto result = getInversed(*this, dim0, dim1);
            if (result.defined) {
                *this = std::move(result.get());
                return true;
            }
            return false;
        }

        void grow(Rt::u1 dim, Rt::Option<std::function<void()>> f = Rt::Option<std::function<void()>>()) {
            dims.resize(dim, 1);
            for (int i = 0; i < dim - this->dim; i++)
                layout.permutation.push_back(this->dim + i);
            if (f.defined) f.get()();
            update();
            layout.calcPartialProducts(dims);
            data.resize(numberOfElements);
        }

        static Matrix<T, I> getTransposed(const Matrix<T, I, Alignment>& m, Rt::u1 dim0 = 0, Rt::u1 dim1 = 1) {
            auto result(m);
            result.transpose(dim0, dim1);
            return result;
        }

        void transpose(Rt::u1 dim0 = 0, Rt::u1 dim1 = 1) {
            grow(std::max(dim0, dim1) + 1, Rt::Option<std::function<void(void)>>([&]() {
                auto dim0iter = std::find(layout.permutation.begin(), layout.permutation.end(), dim0);
                auto dim1iter = std::find(layout.permutation.begin(), layout.permutation.end(), dim1);
                *dim0iter = dim1;
                *dim1iter = dim0;
            }));
        }

        void loadIdentity() {
            if (areAllDimensionsEqual)
                if (actualDim == 0)
                    data[0] = T(1);
                else {
                    iterateIndices([&](const std::vector<I>& indices) {
                        bool diagonal = std::find_if(indices.begin(), indices.end(), [&](I index) -> bool {
                            return index != indices[0];
                        }) == indices.end();
                        set(indices, diagonal ? T(1) : T(0));
                    });
                }
        }

        void print() {
            printf("dim: %u\nactualDim: %u\n# of elements: %u\nareAllDimensionsEqual: %c\n",
                    dim, actualDim, numberOfElements, areAllDimensionsEqual ? 'y' : 'n');

            printf("dims: ");
            for (auto& x : dims) printf("%u ", x);
            printf("\n");

            printf("layout.permutation: ");
            for (auto& x : layout.permutation) printf("%u ", x);
            printf("\n");

            printf("layout.partialProducts: ");
            for (auto& x : layout.partialProducts) printf("%u ", x);
            printf("\n");

            printf("data:\n");

            std::vector<I> indices(dim, 0);

            for (Rt::u1 k = 0; k < dim - 2; k++) {
                for (Rt::u1 l = 0; l < k; l++) printf("  ");
                printf("%u: 0\n", k);
            }

            for (Rt::u4 i = 0; i < numberOfElements; i++) {
                auto _indices = indices;

                if (dim >= 1)
                    for (Rt::s1 j = dim - 1; j >= 0; j--) {
                        indices[j]++;
                        if (indices[j] < dims[j])
                        {
                            for (Rt::u1 k = j; k < dim - 2; k++) {
                                for (Rt::u1 l = 0; l < k; l++) printf("  ");
                                printf("%u:\n", indices[k]);
                            }
                            break;
                        }
                        else {
                            indices[j] = 0;
                        }
                    }
                printf("%f ", get(_indices));
                if (dim >= 2)
                    if (indices[dim - 2] != _indices[dim - 2]) {
                        printf("\n");
                        for (Rt::u1 l = 0; l < dim - 2; l++) printf("  ");
                    }
            }

            printf("\n");
            /*
            Rt::Option<I> lastIndices;
            iterateIndices([&lastIndices](const std::vector<I>& indices) {
                if (lastIndices.defined) {
                    Rt::u1 firstChangedIndex = 0;
                    for (; firstChangedIndex < indices.size(); firstChangedIndex++)
                        if ()
                    for (auto i = firstChangedIndex; i < indices.size(); i++)
                        if (!indices[i]);
                }
                else {
                    for (auto i = 0; i < indices.size(); i++)
                }
                lastIndices.define(indices);
            })*/
        }
    };

    template <typename T = float, typename I = Rt::u1>
    Matrix<T, I> operator*(const Matrix<T, I>& a, const Matrix<T, I>& b) {
        auto result = b;
        result *= a;
        return result;
    }

    template <typename T = float, typename I = Rt::u1, std::size_t Alignment = 32>
    Matrix<T, I, Alignment> makeScalar() {
        Matrix<T, I> result;
        result.initScalar();
        return result;
    }

    template <typename T = float, typename I = Rt::u1, std::size_t Alignment = 32>
    Matrix<T, I, Alignment> makeScalar(T value) {
        std::vector<I> dimensions;
        std::vector<T, Rt::AlignedAllocator<T, Alignment>> data(1);
        data[0] = value;
        return Matrix<T, I>(dimensions, data);
    }

    template <typename T = float, typename I = Rt::u1, std::size_t Alignment = 32>
    Matrix<T, I, Alignment> makeVector(std::vector<T, Rt::AlignedAllocator<T, Alignment>> data) {
        std::vector<I> dimensions(1);
        dimensions[0] = data.size();
        return Matrix<T, I>(dimensions, data);
    }

    template <typename T = float, typename I = Rt::u1, std::size_t Alignment = 32>
    Matrix<T, I, Alignment> makeVector(const T* data, I size) {
        std::vector<T, Rt::AlignedAllocator<T, Alignment>> dataVector(size);
        std::vector<I> dimensions(1);
        dimensions[0] = size;
        memcpy(dataVector.data(), data, size * sizeof(T));
        return Matrix<T, I, Alignment>(dimensions, std::move(dataVector));
    }

    template <typename T = float, typename I = Rt::u1, std::size_t Alignment = 32>
    Matrix<T, I, Alignment> makeVector(T x, T y) {
        std::vector<I> dimensions(1);
        std::vector<T, Rt::AlignedAllocator<T, Alignment>> data(2);

        dimensions[0] = 2;
        data[0] = x;
        data[1] = y;

        return Matrix<T, I>(dimensions, data);
    }

    template <typename T = float, typename I = Rt::u1, std::size_t Alignment = 32>
    Matrix<T, I, Alignment> makeVector(T x, T y, T z) {
        std::vector<I> dimensions(1);
        std::vector<T> data(3);

        dimensions[0] = 3;
        data[0] = x;
        data[1] = y;
        data[2] = z;

        return Matrix<T, I>(dimensions, data);
    }

    template <typename T = float, typename I = Rt::u1, std::size_t Alignment = 32>
    Matrix<T, I, Alignment> makeVector(T x, T y, T z, T w) {
        std::vector<I> dimensions(1);
        std::vector<T> data(4);

        dimensions[0] = 4;
        data[0] = x;
        data[1] = y;
        data[2] = z;
        data[3] = w;

        return Matrix<T, I>(dimensions, data);
    }

    template <typename T = float, typename I = Rt::u1, std::size_t Alignment = 32>
    Matrix<T, I> makeMatrix(I size = 4, bool loadIdentity = true) {
        Matrix<T, I> result(size);
        if (loadIdentity) result.loadIdentity();
        return result;
    }

    template <typename T = float, typename I = Rt::u1, std::size_t Alignment = 32>
    Matrix<T, I> makeMatrix(T size, const std::vector<T, Rt::AlignedAllocator<T, Alignment>>& data,
                            Rt::Option<std::vector<Rt::u1>> layout = Rt::Option<std::vector<Rt::u1>>())
    {
        std::vector<I> dimensions(2);

        dimensions[0] = size;
        dimensions[1] = size;

        return Matrix<T, I>(dimensions, data, layout);
    }
}

#endif
