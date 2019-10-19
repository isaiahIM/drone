/**
 * @file drone_lib.h
 * @author isaiah IM || isaiahim0214@gmail.com
 * @brief drone library header file
 * @version 0.1
 * @date 2019-09-17
 * 
 * @copyright Copyright (c) 2019 isaiah IM
 * 
 */
#ifndef DRONE_LIB__H
#define DRONE_LIB__H

#include "common_def.h"
#include "drone_types.h"
#include "propeller_control.h"

/*user define */
#define DRONE_INIT_SUCCESS 0x00
#define DRONE_AP_INIT_FAIL 0x01
#define DRONE_HW_INIT_FAIL 0x02 

#define DRONE_PROPELLER_INIT_FAIL 0X01
#define DRONE_PROPELLER_CONF_FAIL 0X02

#define DRONE_ARM_SUCCESS 0X00
#define DRONE_ARM_FAIL 0X01

/**
 * @brief Drone initlaize.
 * @detail This function is initalize propeller, IMU, GPS, 
 * 
 * @return ret initalize result.
 *  @arg DRONE_INIT_SUCCESS initalize success
 *  @arg DRONE_PROPELLER_INIT_FAILl propeller initalize fail
 *  @arg DRONE_PROPELLER_CONF_FAIL propeller configuration fail
 */
ret Drone_Init(void);

/**
 * @brief arming drone.
 * 
 * @return ret arming result
 *  @arg DRONE_ARM_SUCCESS armming success.
 *  @arg DRONE_ARM_FAIL arming fail
 */
ret Drone_Arm(void);


#endif
