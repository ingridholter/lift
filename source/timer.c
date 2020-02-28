/**
* @file
* @brief Implementation of the timer module
*/

#include "timer.h"


/**
 * @brief Sets a new timestamp
*/
const int timeLimit = 3;

/**
 * @brief Sets a new timestamp
*/
static clock_t clockVar;


void timerReset(){
	clockVar = clock();
}

int timerExpired(){
	clock_t clockNow = clock();
	return ((clockNow - clockVar) >= timeLimit * CLOCKS_PER_SEC);
}
