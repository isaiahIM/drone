/**
 * @file esc_lib.c
 * @author isaiah IM ||isaiahim0214@gmail.com
 * @brief esc HAL Library source file
 * @version 0.2.1
 * @date 2019-11-28
 * 
 * @copyright Copyright (c) 2019 isaiah IM
 * 
 */

#include "esc_lib.h"

/**ESC information structure */
static ESC_infoStruct esc_info; 

ret ESC_Init(uint8_t count)
{
	/**ESC_Init() sequence: */

	ret ret_val=ESC_OK;

	/**initalize values */
	esc_info.count=count;
	esc_info.init_arr=NULL;
	esc_info.ctrl_arr=NULL;

	/**H/W part part initlaize */
	ret_val|=BSP_ESC_HW_Initalize();
	if(ret_val!=ESC_OK)
	{
		ret_val=ESC_HW_INIT_FAIL;
	}

	/**memory initalize */

	/*initalize info memory initalize*/
	esc_info.init_arr=(ESC_initStruct*)calloc(count, sizeof(ESC_initStruct) );
	if(esc_info.init_arr==NULL)
	{
		ret_val|=ESC_MEMALLOC_FAIL;
	}

	/*control info memory initalize*/
	esc_info.ctrl_arr=(ESC_ctrlStruct*)calloc(count, sizeof(ESC_ctrlStruct) );
	if(esc_info.ctrl_arr==NULL)
	{
		ret_val|=ESC_MEMALLOC_FAIL;
	}

	return ret_val;
}


ret ESC_Rotate(uint8_t num, ESC_ctrlStruct esc)
{
	/**ESC_Rotate() sequence: */
											printf("call ESC_Rotate();\n");
	/**declare and initalize value*/
	ret ret_val;

	uint8_t dir;
	uint16_t speed;
	ESC_ctrlStruct *esc_buf;


	ret_val=ESC_OK;

	speed=ESC_GetSpeed(esc);/// get purpose speed
	dir=ESC_GetRotateDir(esc);/// get purpose direction

	ret_val|=ESC_GetControlInfo(num, &esc_buf);/// get control information in list

	/**set purpose control data in list */
	ret_val|=ESC_SetRotateDir(esc_buf, dir);
	ret_val|=ESC_SetCurSpeed(esc_buf, speed);
	
	/**rotation dirction check*/
	if(dir==ESC_DIR_CW)
	{
		BSP_ESC_RotateCW(num, speed);
	}
	else if (dir==ESC_DIR_CCW)
	{
		BSP_ESC_RotateCCW(num, speed);
	}
	else
	{
												printf("ESC unknown direction!\n");
		return ESC_UNKNOWN_DIR;
	}
	
												printf("exit ESC_Rotate();\n");
	return ret_val;
}

uint8_t ESC_GetRotateDir(const ESC_ctrlStruct esc)
{
	return esc.rotate_dir;
}

uint16_t ESC_GetSpeed(const ESC_ctrlStruct esc)
{
	return esc.speed;
}


ret ESC_SetMaxSpeed(ESC_initStruct *p_esc, uint16_t speed)
{
	ret ret_val=ESC_OK;

	p_esc->speed_max=speed;

	return ret_val;
}

ret ESC_SetMinSpeed(ESC_initStruct *p_esc, uint16_t speed)
{
	ret ret_val=ESC_OK;

	p_esc->speed_min=speed;

	return ret_val;
}


ret ESC_SetCurSpeed(ESC_ctrlStruct *p_esc, uint16_t speed)
{
	ret ret_val=ESC_OK;

	p_esc->speed=speed;

	return ret_val;
}

ret ESC_SetRotateDir(ESC_ctrlStruct *p_esc, uint8_t dir)
{
	ret ret_val=ESC_OK;

	p_esc->rotate_dir=dir;

	return ret_val;
}


ret ESC_GetControlInfo(uint8_t esc_num, ESC_ctrlStruct **p_esc)
{
	/**ESC_GetControlInfo() sequence: */
														printf("call ESC_GetControlInfo();\n");

	/**declare values */
	uint8_t i;

	/**search esc number*/
	if(esc_num>= esc_info.count || esc_num<0)
	{
		return ESC_UNKNOWN_NUM;
	}
	else
	{
		*p_esc=&(esc_info.ctrl_arr[esc_num]);
		printf("esc data: speed: %d, dir: %d\n", (*p_esc)->speed, (*p_esc)->rotate_dir);
	}

													printf("exit ESC_GetControlInfo();\n");
	return ESC_OK;
}



ret ESC_GetInitalizeInfo(uint8_t esc_num, ESC_initStruct **p_esc)
{
	/**ESC_GetInitalizeInfo() sequence: */
																		printf("call ESC_GetInitalizeInfo();\n");
	/**declare values */
	uint8_t i;
																		printf("num: %d\n", esc_num);
	/**search esc number*/
	if(esc_num>= esc_info.count || esc_num<0)
	{
		return ESC_UNKNOWN_NUM;
	}
	else
	{
		*p_esc=&(esc_info.init_arr[i]);
		printf("esc data: speed_max: %d, speed_min: %d\n", (*p_esc)->speed_max, (*p_esc)->speed_min);
	}
																		printf("exit ESC_GetInitalizeInfo();\n");

	return ESC_OK;
}


void ESC_Terminate(void)
{
								printf("call ESC_Rerminate();\n");
	free(esc_info.ctrl_arr);
	free(esc_info.init_arr);
	esc_info.count=0;
								printf("exit ESC_Terminate();\n ");
}