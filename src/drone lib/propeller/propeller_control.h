#ifndef PROPELLER_CONTROL__H
#define PROPELLER_CONTROL__H


/**include header*/
#include "esc_lib.h"
#include "drone_types.h"


/**user define*/
#define PROPELLER_1 0X01
#define PROPELLER_2 0X02
#define PROPELLER_3 0X04
#define PROPELLER_4 0X08
#define PROPELLER_ALL 0x0f

#define PROPELLER_CNT 4

#define PROPELLER_STOP 0
#define PROPELLER_SPEED_MAX 100
#define PROPELLER_SPEED_MIN 5

#define PROPELLER_OK 0

#define PROPELLER_DIR_CW ESC_DIR_CW
#define PROPELLER_DIR_CCW ESC_DIR_CCW

ret Propeller_HW_Init(void);
ret Propeller_SW_Init(void);

ret Propeller_Init(uint32_t propeller_num, uint16_t max_speed, uint16_t min_speed);
ret Propeller_DeInit(uint32_t propeller_num);
ret Propeller_CCW_Rotate(uint32_t propeller_num, uint16_t speed);
ret Propeller_CW_Rotate(uint32_t propeller_num, uint16_t speed);

ret Propeller_Start(uint32_t propeller_num);
ret Propeller_Stop(uint32_t propeller_num);

#endif
