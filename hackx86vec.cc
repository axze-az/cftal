#include "x86vec.h"
#include "emuvec.h"
#include "divisor.h"
#include "x86vec_test.h"
#include "bitops.h"
#include "d_int.h"
#include <functional>
#include <iomanip>


x86vec::v4u32 muluh(x86vec::v4u32 a, x86vec::v4u32 b)
{
        return mulh(a, b);
}

x86vec::v4s32 mulsh(x86vec::v4s32 a, x86vec::v4s32 b)
{
        return mulh(a, b);
}

x86vec::v2u64 muluh(x86vec::v2u64 a, x86vec::v2u64 b)
{
        return mulh(a, b);
}

x86vec::v2s64 mulsh(x86vec::v2s64 a, x86vec::v2s64 b)
{
        return mulh(a, b);
}

int main(int argc, char** argv)
{
        return 0;
}
