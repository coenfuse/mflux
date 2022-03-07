// standard includes
#include <iostream>

// internal includes
#include "app-config.h"
#include "unita/unita.h"

// module includes
// ..

// third party includes
// ..

void Unita::getInfo()
{
    std::cout << "I am a unit called Unita. I'm used by " << app_NAME << " internally." << std::endl;
}

int Unita::triple(int num)
{
    return num * 3;
}