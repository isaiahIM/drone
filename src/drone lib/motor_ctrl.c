#include "motor_ctrl.h"

ret Motor_Init(uint32_t motor_num, uint16_t max_speed, uint16_t min_speed)
{
												printf("\t\tcall Motor_Init();\n");
	/**declare and initalize value*/
	ESC_initStruct esc;
	ret ret_val;
	uint32_t mask;
	uint8_t mask_number;

	ret_val=MOTOR_OK;
	mask=0x01;
	mask_number=1;
	esc.speed_max=max_speed;
	esc.speed_min=min_speed;

	/**esc initalize*/
	while(mask!=0x00)
	{
		if( (mask&motor_num)!=0 )
		{
											printf("motor num: %d\n", mask_number);
			esc.num=mask_number;
			ret_val|=ESC_Init(esc);
		}
		mask<<=1;
		mask_number++;
	}
											printf("\t\texit Motor_Init();\n");
	return ret_val;
}


ret Motor_CCW_Rotate(uint32_t motor_num, uint16_t speed)
{
														printf("\t\tcall Motor_CCW_Rotate();\n");
	/**declare and initalize value*/
	ret ret_val;
	ESC_ctrlStruct esc;
	uint32_t mask;
	uint8_t mask_number;

	ret_val=MOTOR_OK;
	mask=0x01;
	mask_number=1;

	while(mask!=0x00)
	{
		if( (mask&motor_num)!=0 )
		{
													printf("motor num: %d, speed: %d\n", mask_number, speed);
			esc.num=mask_number;
			esc.speed=speed;
			esc.rotate_dir=ESC_DIR_CCW;

			ret_val|=ESC_Rotate(esc);
		}
		mask<<=1;
		mask_number++;
	}
													printf("\t\texit Motor_CCW_Rotate();\n");
	return ret_val;
}

ret Motor_CW_Rotate(uint32_t motor_num, uint16_t speed)
{
																		printf("\t\tcall Motor_CW_Rotate\n");
	/**declare and initalize value*/
	ret ret_val;
	ESC_ctrlStruct esc;
	uint32_t mask;
	uint8_t mask_number;

	ret_val=MOTOR_OK;
	mask=0x01;
	mask_number=1;

	while(mask!=0x00)
	{
		if( (mask&motor_num)!=0 )
		{
												printf("motor num: %d, speed: %d\n", mask_number, speed);
			esc.num=mask_number;
			esc.speed=speed;
			esc.rotate_dir=ESC_DIR_CW;

			ret_val|=ESC_Rotate(esc);
		}
		mask<<=1;
		mask_number++;
	}
													printf("\t\texitMotor_CW_Rotate\n");
	return ret_val;
}


ret Motor_Start(uint32_t motor_num)
{
															printf("\t\tcall Motor_Start\n");
	ret ret_val;
	ESC_ctrlStruct esc;
	uint32_t mask=0x01;
	uint8_t mask_number=1, motor_dir;

	ret_val=MOTOR_OK;

	while(mask!=0x00)
	{
		if( (mask&motor_num)!=0 )
		{
			ret_val|=ESC_GetRotateDirection(mask_number, &motor_dir);

			esc.num=mask_number;
			esc.speed=MOTOR_SPEED_MIN;
			esc.rotate_dir=motor_dir;

			ret_val|=ESC_Rotate(esc);
															printf("motor num: %d, speed: %d\n", mask_number, MOTOR_SPEED_MIN);
		}
		mask<<=1;
		mask_number++;
	}
															printf("\t\texit Motor_Start\n");
	return ret_val;
}

ret Motor_Stop(uint32_t motor_num)
{
															printf("\t\tcall Motor_Stop\n");
	ret ret_val;
	ESC_ctrlStruct esc;
	uint32_t mask=0x01;
	uint8_t mask_number=1, motor_dir;

	ret_val=MOTOR_OK;

	while(mask!=0x00)
	{
		if( (mask&motor_num)!=0 )
		{
			ret_val|=ESC_GetRotateDirection(mask_number, &motor_dir);

			esc.num=mask_number;
			esc.speed=MOTOR_STOP;
			esc.rotate_dir=motor_dir;

			ret_val|=ESC_Rotate(esc);
															printf("motor num: %d, speed: %d\n", mask_number, MOTOR_STOP);
		}
		mask<<=1;
		mask_number++;
	}
															printf("\t\texit Motor_Stop\n");
	return ret_val;
}

