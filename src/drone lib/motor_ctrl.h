#ifndef MOTOR_CTRL__H
#define MOTOR_CTRL__H


/**include header*/
#include "esc_lib.h"
#include "drone_types.h"


/**user define*/
#define MOTOR1 0X01
#define MOTOR2 0X02
#define MOTOR3 0X04
#define MOTOR4 0X08
#define MOTOR_ALL 0x0f

#define MOTOR_CNT 4

#define MOTOR_STOP 0
#define MOTOR_SPEED_MAX 100
#define MOTOR_SPEED_MIN 5

#define MOTOR_OK 0

#define MOTOR_DIR_CW ESC_DIR_CW
#define MOTOR_DIR_CCW ESC_DIR_CCW

ret Motor_HW_Init(void);
ret Motor_Init(uint32_t motor_num, uint16_t max_speed, uint16_t min_speed);
ret Motor_CCW_Rotate(uint32_t motor_num, uint16_t speed);
ret Motor_CW_Rotate(uint32_t motor_num, uint16_t speed);
ret Motor_Stop(uint32_t moto_num);

#endif
