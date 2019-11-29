/**
 * @file esc_lib.h
 * @author isaiah IM || isaiahim0214@gmail.com
 * @brief esc HAL Library header file
 * @version 0.2.1
 * @date 2019-11-28
 * 
 * @copyright Copyright (c) 2019 isaiah IM
 * 
 */


#ifndef ESC_LIB_H
#define ESC_LIB_H

/*common define */
#include "common_def.h"

/* user include*/
#include "drone_types.h"
#include "esc_driver.h"

/*user define*/
#define ESC_DIR_CW 0x00 /// ESC CW direction
#define ESC_DIR_CCW 0x01 /// ESC CCW direction

#define ESC_OK 0x00

#define ESC_MEMALLOC_FAIL 0X01
#define ESC_UNKNOWN_NUM 0X02
#define ESC_UNKNOWN_DIR 0x04

#define ESC_HW_INIT_FAIL 0x01
#define ESC_AP_INIT_FAIL 0x02

/**
 * @brief ESC intialize information structure.
 */
typedef struct ESC_initalize_structure
{
	uint16_t speed_max;///< esc maximum speed
	uint16_t speed_min;///< esc munumum speed
} ESC_initStruct;

/**
 * @brief ESC control informaition structure.
 */
typedef struct ESC_control_structure
{
	uint8_t rotate_dir;///< esc current direction
	uint16_t speed;///< esc current speed
} ESC_ctrlStruct;

/**
 * @brief ESC information structure
 */
typedef struct ESC_information_structure
{
	uint8_t count;///< esc count
	ESC_initStruct *init_arr;///< initalize info array
	ESC_ctrlStruct *ctrl_arr;///< control info array
} ESC_infoStruct;


/**
 * @brief ESC H/W, application initalize
 * 
 * @param count esc count
 * @return ret initalize result
 *  @arg ESC_OK ESC initalze success.
 *  @arg ESC_HW_INIT_FAIL ESC H/W initalize fail
 *  @arg ESC_MEMALLOC_FAIL ESC memory initalize fail
 */
ret ESC_Init(uint8_t count);


/**
 * @brief Rotate ESC.
 * @detail This functon is rotating ESC, update control data in list.
 * 			and, control signal send using BSP_ESC_RotateCW(), BSP_ESC_RotateCCW() function
 * @see BSP_ESC_RotateCW()
 * @see BSP_ESC_RotateCCW()
 * 
 * @param num esc number
 * @param esc ESC control data satructure
 * @return ret result of ESC rotate
 *	@arg ESC_OK ESC success to rotate
 * 	@arg ESC_UNKNOWN_NUM unknown ESC number 
 */
ret ESC_Rotate(uint8_t num, ESC_ctrlStruct esc);


/**
 * @brief Get ESC rotate direction.
 * 
 * @param esc ESC control data structure
 * @return uint8_t rotate direction
 *  @arg ESC_DIR_CW Clockwise direction
 *  @arg ESC_DIR_CCW Counterclockwise direction
 */
uint8_t ESC_GetRotateDir(const ESC_ctrlStruct esc);

/**
 * @brief Get ESC current speed.
 * 
 * @param esc ESC control data structure
 * @return uint16_t ESC rotate speed
 */
uint16_t ESC_GetSpeed(const ESC_ctrlStruct esc);


/**
 * @brief Set ESC maximum speed.
 * 
 * @param p_esc Pointed ESC initalize data in list(pointer type). 
 * @param speed maximum speed
 * @return ret result of function state.
 */
ret ESC_SetMaxSpeed(ESC_initStruct *p_esc, uint16_t speed);

/**
 * @brief Set ESC minimum speed.
 * 
 * @param p_esc Pointed ESC initalize data in list(pointer type). 
 * @param speed minumum speed
 * @return ret result of function state.
 */
ret ESC_SetMinSpeed(ESC_initStruct *p_esc, uint16_t speed);

/**
 * @brief Set ESC current speed
 * 
 * @param p_esc Pointed ESC control data in list(pointer type). 
 * @param speed input speed
 * @return ret result of function state.
 */
ret ESC_SetCurSpeed(ESC_ctrlStruct *p_esc, uint16_t speed);

/**
 * @brief Set ESC rotate direction speed
 * 
 * @param p_esc Pointed ESC control data in list(pointer type). 
 * @param dir input direction.
 * @return ret result of function state.
 */
ret ESC_SetRotateDir(ESC_ctrlStruct *p_esc, uint8_t dir);


/**
 * @brief Get control information in list.
 * 
 * @param esc_num ESC number
 * @param p_esc Get pointed ESC control data in list(pointer type). 
 * @return ret result of function state.
 * 	@arg ESC_OK success to get control information.
 *  @arg ESC_UNKNOWN_NUM fail to ger control information.
 */
ret ESC_GetControlInfo(uint8_t esc_num, ESC_ctrlStruct **p_esc);


/**
 * @brief Get initalize information in list.
 * 
 * @param esc_num ESC number
 * @param p_esc Get pointed ESC initalize data in list(pointer type). 
 * @return ret result of function state.
 * 	@arg ESC_OK success to get initalize information.
 *  @arg ESC_UNKNOWN_NUM fail to ger initalize information.
 */
ret ESC_GetInitalizeInfo(uint8_t esc_num, ESC_initStruct **p_esc);

/**
 * @brief terminate ESC
 * 
 */
void ESC_Terminate(void);
#endif
