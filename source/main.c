/**
 * @file
 * @brief The main function of the application
 */

#include "drive.h"

int main() {
    int initialized = driveToDefinedState();
    
    while (initialized) {
        //hei
        stateMachine();
    }
    return 0;
}
