/**
* @file
* @brief Implementation of the timer module
*/

#include "timer.h"

timeLimit = 3;

void timerReset(){
	clockVar = clock();
}

int timerExpired(){
	clock_t clockNow = clock();
	return ((clockNow - clockVar) >= timeLimit * CLOCKS_PER_SEC);
}
