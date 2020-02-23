#ifndef _TIMER__
#define _TIMER__

#include <time.h>

//resets timer
void timer_reset();

//Checks if more than TIME_LIMIT seconds since last ?timestamp?
int timer_expired();


#endif

