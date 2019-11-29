/**
 * @file compass_lib.c
 * @author isaiah IM || isaiahim0214@gmail.com
 * @brief compass HAL Library source file
 * @version 0.2.1
 * @date 2019-11-30
 * 
 * @copyright Copyright (c) 2019 isaiah IM
 * 
 */
#include "compass_lib.h"


Compass_infoStruct compass_info;

ret Compass_Init(uint8_t count)
{
    /**Compass_Init() sequence: */

    ret ret_val=COMPASS_OK;
                                printf("\t\tSTART Compass_Init();\n ");
    
    /**initalize values */
    compass_info.count=count;
    compass_info.data_arr=NULL;
    compass_info.init_arr=NULL;

    /**compass h/w initalize */
    ret_val|=BSP_Compass_HW_Initalize();
    if(ret_val!=COMPASS_OK)
    {
        ret_val|=COMPASS_HW_INIT_FAIL;
    }

    /**compass application initalize */

    /*initalize info memory initalize */
    compass_info.init_arr=(Compass_initStruct*)calloc(count, sizeof(Compass_initStruct));
    if(compass_info.init_arr==NULL)
    {
                                        printf("Compass_Init(); fail!!\n ");
        ret_val|=COMPASS_MEMALLOC_FAIL;
    }

    /*data info memory initalize */
    compass_info.data_arr=(Compass_dataStruct*)calloc(count, sizeof(Compass_dataStruct));
    if(compass_info.data_arr==NULL)
    {
                                        printf("Compass_Init(); fail2!!\n ");
        ret_val|=COMPASS_MEMALLOC_FAIL;
    }
                                printf("\t\tEXIT Compass_Init();\n ");
    return ret_val;
}

uint8_t Compass_ChkConnect(uint8_t num)
{
                                printf("\t\tSTART Compass_ChkConnect();\n ");
    uint8_t connect_status=COMPASS_DISCONNECTED;

    connect_status=BSP_Compass_ChkConnect(num);
                                printf("\t\tEXIT Compass_ChkConnect();\n ");
    return connect_status;
}


ret Compass_GetInitalizeInfo(uint8_t num, Compass_initStruct **p_compass)
{
    /**Compass_GetInitalizeInfo() sequence: */

                                printf("\t\tSTART Compass_GetInitalizeInfo();\n ");

    /**search compass number */
    if(num>=compass_info.count || num<0)
    {
        return COMPASS_UNKNOWN_DATA;
    }
    else
    {
        *p_compass=&(compass_info.init_arr[num]);
    }

                                printf("\t\tEND Compass_GetInitalizeInfo();\n ");

    return COMPASS_OK;
}


ret Compass_GetDataInfo(uint8_t num, Compass_dataStruct **p_compass)
{
    /**Compass_GetDataInfo() sequence: */

                                printf("\t\tSTART Compass_GetDataInfo();\n");

    /**search compass number */
    if(num>=compass_info.count || num<0)
    {
        return COMPASS_UNKNOWN_DATA;
    }
    else
    {
        *p_compass=&(compass_info.data_arr[num]);
    }

                                printf("\t\tEND Compass_GetDataInfo();\n ");

    return COMPASS_OK;
}


ret Compass_SetResolution(Compass_initStruct *p_compass, uint8_t resolution_bit)
{
    ret ret_val=COMPASS_OK;

                                printf("\t\tSTART Compass_SetResolution();\n ");

    if(p_compass==NULL)
    {
        printf("compass set fail!!\n");

        ret_val=COMPASS_SET_DATA_FAIL;
        return ret_val;
    }

    p_compass->resolution=resolution_bit;

    printf("resolution: %d\n", p_compass->resolution);

                                printf("\t\tEND Compass_SetResolution();\n ");

    return ret_val;
}

ret Compass_SetCaptureFreq(Compass_initStruct *p_compass, uint32_t freq)
{
    ret ret_val=COMPASS_OK;
                                printf("\t\tSTART Compass_SetCaptureFreq();\n ");

    if(p_compass==NULL)
    {
        printf("compass set fail!!\n");

        ret_val=COMPASS_SET_DATA_FAIL;
        return ret_val;
    }

    p_compass->capture_freq=freq;

    printf("cap_frq: %d\n", p_compass->capture_freq);

                                printf("\t\tEND Compass_SetCaptureFreq();\n ");

    return ret_val;
}

