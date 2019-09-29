/**
 * @file esc_lib.c
 * @author isaiah IM ||isaiahim0214@gmail.com
 * @brief esc HAL Library source file
 * @version 0.1.1
 * @date 2019-09-26
 * 
 * @copyright Copyright (c) 2019 isaiah IM
 * 
 */


#include "esc_lib.h"

ret ESC_Init(void)
{
	/**ESC_Init() sequence: */

	ret ret_val=ESC_SUCCESS;

	/**H/W part part initlaize */
	ret_val|=BSP_ESC_HW_Initalize();
	if(ret_val!=ESC_SUCCESS)
	{
		ret_val=ESC_HW_INIT_FAIL;
	}

	/**Application part initalize */

	/*initalize esc initalizing data list*/
	init_prev=init_head;
	init_head=(ESC_initStruct*)malloc(sizeof(ESC_initStruct) );
	if(init_head==NULL)
	{
		ret_val|=ESC_AP_INIT_FAIL;
	}
	init_cur=init_head;
	init_head->next=NULL;

	/*initalize esc control data list*/
	ctrl_prev=ctrl_head;
	ctrl_head=(ESC_ctrlStruct*)malloc(sizeof(ESC_ctrlStruct) );
	if(ctrl_head==NULL)
	{
		ret_val|=ESC_AP_INIT_FAIL;
	}
	ctrl_cur=ctrl_head;
	ctrl_head->next=NULL;

	return ret_val;
}

ret ESC_AddESC(ESC_initStruct esc_init, ESC_ctrlStruct esc_ctrl)
{
	/**ESC_AddESC() sequence: */
	ret ret_val=ESC_SUCCESS;

	/**add initalize info */
	ret_val|=ESC_AddInitalizeInfo(esc_init);

	/**add control info */
	ret_val|=ESC_AddControlInfo(esc_ctrl);
	
	return ret_val;
}

ret ESC_DeleteESC(uint8_t esc_num)
{
	/**ESC_DeleteESC() sequence: */
	ret ret_val=ESC_SUCCESS;

	/**delete control info */
	ret_val|=ESC_DeleteControlInfo(esc_num);

	/**delete initalize info */
	ret_val|=ESC_DeleteInitalizeInfo(esc_num);
	
	return ret_val;
}

