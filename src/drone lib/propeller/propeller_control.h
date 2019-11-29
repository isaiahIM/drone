/**
 * @file propeller_control.h
 * @author isaiah IM || isaiahim0214@gmail.com
 * @brief propeller control header file
 * @version 0.1
 * @date 2019-09-22
 * 
 * @copyright Copyright (c) 2019 isaiah IM
 * 
 */
#ifndef PROPELLER_CONTROL__H
#define PROPELLER_CONTROL__H


/*include header*/
#include "common_def.h"
#include "esc_lib.h"
#include "drone_types.h"
#include "config.h"

#define PROPELLER_STOP 0
#define PROPELLER_SPEED_MAX 100
#define PROPELLER_SPEED_MIN 5

#define PROPELLER_OK 0
#define PROPELLER_FAIL 0X01

#define PROPELLER_DIR_CW ESC_DIR_CW
#define PROPELLER_DIR_CCW ESC_DIR_CCW

#define PROPELLER_HW_INIT_FAIL ESC_HW_INIT_FAIL
#define PROPELLER_SW_INIT_FAIL ESC_AP_INIT_FAIL


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
 *  @arg PROPELLER_FAIL propeller configuration fail
 */
ret Propeller_Config(uint32_t propeller_num, uint16_t max_speed, uint16_t min_speed, uint8_t propeller_dir);


/**
 * @brief propeller Counterclockwise direction rotate
 * 
 * @param propeller_num propeller number
 * @param speed ratarte speed
 * @return ret CCW rotate result
 *  @arg PROPELLER_OK ccw rotate success
 *  @arg PROPELLER_FAIL ccw rotate fail
 */
ret Propeller_CCW_Rotate(uint32_t propeller_num, uint16_t speed);

/**
 * @brief propeller Clockwise direction rotate
 * 
 * @param propeller_num propeller number
 * @param speed ratarte speed
 * @return ret CW rotate result
 *  @arg PROPELLER_OK cw rotate success
 *  @arg PROPELLER_FAIL cw rotate fail
 */
ret Propeller_CW_Rotate(uint32_t propeller_num, uint16_t speed);

/**
 * @brief propeller armming(start to run)
 * 
 * @param propeller_num propeller number
 * @return ret propeller start result
 *  @arg PROPELLER_OK propeller start success
 *  @arg PROPELLER_FAIL propeller start fail
 */
ret Propeller_Start(uint32_t propeller_num);

/**
 * @brief propeller de-armming(stop to run)
 * 
 * @param propeller_num propeller number
 * @return ret propeller stop result
 *  @arg PROPELLER_OK propeller stop success
 *  @arg PROPELLER_FAIL propeller stop fail
 */
ret Propeller_Stop(uint32_t propeller_num);

void Propeller_Terminate(void);
#endif
