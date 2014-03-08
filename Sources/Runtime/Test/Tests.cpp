#include <Runtime/Runtime.h>
#include <Runtime/Test.h>
//#include <Runtime/IDAllocator/Test.h>
#include <Runtime/Allocator/Test.h>
#include <Runtime/Memory/Test.h>
//#include <Runtime/Tree/RB/Test.h>
#include <Runtime/Branching/Test.h>
#include <Runtime/Type/Test.h>

using namespace Rt;

int main(int argc, char** argv)
{
    int result;

    result = Rt::SelfTest().run();
    if (result) return result;

//    result = Tree::RB::Test::All<u4, u4>().run();
//    if (result) return result;

    result = Allocator::Test<u8, IDAllocator::Default<u8>>().run();
    if (result) return result;

    result = Memory::Test<u4, IDAllocator::Default<u2>>(false).run();
    if (result) return result;

    result = Branching::Test<u4>().run();
    if (result) return result;

    result = Type::Test<u4, u2>().run();
    if (result) return result;

    return 0;
}
