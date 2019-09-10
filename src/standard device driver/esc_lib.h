#ifndef ESC_LIB_H
#define ESC_LIB_H

#include <stdlib.h>
#include <string.h>

#include "drone_types.h"
#include "esc_driver.h"

#define ESC_DIR_CW 0
#define ESC_DIR_CCW 1
#define ESC_DIR_UNKNOWN 2

#define ESC_SUCCESS 0
#define ESC_MEMALLOC_FAIL 0X01
#define ESC_UNKNOWN_NUM 0X02
#define ESC_FIRST_CONTROL 0X04
#define ESC_UNKNOWN_DIR 0x08

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
	uint16_t speed;///< esc current speed
	uint8_t rotate_dir;///< esc current direction
	struct ESC_control_structure *next;///< list link
} ESC_ctrlStruct;

static uint8_t esc_count=0;/// esc count

static ESC_initStruct *esc_info_list=NULL;/// esc initalize data
static ESC_ctrlStruct *esc_ctrl_list=NULL;/// esc control data

/**ESC_initStruct position*/
static ESC_initStruct *init_head=NULL;
static ESC_initStruct *init_cur=NULL;
static ESC_initStruct *init_prev=NULL;

/**ESC_ctrlStruct position*/
static ESC_ctrlStruct *ctrl_head=NULL;
static ESC_ctrlStruct *ctrl_cur=NULL;
static ESC_ctrlStruct *ctrl_prev=NULL;

/**user functions*/

ret ESC_Init(ESC_initStruct esc);
ret ESC_Rotate(ESC_ctrlStruct esc);
ret ESC_GetRotateDirection(uint8_t esc_num, uint8_t *motor_dir);
uint8_t ESC_GetNumber(const ESC_ctrlStruct esc);
uint16_t ESC_GetSpeed(const ESC_ctrlStruct esc);

ret ESC_AddControlInfo(const ESC_ctrlStruct esc);
ret ESC_DeleteControlInfo(uint8_t esc_num);
ret ESC_GetControlInfo(uint8_t esc_num, ESC_ctrlStruct *esc);
ret ESC_ConfigControlInfo(const ESC_ctrlStruct esc);

ret ESC_AddInitalizeInfo(const ESC_initStruct esc);
ret ESC_DeleteInitalizeInfo(uint8_t esc_num);
ret ESC_GetInitalizeInfo(uint8_t esc_num, ESC_initStruct *esc);

void ESC_CountIncrement(void);
void ESC_CountDecrement(void);

void ESC_ResetCtrlListPosition(void);
void ESC_ResetInitListPosition(void);
#endif
