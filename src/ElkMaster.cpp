#include <iostream>
#include <fstream>
#include <ctime>
#include <random>
#include <cstdlib>
#include <sstream>
#include "ElkMaster.h"
#include "ElkHerd.h"
#include "Wolf.h"

using namespace std;

ElkMaster::ElkMaster()
{
    health = 100.0;
    speed = 5.0;
    positionX = 0.0;
    positionY = 0.0;
}

ElkMaster::~ElkMaster()
{
    //dtor
}
