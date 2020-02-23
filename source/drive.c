printf("velg retning")

int array[] {0};


int prevFloor = -1;
for (i=0; i<4;i++){
    if(hardware_floor_sensor(i)==1)
        int prevFloor = currentFloor;
        int currentFloor = hardware_floor_sensor(i);
        return currentFloor;
} //skal vi gjøre med prevFloor

//Initializing
bool driveToDefinedState() {
    int error = hardware_init();
    if (error != 0) {
        printf("Unable to initialize hardware\n");
        return FALSE;
    }
    
    while (currentFloor > 3) {
    //Checks if lift is at floor
        for (floor = 0; i < 4; i++) {
            if (hardware_read_floor_sensor(floor) == 1)
                currentFloor = floor;
        }
        hardware_command_movement (HARDWARE_MOVEMENT_DOWN)
    }
    
    hardware_command_movement (HARDWARE_MOVEMENT_STOP)
    //Changes floor light to given floor
    void hardware_command_floor_indicator_on (currentFloor)
    
    return TRUE;
}

int setDirection()
{
    int currentFloor; //finnes
    int direction;
    for (i=0; i<10, i++)
    {
        array[i][1]
        if(array[i][1]==inside) //bestilt fra insiden
        {
            if(array[i][0]>currentFloor){
                direction = up;
                return direction;
            }
            if (array[i][0]<currentFloor){
                direction = down;
                return direction;
            }
        }
        //hva mer skal gjøres her;
    }
    
}



//må ha en neste tilstand varibabel
