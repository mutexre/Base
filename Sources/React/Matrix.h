#ifndef header_0352A5F6AB78
#define header_0352A5F6AB78

namespace React
{
    template <typename T = float, typename I = Rt::u1, std::size_t Alignment = 32>
    using Matrix = Scalar<Math::Matrix<T, I, Alignment>>;

/*    template <typename T = float, typename I = Rt::u1, std::size_t Alignment = 32>
    class Matrix : public Scalar<Math::Matrix<T, I, Alignment>>
    {
    public:
        using Ref = typename Math::Matrix<T, I, Alignment>::Ref;

    public:
        Matrix() {}

        Matrix(Math::Matrix<T, I, Alignment> value) {
            this->value = value;
            this->setValidity(true);
        }

        virtual ~Matrix() {}

        virtual Math::Matrix<T, I, Alignment>& get() {
            return Scalar<Math::Matrix<T, I, Alignment>>::get();
        }

        virtual void set(T value) {
            Scalar<Math::Matrix<T, I, Alignment>>::set(value);
        }

        Ref get(I i) {
            this->evaluateIfNeeded();
            return this->value.get(i);
        }

        const Ref get(I i) const {
            this->evaluateIfNeeded();
            return this->value.get(i);
        }

        Ref get(I i, I j) {
            this->evaluateIfNeeded();
            return this->value.get(this->layout.getIndex2(i, j));
        }

        const Ref get(I i, I j) const {
            this->evaluateIfNeeded();
            return this->value.get(this->layout.getIndex2(i, j));
        }

        Ref get(I i, I j, I k) {
            this->evaluateIfNeeded();
            return this->value.get(this->layout.getIndex3(i, j, k));
        }

        const Ref get(I i, I j, I k) const {
            this->evaluateIfNeeded();
            return this->value.get(this->layout.getIndex3(i, j, k));
        }

        Ref get(const std::vector<I>& indices) {
            this->evaluateIfNeeded();
            return this->value.get(this->layout.getIndex(indices));
        }

        const Ref get(const std::vector<I>& indices) const {
            this->evaluateIfNeeded();
            return this->value.get(this->layout.getIndex(indices));
        }

        void set(I i, T value) {
            this->value.set(i, value);
        }

        void set(I i, I j, T value) {
            this->value.set(i, j, value);
        }

        void set(I i, I j, I k, T value) {
            this->value.set(i, j, k, value);
        }

        void set(const std::vector<I>& indices, T value) {
            this->value.set(indices, value);
        }
    };*/

    template <typename T = float, typename I = Rt::u1, std::size_t Alignment = 32>
    using MatrixPtr = std::shared_ptr<Matrix<T, I, Alignment>>;

    template <typename T = float, typename I = Rt::u1, std::size_t Alignment = 32>
    using MatrixUniquePtr = std::unique_ptr<Matrix<T, I, Alignment>>;

    template <typename T = float, typename I = Rt::u1, std::size_t Alignment = 32>
    using MatrixWeakPtr = std::weak_ptr<Matrix<T, I, Alignment>>;

    template <typename T = float, typename I = Rt::u1, std::size_t Alignment = 32>
    MatrixPtr<T, I, Alignment> makeMatrixScalar() {
        return std::make_shared<Matrix<T, I, Alignment>>(Math::makeScalar<T, I, Alignment>());
    }

    template <typename T = float, typename I = Rt::u1, std::size_t Alignment = 32>
    MatrixPtr<T, I, Alignment> makeMatrixScalar(T value) {
        return std::make_shared<Matrix<T, I, Alignment>>(Math::makeScalar<T, I, Alignment>(value));
    }

    template <typename T = float, typename I = Rt::u1, std::size_t Alignment = 32>
    MatrixPtr<T, I, Alignment> makeVector(const std::vector<T>& data) {
        return std::make_shared<Matrix<T, I, Alignment>>(Math::makeVector<T, I, Alignment>(data));
    }

    template <typename T = float, typename I = Rt::u1, std::size_t Alignment = 32>
    MatrixPtr<T, I, Alignment> makeVector(const T* data, std::size_t size) {
        return std::make_shared<Matrix<T, I, Alignment>>(Math::makeVector<T, I, Alignment>(data, size));
    }

    template <typename T = float, typename I = Rt::u1, std::size_t Alignment = 32>
    MatrixPtr<T, I, Alignment> makeVector(T x, T y) {
        return std::make_shared<Matrix<T, I, Alignment>>(Math::makeVector<T, I, Alignment>(x, y));
    }

    template <typename T = float, typename I = Rt::u1, std::size_t Alignment = 32>
    MatrixPtr<T, I, Alignment> makeVector(T x, T y, T z) {
        return std::make_shared<Matrix<T, I, Alignment>>(Math::makeVector<T, I, Alignment>(x, y, z));
    }

    template <typename T = float, typename I = Rt::u1, std::size_t Alignment = 32>
    MatrixPtr<T, I, Alignment> makeVector(T x, T y, T z, T w) {
        return std::make_shared<Matrix<T, I, Alignment>>(Math::makeVector<T, I, Alignment>(x, y, z, w));
    }

    template <typename T = float, typename I = Rt::u1, std::size_t Alignment = 32>
    MatrixPtr<T, I, Alignment> makeMatrix(Rt::u1 size = 4, bool loadIdentity = true) {
        return std::make_shared<Matrix<T, I, Alignment>>(Math::makeMatrix<T, I, Alignment>(size, loadIdentity));
    }

    template <typename T = float, typename I = Rt::u1, std::size_t Alignment = 32>
    MatrixPtr<T, I, Alignment> makeMatrix(T size, const std::vector<T, Rt::AlignedAllocator<T, Alignment>>& data,
                                         Rt::Option<std::vector<Rt::u1>> layout = Rt::Option<std::vector<Rt::u1>>())
    {
        return std::make_shared<Matrix<T, I, Alignment>>(Math::makeMatrix<T, I, Alignment>(size, data, layout));
    }
}

#endif
