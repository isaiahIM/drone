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

// TODO:
// FIX BUGS, ERRORS
// 
// 
ret Gyro_Init(void)
{
    /**Gyro_Init() sequence: */

    ret ret_val=GYRO_OK;

    /**gyro h/w initalize */
    ret_val|=BSP_Gyro_HW_Initalize();
    if(ret_val!=GYRO_OK)
    {
        ret_val|=GYRO_HW_INIT_FAIL;
    }

    /**gyro application initalize */

    /*make initalize structure dummy node */
    init_head=(Gyro_initStruct*)malloc(sizeof(Gyro_initStruct));
    if(init_head==NULL)
    {
        ret_val|=GYRO_AP_INIT_FAIL;
        return ret_val;
    }
    init_cur=init_head;
    init_head->next=NULL;

    /*make data structure dummy node */
    data_head=(Gyro_dataStruct*)malloc(sizeof(Gyro_dataStruct));
    if(data_head==NULL)
    {
        ret_val|=GYRO_AP_INIT_FAIL;
        return ret_val;
    }
    data_cur=data_head;
    data_head->next=NULL;

    /**gyro count reset */
    gyro_count=0;

    /**return result */
    return ret_val;
}

uint8_t Gyro_ConnectCheck(uint8_t num)
{
    uint8_t connect_status=GYRO_DISCONNECTED;

    connect_status|=BSP_Gyro_ChkConnect(num);

    return connect_status;
}


ret Gyro_AddGyro(Gyro_initStruct gyro)
{
    /**Gyro_AddGyro() sequence: */

    Gyro_dataStruct gyro_data;
    ret ret_val=GYRO_OK;

    /**gyro H/W setting */
    ret_val|=BSP_Gyro_SetReolution(num, resolution);
    ret_val|=BSP_Gyro_SetCaptureFreq(num, capture_freq);

    /**gyro add informaion in list */
    ret_val|=Gyro_AddInitalizeInfo(gyro);
    ret_val|=Gyro_AddDataInfo(gyro_data);

    /**increment gyro count */
    Gyro_CountIncrement();

    /**return result */
    return ret_val;
}

ret Gyro_DeleteGyro(uint8_t num)
{
    /**Gyro_DeleteGyro() sequence: */

    /**delcare and initalize values */
    ret ret_val=GYRO_OK;

    ret_val|=Gyro_DeleteDataInfo(num);
    ret_val|=Gyro_DeleteInitalizeInfo(num);

    return ret_val;
}


ret Gyro_AddInitalizeInfo(Gyro_initStruct gyro)
{
    /**Gyro_AddInitalizeInfo() sequence: */

    /**declare and initalize values */
    ret ret_val=GYRO_OK;
    Gyro_initStruct *buf;
    uint8_t num, resolution;
    uint32_t cap_freq, communicate_freq;

    /**get data in structure */
    cap_freq=Gyro_GetCaptureFreq(gyro);
    resolution=Gyro_GetResolution(gyro);
    communicate_freq=Gyro_GetCommunicateFreq(gyro);
    num=Gyro_GetInitNum(gyro);

    /**node allocate */
    buf=(Gyro_initStruct*)malloc(sizeof(Gyro_initStruct));
    if(buf==NULL)
    {
        ret_val=GYRO_ADD_FAIL;
        return ret_val;
    }

    /**structure data copy */
    buf->num=num;
    buf->resolution=resolution;
    buf->capture_freq=cap_freq;
    buf->communication_freq=communicate_freq;

    /**add node in list */
    init_prev=init_cur;
    buf->next=init_cur->next;
    init_cur->next=buf;
    init_cur=buf;

    /**return result */
    return ret_val;
}

ret Gyro_GetInitalizeInfo(uint8_t num, Gyro_initStruct **gyro)
{
    /**Gyro_GetInitalizeInfo() sequence: */

    /**declare and reset values */
    ret ret_val=GYRO_OK;

    /**reset current, preview position */
    Gyro_ResetInitPos();

    /**search number in list */
    while(init_cur!=NULL)
    {
        if(Gyro_GetDataNum(init_cur)==num)
        {
            *gyro=init_cur;
            break;
        }
        init_prev=init_cur;
        init_cur=init_cur->next;
    }

    if(data_cur==NULL)
    {
        ret_val|=GYRO_UNKNOWN_DATA;
    }

    return ret_val;
}


ret Gyro_DeleteInitalizeInfo(uint8_t num)
{
    /**Gyro_DeleteInitalizeInfo() sequence: */

    /**declare and reset position */
    Gyro_initStruct *delete;
    ret ret_val=GYRO_OK;

    /**get delete node in list */
    ret_val|=Gyro_GetInitalizeInfo(num, &delete);

    /**unlink data */
    init_prev->next=delete->next;
    init_cur=delete->next;

    /**delete data in list */
    free(delete);

    /**decrement gyro count */
    Gyro_CountDecrement();

    /**return result */
    return ret_val;
}


