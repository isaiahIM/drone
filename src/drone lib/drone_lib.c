/**
 * @file drone_lib.c
 * @author isaiah IM || isaiahim0214@gmail.com
 * @brief drone library source file
 * @version 0.1
 * @date 2019-09-22
 * 
 * @copyright Copyright (c) 2019 isaiah IM
 * 
 */
#include "drone_lib.h"

ret Drone_Init(void)
{
    /**Drone_Init() sequence: */
    ret ret_val=DRONE_OK;

    /**propeller initalize */
    if(Propeller_Init()!=PROPELLER_OK)
    {
        ret_val|=DRONE_FAIL;
    }

    /**kalman filter system initalize */
    ret_val|=Kalman_Init();

    /**drone configuration */

    /**propeller configuration */
    if(Propeller_Config(PROPELLER_1|PROPELLER_3, PROPELLER_SPEED_MAX, PROPELLER_STOP, PROPELLER_DIR_CW)!=DRONE_INIT_SUCCESS)
    {
        ret_val|=DRONE_FAIL;
    }
    if(Propeller_Config(PROPELLER_2|PROPELLER_4, PROPELLER_SPEED_MAX, PROPELLER_STOP, PROPELLER_DIR_CCW)!=DRONE_INIT_SUCCESS)
    {
        ret_val|=DRONE_FAIL;
    }
    
    return ret_val;
}


ret Drone_Arm(void)
{/**Drone_Arm() sequence: */
    ret ret_val=DRONE_OK;

    /**arming */
    if(Propeller_Start(PROPELLER_ALL)!=PROPELLER_OK)
    {
        ret_val|=DRONE_FAIL;
    }

    return ret_val;
}