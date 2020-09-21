#include "ElkHerd.h"
#include <cstddef>

ElkHerd::ElkHerd()
{
    health = 100.0;
    speed = 3.5;
    positionX = 0.0;
    positionY = 0.0;
    age = 0;
    id = 0;
    next = NULL;
}

ElkHerd::~ElkHerd()
{
    //dtor
}
