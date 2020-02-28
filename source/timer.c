/**
* @file
* @brief Implementation of the timer module
*/

#include "timer.h"
/**
* @brief Checks if the lift is ordered and sets the liftOrders array. Lights the order lights accordingly
*/
const int timeLimit = 3;

/**
* @brief Checks if the lift is ordered and sets the liftOrders array. Lights the order lights accordingly
*/
static clock_t clockVar;

void timerReset(){
	clockVar = clock();
}

int timerExpired(){
	clock_t clockNow = clock();
	return ((clockNow - clockVar) >= timeLimit * CLOCKS_PER_SEC);
}
