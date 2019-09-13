#ifndef ESC_LIB_H
#define ESC_LIB_H

#include <stdlib.h>
#include <string.h>

#include "drone_types.h"
#include "esc_driver.h"

#define ESC_DIR_CW 0x00
#define ESC_DIR_CCW 0x01
#define ESC_DIR_UNKNOWN 0x02

#define ESC_SUCCESS 0x00
#define ESC_MEMALLOC_FAIL 0X01
#define ESC_UNKNOWN_NUM 0X02
#define ESC_UNKNOWN_DIR 0x04


typedef struct ESC_initalize_structure
{
	uint8_t num;///< esc number
	uint16_t speed_max;///< esc maximum speed
	uint16_t speed_min;///< esc munumum speed
	struct ESC_initalize_structure *next;///< list link
} ESC_initStruct;


typedef struct ESC_control_structure
{
	uint8_t num;///< esc number
	uint8_t rotate_dir;///< esc current direction
	uint16_t speed;///< esc current speed
	struct ESC_control_structure *next;///< list link
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

ret ESC_SystemInit(void);
ret ESC_HW_Init(void);

ret ESC_AddInfo(ESC_initStruct esc_init, ESC_ctrlStruct esc_ctrl);
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
