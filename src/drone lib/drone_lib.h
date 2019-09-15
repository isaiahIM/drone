#ifndef DRONE_LIB__H
#define DRONE_LIB__H

#include "drone_types.h"
#include "propeller_control.h"


#define DRONE_INIT_SUCCESS 0x00
#define DRONE_AP_INIT_FAIL 0x01
#define DRONE_HW_INIT_FAIL 0x02 

ret Drone_Init(void);

ret Drone_HW_Init(void);
ret Drone_AP_Init(void);
ret Drone_Arm(void);
#endif
