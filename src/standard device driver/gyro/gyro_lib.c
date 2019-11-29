/**
 * @file gyro_lib.c
 * @author isaiah IM || isaiahim0214@gmail.com
 * @brief gyroscope HAL Library source file
 * @version 0.1
 * @date 2019-09-22
 * 
 * @copyright Copyright (c) 2019 isaiah IM
 * 
 */
#include "gyro_lib.h"


Gyro_infoStruct gyro_info;


ret Gyro_Init(uint8_t count)
{
    /**Gyro_Init() sequence: */

    ret ret_val=GYRO_OK;
                                printf("\t\tSTART Gyro_Init();\n ");
    
    /**initalize values */
    gyro_info.count=count;
    gyro_info.data_arr=NULL;
    gyro_info.init_arr=NULL;

    /**gyro h/w initalize */
    ret_val|=BSP_Gyro_HW_Initalize();
    if(ret_val!=GYRO_OK)
    {
        ret_val|=GYRO_HW_INIT_FAIL;
    }

    /**gyro memory initalize */

    /*initalize info memory initalize */
    gyro_info.init_arr=(Gyro_initStruct*)calloc(count, sizeof(Gyro_initStruct));
    if(gyro_info.init_arr==NULL)
    {
                                        printf("Gyro_Init(); fail!!\n ");
        ret_val|=GYRO_MEMALLOC_FAIL;
    }

    /*data info memory initalize */
    gyro_info.data_arr=(Gyro_dataStruct*)calloc(count, sizeof(Gyro_dataStruct));
    if(gyro_info.data_arr==NULL)
    {
                                        printf("Gyro_Init(); fail2!!\n ");
        ret_val|=GYRO_MEMALLOC_FAIL;
    }

                                printf("\t\tEXIT Gyro_Init();\n ");
    /**return result */
    return ret_val;
}

uint8_t Gyro_ChkConnect(uint8_t num)
{
                                printf("\t\tSTART Gyro_ChkConnect();\n ");
    uint8_t connect_status=GYRO_DISCONNECTED;

    connect_status=BSP_Gyro_ChkConnect(num);
                                printf("\t\tEXIT Gyro_ChkConnect();\n ");
    return connect_status;
}


ret Gyro_GetInitalizeInfo(uint8_t num, Gyro_initStruct **p_gyro)
{
    /**Gyro_GetInitalizeInfo() sequence: */

                                printf("\t\tSTART Gyro_GetInitalizeInfo();\n ");

    /**search gyro number */
    if(num>=gyro_info.count || num<0)
    {
        return GYRO_UNKNOWN_DATA;
    }
    else
    {
        *p_gyro=&(gyro_info.init_arr[num]);
    }

                                printf("\t\tEND Gyro_GetInitalizeInfo();\n ");

    return GYRO_OK;
}


ret Gyro_GetDataInfo(uint8_t num, Gyro_dataStruct **p_gyro)
{
    /**Gyro_GetDataInfo() sequence: */

                                printf("\t\tSTART Gyro_GetDataInfo();\n");

    /**search gyro number */
    if(num>=gyro_info.count || num<0)
    {
        return GYRO_UNKNOWN_DATA;
    }
    else
    {
        *p_gyro=&(gyro_info.data_arr[num]);
    }

                                printf("\t\tEND Gyro_GetDataInfo();\n ");

    return GYRO_OK;
}


ret Gyro_SetResolution(Gyro_initStruct *p_gyro, uint8_t resolution_bit)
{
    ret ret_val=GYRO_OK;

                                printf("\t\tSTART Gyro_SetResolution();\n ");

    if(p_gyro==NULL)
    {
        printf("gyro set fail!!\n");

        ret_val=GYRO_SET_DATA_FAIL;
        return ret_val;
    }

    p_gyro->resolution=resolution_bit;

    printf("resolution: %d\n", p_gyro->resolution);

                                printf("\t\tEND Gyro_SetResolution();\n ");

    return ret_val;
}

ret Gyro_SetCaptureFreq(Gyro_initStruct *p_gyro, uint32_t freq)
{
    ret ret_val=GYRO_OK;
                                printf("\t\tSTART Gyro_SetCaptureFreq();\n ");

    if(p_gyro==NULL)
    {
        printf("gyro set fail!!\n");

        ret_val=GYRO_SET_DATA_FAIL;
        return ret_val;
    }

    p_gyro->capture_freq=freq;

    printf("cap_frq: %d\n", p_gyro->capture_freq);

                                printf("\t\tEND Gyro_SetCaptureFreq();\n ");

    return ret_val;
}

