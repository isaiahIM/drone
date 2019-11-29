#include <stdio.h>
#include <stdlib.h>

// TODO:
// implement IMU middleware
// implement log, history system
// implement GPS middleware

/*user include header*/
#include "drone_lib.h"
#include "gyro_lib.h"
#include "config.h"
#include "accel_lib.h"
#include "compass_lib.h"

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

	Propeller_Terminate();



	printf("\n\n-------GYRO----------\n\n");

	Gyro_initStruct *gyro1, *gyro2, *gyro3;
	Gyro_dataStruct *g1, *g2, *g3;
	gyroType_t gdata_x, gdata_y, gdata_z;

	ret_val|=Gyro_Init(GYRO_CNT);

	ret_val|=Gyro_GetInitalizeInfo(0, &gyro1);
	ret_val|=Gyro_GetInitalizeInfo(1, &gyro2);
	ret_val|=Gyro_GetInitalizeInfo(2, &gyro3);

	ret_val|=Gyro_GetDataInfo(0, &g1);
	ret_val|=Gyro_GetDataInfo(1, &g2);
	ret_val|=Gyro_GetDataInfo(2, &g3);

	ret_val|=Gyro_SetResolution(gyro1, 1);
	ret_val|=Gyro_SetCaptureFreq(gyro1, 1234);
	ret_val|=Gyro_SetCommunicateFreq(gyro1, 1234);


	ret_val|=Gyro_SetResolution(gyro2, 1);
	ret_val|=Gyro_SetCaptureFreq(gyro2, 1234);
	ret_val|=Gyro_SetCommunicateFreq(gyro2, 1234);


	ret_val|=Gyro_SetResolution(gyro3, 1);
	ret_val|=Gyro_SetCaptureFreq(gyro3, 1234);
	ret_val|=Gyro_SetCommunicateFreq(gyro3, 1234);


	ret_val|=Gyro_ChkConnect(1);
	ret_val|=Gyro_ChkConnect(2);
	ret_val|=Gyro_ChkConnect(3);

	ret_val|=Gyro_UpdateData(0, g1);
	ret_val|=Gyro_UpdateData(1, g2);
	ret_val|=Gyro_UpdateData(2, g3);

	gdata_x=Gyro_Get_X(*g1);
	gdata_y=Gyro_Get_Y(*g1);
	gdata_z=Gyro_Get_Z(*g1);

	printf("\t\tDATA: x: %d, y:%d, z:%d\n", gdata_x, gdata_y, gdata_z);
	printf("roll: %f, pitch: %f, yaw: %f\n", Gyro_GetRoll(*g1), Gyro_GetPitch(*g1), Gyro_GetYaw(*g1));
	
	gdata_x=Gyro_Get_X(*g2);
	gdata_y=Gyro_Get_Y(*g2);
	gdata_z=Gyro_Get_Z(*g2);

	printf("\t\tDATA: x: %d, y:%d, z:%d\n", gdata_x, gdata_y, gdata_z);
	printf("roll: %f, pitch: %f, yaw: %f\n", Gyro_GetRoll(*g2), Gyro_GetPitch(*g2), Gyro_GetYaw(*g2));

	gdata_x=Gyro_Get_X(*g3);
	gdata_y=Gyro_Get_Y(*g3);
	gdata_z=Gyro_Get_Z(*g3);

	printf("\t\tDATA: x: %d, y:%d, z:%d\n", gdata_x, gdata_y, gdata_z);
	printf("roll: %f, pitch: %f, yaw: %f\n", Gyro_GetRoll(*g3), Gyro_GetPitch(*g3), Gyro_GetYaw(*g3));

	Gyro_Terminate();


