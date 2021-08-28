#include <cstdlib>
#include <ctime>
#include "Utilities.hpp"

int getRandNumber(int min, int max) {
    srand(time(NULL));
    int rtn = rand() % (max - min + 1) + min;
    return rtn;
}
