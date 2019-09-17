/**
 * @file esc_lib.h
 * @author isaiah IM || isaiahim0214@gmail.com
 * @brief esc HAL library header file
 * @version 0.1
 * @date 2019-09-13
 * 
 * @copyright Copyright (c) 2019
 * 
 */


#ifndef ESC_LIB_H
#define ESC_LIB_H

#include <stdlib.h>
#include <string.h>

/** user include*/
#include "drone_types.h"
#include "esc_driver.h"

/**user define*/
#define ESC_DIR_CW 0x00 /// ESC CW direction
#define ESC_DIR_CCW 0x01 /// ESC CCW direction

#define ESC_SUCCESS 0x00
#define ESC_MEMALLOC_FAIL 0X01
#define ESC_UNKNOWN_NUM 0X02
#define ESC_UNKNOWN_DIR 0x04

/**
 * @brief ESC intialize information structure.
 * @detail This structure is including Self Referential Struct. so, it can using list.
 */
typedef struct ESC_initalize_structure
{
	uint8_t num;///< esc number
	uint16_t speed_max;///< esc maximum speed
	uint16_t speed_min;///< esc munumum speed
	struct ESC_initalize_structure *next;///< Self Referential Struct
} ESC_initStruct;

/**
 * @brief ESC control informaition structure.
 * @detail This structure is including Self Referential Struct. so, it can using list.
 */
typedef struct ESC_control_structure
{
	uint8_t num;///< esc number
	uint8_t rotate_dir;///< esc current direction
	uint16_t speed;///< esc current speed
	struct ESC_control_structure *next;///< Self Referential Struct
} ESC_ctrlStruct;


static uint8_t esc_count=0;/// esc count


/**ESC_initStruct position*/
static ESC_initStruct *init_head=NULL;
static ESC_initStruct *init_cur=NULL;
static ESC_initStruct *init_prev=NULL;

/**ESC_ctrlStruct position*/
static ESC_ctrlStruct *ctrl_head=NULL;
static ESC_ctrlStruct *ctrl_cur=NULL;
static ESC_ctrlStruct *ctrl_prev=NULL;

/**user functions*/

/**
 * @brief ESC system initalize.
 * @detail This function is initaling ESC_initStruct, ESC_ctrlStruct.
 * 			And, these structure are using dummy node base linked list. and queue type list insert. 
 * @see typedef struct ESC_initalize_structure
 * @see typedef struct ESC_control_structu
 * re
 * @return ret initalize result
 * 	@arg ESC_SUCCESS ESC initalze success.
 * 	@arg ESC_MEMALLOC_FAIL ESC node memory allocate fail.
 */
ret ESC_SystemInit(void);

/**
 * @brief ESC H/W initalize.
 * @detail This function is ESC hardware initalizing function.
 * 			And hardware initalizing is Referential BSP function.
 * @see BSP_ESC_HW_Initalize()
 * 
 * @return ret initalize result
 * 	@arg ESC_SUCCESS ESC initalze success.
 */
ret ESC_HW_Init(void);

/**
 * @brief Add ESC inforamtion.
 * @detail This function is add initalize and control data in list.
 * 			initalize data add is using ESC_AddInitalizeInfo().
 * 			control data add is using ESC_AddControlInfo().
 * @see ESC_AddInitalizeInfo(const ESC_initStruct esc)
 * @see ESC_AddControlInfo(const ESC_ctrlStruct esc)
 * 
 * @param esc_init initalize data 
 * @param esc_ctrl control data 
 * @return ret result of adding information in list.
 *  @arg ESC_SUCCESS Success to add information.
 * 	@arg ESC_MEMALLOC_FAIL ESC node memory allocate fail.
 */
ret ESC_AddInfo(ESC_initStruct esc_init, ESC_ctrlStruct esc_ctrl);

/**
 * @brief Delete ESC information.
 * @detail This function is delete ESC initalize data, control data in list.
 * 			Delete initalize data is using ESC_DeleteInitalizeInfo().
 * 			Delete control data is using ESC_DeleteControlInfo().
 * @see ESC_DeleteInitalizeInfo(uint8_t esc_num)
 * @see ESC_DeleteControlInfo(uint8_t esc_num)
 * 
 * @param esc_num number of ESC
 * @return ret result of deleting information in list.
 * 	@arg ESC_SUCCESS Success to delete information in list.
 *  @arg ESC_UNKNOWN_NUM unknown ESC number 
 */
ret ESC_DeleteInfo(uint8_t esc_num);

/**
 * @brief Rotate ESC.
 * @detail This functon is rotating ESC, update control data in list.
 * 			and, control signal send using BSP_ESC_RotateCW(), BSP_ESC_RotateCCW() function
 * @see BSP_ESC_RotateCW()
 * @see BSP_ESC_RotateCCW()
 * 
 * @param esc ESC control data satructure
 * @return ret result of ESC rotate
 *	@arg ESC_SUCCESS ESC success to rotate
 * 	@arg ESC_UNKNOWN_NUM unknown ESC number 
 */
ret ESC_Rotate(ESC_ctrlStruct esc);

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
 * @brief Get motor number.
 * 
 * @param esc ESC control data structure
 * @return uint8_t ESC number
 */
uint8_t ESC_GetNumber(const ESC_ctrlStruct esc);

