#ifndef header_B74E4EF3F4B6
#define header_B74E4EF3F4B6

#include <memory>
#include <set>
#include <stdlib.h>
#include <boost/signals2.hpp>

#include <Runtime/Platform.h>
#include <Runtime/Log.h>
#include <Runtime/Debug.h>
#include <Runtime/Object.h>
#include <Runtime/Exception.h>
#include <Runtime/Option.h>
#include <Runtime/Either.h>
#include <Runtime/Versioned.h>
#include <Runtime/Test/Test.h>
#include <Runtime/Range.h>
#include <Runtime/Bit.h>
#include <Runtime/Float.h>
#include <Runtime/Subroutines.h>
#include <Runtime/AlignedAllocator.h>

#include <Runtime/IDAllocator/Trait.h>
#include <Runtime/IDAllocator/Default.h>
#include <Runtime/IDAllocator/Counting.h>

//#include <Runtime/Tree/RB/Default.h>
#include <Runtime/Allocator/Default.h>

#include <Runtime/Collections/VectorAlgorithms.h>

#include <Runtime/Value/Trait.h>
#include <Runtime/Value/Scalar.h>
//#include <Runtime/Value/Uuid.h>
#include <Runtime/Value/Container.h>
#include <Runtime/Value/Map.h>
#include <Runtime/Value/Vector.h>

#include <Runtime/Memory/CommonRequirements.h>
#include <Runtime/Memory/Trait.h>
#include <Runtime/Memory/Malloc.h>
#include <Runtime/Memory/Buffer.h>
#include <Runtime/Memory/Compound/Compound.h>
#include <Runtime/Memory/Multibuffer/Alloc.h>
#include <Runtime/Memory/Multibuffer/Default.h>
#include <Runtime/Memory/Allocation.h>

#include <Runtime/XML/Subroutines.h>
#include <Runtime/XML/ElementProcessor.h>
#include <Runtime/XML/Parser.h>

#include <Runtime/Branching/Default.h>
#include <Runtime/Type/Trait.h>
#include <Runtime/Type/Atom.h>
#include <Runtime/Type/Struct.h>
#include <Runtime/Type/Matrix.h>
#include <Runtime/Type/XMLLoader.h>

#endif
