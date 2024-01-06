#include "time.hpp"

static Time time = {
    .minutes = 0,
    .seconds = 0,
    .milliseconds = 0
};

void timeIRQ() {
    time.milliseconds += 1;

    if (time.milliseconds >= 1000) {
        time.seconds += time.milliseconds / 1000;
        time.milliseconds %= 1000;
    }

    if (time.seconds >= 60) {
        time.minutes += time.seconds / 60;
        time.seconds %= 60;
    }
}

void setupTime() {
    TIMER0_CR = TIMER_ENABLE | TIMER_DIV_1 | TIMER_IRQ_REQ;
    TIMER0_DATA = TIMER_FREQ(1000);

    irqSet(IRQ_TIMER0, timeIRQ);
    irqEnable(IRQ_TIMER0);
}

const Time& currentTime() {
    return time;
}
void resetTime() {
    time = Time{ .minutes = 0,.seconds = 0,.milliseconds = 0 };
}

uint32_t timeAsSeconds() {
    return time.seconds + time.minutes * 60;
}
uint32_t timeAsMilliseconds() {
    return time.milliseconds + 1000 * (time.seconds + time.minutes * 60);
}