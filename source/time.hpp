#include <nds.h>

struct Time {
    uint32_t minutes;
    uint32_t seconds;
    uint32_t milliseconds;
};

/**
 * Returns the current time mesured by the timer0
*/
const Time& currentTime();

/**
 * Sets up time measure using timer0
*/
void setupTime();
/**
 * Reset current time to 0
*/
void resetTime();

/**
 * Returns the current time as seconds, converting minutes into seconds
*/
uint32_t timeAsSeconds(); 
/**
 * Returns the current time as milliseconds, converting minutes and seconds into milliseconds
*/
uint32_t timeAsMilliseconds();

