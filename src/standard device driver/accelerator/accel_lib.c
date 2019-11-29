/**
 * @file accel_lib.c
 * @author isaiah IM || isaiahim0214@gmail.com
 * @brief accelerator HAL Library source file
 * @version 0.1
 * @date 2019-10-11
 * 
 * @copyright Copyright (c) 2019 isaiah IM
 * 
 */
#include "accel_lib.h"


Accel_infoStruct accel_info;

ret Accel_Init(uint8_t count)
{
    /**Accel_Init() sequence: */

    ret ret_val=ACCEL_OK;
                                printf("\t\tSTART Accel_Init();\n ");
    
    /**initalize values */
    accel_info.count=count;
    accel_info.data_arr=NULL;
    accel_info.init_arr=NULL;

    /**accel h/w initalize */
    ret_val|=BSP_Accel_HW_Initalize();
    if(ret_val!=ACCEL_OK)
    {
        ret_val|=ACCEL_HW_INIT_FAIL;
    }

    /**accel application initalize */

    /*initalize info memory initalize */
    accel_info.init_arr=(Accel_initStruct*)calloc(count, sizeof(Accel_initStruct));
    if(accel_info.init_arr==NULL)
    {
                                        printf("Accel_Init(); fail!!\n ");
        ret_val|=ACCEL_MEMALLOC_FAIL;
    }

    /*data info memory initalize */
    accel_info.data_arr=(Accel_dataStruct*)calloc(count, sizeof(Accel_dataStruct));
    if(accel_info.data_arr==NULL)
    {
                                        printf("Accel_Init(); fail2!!\n ");
        ret_val|=ACCEL_MEMALLOC_FAIL;
    }
                                printf("\t\tEXIT Accel_Init();\n ");
    return ret_val;
}

uint8_t Accel_ChkConnect(uint8_t num)
{
                                printf("\t\tSTART Accel_ChkConnect();\n ");
    uint8_t connect_status=ACCEL_DISCONNECTED;

    connect_status=BSP_Accel_ChkConnect(num);
                                printf("\t\tEXIT Accel_ChkConnect();\n ");
    return connect_status;
}


ret Accel_GetInitalizeInfo(uint8_t num, Accel_initStruct **accel)
{
    /**Accel_GetInitalizeInfo() sequence: */

                                printf("\t\tSTART Accel_GetInitalizeInfo();\n ");

    /**search accel number */
    if(num>=accel_info.count || num<0)
    {
        return ACCEL_UNKNOWN_DATA;
    }
    else
    {
        *accel=&(accel_info.init_arr[num]);
    }

                                printf("\t\tEND Accel_GetInitalizeInfo();\n ");

    return ACCEL_OK;
}


ret Accel_GetDataInfo(uint8_t num, Accel_dataStruct **accel)
{
    /**Accel_GetDataInfo() sequence: */

                                printf("\t\tSTART Accel_GetDataInfo();\n");

    /**search accel number */
    if(num>=accel_info.count || num<0)
    {
        return ACCEL_UNKNOWN_DATA;
    }
    else
    {
        *accel=&(accel_info.data_arr[num]);
    }

                                printf("\t\tEND Accel_GetDataInfo();\n ");

    return ACCEL_OK;
}


ret Accel_SetResolution(Accel_initStruct *p_accel, uint8_t resolution_bit)
{
    ret ret_val=ACCEL_OK;

                                printf("\t\tSTART Accel_SetResolution();\n ");

    if(p_accel==NULL)
    {
        printf("accel set fail!!\n");

        ret_val=ACCEL_SET_DATA_FAIL;
        return ret_val;
    }

    p_accel->resolution=resolution_bit;

    printf("resolution: %d\n", p_accel->resolution);

                                printf("\t\tEND Accel_SetResolution();\n ");

    return ret_val;
}

ret Accel_SetCaptureFreq(Accel_initStruct *p_accel, uint32_t freq)
{
    ret ret_val=ACCEL_OK;
                                printf("\t\tSTART Accel_SetCaptureFreq();\n ");

    if(p_accel==NULL)
    {
        printf("accel set fail!!\n");

        ret_val=ACCEL_SET_DATA_FAIL;
        return ret_val;
    }

    p_accel->capture_freq=freq;

    printf("cap_frq: %d\n", p_accel->capture_freq);

                                printf("\t\tEND Accel_SetCaptureFreq();\n ");

    return ret_val;
}