ret Gyro_AddDataInfo(Gyro_dataStruct gyro)
{
    /**Gyro_AddDataInfo() sequence: */

    /**declare and initlize values */
    Gyro_dataStruct *buf;
    ret ret_val=GYRO_OK;

    /**node allocate */
    buf=(Gyro_dataStruct*)malloc(sizeof(Gyro_dataStruct));
    if(buf==NULL)
    {
        ret_val=GYRO_ADD_FAIL;
        return ret_val;
    }

    /**add node in list */
    data_prev=data_cur;
    buf->next=data_cur->next;
    data_cur->next=buf;
    data_cur=buf;

    /**return result */
    return ret_val;
}

ret Gyro_GetDataInfo(uint8_t num, Gyro_dataStruct **gyro)
{
    /**Gyro_GetDataInfo() sequence: */

    /**declare and reset values */
    ret ret_val=GYRO_OK;

    /**reset current, preview position */
    Gyro_ResetDataPos();

    /**search number in list */
    while(data_cur!=NULL)
    {
        if(Gyro_GetDataNum(data_cur)==num)
        {
            *gyro=data_cur;
            break;
        }
        data_prev=data_cur;
        data_cur=data_cur->next;
    }

    if(data_cur==NULL)
    {
        ret_val|=GYRO_UNKNOWN_DATA;
    }

    return ret_val;
}

ret Gyro_DeleteDataInfo(uint8_t num)
{
    /**Gyro_DeleteDataInfo() sequence: */

    /**declare and reset position */
    Gyro_dataStruct *delete;
    ret ret_val=GYRO_OK;

    /**get delete node in list */
    ret_val|=Gyro_GetDataInfo(num, &delete);

    /**unlink data */
    data_prev->next=delete->next;
    data_cur=delete->next;

    /**delete data in list */
    free(delete);

    /**return result */
    return ret_val;
}


ret Gyro_SetNum(Gyro_initStruct *gyro, uint8_t num)
{
    ret ret_val=GYRO_OK;

    if(gyro==NULL)
    {
        ret_val=GYRO_SET_DATA_FAIL;
        return ret_val;
    }

    gyro->num=num;

    return ret_val;
}

ret Gyro_SetResolution(Gyro_initStruct *gyro, uint8_t resolution_bit)
{
    ret ret_val=GYRO_OK;

    if(gyro==NULL)
    {
        ret_val=GYRO_SET_DATA_FAIL;
        return ret_val;
    }

    gyro->resolution=resolution_bit;

    return ret_val;
}

ret Gyro_SetCaptureFreq(Gyro_initStruct *gyro, uint32_t freq)
{
    ret ret_val=GYRO_OK;

    if(gyro==NULL)
    {
        ret_val=GYRO_SET_DATA_FAIL;
        return ret_val;
    }

    gyro->capture_freq=freq;

    return ret_val;
}

ret Gyro_SetCommunicateFreq(Gyro_initStruct *gyro, uint32_t freq)
{
    ret ret_val=GYRO_OK;

    if(gyro==NULL)
    {
        ret_val=GYRO_SET_DATA_FAIL;
        return ret_val;
    }

    gyro->communication_freq=freq;

    return ret_val;
}


uint8_t Gyro_GetInitNum(Gyro_initStruct gyro)
{
    return gyro.num;
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


gyroType_t Gyro_Get_X(Gyro_dataStruct gyro)
{
    BSP_Gyro_GetX(gyro.num, &gyro.gyro_x);
    return gyro.gyro_x;
}

gyroType_t Gyro_Get_Y(Gyro_dataStruct gyro)
{
    BSP_Gyro_GetY(gyro.num, &gyro.gyro_y);
    return gyro.gyro_y;
}

gyroType_t Gyro_Get_Z(Gyro_dataStruct gyro)
{
    BSP_Gyro_GetZ(gyro.num, &gyro.gyro_z);
    return gyro.gyro_z;
}


uint8_t Gyro_GetDataNum(Gyro_dataStruct gyro)
{
    return gyro.num;
}


void Gyro_CountIncrement(void)
{
    gyro_count+=1;
}

void Gyro_CountDecrement(void)
{
    gyro_count-=1;
}


void Gyro_ResetDataPos(void)
{
    data_cur=data_head->next;
    data_prev=data_head;
}

void Gyro_ResetInitPos(void)
{
    init_cur=init_head->next;
    init_prev=init_head;
}