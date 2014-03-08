#ifndef header_48D2A443AE51
#define header_48D2A443AE51

#include <stdarg.h>

namespace Rt
{
    namespace Type
    {
        template <typename T, typename I> class Atom;
        template <typename T, typename I> class Struct;
        template <typename T, typename I> class Matrix;

        template <typename T = u4, typename I = u4>
        class Trait : public Object
        {
        public:
            typedef T SizeType;
            typedef I IndexType;

        private:
            Option<std::string> name;
            Option<T> rounding;
            Option<Trait*> parent;
            void* userData;

            T round(T x, T rounding);

        protected:
            enum class Kind {
                Atom, Struct, Matrix
            }
            kind;

            void copyAttributesTo(Trait<T, I>* that);

        public:
            virtual ~Trait();

            T getRoundedSize();

            Option<std::string> getName() const;
            void setName(Option<std::string> name);

            Option<T> getRounding() const;
            void setRounding(Option<T> rounding);
            virtual void setRoundingRecursively(Option<T> rounding);

            Option<Trait*> getParent() const;
            void setParent(Option<Trait*> parent);

            Kind getKind() const;

            void* getUserData() const;
            void setUserData(void* data);

            bool execAppropriateFunc(std::function<bool (Atom<T, I>*)> atomOp,
                                     std::function<bool (Struct<T, I>*)> structOp,
                                     std::function<bool (Matrix<T, I>*)> matrixOp);

            void traverseAncestors(std::function<bool (Trait*)> f);

            void traverseAncestors(std::function<bool (Struct<T, I>*)> structOp,
                                   std::function<bool (Matrix<T, I>*)> matrixOp);

            virtual void traverseTree(std::function<void (Trait*)> f);

//            void releaseRecursively();
            void updateRecursively();

            std::list<Trait*> getAncestors();

            I getNumberOfOccurences();

            std::list<I> getBranchingFactors();

            T offsetOfOccurenceWithIndex(I index);
            Option<std::pair<T, T>> getStrideAndOffset();

            Matrix<T, I>* operator*(I n);

            virtual T getSize() = 0;
            virtual Trait<T, I>* at(const char* pathComponent) = 0;
            virtual std::string toString() const = 0;
            virtual Trait<T, I>* copyRecursively() = 0;
        };
/*
        template <typename T, typename I, class Allocator>
        class Instance : public Rt::Object
        {
        private:
            Trait<T, I>* type = 0;
            Memory::Allocation<Allocator> allocation;

        public:
            Instance() {}

            Instance(Trait<T, I>* type, Allocator* allocator) {
                init(type, allocator);
            }

            void init(Trait<T, I>* type, Allocator* allocator) {
                this->type = type;
                this->allocation.allocator = allocator;
                instantiate();
            }

            void instantiate() {
                allocation.instantiate(type->getRoundedSize());
            }

            const Memory::Allocation<Allocator>& getAllocation() {
                return allocation;
            }
        };
*/
    }
}

#include <Runtime/Type/TraitDefinition.h>

#endif
