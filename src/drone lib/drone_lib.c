#include "drone_lib.h"

ret Drone_Init(void)
{
    ret ret_val=DRONE_INIT_SUCCESS;

    /**drone initalize */
    if(Propeller_Init()!=DRONE_INIT_SUCCESS)
    {
        ret_val|=DRONE_PROPELLER_INIT_FAIL;
    }

    /**drone configuration */

    /**propeller configuration */
    if(Propeller_Config(PROPELLER_1|PROPELLER_3, PROPELLER_SPEED_MAX, PROPELLER_STOP, PROPELLER_DIR_CW)!=DRONE_INIT_SUCCESS)
    {
        ret_val|=DRONE_PROPELLER_CONF_FAIL;
    }
    if(Propeller_Config(PROPELLER_2|PROPELLER_4, PROPELLER_SPEED_MAX, PROPELLER_STOP, PROPELLER_DIR_CCW)!=DRONE_INIT_SUCCESS)
    {
        ret_val|=DRONE_PROPELLER_CONF_FAIL;
    }
    
    return ret_val;
}


ret Drone_Arm(void)
{
    ret ret_val=DRONE_ARM_SUCCESS;

    /**arming */
    if(Propeller_Start(PROPELLER_ALL)!=DRONE_ARM_SUCCESS)
    {
        ret_val|=DRONE_ARM_FAIL;
    }

    return ret_val;
}