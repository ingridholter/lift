/**
* @file
* @brief Implementation of the timer module
*/

#include "timer.h"

void timerReset(){
	clockVar = clock();
}

int timerExpired(){
	clock_t clockNow = clock();
	return ((clockNow - clockVar) >= timeLimit * CLOCKS_PER_SEC);
}
