#include "drone_lib.h"

ret Drone_Init(void)
{
    ret ret_val=DRONE_INIT_SUCCESS;

    /**H/W initalize */

    if(Drone_HW_Init()==DRONE_INIT_SUCCESS)
    {
        ret_val|=DRONE_HW_INIT_FAIL;
    }

    if(Drone_AP_Init()==DRONE_INIT_SUCCESS)
    {
        ret_val|=DRONE_AP_INIT_FAIL; 
    }

    Propeller_Init(PROPELLER_ALL, PROPELLER_SPEED_MAX, PROPELLER_STOP);
    
    Propeller_Start(PROPELLER_ALL);
    
    return ret_val;
}

ret Drone_HW_Init(void)
{
    ret ret_val=DRONE_INIT_SUCCESS;

    ret_val|=Propeller_HW_Init();

    return ret_val;
}

ret Drone_AP_Init(void)
{
    ret ret_val=DRONE_INIT_SUCCESS;

    /**ESC application initalize */
    ret_val|=Propeller_SW_Init();

    return ret_val;
}