ret Compass_SetCommunicateFreq(Compass_initStruct *p_compass, uint32_t freq)
{
    ret ret_val=COMPASS_OK;

                                printf("\t\tSTART Compass_SetCommunicateFreq();\n ");

    if(p_compass==NULL)
    {
        printf("compass set fail!!\n");

        ret_val=COMPASS_SET_DATA_FAIL;
        return ret_val;
    }

    p_compass->communication_freq=freq;

    printf("communication_freq: %d\n", p_compass->communication_freq);

                                printf("\t\tEND Compass_SetCommunicateFreq();\n ");

    return ret_val;
}


uint8_t Compass_GetResolution(Compass_initStruct compass)
{
    return compass.resolution;
}

uint32_t Compass_GetCaptureFreq(Compass_initStruct compass)
{
    return compass.capture_freq;
}

uint32_t Compass_GetCommunicateFreq(Compass_initStruct compass)
{
    return compass.communication_freq;
}

ret Compass_UpdateData(uint8_t num, Compass_dataStruct *p_compass)
{
    /**Compass_UpdateData() sequence: */

    /**declare values */
    ret ret_val=COMPASS_OK;
    Compass_dataStruct *p_buf;
    uint32_t data;
    double roll, pitch, yaw;
    compassType_t x, y, z;

    /**get privious data */
    ret_val|=Compass_GetDataInfo(num, &p_buf);
    if(ret_val!=COMPASS_OK)
    {
        return COMPASS_GET_DATA_FAIL;
    }
    roll=Compass_GetRoll(*p_buf);
    pitch=Compass_GetPitch(*p_buf);
    yaw=Compass_GetYaw(*p_buf);

    /**get current compass x, y, z data */
    ret_val|=BSP_Compass_GetX(num, &x);
    ret_val|=BSP_Compass_GetY(num, &y);
    ret_val|=BSP_Compass_GetZ(num, &z);

    /**calculate roll, pitch, yaw */
    /*arm-dsp use */
    #ifdef USE_ARM_DSP

    float32_t root;

    /*roll calculate */
    if(arm_sqrt_f32(x*x + z*z, &root)!=ARM_MATH_SUCCESS)
    {
        return ACCEL_GET_DATA_FAIL;
    }
    roll=180*atan((double)(x/root) )/M_PI;

    /*pitch calculate */
    if(arm_sqrt_f32(y*y + z*z, &root)!=ARM_MATH_SUCCESS)
    {
        return ACCEL_GET_DATA_FAIL;
    }
    pitch=180*atan( (double)(x/root) )/M_PI;

    /*arm-dsp not use */
    #else

    roll=180*atan(y/sqrt( (double)(x*x + z*z) ))/M_PI;
    pitch=180*atan(x/sqrt( (double)(y*y + z*z) ))/M_PI;
    #endif

    /*yaw calculate */
    yaw = 180 * atan((double)(y/x))/M_PI;

    /**update data */
    p_buf->compass_x=x;
    p_buf->compass_y=y;
    p_buf->compass_z=z;
    p_buf->roll=roll;
    p_buf->pitch=pitch;
    p_buf->yaw=yaw;

    /**move data */
    memcpy( (void*)p_compass, (void*)p_buf, sizeof(Compass_dataStruct) );

    printf("================================Compass_UpdateData:\n");
    printf("1. roll: %lf, pitch: %lf, x: %d, y: %d, z: %d\n", p_buf->roll, p_buf->pitch, p_buf->compass_x, p_buf->compass_y, p_buf->compass_z);
    printf("2. roll: %lf, pitch: %lf, x: %d, y: %d, z: %d\n", p_compass->roll, p_compass->pitch, p_compass->compass_x, p_compass->compass_y, p_compass->compass_z);

    /**return result */
    if(ret_val!=COMPASS_OK)
    {
        return COMPASS_GET_DATA_FAIL;
    }
    else
    {
        return COMPASS_OK;
    }
}


double Compass_GetRoll(Compass_dataStruct compass)
{
    return compass.roll;
}

double Compass_GetPitch(Compass_dataStruct compass)
{
    return compass.pitch;
}

double Compass_GetYaw(Compass_dataStruct compass)
{
    return compass.yaw;
}

compassType_t Compass_Get_X(Compass_dataStruct compass)
{
    return compass.compass_x;
}

compassType_t Compass_Get_Y(Compass_dataStruct compass)
{
    return compass.compass_y;
}

compassType_t Compass_Get_Z(Compass_dataStruct compass)
{
    return compass.compass_z;
}

void Compass_Terminate(void)
{
    free(compass_info.data_arr);
    free(compass_info.init_arr);
}