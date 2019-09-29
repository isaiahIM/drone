/**
 * @file propeller_control.c
 * @author isaiah IM || isaiahim0214@gmail.com
 * @brief propeller control source file
 * @version 0.1
 * @date 2019-09-22
 * 
 * @copyright Copyright (c) 2019 isaiah IM
 * 
 */
#include "propeller_control.h"

ret Propeller_Init(void)
{
	ret ret_val=PROPELLER_OK;

	ret_val|=ESC_Init();

	return ret_val;
}

ret Propeller_Config(uint32_t propeller_num, uint16_t max_speed, uint16_t min_speed, uint8_t propeller_dir)
{
	/**Propeller_Config() sequence: */

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

	
    ret_val|=ESC_SetMaxSpeed(&esc_init, max_speed);
	ret_val|=ESC_SetMinSpeed(&esc_init, min_speed);

    ret_val|=ESC_SetCurrentSpeed(&esc_ctrl, PROPELLER_STOP);
    ret_val|=ESC_SetRotateDir(&esc_ctrl, propeller_dir);
    
	/**esc initalize*/
	while(mask!=0x00)
	{
		if( (mask&propeller_num)!=0 )
		{
											printf("propeller num: %d\n", mask_number);
			ret_val|=ESC_SetInitNum(&esc_init, mask_number);
			ret_val|=ESC_SetCurrentNum(&esc_ctrl, mask_number);

			ret_val|=ESC_AddESC(esc_init, esc_ctrl);
		}
		mask<<=1;
		mask_number++;
	}
											printf("\t\texit Propeller_Init();\n");

	if(ret_val|=PROPELLER_OK)
	{
		ret_val=PROPELLER_CONF_FAIL;
	}

	return ret_val;
}

ret Propeller_DeConfig(uint32_t propeller_num)
{
	/**Propeller_DeConfig() sequence: */

	ret ret_val;
	uint32_t mask;
	uint8_t mask_number;

	ret_val=PROPELLER_OK;
	mask=0x01;
	mask_number=1;
    
	/**esc de-initalize*/
	while(mask!=0x00)
	{
		if( (mask&propeller_num)!=0 )
		{
											printf("propeller num: %d\n", mask_number);
			ret_val|=ESC_DeleteESC(mask_number);
		}
		mask<<=1;
		mask_number++;
	}

	if(ret_val !=PROPELLER_OK)
	{
		ret_val=PROPELLER_DECONF_FAIL;
	}
	return ret_val;
}

ret Propeller_CCW_Rotate(uint32_t propeller_num, uint16_t speed)
{
	/**Propeller_CCW_Rotate() sequence: */

														printf("\t\tcall Propeller_CCW_Rotate();\n");
	/**declare and initalize value*/
	ret ret_val;
	ESC_ctrlStruct esc, *p_esc;
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
			/**set rotate data */
			ret_val|=ESC_SetCurrentNum(&esc, mask_number);
			ret_val|=ESC_SetRotateDir(&esc, ESC_DIR_CCW);
			ret_val|=ESC_SetCurrentSpeed(&esc, speed);

			if(speed<PROPELLER_SPEED_MIN || speed>PROPELLER_SPEED_MAX)
			{
				ret_val|=PROPELLER_ROTATE_FAIL;
				break;
			}

			ret_val|=ESC_Rotate(esc);

			/**check rotate success */
			ret_val|=ESC_GetControlInfo(mask_number, &p_esc);
			
			printf("current speed: %d\n", ESC_GetSpeed(*p_esc));
			printf("current dir: %d\n", ESC_GetRotateDir(*p_esc));
		}
		mask<<=1;
		mask_number++;
	}
													printf("\t\texit Propeller_CCW_Rotate();\n");

	if(ret_val!=PROPELLER_OK)
	{
		ret_val=PROPELLER_ROTATE_FAIL;
	}

	return ret_val;
}

