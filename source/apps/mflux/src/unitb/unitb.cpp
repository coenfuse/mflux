// standard includes
#include <iostream>

// internal includes
#include "app-config.h"
#include "unitb/unitb.h"

// module includes
// ..

// third party includes
// ..

void Unitb::getInfo()
{
    std::cout << "I am a unit called Unitb. I'm used by " << app_NAME << " internally." << std::endl;
}

int Unitb::square(int num)
{
    return num * num;
}