#include <nds.h>

struct Time {
    uint32_t minutes;
    uint32_t seconds;
    uint32_t milliseconds;
};

const Time& currentTime();
void setupTime();
void resetTime();

uint32_t timeAsSeconds(); 
uint32_t timeAsMilliseconds();

