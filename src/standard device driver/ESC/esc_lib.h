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
 * @brief ESC system initalize
 * @detail This function is initaling ESC_initStruct, ESC_ctrlStruct.
 * 			And, these structure are using dummy node base linked list. and queue type list insert. 
 * @see typedef struct ESC_initalize_structure
 * @see typedef struct ESC_control_structure
 * @return ret initalize result
 * 	@param ESC_SUCCESS ESC initalze success.
 * 	@param ESC_MEMALLOC_FAIL ESC node memory allocate fail.
 */
ret ESC_SystemInit(void);

/**
 * @brief ESC H/W initalize
 * @detail This function is ESC hardware initalizing function.
 * 			And hardware initalizing is Referential BSP function.
 * @see BSP_ESC_HW_Initalize()
 * @return ret initalize result
 * 	@arg ESC_SUCCESS ESC initalze success.
 */
ret ESC_HW_Init(void);

/**
 * @brief Add ESC inforamtion
 * @detail This function is add initalize and control data in list.
 * 			initalize data add is using ESC_AddInitalizeInfo().
 * 			control data add is using ESC_AddControlInfo().
 * @see ESC_AddInitalizeInfo(const ESC_initStruct esc)
 * @see ESC_AddControlInfo(const ESC_ctrlStruct esc)
 * @param esc_init initalize data 
 * @param esc_ctrl control data 
 * @return ret result of adding information in list.
 */
ret ESC_AddInfo(ESC_initStruct esc_init, ESC_ctrlStruct esc_ctrl);

/**
 * @brief Delete ESC information
 * @detail This function is delete ESC initalize data, control data in list.
 * 			Delete initalize data is using ESC_DeleteInitalizeInfo().
 * 			Delete control data is using ESC_DeleteControlInfo().
 * @see ESC_DeleteInitalizeInfo(uint8_t esc_num)
 * @see ESC_DeleteControlInfo(uint8_t esc_num)
 * @param esc_num number of esc
 * @return ret result of deleting information in list.
 */
ret ESC_DeleteInfo(uint8_t esc_num);


ret ESC_Rotate(ESC_ctrlStruct esc);


uint8_t ESC_GetRotateDir(const ESC_ctrlStruct esc);


uint8_t ESC_GetNumber(const ESC_ctrlStruct esc);
uint16_t ESC_GetSpeed(const ESC_ctrlStruct esc);


uint8_t ESC_GetCurrentDir(uint8_t esc_num);
uint16_t ESC_GetCurrentSpeed(uint8_t esc_num);

ret ESC_SetInitNum(ESC_initStruct *esc, uint8_t num);
ret ESC_SetMaxSpeed(ESC_initStruct *esc, uint16_t speed);
ret ESC_SetMinSpeed(ESC_initStruct *esc, uint16_t speed);

ret ESC_SetCurrentSpeed(ESC_ctrlStruct *esc, uint16_t speed);
ret ESC_SetRotateDir(ESC_ctrlStruct *esc, uint8_t dir);
ret ESC_SetCurrentNum(ESC_ctrlStruct *esc, uint8_t num);

ret ESC_AddControlInfo(const ESC_ctrlStruct esc);
ret ESC_DeleteControlInfo(uint8_t esc_num);
ret ESC_GetControlInfo(uint8_t esc_num, ESC_ctrlStruct **esc);

ret ESC_AddInitalizeInfo(const ESC_initStruct esc);
ret ESC_DeleteInitalizeInfo(uint8_t esc_num);
ret ESC_GetInitalizeInfo(uint8_t esc_num, ESC_initStruct **esc);

void ESC_CountIncrement(void);
void ESC_CountDecrement(void);

void ESC_ResetCtrlListPosition(void);
void ESC_ResetInitListPosition(void);


#endif
