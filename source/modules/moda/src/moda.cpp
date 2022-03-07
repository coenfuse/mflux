// standard includes
#include <iostream>

// internal includes
#include "moda/moda.h"

// module includes
// ..

// third party includes
// ..


void Moda::getInfo()
{
    std::cout << "I am a module called Moda. I'm used by multiple apps." << std::endl;
}

int Moda::quadruple(int num)
{
    return num * 4;
}