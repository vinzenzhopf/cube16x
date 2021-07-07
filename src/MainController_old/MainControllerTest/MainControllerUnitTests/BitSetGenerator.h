#pragma once


#include "CubeFrame.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <memory>

using namespace std;

class BitsetGenerator {
	
	BitsetGenerator();

	unique_ptr<std::bitset<CUBE_FRAME_CUBE_SIZE>> getRandomBitset();

};