/**
 * @brief Get ESC current speed.
 * 
 * @param esc ESC control data structure
 * @return uint16_t ESC rotate speed
 */
uint16_t ESC_GetSpeed(const ESC_ctrlStruct esc);

/**
 * @brief Get ESC rotate direction.
 * @detail This function call ESC_GetRotateDir().
 * @see ESC_GetRotateDir(const ESC_ctrlStruct esc).
 * 
 * @param esc_num ESC number
 * @return uint8_t ESC current direction
 *  @arg ESC_DIR_CW Clockwise direction
 *  @arg ESC_DIR_CCW Counterclockwise direction
 */
uint8_t ESC_GetCurrentDir(uint8_t esc_num);

/**
 * @brief Get ESC current speed.
 * @detail This function call ESC_GetSpeed() function.
 * @see ESC_GetSpeed(const ESC_ctrlStruct esc).
 * 
 * @param esc_num ESC number
 * @return uint16_t current speed
 */
uint16_t ESC_GetCurrentSpeed(uint8_t esc_num);

/**
 * @brief Set initalize number in list.
 * 
 * @param esc Pointed ESC initalize data in list(pointer type). 
 * @param num ESC numnber
 * @return ret result of function state.
 */
ret ESC_SetInitNum(ESC_initStruct *esc, uint8_t num);

/**
 * @brief Set ESC maximum speed.
 * 
 * @param esc Pointed ESC initalize data in list(pointer type). 
 * @param speed maximum speed
 * @return ret result of function state.
 */
ret ESC_SetMaxSpeed(ESC_initStruct *esc, uint16_t speed);

/**
 * @brief Set ESC minimum speed.
 * 
 * @param esc Pointed ESC initalize data in list(pointer type). 
 * @param speed minumum speed
 * @return ret result of function state.
 */
ret ESC_SetMinSpeed(ESC_initStruct *esc, uint16_t speed);

/**
 * @brief Set ESC current speed
 * 
 * @param esc Pointed ESC control data in list(pointer type). 
 * @param speed input speed
 * @return ret result of function state.
 */
ret ESC_SetCurrentSpeed(ESC_ctrlStruct *esc, uint16_t speed);

/**
 * @brief Set ESC rotate direction speed
 * 
 * @param esc Pointed ESC control data in list(pointer type). 
 * @param dir input direction.
 * @return ret result of function state.
 */
ret ESC_SetRotateDir(ESC_ctrlStruct *esc, uint8_t dir);

/**
 * @brief Set ESC control number
 * 
 * @param esc Pointed ESC control data in list(pointer type). 
 * @param num ESC control number
 * @return ret result of function state.
 */
ret ESC_SetCurrentNum(ESC_ctrlStruct *esc, uint8_t num);

/**
 * @brief Add control information in list.
 * 
 * @param esc add control information
 * @return ret result of function state.
 */
ret ESC_AddControlInfo(const ESC_ctrlStruct esc);

/**
 * @brief Delete Control information in list.
 * 
 * @param esc_num remove control number. 
 * @return ret result of function state.
 *  @arg ESC_SUCCESS success to delete control information in list
 *  @arg ESC_UNKNOWN_NUM unknown ESC control number
 */
ret ESC_DeleteControlInfo(uint8_t esc_num);

/**
 * @brief Get control information in list.
 * 
 * @param esc_num ESC number
 * @param esc Get pointed ESC control data in list(pointer type). 
 * @return ret result of function state.
 * 	@arg ESC_SUCCESS success to get control information.
 *  @arg ESC_UNKNOWN_NUM fail to ger control information.
 */
ret ESC_GetControlInfo(uint8_t esc_num, ESC_ctrlStruct **esc);

/**
 * @brief Set initalize information in list.
 * 
 * @param esc Input ESC initalize data
 * @return ret result of function state.
 *  @arg ESC_SUCCESS success to add initalize information in list
 *  @arg ESC_MEMALLOC_FAIL list memory allocate fail.
 */
ret ESC_AddInitalizeInfo(const ESC_initStruct esc);

/**
 * @brief Delete ESC initalize information in list
 * 
 * @param esc_num delete esc number
 * @return ret result of function state.
 *  @argESC_SUCCESS success to delete initalize information in list
 *  @arg ESC_UNKNOWN_NUM esc number is not exist.
 */
ret ESC_DeleteInitalizeInfo(uint8_t esc_num);

/**
 * @brief Get initalize information in list.
 * 
 * @param esc_num ESC number
 * @param esc Get pointed ESC initalize data in list(pointer type). 
 * @return ret result of function state.
 * 	@arg ESC_SUCCESS success to get initalize information.
 *  @arg ESC_UNKNOWN_NUM fail to ger initalize information.
 */
ret ESC_GetInitalizeInfo(uint8_t esc_num, ESC_initStruct **esc);

/**
 * @brief Increment ESC total count. 
 * 
 */
void ESC_CountIncrement(void);

/**
 * @brief Decrement ESC total count.
 * 
 */
void ESC_CountDecrement(void);

/**
 * @brief Reset pointed control list position(current position, preview position).
 * 
 */
void ESC_ResetCtrlListPosition(void);

/**
 * @brief Reset pointed initalize list position(current position, preview position).
 * 
 */
void ESC_ResetInitListPosition(void);


#endif
