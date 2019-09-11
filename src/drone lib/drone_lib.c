#include "drone_lib.h"

ret Drone_Init(void)
{
    ret ret_val;

    /**H/W initalize */
    ret_val|=Motor_HW_Init();

    /**motors initalize */
    ret_val|=Motor_Init(MOTOR_ALL, MOTOR_SPEED_MAX, MOTOR_SPEED_MIN);
    
    return ret_val;
}