ret Accel_SetCommunicateFreq(Accel_initStruct *p_accel, uint32_t freq)
{
    ret ret_val=ACCEL_OK;

                                printf("\t\tSTART Accel_SetCommunicateFreq();\n ");

    if(p_accel==NULL)
    {
        printf("accel set fail!!\n");

        ret_val=ACCEL_SET_DATA_FAIL;
        return ret_val;
    }

    p_accel->communication_freq=freq;

    printf("communication_freq: %d\n", p_accel->communication_freq);

                                printf("\t\tEND Accel_SetCommunicateFreq();\n ");

    return ret_val;
}


uint8_t Accel_GetResolution(Accel_initStruct accel)
{
    return accel.resolution;
}

uint32_t Accel_GetCaptureFreq(Accel_initStruct accel)
{
    return accel.capture_freq;
}

uint32_t Accel_GetCommunicateFreq(Accel_initStruct accel)
{
    return accel.communication_freq;
}

ret Accel_UpdateData(uint8_t num, Accel_dataStruct *p_accel)
{
    /**Accel_UpdateData() sequence: */

    /**declare values */
    Accel_dataStruct *p_buf;
    ret ret_val=ACCEL_OK;
    accelType_t x, y, z;
    double pitch, roll;

    /**get previous accelerator data */
    ret_val|=Accel_GetDataInfo(num, &p_buf);
    if(ret_val!=ACCEL_OK)
    {
        return ACCEL_GET_DATA_FAIL;
    }

    /**get current accelerator x, y, z data */
    ret_val|=BSP_Accel_GetX(num, &x);
    ret_val|=BSP_Accel_GetY(num, &y);
    ret_val|=BSP_Accel_GetZ(num, &z);

    /**calculate roll, pitch */
    
    /*arm-dsp use */
    #ifdef USE_ARM_DSP

    float32_t root;

    /*pitch calculate */
    if(arm_sqrt_f32(y*y + z*z, &root)!=ARM_MATH_SUCCESS)
    {
        return 0;
    }
    pitch=180*atan(x/root)/M_PI;
    
    /*roll calculate */
    if(arm_sqrt_f32(x*x + z*z, &root)!=ARM_MATH_SUCCESS)
    {
        return 0;
    }
    roll=180*atan(x/root)/M_PI;

    /*arm-dsp not use */
    #else

    pitch=180*atan(x/sqrt(y*y + z*z))/M_PI;
    roll=180*atan(y/sqrt(x*x + z*z))/M_PI;
    #endif

    /**update data */
    p_buf->accel_x=x;
    p_buf->accel_y=y;
    p_buf->accel_z=z;
    p_buf->roll=roll;
    p_buf->pitch=pitch;

    /**move data */
    memcpy( (void*)p_accel, (void*)p_buf, sizeof(Accel_dataStruct) );
    
    printf("================================Accel_UpdateData:\n");
    printf("1. roll: %lf, pitch: %lf, x: %d, y: %d, z: %d\n", p_buf->roll, p_buf->pitch, p_buf->accel_x, p_buf->accel_y, p_buf->accel_z);
    printf("2. roll: %lf, pitch: %lf, x: %d, y: %d, z: %d\n", p_accel->roll, p_accel->pitch, p_accel->accel_x, p_accel->accel_y, p_accel->accel_z);

    /**return result */
    if(ret_val!=ACCEL_OK)
    {
        return ACCEL_GET_DATA_FAIL;
    }
    else
    {
        return ACCEL_OK;
    }
}


double Accel_GetPitch(Accel_dataStruct accel)
{
    return accel.pitch;
}

double Accel_GetRoll(Accel_dataStruct accel)
{
    return accel.roll;
}


accelType_t Accel_Get_X(Accel_dataStruct accel)
{
    return accel.accel_x;
}

accelType_t Accel_Get_Y(Accel_dataStruct accel)
{
    return accel.accel_y;
}

accelType_t Accel_Get_Z(Accel_dataStruct accel)
{
    return accel.accel_z;
}

void Accel_Terminate(void)
{
    free(accel_info.data_arr);
    free(accel_info.init_arr);
}