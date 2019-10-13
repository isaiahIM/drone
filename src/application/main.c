#include <stdio.h>
#include <stdlib.h>

// TODO:
// implement IMU middleware
// implement log, history system
// implement GPS middleware

/*user include header*/
#include "drone_lib.h"
#include "gyro_lib.h"

int main(int argc, char *argv[])
{
	ret ret_val;
	ret_val|=Drone_Init();

	Drone_Arm();
	
	Propeller_CCW_Rotate(PROPELLER_1, 30);
	Propeller_CCW_Rotate(PROPELLER_1, 50);

	Propeller_CCW_Rotate(PROPELLER_2, 40);
	Propeller_CCW_Rotate(PROPELLER_3, 60);
	Propeller_CCW_Rotate(PROPELLER_4, 20);
	Propeller_CCW_Rotate(PROPELLER_2|PROPELLER_3, 56);

	Propeller_CW_Rotate(PROPELLER_1, 30);
	Propeller_CW_Rotate(PROPELLER_1, 50);

	Propeller_CW_Rotate(PROPELLER_2, 40);
	Propeller_CW_Rotate(PROPELLER_3, 60);
	Propeller_CW_Rotate(PROPELLER_2|PROPELLER_3, 56);

	Propeller_Stop(PROPELLER_2);
	Propeller_Stop(PROPELLER_1|PROPELLER_3);

	Propeller_DeConfig(PROPELLER_ALL);



	printf("\n\n-------GYRO----------\n\n");

	Gyro_initStruct gyro1, gyro2, gyro3;
	Gyro_dataStruct g1, g2, g3;
	gyroType_t data_x, data_y, data_z;

	ret_val|=Gyro_Init();

	ret_val|=Gyro_SetNum(&gyro1, 1);
	ret_val|=Gyro_SetResolution(&gyro1, GYRO_RESOLUTION_8BIT);
	ret_val|=Gyro_SetCaptureFreq(&gyro1, 1234);
	ret_val|=Gyro_SetCommunicateFreq(&gyro1, 1234);

	ret_val|=Gyro_SetNum(&gyro2, 2);
	ret_val|=Gyro_SetResolution(&gyro2, GYRO_RESOLUTION_8BIT);
	ret_val|=Gyro_SetCaptureFreq(&gyro2, 1234);
	ret_val|=Gyro_SetCommunicateFreq(&gyro2, 1234);

	ret_val|=Gyro_SetNum(&gyro3, 3);
	ret_val|=Gyro_SetResolution(&gyro3, GYRO_RESOLUTION_8BIT);
	ret_val|=Gyro_SetCaptureFreq(&gyro3, 1234);
	ret_val|=Gyro_SetCommunicateFreq(&gyro3, 1234);

	
	ret_val|=Gyro_AddGyro(gyro1);
	ret_val|=Gyro_AddGyro(gyro2);
	ret_val|=Gyro_AddGyro(gyro3);

	ret_val|=Gyro_ConnectCheck(1);
	ret_val|=Gyro_ConnectCheck(2);
	ret_val|=Gyro_ConnectCheck(3);

	ret_val|=Gyro_GetGyroData(1, &g1);
	ret_val|=Gyro_GetGyroData(2, &g2);
	ret_val|=Gyro_GetGyroData(3, &g3);

	data_x=Gyro_Get_X(g1);
	data_y=Gyro_Get_Y(g1);
	data_z=Gyro_Get_Z(g1);

	printf("\t\tDATA: x: %d, y:%d, z:%d\n", data_x, data_y, data_z);

	data_x=Gyro_Get_X(g2);
	data_y=Gyro_Get_Y(g2);
	data_z=Gyro_Get_Z(g2);

	printf("\t\tDATA: x: %d, y:%d, z:%d\n", data_x, data_y, data_z);


	data_x=Gyro_Get_X(g3);
	data_y=Gyro_Get_Y(g3);
	data_z=Gyro_Get_Z(g3);

	printf("\t\tDATA: x: %d, y:%d, z:%d\n", data_x, data_y, data_z);

	ret_val|=Gyro_DeleteGyro(1);
	ret_val|=Gyro_DeleteGyro(2);
	ret_val|=Gyro_DeleteGyro(3);

	return 0;
}