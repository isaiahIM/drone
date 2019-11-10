#include "imu.h"

IMU_dataStruct *IMU;

ret IMU_Init(uint8_t imu_count)
{
    /**IMU_Init() sequence: */

    /**declare values */
    ret ret_val=IMU_SUCCESS;
    int i;
    Gyro_initStruct gyro;
    Accel_initStruct acc;
    Compass_initStruct comp;
    Kalman_initStruct kalman;

    /**IMU memory allocate */
    IMU=calloc(imu_count,sizeof(IMU_dataStruct));
    if(IMU==NULL)
    {
                                                                printf("IMU allocate fail!!\n");
        return IMU_FAIL;
    }

    /**IMU H/W initalze */
    ret_val|=Gyro_Init();
    ret_val|=Accel_Init();
    ret_val|=Compass_Init();

    /**IMU resolution set */
    ret_val|=Gyro_SetResolution(&gyro, 12);
    ret_val|=Accel_SetResolution(&acc, 12);
    ret_val|=Compass_SetResolution(&comp, 12);

    /**IMU capture frequency set */
    ret_val|=Gyro_SetCaptureFreq(&gyro, 100);
    ret_val|=Accel_SetCaptureFreq(&acc, 100);
    ret_val|=Compass_SetCaptureFreq(&comp, 100);

    /**IMU communication frequency set */
    ret_val|=Gyro_SetCommunicateFreq(&gyro, 100);
    ret_val|=Accel_SetCommunicateFreq(&acc, 100);
    ret_val|=Compass_SetCommunicateFreq(&comp, 100);


    for(i=0; i<imu_count; i++)
    {
        /**IMU connect check */
        if(IMU_ChkConnect(i)!=IMU_CONNECTED)
        {
            printf("IMU[%d] is not connect!!\n", i);
            return IMU_FAIL;
        }

        /**IMU numbering */
        ret_val|=Gyro_SetNum(&gyro, i);
        ret_val|=Accel_SetNum(&acc, i);
        ret_val|=Compass_SetNum(&comp, i);

        /**update IMU setting values */
        ret_val|=Gyro_AddGyro(gyro);
        ret_val|=Accel_AddAccel(acc);
        ret_val|=Compass_AddCompass(comp);

        /**kalman filter setting */
        Kalman_Add(i, kalman);
    }

    return ret_val;
}

ret IMU_ChkConnect(uint8_t num)
{
    /**IMU_ChkConnect() sequence: */
    
    ret ret_val=IMU_CONNECTED;

    /**gyroscope connect check */
    if(Gyro_ChkConnect(num)!=GYRO_CONNECTED)
    {
        printf("gyro[%d] is not connect!\n", num);
        ret_val|=IMU_DISCONNECTED;
    }

    /**accelerator connect check */
    if(Accel_ChkConnect(num)!=ACCEL_CONNECTED)
    {    
        printf("accel[%d] is not connect!\n", num);
        ret_val|=IMU_DISCONNECTED;
    }

    /**compass connect check */
    if(Compass_ChkConnect(num)!=COMPASS_CONNECTED)
    {
        printf("compass[%d] is not connect!\n", num);
        ret_val|=IMU_DISCONNECTED;
    }

    return ret_val;
}


ret IMU_UpdateData(uint8_t num)
{
    /**IMU_UpdateData() sequence: */

    /**declare values */
    ret ret_val;
    Gyro_initStruct gyro;
    Accel_initStruct acc;
    Compass_initStruct comp;
    double roll, pitch, yaw;

    /**update gyroscope data */
    ret_val|=Gyro_UpdateData(num, &gyro);

    /**update accelerator data */
    ret_val|=Accel_UpdateData(num, &acc);

    /**update compass data */
    ret_val|=Compass_UpdateData(num, &comp);

    /**calculate roll/pitch/yaw */
    roll=Kalman_GetRoll(num, Gyro_GetRoll(gyro), Accel_GetRoll(acc), Compass_GetRoll(comp) );
    pitch=Kalman_GetPitch(num, Gyro_GetPitch(gyro), Accel_GetPitch(acc), Compass_GetPitch(comp) );
    yaw=Kalman_GetYaw(num, Gyro_GetYaw(gyro), Compass_GetYaw(comp) );

    /**make corrections roll errors */
    roll-=roll_zero;
    if(roll>=0)
    {
        roll*=roll_inc_scale;
    }
    else
    {
        roll*=roll_dec_scale;
    }

    /**make corrections pitch errors */
    pitch-=pitch_zero;
    if(pitch>=0)
    {
        pitch*=pitch_inc_scale;
    }
    else
    {
        pitch*=pitch_dec_scale;
    }

    /**make corrections yaw errors */
    yaw-=yaw_zero;
    if(yaw>=0)
    {
        yaw*=yaw_inc_scale;
    }
    else
    {
        yaw*=yaw_dec_scale;
    }

    /**update roll/pitch/yaw */
    IMU[num].roll=roll;
    IMU[num].pitch=pitch;
    IMU[num].yaw=yaw;

    return ret_val;
}

ret IMU_CalibrateRoll(uint8_t num, double roll_zero, double roll_pos90, double roll_neg90)
{
    /**IMU_CalibrateRoll() sequence: */

    ret ret_val=IMU_SUCCESS;
    
    /**set zero position */
    IMU[num].roll_zero=roll_zero;

    /**calculate increment scale */
    IMU[num].roll_inc_scale=(roll_pos90-roll_zero)/90;

    /**calculate decrement scale */
    IMU[num].roll_dec_scale=(roll_zero-roll_neg90)/90;

    return ret_val;
}

ret IMU_CalibratePitch(uint8_t num, double pitch_zero, double pitch_pos90, double pitch_neg90)
{
    /**IMU_CalibratePitch() sequence: */

    ret ret_val=IMU_SUCCESS;
    
    /**set zero position */
    IMU[num].pitch_zero=pitch_zero;

    /**calculate increment scale */
    IMU[num].pitch_inc_scale=(pitch_pos90-pitch_zero)/90;

    /**calculate decrement scale */
    IMU[num].ptich_dec_scale=(pitch_zero-pitch_neg90)/90;

    return ret_val;
}

ret IMU_CalibrateYaw(uint8_t num, double yaw_zero, double yaw_pos90, double yaw_neg90)
{
    /**IMU_CalibrateYaw() sequence: */

    ret ret_val=IMU_SUCCESS;
    
    /**set zero position */
    IMU[num].yaw_zero=yaw_zero;

    /**calculate increment scale */
    IMU[num].pitch_inc_scale=(yaw_pos90-yaw_zero)/90;

    /**calculate decrement scale */
    IMU[num].ptich_dec_scale=(yaw_zero-yaw_neg90)/90;

    return ret_val;
}


double IMU_GetRoll(uint8_t num)
{
    return IMU[num].roll;
}

double IMU_GetPitch(uint8_t num)
{
    return IMU[num].pitch;
}

double IMU_GetYaw(uint8_t num)
{
    return IMU[num].yaw;
}