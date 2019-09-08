#include "esc_lib.h"

ret ESC_Init(ESC_initStruct esc)
{
												printf("call ESC_Init();\n");
	/**declare and initalize value*/
	ret ret_val;
	ret_val=ESC_SUCCESS;
	
	ret_val|=ESC_AddInitalizeInfo( (const ESC_initStruct)esc);///< add initalize info
	ESC_ResetInitListPosition();
												printf("exit ESC_Init();\n");
	return ret_val;
}

ret ESC_DeInit(ESC_initStruct esc)
{
												printf("call ESC_DeInit();\n");
	/**declare and initalize value*/
	ret ret_val;
	ret_val=ESC_SUCCESS;

	/**esc nodes deinitalize*/
	ret_val|=ESC_DeleteInitalizeInfo(esc.num);
	ret_val|=ESC_DeleteControlInfo(esc.num);
												printf("exit ESC_DeInit();\n");
	return ret_val;
}

ret ESC_Rotate(ESC_ctrlStruct esc)
{
											printf("call ESC_Rotate();\n");
	/**declare and initalize value*/
	ret ret_val;
	ret buf;
	uint8_t dir;
	ESC_ctrlStruct *esc_buf;

	ret_val=ESC_SUCCESS;

	buf=ESC_GetControlInfo(esc.num, esc_buf);

	/**if first rotate*/
	if(buf == ESC_FIRST_CONTROL)
	{
												printf("ESC_Rotate: first control!\n");
		ret_val|=ESC_AddControlInfo(esc);///< insert node
	}
	else if(buf == ESC_UNKNOWN_NUM)
	{
												printf("ESC_Rotate: unknown esc number\n");
		return ESC_UNKNOWN_NUM;
	}
	
	ret_val|=ESC_GetRotateDirection(esc.num, &dir);///< get control info

	/**rotation dirction check*/
	if(dir==ESC_DIR_CW)
	{
		BSP_ESC_RotateCW(esc.num, esc.speed);
	}
	else
	{
		BSP_ESC_RotateCCW(esc.num, esc.speed);
	}
	
												printf("exit ESC_Rotate();\n");
	return ret_val;
}

ret ESC_GetRotateDirection(uint8_t esc_num, uint8_t *motor_dir)
{
												printf("call ESC_GetRotateDirection();\n");
	/**declare and initalize value*/
	ret ret_val;
	ESC_ctrlStruct esc;

	ret_val=ESC_SUCCESS;

	ret_val|=ESC_GetControlInfo(esc_num, &esc);///< get control info
	
	*motor_dir=esc.rotate_dir;///< get rotation info

													printf("ESC_GetRotateDirection: esc rotate dir1: %d\n", *motor_dir);
													printf("exit ESC_GetRotateDirection();\n");
	return ret_val;
}

ret ESC_AddControlInfo(const ESC_ctrlStruct esc)
{
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

	/**struct copy*/
	buf->num=esc.num;
	buf->speed=esc.speed;
	buf->rotate_dir=esc.rotate_dir;

	/**if first insert*/
	if(ctrl_head==NULL)
	{
													printf("ESC_AddControlInfo: first insert\n");
		/**make dummy node*/
		ctrl_prev=ctrl_head;
		ctrl_head=(ESC_ctrlStruct*)malloc(sizeof(ESC_ctrlStruct) );
		ctrl_cur=ctrl_head;
	}


	/**insert new node*/
	ctrl_prev=ctrl_cur;
	ctrl_cur->next=buf;
	ctrl_cur=buf;
	buf->next=NULL;
													printf("ESC_AddControlInfo:\n");
													printf("num: %d, speed: %d, dir: %d\n", ctrl_cur->num, ctrl_cur->speed, ctrl_cur->rotate_dir);
													printf("exit ESC_AddControlInfo();\n");
	return ESC_SUCCESS;
}

