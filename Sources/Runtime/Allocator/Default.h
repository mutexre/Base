#ifndef header_BBA5F55DA35E
#define header_BBA5F55DA35E

#include <map>

namespace Rt
{
    namespace Allocator
    {
        template <typename Size, class IdAlloc>
        class Default
        {
        public:
            typedef Size Offset;
            typedef typename IdAlloc::IdType Id;

            struct Range
            {
                Offset offset;
                Size size;

                Range() {}

                Range(Offset offset, Size size)
                {
                    this->offset = offset;
                    this->size = size;
                }

                Range(std::pair<Offset, Size> pair)
                {
                    this->offset = pair.first;
                    this->size = pair.second;
                }
            };

            struct NeighborRange : public Range
            {
                unsigned short int exists;

                NeighborRange() : exists(0) {}

                void operator=(const Range& that)
                {
                    this->offset = that.offset;
                    this->size = that.size;
                    exists = 1;
                }
            };

        protected:
            std::map<Offset, Size> all;
            std::map<Offset, Size> unused;
            std::map<Id, Range> allocated;
//            Tree::RB::Default<Offset, Size> unused;

            IdAlloc idAllocator;
            Size size, allocatedSize;

            virtual Id allocFirstFit(Size, Size alignment);
            virtual Id allocNextFit(Size);
            virtual Id allocBestFit(Size);
            virtual Id allocWorstFit(Size);

            void findFreeNeighborRanges(Range range, NeighborRange& left, NeighborRange& right);
            void insertAndCoalesceUnusedRange(Range range);

        public:
            Default();
            virtual bool init(Size);

            virtual Id alloc(Size, Size alignment = 1);
            virtual void free(Id);

            virtual bool getAllocationInfo(Id, Range*);
            virtual bool getAllocationInfo(Id, Offset*, Size*);
            virtual void getInfo(Size* size, Size* allocatedSize);

            std::map<Offset, Size>& getAll() { return all; }
            std::map<Offset, Size>& getUnused() { return unused; }
            std::map<Id, Range>& getAllocated() { return allocated; }
        };
    }
}

#include <Runtime/Allocator/DefaultDefinition.h>

#endif