ret Gyro_SetCommunicateFreq(Gyro_initStruct *p_gyro, uint32_t freq)
{
    ret ret_val=GYRO_OK;

                                printf("\t\tSTART Gyro_SetCommunicateFreq();\n ");

    if(p_gyro==NULL)
    {
        printf("gyro set fail!!\n");

        ret_val=GYRO_SET_DATA_FAIL;
        return ret_val;
    }

    p_gyro->communication_freq=freq;

    printf("communication_freq: %d\n", p_gyro->communication_freq);

                                printf("\t\tEND Gyro_SetCommunicateFreq();\n ");

    return ret_val;
}


uint8_t Gyro_GetResolution(Gyro_initStruct gyro)
{
    return gyro.resolution;
}

uint32_t Gyro_GetCaptureFreq(Gyro_initStruct gyro)
{
    return gyro.capture_freq;
}

uint32_t Gyro_GetCommunicateFreq(Gyro_initStruct gyro)
{
    return gyro.communication_freq;
}


ret Gyro_UpdateData(uint8_t num, Gyro_dataStruct *p_gyro)
{
    /**Gyro_UpdateData() sequence: */

    /**declare values */
    Gyro_dataStruct *p_buf;
    ret ret_val=GYRO_OK;
    double roll, pitch, yaw;
    double dt, cur_sec;
    gyroType_t x, y, z;

    /**get previous gyroscope data */
    ret_val|=Gyro_GetDataInfo(num, &p_buf);
    if(ret_val!=GYRO_OK)
    {
        return GYRO_GET_DATA_FAIL;
    }

    /**get previous roll, pitch, yaw */
    roll=Gyro_GetRoll(*p_buf);
    pitch=Gyro_GetPitch(*p_buf);
    yaw=Gyro_GetYaw(*p_buf);

    /**get current gyroscope data */
    ret_val|=BSP_Gyro_GetX(num, (uint32_t*)&x);
    ret_val|=BSP_Gyro_GetY(num, (uint32_t*)&y);
    ret_val|=BSP_Gyro_GetZ(num, (uint32_t*)&z);
    
    /**update time */
    cur_sec=Time_GetRunTimeSec();
    dt=cur_sec-p_buf->cap_sec;
    p_buf->cap_sec=cur_sec;

    /**calculate current roll, pitch, yaw */
    roll=roll + dt*x;
    pitch=pitch + dt*y;
    yaw=yaw + dt*z;

    /**update gyro data */
    p_buf->gyro_x=x;
    p_buf->gyro_y=y;
    p_buf->gyro_z=z;
    p_buf->roll=roll;
    p_buf->pitch=pitch;
    p_buf->yaw=yaw;

    /**move data */
    memcpy( (void*)p_gyro, (void*)p_buf, sizeof(Gyro_dataStruct) );

    printf("================================Gyro_UpdateData:\n");
    printf("1. roll: %f, pitch: %f, yaw: %f, x: %d, y: %d, z: %d\n", p_buf->roll, p_buf->pitch, p_buf->yaw, p_buf->gyro_x, p_buf->gyro_y, p_buf->gyro_z);
    printf("2. roll: %f, pitch: %f, yaw: %f, x: %d, y: %d, z: %d\n", p_gyro->roll, p_gyro->pitch, p_gyro->yaw, p_gyro->gyro_x, p_gyro->gyro_y, p_gyro->gyro_z);

    /**return result */
    if(ret_val!=GYRO_OK)
    {
        return GYRO_GET_DATA_FAIL;
    }
    else
    {
        return GYRO_OK;
    }
}

double Gyro_GetRoll(Gyro_dataStruct gyro)
{
    return gyro.roll;
}

double Gyro_GetPitch(Gyro_dataStruct gyro)
{
    return gyro.pitch;
}

double Gyro_GetYaw(Gyro_dataStruct gyro)
{
    return gyro.yaw;
}

gyroType_t Gyro_Get_X(Gyro_dataStruct gyro)
{
    return gyro.gyro_x;
}

gyroType_t Gyro_Get_Y(Gyro_dataStruct gyro)
{
    return gyro.gyro_y;
}

gyroType_t Gyro_Get_Z(Gyro_dataStruct gyro)
{
    return gyro.gyro_z;
}


void Gyro_Terminate(void)
{
    free(gyro_info.data_arr);
    free(gyro_info.init_arr);
}