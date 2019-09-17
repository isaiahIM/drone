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

#define PROPELLER_HW_INIT_FAIL 0X01
#define PROPELLER_SW_INIT_FAIL 0X01
#define PROPELLER_CONF_FAIL 0X01

/**
 * @brief propeller hardware initalize.
 * 
 * @return ret initalize result
 *  @arg PROPELLER_OK propeller hardware initalize success
 *  @arg PROPELLER_HW_INIT_FAIL propeller hardware initalize fail
 */
ret Propeller_HW_Init(void);

/**
 * @brief propeller sortware initalize.
 * 
 * @return ret initalize result
 *  @arg PROPELLER_OK propeller software initalize success
 *  @arg PROPELLER_SW_INIT_FAIL propeller software initalize fail
 */
ret Propeller_SW_Init(void);

/**
 * @brief propeller hardware, software initalize.
 * @see Propeller_HW_Init(void)
 * @see Propeller_SW_Init(void)
 * 
 * @return ret initalize result
 *  @arg PROPELLER_OK propeller initalize success
 *  @arg PROPELLER_HW_INIT_FAIL propeller hardware initalize fail
 *  @arg PROPELLER_SW_INIT_FAIL propeller software initalize fail
 */
ret Propeller_Init(void);

/**
 * @brief propeller configuration.
 * 
 * @param propeller_num propeller number
 * @param max_speed propeller maximum speed
 * @param min_speed propeller minimum speed
 * @param propeller_dir propeller rotate direction
 * @return ret configuration result
 *  @arg PROPELLER_OK propeller initalize success
 *  @arg PROPELLER_CONF_FAIL propeller configuration fail
 */
ret Propeller_Config(uint32_t propeller_num, uint16_t max_speed, uint16_t min_speed, uint8_t propeller_dir);
ret Propeller_DeConfig(uint32_t propeller_num);
ret Propeller_CCW_Rotate(uint32_t propeller_num, uint16_t speed);
ret Propeller_CW_Rotate(uint32_t propeller_num, uint16_t speed);

ret Propeller_Start(uint32_t propeller_num);
ret Propeller_Stop(uint32_t propeller_num);

#endif