ret ESC_DeleteControlInfo(uint8_t esc_num)
{
													printf("call ESC_DeleteControlInfo();\n");
	/**declare and initalize value*/
	ret ret_val;
	ESC_ctrlStruct *esc;

	ret_val|=ESC_GetControlInfo(esc_num, esc);

	/**unlink node*/
	ctrl_prev->next=ctrl_cur->next;
	ctrl_cur=ctrl_cur->next;
	esc->next=NULL;
	ctrl_prev=ctrl_cur;
													printf("ESC_DeleteControlInfo:\n");
													printf("num: %d, speed: %d, dir: %d\n", ctrl_cur->num, ctrl_cur->speed, ctrl_cur->rotate_dir);
	free(esc);///< node de-allocate
													printf("exit ESC_DeleteControlInfo();\n");
	return ret_val;
}

ret ESC_GetControlInfo(uint8_t esc_num, ESC_ctrlStruct *esc)
{
														printf("call ESC_GetControlInfo();\n");
	ESC_initStruct *buf;

	/**if unknown esc*/
	if(ESC_GetInitalizeInfo(esc_num, buf)==ESC_UNKNOWN_NUM)
	{
		return ESC_UNKNOWN_NUM;///< return ESC_UNKNOWN_NUM
	}

	/**if first control*/
	if(ctrl_cur==NULL)
	{
		return ESC_FIRST_CONTROL;///< return ESC_FIRST_CONTROL
	}

	/**reset position*/
	ESC_ResetCtrlListPosition();

	/**search esc number*/
	while(ctrl_cur!=NULL)
	{
		if(ctrl_cur->num==esc_num)
		{
			esc=ctrl_cur;
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
		ESC_ResetCtrlListPosition();
		return ESC_FIRST_CONTROL;///< return ESC_FIRST_CONTROL
	}
	else
	{
		ESC_ResetCtrlListPosition();
		return ESC_SUCCESS;
	}
	
}


ret ESC_AddInitalizeInfo(const ESC_initStruct esc)
{
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

	buf->num=esc.num;
	buf->speed_max=esc.speed_max;
	buf->speed_min=esc.speed_min;

	/**if first insert*/
	if(init_head==NULL)
	{
		/**make dummy node*/
		init_prev=init_head;
		init_head=(ESC_initStruct*)malloc(sizeof(ESC_initStruct) );
		init_cur=init_head;
	}

	/**insert new node*/
	init_prev=init_cur;
	init_cur->next=buf;
	init_cur=buf;
	buf->next=NULL;

	BSP_ESC_Initalize(init_cur->num, init_cur->speed_min, init_cur->speed_max);///< ESC initalize(bsp)

	ESC_CountIncrement();///< increment esc count
																	printf("exit ESC_AddInitalizeInfo();\n");

	return ESC_SUCCESS;
}

ret ESC_DeleteInitalizeInfo(uint8_t esc_num)
{
																		printf("call ESC_DeleteInitalizeInfo();\n");
	/**declare and initalize value*/
	ret ret_val;
	ESC_initStruct *esc;

	ret_val=ESC_SUCCESS;

	/**get esc initalize info*/
	ret_val|=ESC_GetInitalizeInfo(esc_num, esc);

	if(ret_val!=ESC_SUCCESS)///< if can't get initalize info
	{
		return ESC_UNKNOWN_NUM;///< return ESC_UNKNOWN_NUM
	}
	else
	{
		/**unlink node*/
		init_prev->next=init_cur->next;
		init_cur=init_cur->next;
		esc->next=NULL;

		BSP_ESC_Deinitalize(esc->num);///< esc de-initalize(bsp)

		free(esc);///< node de-allocate

		ESC_CountDecrement();///< decrement esc count
	}
																	printf("exit ESC_DeleteInitalizeInfo();\n");
	return ESC_SUCCESS;
}

ret ESC_GetInitalizeInfo(uint8_t esc_num, ESC_initStruct *esc)
{
																		printf("call ESC_GetInitalizeInfo();\n");
	/**reset position*/
	ESC_ResetInitListPosition();
																		printf("num: %d\n", esc_num);
	/**search esc number*/
	while(init_cur!=NULL)
	{
		if(init_cur->num==esc_num)
		{
			esc=init_cur;
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
		ESC_ResetInitListPosition();
		return ESC_UNKNOWN_NUM;
	}
	else
	{
		ESC_ResetInitListPosition();
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