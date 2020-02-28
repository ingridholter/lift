#include "drive.h"

int main() {
    int initialized = driveToDefinedState();
    
    while (initialized) {
        stateMachine();
    }
    return 0;
}
