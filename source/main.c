/**
 * @file
 * @brief The main function of the application
 */

#include "drive.h"

/*
 IKKE NØDVENDIG: ?
#include "hardware.h"
#include <stdio.h>
#include <stdlib.h>
*/

int main() {
    int initialized = driveToDefinedState();
    
    while (initialized) {
        stateMachine();
    }
    return 0;
}
