#include "esc_driver.h"

ret ESC_Init(ESC_initStruct esc)
{
	ret ret_val;
	ret_val=ESC_SUCCESS;
	
	return ret_val;
}

ret ESC_DeInit(ESC_initStruct esc)
{
	
}

ret ESC_Rotate(ESC_ctrlStruct esc)
{
	ret ret_val;
	ret_val=ESC_SUCCESS;
	
	return ret_val;
}


ret ESC_AddControlInfo(const ESC_ctrlStruct esc)
{
	ESC_ctrlStruct *buf;

	/**node allocate*/
	buf=(ESC_ctrlStruct*)malloc(sizeof(ESC_ctrlStruct) );

	memcpy((void*)buf, (void*)&esc, (int)sizeof(ESC_ctrlStruct) );

	if(buf==NULL)
	{
		return ESC_MEMALLOC_FAIL;
	}

	/**if first insert*/
	if(ctrl_head==NULL)
	{
		/**make dummy node*/
		ctrl_prev=ctrl_head;
		ctrl_head=buf;
		ctrl_cur=cur_head;
	}

	/**insert new node*/
	ctrl_prev=ctrl_cur;
	ctrl_cur->next=buf;
	ctrl_cur=ctrl_cur->next;
	ctrl_cur->next=NULL;

	ESC_CountIncrement();
	
	return ESC_SUCCESS;
}

ret ESC_GetControlInfo(uint8_t esc_num, ESC_ctrlStruct *esc)
{
	/**reset position*/
	ctrl_cur=ctrl_head->next;
	ctrl_prev=ctrl_head;

	/**search esc number*/
	do
	{
		if(ctrl_cur->num==esc_num)
		{
			break;
		}
		else
		{
			ctrl_prev=ctrl_cur;
			ctrl_cur=ctrl_cur->next;
		}

	}while(ctrl_cur!=NULL)

	esc=ctrl_cur;///< copy result

	/**return value*/
	if(ctrl_cur==NULL)
	{
		return ESC_UNKNOWN_NUM;
	}
	else
	{
		return ESC_SUCCESS;
	}
}

/*
TODO:
DUMMY NODE based list implement!! 
*/


// typedef struct ESC_initalize_structure
// {
// 	uint32_t num;///< esc number
// 	uint16_t speed_max;///< esc maximum speed
// 	uint16_t speed_min;///< esc munumum speed
// 	struct ESC_initalize_structure *next;///< list link
// } ESC_initStruct;
// /**ESC_initStruct position*/
// static ESC_initStruct *init_head=NULL;
// static ESC_initStruct *init_cur=NULL;
// static ESC_initStruct *init_prev=NULL;
ret ESC_AddInitalizeInfo(const ESC_initStruct esc)
{
}

/*
TODO:
DUMMY NODE based list implement!! 
*/
ret ESC_GetInitalizeInfo(uint8_t esc_num, ESC_initStruct *esc)
{	
}

void ESC_CountIncrement(void)
{
	esc_count+=1;
}

void Ese_CountDecrement(void)
{
	esc_count-=1;
}