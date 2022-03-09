#include "common/doctest-main.h"

// ---------------------------------------------------------

#include "unita/unita.h"
TEST_CASE("Testing Unita") 
{
    Unita aobj;

    CHECK(aobj.triple(2) == 6);
    CHECK(aobj.triple(3) == 9);
    CHECK(aobj.triple(4) == 12);
    CHECK(aobj.triple(5) == 15);
    CHECK(aobj.triple(6) == 18);
}

// ---------------------------------------------------------

#include "unitb/unitb.h"
TEST_CASE("Testing Unitb")
{
    Unitb bobj;

    CHECK(bobj.square(2) == 4);
    CHECK(bobj.square(3) == 9);
    CHECK(bobj.square(4) == 16);
    CHECK(bobj.square(5) == 25);
    CHECK(bobj.square(6) == 36);
}