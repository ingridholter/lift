/**
* @brief Implementation of the timer module
*/

#include "timer.h"


const int TIME_LIMIT = 3;


static clock_t clock_var;

void timer_reset(){
	clock_var = clock();
}

int timer_expired(){
	clock_t clock_now = clock();
	return ((clock_now -clock_var) >= TIME_LIMIT * CLOCKS_PER_SEC);
}
