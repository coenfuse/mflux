// standard includes
#include <iostream>

// internal includes
#include "app-config.h"
#include "unita/unita.h"
#include "unitb/unitb.h"

// module includes
#include "moda/moda.h"

// third party includes
#include "fmt/format.h"


int main(int argc, char** argv)
{
    auto intro = fmt::format("I am an app called {} v{}", app_NAME, app_VERSION);
    auto untro = fmt::format("I am made up of various units");
    auto mntro = fmt::format("I use various modules as my dependencies");
    auto tntro = fmt::format("I also use third party libs like fmt that is showing you this message");
    
    fmt::print("{}\n{}\n{}\n{}\n\n", intro, untro, mntro, tntro);

    Unita aobj;
    aobj.getInfo();

    Unitb bobj;
    bobj.getInfo();

    Moda mobj;
    mobj.getInfo();

    return 0;
}