ret Propeller_CW_Rotate(uint32_t propeller_num, uint16_t speed)
{
	/**Propeller_CW_Rotate() sequence:  */
																		printf("\t\tcall Propeller_CW_Rotate\n");
	/**declare and initalize value*/
	ret ret_val;
	ESC_ctrlStruct esc, *p_esc;
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
			/**set rotate data */
			ret_val|=ESC_SetCurrentNum(&esc, mask_number);
			ret_val|=ESC_SetRotateDir(&esc, ESC_DIR_CW);
			ret_val|=ESC_SetCurrentSpeed(&esc, speed);

			if(speed<PROPELLER_SPEED_MIN || speed>PROPELLER_SPEED_MAX)
			{
				ret_val|=PROPELLER_ROTATE_FAIL;
				break;
			}
			/**propeller rotate */
			ret_val|=ESC_Rotate(esc);

			/**check rotate success */
			ESC_GetControlInfo(mask_number, &p_esc);
			
			printf("current speed: %d\n", ESC_GetSpeed(*p_esc));
			printf("current dir: %d\n", ESC_GetRotateDir(*p_esc));
		}
		mask<<=1;
		mask_number++;
	}
													printf("\t\texit Propeller_CW_Rotate\n");
	if(ret_val!=PROPELLER_OK)
	{
		ret_val=PROPELLER_ROTATE_FAIL;
	}

	return ret_val;
}


ret Propeller_Start(uint32_t propeller_num)
{
	/**Propeller_Start() sequence: */
															printf("\t\tcall Propeller_Start\n");
	ret ret_val;
	ESC_ctrlStruct esc, *p_esc;
	uint32_t mask=0x01;
	uint8_t mask_number=1, propeller_dir;

	ret_val=PROPELLER_OK;


	while(mask!=0x00)
	{
		/**propeller arming */
		if( (mask&propeller_num)!=0 )
		{
			ESC_GetControlInfo(mask_number, &p_esc);

			ret_val|=ESC_SetCurrentNum(&esc, mask_number);
			ret_val|=ESC_SetRotateDir(&esc, ESC_GetRotateDir(*p_esc));
			ret_val|=ESC_SetCurrentSpeed(&esc, PROPELLER_SPEED_MIN);

			ret_val|=ESC_Rotate(esc);
															printf("propeller num: %d, speed: %d\n", mask_number, PROPELLER_SPEED_MIN);
		}
		mask<<=1;
		mask_number++;
	}
															printf("\t\texit Propeller_Start\n");
	if(ret_val!=PROPELLER_OK)
	{
		ret_val=PROPELLER_START_FAIL;
	}

	return ret_val;
}

ret Propeller_Stop(uint32_t propeller_num)
{
	/**Propeller_Stop() sequence: */
															printf("\t\tcall Propeller_Stop\n");
	ret ret_val;
	ESC_ctrlStruct esc, *p_esc;
	uint32_t mask=0x01;
	uint8_t mask_number=1, propeller_dir;

	ret_val=PROPELLER_OK;

	/**propeller de-arming */
	while(mask!=0x00)
	{
		if( (mask&propeller_num)!=0 )
		{
			ESC_GetControlInfo(mask_number, &p_esc);

			ret_val|=ESC_SetCurrentNum(&esc, mask_number);
			ret_val|=ESC_SetRotateDir(&esc, ESC_GetRotateDir(*p_esc));
			ret_val|=ESC_SetCurrentSpeed(&esc, PROPELLER_STOP);

			ret_val|=ESC_Rotate(esc);
															printf("propeller num: %d, speed: %d\n", mask_number, PROPELLER_STOP);
		}
		mask<<=1;
		mask_number++;
	}
															printf("\t\texit Propeller_Stop\n");
	if(ret_val!=PROPELLER_OK)
	{
		ret_val=PROPELLER_STOP_FAIL;
	}
	
	return ret_val;
}

