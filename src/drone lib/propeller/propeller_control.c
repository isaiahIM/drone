#include "propeller_control.h"

ret Propeller_HW_Init(void)
{
	ret ret_val=PROPELLER_OK;

	ret_val|=ESC_HW_Init();

	return ret_val;
}

ret Propeller_SW_Init(void)
{
	ret ret_val=PROPELLER_OK;

	ret_val|=ESC_SystemInit();

	return ret_val;
}

ret Propeller_Init(uint32_t propeller_num, uint16_t max_speed, uint16_t min_speed)
{
												printf("\t\tcall Propeller_Init();\n");
	/**declare and initalize value*/
	ESC_initStruct esc_init;
	ESC_ctrlStruct esc_ctrl;

	ret ret_val;
	uint32_t mask;
	uint8_t mask_number;

	ret_val=PROPELLER_OK;
	mask=0x01;
	mask_number=1;

	
    ESC_SetMaxSpeed(&esc_init, max_speed);
	ESC_SetMinSpeed(&esc_init, min_speed);

    ESC_SetCurrentSpeed(&esc_ctrl, PROPELLER_STOP);
    ESC_SetRotateDir(&esc_ctrl, PROPELLER_DIR_CW);
    
	/**esc initalize*/
	while(mask!=0x00)
	{
		if( (mask&propeller_num)!=0 )
		{
											printf("propeller num: %d\n", mask_number);
			ESC_SetInitNum(&esc_init, mask_number);
			ESC_SetCurrentNum(&esc_ctrl, mask_number);

			ESC_AddInfo(esc_init, esc_ctrl);
		}
		mask<<=1;
		mask_number++;
	}
											printf("\t\texit Propeller_Init();\n");
	return ret_val;
}

ret Propeller_DeInit(uint32_t propeller_num)
{
	ret ret_val;
	uint32_t mask;
	uint8_t mask_number;

	ret_val=PROPELLER_OK;
	mask=0x01;
	mask_number=1;
    
	/**esc initalize*/
	while(mask!=0x00)
	{
		if( (mask&propeller_num)!=0 )
		{
											printf("propeller num: %d\n", mask_number);
			ESC_DeleteInfo(mask_number);
		}
		mask<<=1;
		mask_number++;
	}
}

ret Propeller_CCW_Rotate(uint32_t propeller_num, uint16_t speed)
{
														printf("\t\tcall Propeller_CCW_Rotate();\n");
	/**declare and initalize value*/
	ret ret_val;
	ESC_ctrlStruct esc;
	uint32_t mask;
	uint8_t mask_number;

	ret_val=PROPELLER_OK;
	mask=0x01;
	mask_number=1;

	while(mask!=0x00)
	{
		if( (mask&propeller_num)!=0 )
		{
													printf("propeller num: %d, speed: %d\n", mask_number, speed);
			ESC_SetCurrentNum(&esc, mask_number);
			ESC_SetRotateDir(&esc, ESC_DIR_CCW);
			ESC_SetCurrentSpeed(&esc, speed);

			ret_val|=ESC_Rotate(esc);

			printf("current speed: %d\n", ESC_GetCurrentSpeed(mask_number));
			printf("current dir: %d\n", ESC_GetCurrentDir(mask_number));
		}
		mask<<=1;
		mask_number++;
	}
													printf("\t\texit Propeller_CCW_Rotate();\n");
	return ret_val;
}

ret Propeller_CW_Rotate(uint32_t propeller_num, uint16_t speed)
{
																		printf("\t\tcall Propeller_CW_Rotate\n");
	/**declare and initalize value*/
	ret ret_val;
	ESC_ctrlStruct esc;
	uint32_t mask;
	uint8_t mask_number;

	ret_val=PROPELLER_OK;
	mask=0x01;
	mask_number=1;

	while(mask!=0x00)
	{
		if( (mask&propeller_num)!=0 )
		{
												printf("propeller num: %d, speed: %d\n", mask_number, speed);
			ESC_SetCurrentNum(&esc, mask_number);
			ESC_SetRotateDir(&esc, ESC_DIR_CW);
			ESC_SetCurrentSpeed(&esc, speed);

			ret_val|=ESC_Rotate(esc);

			printf("current speed: %d\n", ESC_GetCurrentSpeed(mask_number));
			printf("current dir: %d\n", ESC_GetCurrentDir(mask_number));
		}
		mask<<=1;
		mask_number++;
	}
													printf("\t\texit Propeller_CW_Rotate\n");
	return ret_val;
}


ret Propeller_Start(uint32_t propeller_num)
{
															printf("\t\tcall Propeller_Start\n");
	ret ret_val;
	ESC_ctrlStruct esc;
	uint32_t mask=0x01;
	uint8_t mask_number=1, propeller_dir;

	ret_val=PROPELLER_OK;

	while(mask!=0x00)
	{
		if( (mask&propeller_num)!=0 )
		{
			ESC_SetCurrentNum(&esc, mask_number);
			ESC_SetRotateDir(&esc, ESC_DIR_CW);
			ESC_SetCurrentSpeed(&esc, PROPELLER_SPEED_MIN);

			ret_val|=ESC_Rotate(esc);
															printf("propeller num: %d, speed: %d\n", mask_number, PROPELLER_SPEED_MIN);
		}
		mask<<=1;
		mask_number++;
	}
															printf("\t\texit Propeller_Start\n");
	return ret_val;
}

ret Propeller_Stop(uint32_t propeller_num)
{
															printf("\t\tcall Propeller_Stop\n");
	ret ret_val;
	ESC_ctrlStruct esc;
	uint32_t mask=0x01;
	uint8_t mask_number=1, propeller_dir;

	ret_val=PROPELLER_OK;

	while(mask!=0x00)
	{
		if( (mask&propeller_num)!=0 )
		{
			ESC_SetCurrentNum(&esc, mask_number);
			ESC_SetRotateDir(&esc, ESC_DIR_CW);
			ESC_SetCurrentSpeed(&esc, PROPELLER_STOP);

			ret_val|=ESC_Rotate(esc);
															printf("propeller num: %d, speed: %d\n", mask_number, PROPELLER_STOP);
		}
		mask<<=1;
		mask_number++;
	}
															printf("\t\texit Propeller_Stop\n");
	return ret_val;
}