ret ESC_Rotate(ESC_ctrlStruct esc)
{
	/**ESC_Rotate() sequence: */
											printf("call ESC_Rotate();\n");
	/**declare and initalize value*/
	ret ret_val;

	uint8_t dir, num;
	uint16_t speed;
	ESC_ctrlStruct *esc_buf;


	ret_val=ESC_SUCCESS;

	num=ESC_GetNumber(esc);/// get purpose number
	speed=ESC_GetSpeed(esc);/// get purpose speed
	dir=ESC_GetRotateDir(esc);/// get purpose direction

	ret_val|=ESC_GetControlInfo(num, &esc_buf);/// get control information in list

	/**set purpose control data in list */
	ret_val|=ESC_SetRotateDir(esc_buf, dir);
	ret_val|=ESC_SetCurrentSpeed(esc_buf, speed);
	
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

uint8_t ESC_GetNumber(const ESC_ctrlStruct esc)
{
	return  esc.num;
}

uint16_t ESC_GetSpeed(const ESC_ctrlStruct esc)
{
	return esc.speed;
}

ret ESC_SetInitNum(ESC_initStruct *esc, uint8_t num)
{
	ret ret_val=ESC_SUCCESS;

	esc->num=num;

	return ret_val;
}

ret ESC_SetMaxSpeed(ESC_initStruct *esc, uint16_t speed)
{
	ret ret_val=ESC_SUCCESS;

	esc->speed_max=speed;

	return ret_val;
}

ret ESC_SetMinSpeed(ESC_initStruct *esc, uint16_t speed)
{
	ret ret_val=ESC_SUCCESS;

	esc->speed_min=speed;

	return ret_val;
}


ret ESC_SetCurrentSpeed(ESC_ctrlStruct *esc, uint16_t speed)
{
	ret ret_val=ESC_SUCCESS;

	esc->speed=speed;

	return ret_val;
}

ret ESC_SetRotateDir(ESC_ctrlStruct *esc, uint8_t dir)
{
	ret ret_val=ESC_SUCCESS;

	esc->rotate_dir=dir;

	return ret_val;
}

ret ESC_SetCurrentNum(ESC_ctrlStruct *esc, uint8_t num)
{
	ret ret_val=ESC_SUCCESS;

	esc->num=num;

	return ret_val;
}


ret ESC_AddControlInfo(const ESC_ctrlStruct esc)
{
	/**ESC_AddControlInfo() sequence: */
														printf("call ESC_AddControlInfo();\n");
	/**declare and initalize value*/
	ESC_ctrlStruct *buf;

	/**node allocate*/
	buf=(ESC_ctrlStruct*)malloc(sizeof(ESC_ctrlStruct) );
	if(buf==NULL)
	{
													printf("malloc fail\n");
		return ESC_MEMALLOC_FAIL;
	}

	/**node data set*/
	buf->num=ESC_GetNumber(esc);
	buf->speed=ESC_GetSpeed(esc);
	buf->rotate_dir=ESC_GetRotateDir(esc);

	/**insert new node*/
	ctrl_prev=ctrl_cur;
	buf->next=ctrl_cur->next;
	ctrl_cur->next=buf;
	ctrl_cur=buf;
													printf("exit ESC_AddControlInfo();\n");
	return ESC_SUCCESS;
}

ret ESC_DeleteControlInfo(uint8_t esc_num)
{
	/**ESC_DeleteControlInfo() sequence: */
													printf("call ESC_DeleteControlInfo();\n");
	/**declare and initalize value*/
	ret ret_val;
	ESC_ctrlStruct *esc;

	ret_val|=ESC_GetControlInfo(esc_num, &esc);

	/**unlink node*/
	ctrl_prev->next=ctrl_cur->next;
	esc=ctrl_cur;
	ctrl_cur=ctrl_cur->next;
													
	free(esc);/// node remove in memory
													printf("exit ESC_DeleteControlInfo();\n");
	return ret_val;
}

ret ESC_GetControlInfo(uint8_t esc_num, ESC_ctrlStruct **esc)
{
	/**ESC_GetControlInfo() sequence: */
														printf("call ESC_GetControlInfo();\n");

	/**reset position*/
	ESC_ResetCtrlListPosition();

	/**search esc number*/
	while(ctrl_cur!=NULL)
	{
		if(ctrl_cur->num==esc_num)
		{
			/**copy data */
			*esc=ctrl_cur;
			printf("esc data: num: %d, speed: %d, dir: %d\n", (*esc)->num, (*esc)->speed, (*esc)->rotate_dir);
			break;
		}
		else
		{
			ctrl_prev=ctrl_cur;
			ctrl_cur=ctrl_cur->next;
		}
	}
														printf("exit ESC_GetControlInfo();\n");

	if(ctrl_cur==NULL)
	{
		return ESC_UNKNOWN_NUM;
	}
	else
	{
		return ESC_SUCCESS;
	}
}

ret ESC_AddInitalizeInfo(const ESC_initStruct esc)
{
	/**ESC_AddInitalizeInfo() sequence: */
																printf("call ESC_AddInitalizeInfo();\n");
	/**declare and initalize value*/
	ESC_initStruct *buf;

	/**node allocate*/
	buf=(ESC_initStruct*)malloc(sizeof(ESC_initStruct) );
	if(buf==NULL)
	{
																printf("buf is NULL!\n");
		return ESC_MEMALLOC_FAIL;
	}

	/**copy data */
	buf->num=esc.num;
	buf->speed_max=esc.speed_max;
	buf->speed_min=esc.speed_min;

	/**insert new node*/
	init_prev=init_cur;
	buf->next=init_cur->next;
	init_cur->next=buf;
	init_cur=buf;

	BSP_ESC_Initalize(init_cur->num, init_cur->speed_min, init_cur->speed_max);/// ESC initalize(bsp)

	ESC_CountIncrement();/// increment esc count
																	printf("exit ESC_AddInitalizeInfo();\n");
	return ESC_SUCCESS;
}

ret ESC_DeleteInitalizeInfo(uint8_t esc_num)
{
	/**ESC_DeleteInitalizeInfo() sequence: */
																		printf("call ESC_DeleteInitalizeInfo();\n");
	/**declare and initalize value*/
	ret ret_val;
	ESC_initStruct *esc;

	ret_val=ESC_SUCCESS;

	/**get esc initalize info*/
	ret_val|=ESC_GetInitalizeInfo(esc_num, &esc);

	if(ret_val!=ESC_SUCCESS)/// if can't get initalize info
	{
		return ESC_UNKNOWN_NUM;/// return ESC_UNKNOWN_NUM
	}
	else
	{
		/**unlink node*/
		init_prev->next=init_cur->next;
		esc=init_cur;
		init_cur=init_cur->next;

		BSP_ESC_Deinitalize(esc->num);/// esc de-initalize(bsp)

		free(esc);/// node de-allocate

		ESC_CountDecrement();/// decrement esc count
	}
																	printf("exit ESC_DeleteInitalizeInfo();\n");
	return ESC_SUCCESS;
}

ret ESC_GetInitalizeInfo(uint8_t esc_num, ESC_initStruct **esc)
{
	/**ESC_GetInitalizeInfo() sequence: */
																		printf("call ESC_GetInitalizeInfo();\n");
	/**reset position*/
	ESC_ResetInitListPosition();
																		printf("num: %d\n", esc_num);
	/**search esc number*/
	while(init_cur!=NULL)
	{
		if(init_cur->num==esc_num)
		{
			/**copy data */
																printf("init_cur->num: %d\n", init_cur->num);
			*esc=init_cur;
																printf("esc data: num: %d, speed_max: %d, speed_min: %d\n", (*esc)->num, (*esc)->speed_max, (*esc)->speed_min);
			break;
		}
		else
		{
			init_prev=init_cur;
			init_cur=init_cur->next;
		}
	}
																		printf("exit ESC_GetInitalizeInfo();\n");

	if(init_cur==NULL)
	{
		return ESC_UNKNOWN_NUM;
	}
	else
	{
		return ESC_SUCCESS;
	}
}

void ESC_CountIncrement(void)
{
													printf("call ESC_CountIncrement();\n");
	esc_count+=1;
													printf("exit ESC_CountIncrement();\n");
}

void ESC_CountDecrement(void)
{
													printf("call ESC_CountDecrement();\n");
	esc_count-=1;
													printf("exit ESC_CountDecrement();\n");
}

void ESC_ResetCtrlListPosition(void)
{
	/**reset position*/
	ctrl_cur=ctrl_head->next;
	ctrl_prev=ctrl_head;
}

void ESC_ResetInitListPosition(void)
{
	/**reset position*/
	init_cur=init_head->next;
	init_prev=init_head;
}