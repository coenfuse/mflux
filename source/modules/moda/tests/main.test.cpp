#include "common/doctest-main.h"

// --------------------------------------------------------

#include "moda/moda.h"
TEST_CASE("Testing Moda")
{
    Moda mobj;
    
    CHECK(mobj.quadruple(2) == 8);
    CHECK(mobj.quadruple(3) == 12);
    CHECK(mobj.quadruple(4) == 16);
    CHECK(mobj.quadruple(5) == 20);
    CHECK(mobj.quadruple(6) == 24);
}