printf("\n\n-------ACCLE----------\n\n");

	Accel_initStruct *accel1, *accel2, *accel3;
	Accel_dataStruct *a1, *a2, *a3;
	accelType_t adata_x, adata_y, adata_z;

	ret_val|=Accel_Init(ACCEL_CNT);


	ret_val|=Accel_GetInitalizeInfo(0, &accel1);
	ret_val|=Accel_GetInitalizeInfo(1, &accel2);
	ret_val|=Accel_GetInitalizeInfo(2, &accel3);

	ret_val|=Accel_GetDataInfo(0, &a1);
	ret_val|=Accel_GetDataInfo(1, &a2);
	ret_val|=Accel_GetDataInfo(2, &a3);

	ret_val|=Accel_SetResolution(accel1, 1);
	ret_val|=Accel_SetCaptureFreq(accel1, 1234);
	ret_val|=Accel_SetCommunicateFreq(accel1, 1234);

	ret_val|=Accel_SetResolution(accel2, 1);
	ret_val|=Accel_SetCaptureFreq(accel2, 1234);
	ret_val|=Accel_SetCommunicateFreq(accel2, 1234);

	ret_val|=Accel_SetResolution(accel3, 1);
	ret_val|=Accel_SetCaptureFreq(accel3, 1234);
	ret_val|=Accel_SetCommunicateFreq(accel3, 1234);

	ret_val|=Accel_ChkConnect(0);
	ret_val|=Accel_ChkConnect(1);
	ret_val|=Accel_ChkConnect(2);

	ret_val|=Accel_UpdateData(0, a1);
	ret_val|=Accel_UpdateData(1, a2);
	ret_val|=Accel_UpdateData(2, a3);

	adata_x=Accel_Get_X(*a1);
	adata_y=Accel_Get_Y(*a1);
	adata_z=Accel_Get_Z(*a1);

	printf("\t\tDATA: x: %d, y:%d, z:%d\n", adata_x, adata_y, adata_z);
	printf("roll: %f, pitch: %f\n", Accel_GetRoll(*a1), Accel_GetPitch(*a1) );

	adata_x=Accel_Get_X(*a2);
	adata_y=Accel_Get_Y(*a2);
	adata_z=Accel_Get_Z(*a2);

	printf("\t\tDATA: x: %d, y:%d, z:%d\n", adata_x, adata_y, adata_z);
	printf("roll: %f, pitch: %f\n", Accel_GetRoll(*a2), Accel_GetPitch(*a2) );


	adata_x=Accel_Get_X(*a3);
	adata_y=Accel_Get_Y(*a3);
	adata_z=Accel_Get_Z(*a3);

	printf("\t\tDATA: x: %d, y:%d, z:%d\n", adata_x, adata_y, adata_z);
	printf("roll: %f, pitch: %f\n", Accel_GetRoll(*a3), Accel_GetPitch(*a3) );

	Accel_Terminate();



	printf("\n\n-------COMPASS----------\n\n");

	Compass_initStruct *compass1, *compass2, *compass3;
	Compass_dataStruct *c1, *c2, *c3;
	compassType_t cdata_x, cdata_y, cdata_z;

	ret_val|=Compass_Init(COMPASS_CNT);


	ret_val|=Compass_GetInitalizeInfo(0, &compass1);
	ret_val|=Compass_GetInitalizeInfo(1, &compass2);
	ret_val|=Compass_GetInitalizeInfo(2, &compass3);

	ret_val|=Compass_GetDataInfo(0, &c1);
	ret_val|=Compass_GetDataInfo(1, &c2);
	ret_val|=Compass_GetDataInfo(2, &c3);


	ret_val|=Compass_SetResolution(compass1, 1);
	ret_val|=Compass_SetCaptureFreq(compass1, 1234);
	ret_val|=Compass_SetCommunicateFreq(compass1, 1234);

	ret_val|=Compass_SetResolution(compass2, 1);
	ret_val|=Compass_SetCaptureFreq(compass2, 1234);
	ret_val|=Compass_SetCommunicateFreq(compass2, 1234);

	ret_val|=Compass_SetResolution(compass3, 1);
	ret_val|=Compass_SetCaptureFreq(compass3, 1234);
	ret_val|=Compass_SetCommunicateFreq(compass3, 1234);


	ret_val|=Compass_ChkConnect(0);
	ret_val|=Compass_ChkConnect(1);
	ret_val|=Compass_ChkConnect(2);

	ret_val|=Compass_UpdateData(1, c1);
	ret_val|=Compass_UpdateData(2, c2);
	ret_val|=Compass_UpdateData(3, c3);

	cdata_x=Compass_Get_X(*c1);
	cdata_y=Compass_Get_Y(*c1);
	cdata_z=Compass_Get_Z(*c1);

	printf("\t\tDATA: x: %d, y:%d, z:%d\n", cdata_x, cdata_y, cdata_z);
	printf("roll: %f, pitch: %f, yaw: %f\n", Compass_GetRoll(*c1), Compass_GetPitch(*c1), Compass_GetYaw(*c1));

	cdata_x=Compass_Get_X(*c2);
	cdata_y=Compass_Get_Y(*c2);
	cdata_z=Compass_Get_Z(*c2);

	printf("\t\tDATA: x: %d, y:%d, z:%d\n", cdata_x, cdata_y, cdata_z);
	printf("roll: %f, pitch: %f, yaw: %f\n", Compass_GetRoll(*c2), Compass_GetPitch(*c2), Compass_GetYaw(*c2));


	cdata_x=Compass_Get_X(*c3);
	cdata_y=Compass_Get_Y(*c3);
	cdata_z=Compass_Get_Z(*c3);

	printf("\t\tDATA: x: %d, y:%d, z:%d\n", cdata_x, cdata_y, cdata_z);
	printf("roll: %f, pitch: %f, yaw: %f\n", Compass_GetRoll(*c3), Compass_GetPitch(*c3), Compass_GetYaw(*c3));

	Compass_Terminate();

uint8_t hour, min, sec;
uint16_t year;
uint8_t month, date, day;

	ret_val|=Time_Init();
	ret_val|=Time_SetCurDate(2019, NOV, 2, 2);
	ret_val|=Time_SetCurTime(10, 10, 10);
	ret_val|=Time_GetCurDate(&year, &month, &date, &day);
	ret_val|=Time_GetCurTime(&hour, &min, &sec);
	printf("runtime(sec): %f, runtime(ms): %f\n", Time_GetRunTimeSec(), Time_GetRunTimeMillis() );

	printf("year: %d, mon: %d, date: %d, day: %d\nh: %d, m: %d, s: %d\n", year, month, date, day, hour, min, sec);


printf("\t\tproccess finish!!\n");
	return 0;
}