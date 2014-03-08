#include <typeinfo>
#include <Runtime/Runtime.h>

int Rt::Test::run()
{
    auto name = typeid(this).name();
    printf("\n***** Running test %s:\n\n", name);
    return test();
}
