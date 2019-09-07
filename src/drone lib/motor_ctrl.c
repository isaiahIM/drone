#include "motor_ctrl.h"

ret Motor_Init(ESC_initStruct esc)
{
	/**value initalize*/
	ret ret_val;
	uint32_t mask=0x80000000;
	ret_val=MOTOR_OK;

	/**esc initalize*/
	do
	{
		if( (mask&esc.num)!=0 )
		{
			esc.num=mask;
			ESC_Init(esc);
		}
		mask>>=1;

	}while(mask!=0x00);
	
	return ret_val;
}


ret Motor_CCW_Rotate(uint32_t motor_num, uint8_t speed)
{
	ret ret_val;

	ESC_ctrlStruct esc;

	esc.num=motor_num;
	esc.speed=speed;
	esc.rotate_dir=ESC_DIR_CCW;
	
	ret_val=ESC_Rotate(esc);

	return ret_val
}

ret Motor_CW_Rotate(uint32_t motor_num, uint8_t speed)
{
	ret ret_val;

	ESC_ctrlStruct esc;

	esc.num=motor_num;
	esc.speed=speed;
	esc.rotate_dir=ESC_DIR_CW;
	
	ret_val=ESC_Rotate(esc);

	return ret_val
}


ret Motor_Start(uint32_t motor_num)
{
	ret ret_val;

	ESC_ctrlStruct esc;

	esc.num=motor_num;
	esc.speed=MOTOR_SPEED_MIN;
	esc.rotate_dir=ESC_GetRotateDirection(motor_num);
	
	ret_val=ESC_Rotate(esc);
	
	return ret_val;
}

ret Motor_Stop(uint32_t motor_num)
{
	ret ret_val;

	ESC_ctrlStruct esc;
	
	esc.num=motor_num;
	esc.speed=MOTOR_STOP;
	esc.rotate_dir=ESC_GetRotateDirection(motor_num);;
	
	ret_val=ESC_Rotate(esc);
	
	return ret_val;
}

