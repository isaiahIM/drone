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

static Gyro_dataStruct *data_prev=NULL, *data_cur=NULL, *data_head=NULL;
static Gyro_initStruct *init_prev=NULL, *init_cur=NULL, *init_head=NULL;
static uint8_t gyro_count=0;

ret Gyro_Init(void)
{
    /**Gyro_Init() sequence: */

    ret ret_val=GYRO_OK;
                                printf("\t\tSTART Gyro_Init();\n ");
    /**gyro h/w initalize */
    ret_val|=BSP_Gyro_HW_Initalize();
    if(ret_val!=GYRO_OK)
    {
        ret_val|=GYRO_HW_INIT_FAIL;
    }

    /**gyro application initalize */

    /*make initalize structure dummy node */
    init_head=(Gyro_initStruct*)calloc(1, sizeof(Gyro_initStruct));
    if(init_head==NULL)
    {
                                        printf("Gyro_Init(); fail1!!\n ");
        ret_val|=GYRO_AP_INIT_FAIL;
        return ret_val;
    }
    init_cur=init_head;
    init_head->next=NULL;

    /*make data structure dummy node */
    data_head=(Gyro_dataStruct*)calloc(1, sizeof(Gyro_dataStruct));
    if(data_head==NULL)
    {
                                        printf("Gyro_Init(); fail2!!\n ");
        ret_val|=GYRO_AP_INIT_FAIL;
        return ret_val;
    }
    data_cur=data_head;
    data_head->next=NULL;

    /**gyro count reset */
    gyro_count=0;

                                printf("\t\tEXIT Gyro_Init();\n ");
    /**return result */
    return ret_val;
}

uint8_t Gyro_ConnectCheck(uint8_t num)
{
                                printf("\t\tSTART Gyro_ConnectCheck();\n ");
    uint8_t connect_status=GYRO_DISCONNECTED;

    connect_status=BSP_Gyro_ChkConnect(num);
                                printf("\t\tEXIT Gyro_ConnectCheck();\n ");
    return connect_status;
}


ret Gyro_AddGyro(Gyro_initStruct gyro)
{
    /**Gyro_AddGyro() sequence: */
                                printf("\t\tSTART Gyro_AddGyro();\n ");

    /**declare values */
    Gyro_dataStruct gyro_data;
    ret ret_val=GYRO_OK;
    uint8_t num, resolution;
    uint32_t cap_freq, com_freq;

    /**get gyro data */
    num=Gyro_GetInitNum(gyro);
    Gyro_SetDataNum(&gyro_data, num);

    resolution=Gyro_GetResolution(gyro);
    cap_freq=Gyro_GetCaptureFreq(gyro);
    com_freq=Gyro_GetCommunicateFreq(gyro);
                                printf("num: %d, res: %d, cap_freq: %d, com_freq: %d\n", num, resolution, cap_freq, com_freq);
    
    /**gyro H/W setting */
    ret_val|=BSP_Gyro_SetReolution(num, resolution);
    ret_val|=BSP_Gyro_SetCaptureFreq(num, cap_freq);
    ret_val!=BSP_Gyro_SetCommunicateFreq(num, com_freq);

    /**gyro add informaion in list */
    ret_val|=Gyro_AddInitalizeInfo(gyro);
    ret_val|=Gyro_AddDataInfo(gyro_data);

    /**increment gyro count */
    Gyro_CountIncrement();

                                printf("\t\tEND Gyro_AddGyro();\n ");
    /**return result */
    return ret_val;
}

ret Gyro_DeleteGyro(uint8_t num)
{
    /**Gyro_DeleteGyro() sequence: */
                                printf("\t\tSTART Gyro_DeleteGyro();\n ");
    /**delcare and initalize values */
    ret ret_val=GYRO_OK;
                                printf("delete num: %d\n", num);
    ret_val|=Gyro_DeleteDataInfo(num);
    ret_val|=Gyro_DeleteInitalizeInfo(num);
    
                                printf("\t\tEND Gyro_DeleteGyro();\n ");
    return ret_val;
}


ret Gyro_AddInitalizeInfo(Gyro_initStruct gyro)
{
    /**Gyro_AddInitalizeInfo() sequence: */

                                printf("\t\tSTART Gyro_AddInitalizeInfo();\n ");

    /**declare and initalize values */
    ret ret_val=GYRO_OK;
    Gyro_initStruct *buf;

    /**node allocate */
    buf=(Gyro_initStruct*)calloc(1, sizeof(Gyro_initStruct));
    if(buf==NULL)
    {
        ret_val=GYRO_ADD_FAIL;
        return ret_val;
    }

    /**structure data copy */
    memcpy(buf, &gyro, sizeof(Gyro_initStruct));

    /**add node in list */
    init_prev=init_cur;
    buf->next=init_cur->next;
    init_cur->next=buf;
    init_cur=buf;
                                printf("num: %d, res: %d, cap_freq: %d, com_freq: %d\n", init_cur->num, init_cur->resolution, init_cur->capture_freq, init_cur->communication_freq);
                                printf("\t\tEND Gyro_AddInitalizeInfo();\n ");

    /**return result */
    return ret_val;
}

ret Gyro_GetInitalizeInfo(uint8_t num, Gyro_initStruct **gyro)
{
    /**Gyro_GetInitalizeInfo() sequence: */

                                printf("\t\tSTART Gyro_GetInitalizeInfo();\n ");

    /**declare and reset values */
    ret ret_val=GYRO_OK;

    /**reset current, preview position */
    Gyro_ResetInitPos();

    /**search number in list */
    while(init_cur!=NULL)
    {
        if(Gyro_GetInitNum(*init_cur)==num)
        {
            *gyro=init_cur;

                                    printf("search num: %d, res: %d, cap_freq: %d, com_freq: %d\n", (*gyro)->num, (*gyro)->resolution, (*gyro)->capture_freq, (*gyro)->communication_freq);

            break;
        }
        else
        {
            init_prev=init_cur;
            init_cur=init_cur->next;
        }
        
    }

    if(init_cur==NULL)
    {
                                printf("search fail!!\n");
        ret_val|=GYRO_UNKNOWN_DATA;
    }

                                printf("\t\tEND Gyro_GetInitalizeInfo();\n ");

    return ret_val;
}


ret Gyro_DeleteInitalizeInfo(uint8_t num)
{
    /**Gyro_DeleteInitalizeInfo() sequence: */

                                printf("\t\tSTART Gyro_DeleteInitalizeInfo();\n ");

    /**declare and reset position */
    Gyro_initStruct *delete;
    ret ret_val=GYRO_OK;

    /**get delete node in list */
    ret_val|=Gyro_GetInitalizeInfo(num, &delete);

    /**unlink data */
    init_prev->next=delete->next;
    init_cur=delete->next;

    printf("delete num: %d, res: %d, cap_freq: %d, com_freq: %d\n", delete->num, delete->resolution, delete->capture_freq, delete->communication_freq);

    /**delete data in list */
    free(delete);

    /**decrement gyro count */
    Gyro_CountDecrement();

                                printf("\t\tEND Gyro_DeleteInitalizeInfo();\n ");

    /**return result */
    return ret_val;
}


ret Gyro_AddDataInfo(Gyro_dataStruct gyro)
{
    /**Gyro_AddDataInfo() sequence: */

                                printf("\t\tSTART Gyro_AddDataInfo();\n ");

    /**declare and initlize values */
    Gyro_dataStruct *buf;
    ret ret_val=GYRO_OK;

    printf("PREV num: %d\n", gyro.num);
    /**node allocate */
    buf=(Gyro_dataStruct*)calloc(1, sizeof(Gyro_dataStruct));
    if(buf==NULL)
    {
                                printf("gyro add fail!!\n");
        ret_val=GYRO_ADD_FAIL;
        return ret_val;
    }

    /**data copy */
    memcpy(buf, &gyro, sizeof(Gyro_dataStruct));

    /**add node in list */
    data_prev=data_cur;
    buf->next=data_cur->next;
    data_cur->next=buf;
    data_cur=buf;

                                printf("\t\tEND Gyro_AddDataInfo();\n ");

    /**return result */
    return ret_val;
}

ret Gyro_GetDataInfo(uint8_t num, Gyro_dataStruct **gyro)
{
    /**Gyro_GetDataInfo() sequence: */

                                printf("\t\tSTART Gyro_GetDataInfo();\n");

    /**declare and reset values */
    ret ret_val=GYRO_OK;

    /**reset current, preview position */
    Gyro_ResetDataPos();

    /**search number in list */
    while(data_cur!=NULL)
    {
        if(Gyro_GetDataNum(*data_cur)==num)
        {
            *gyro=data_cur;

            printf("search num: %d, gyro_x: %d, gyro_y: %d, gyro_z: %d\n", (*gyro)->num, (*gyro)->gyro_x, (*gyro)->gyro_y, (*gyro)->gyro_z);

            break;
        }
        else
        {
            data_prev=data_cur;
            data_cur=data_cur->next;
        }
        
    }

    if(data_cur==NULL)
    {
        printf("gyro search fail!!\n");
        ret_val|=GYRO_UNKNOWN_DATA;
    }

                                printf("\t\tEND Gyro_GetDataInfo();\n ");

    return ret_val;
}

ret Gyro_DeleteDataInfo(uint8_t num)
{
    /**Gyro_DeleteDataInfo() sequence: */

                                printf("\t\tSTART Gyro_DeleteDataInfo();\n ");

    /**declare and reset position */
    Gyro_dataStruct *delete;
    ret ret_val=GYRO_OK;

    /**get delete node in list */
    ret_val|=Gyro_GetDataInfo(num, &delete);

    /**unlink data */
    data_prev->next=delete->next;
    data_cur=delete->next;

    printf("delete num: %d, gyro_x: %d, gyro_y: %d, gyro_z: %d\n", delete->num, delete->gyro_x, delete->gyro_y, delete->gyro_z);

    /**delete data in list */
    free(delete);

                                printf("\t\tEND Gyro_DeleteDataInfo();\n ");


    /**return result */
    return ret_val;
}


ret Gyro_SetNum(Gyro_initStruct *gyro, uint8_t num)
{
    ret ret_val=GYRO_OK;

                                printf("\t\tSTART Gyro_SetNum();\n ");

    if(gyro==NULL)
    {
        printf("gyro set fail!!\n");

        ret_val=GYRO_SET_DATA_FAIL;
        return ret_val;
    }

    gyro->num=num;

    printf("num: %d\n", gyro->num);

                                printf("\t\tEND Gyro_SetNum();\n ");
    return ret_val;
}

ret Gyro_SetResolution(Gyro_initStruct *gyro, uint8_t resolution_bit)
{
    ret ret_val=GYRO_OK;

                                printf("\t\tSTART Gyro_SetResolution();\n ");

    if(gyro==NULL)
    {
        printf("gyro set fail!!\n");

        ret_val=GYRO_SET_DATA_FAIL;
        return ret_val;
    }

    gyro->resolution=resolution_bit;

    printf("resolution: %d\n", gyro->resolution);

                                printf("\t\tEND Gyro_SetResolution();\n ");

    return ret_val;
}

ret Gyro_SetCaptureFreq(Gyro_initStruct *gyro, uint32_t freq)
{
    ret ret_val=GYRO_OK;
                                printf("\t\tSTART Gyro_SetCaptureFreq();\n ");

    if(gyro==NULL)
    {
        printf("gyro set fail!!\n");

        ret_val=GYRO_SET_DATA_FAIL;
        return ret_val;
    }

    gyro->capture_freq=freq;

    printf("cap_frq: %d\n", gyro->capture_freq);

                                printf("\t\tEND Gyro_SetCaptureFreq();\n ");

    return ret_val;
}

ret Gyro_SetCommunicateFreq(Gyro_initStruct *gyro, uint32_t freq)
{
    ret ret_val=GYRO_OK;

                                printf("\t\tSTART Gyro_SetCommunicateFreq();\n ");

    if(gyro==NULL)
    {
        printf("gyro set fail!!\n");

        ret_val=GYRO_SET_DATA_FAIL;
        return ret_val;
    }

    gyro->communication_freq=freq;

    printf("communication_freq: %d\n", gyro->communication_freq);

                                printf("\t\tEND Gyro_SetCommunicateFreq();\n ");

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


ret Gyro_UpdateData(uint8_t num, Gyro_dataStruct *gyro)
{
    /**Gyro_UpdateData() sequence: */

    /**declare values */
    Gyro_dataStruct *p_gyro;
    ret ret_val=GYRO_OK;
    double roll, pitch, yaw;
    double dt, cur_sec;
    gyroType_t x, y, z;

    /**get previous gyroscope data */
    ret_val|=Gyro_GetDataInfo(num, &p_gyro);
    if(ret_val!=GYRO_OK)
    {
        return GYRO_GET_DATA_FAIL;
    }

    /**get previous roll, pitch, yaw */
    roll=Gyro_GetRoll(*p_gyro);
    pitch=Gyro_GetPitch(*p_gyro);
    yaw=Gyro_GetYaw(*p_gyro);

    /**get current gyroscope data */
    ret_val|=BSP_Gyro_GetX(num, (uint32_t*)&x);
    ret_val|=BSP_Gyro_GetY(num, (uint32_t*)&y);
    ret_val|=BSP_Gyro_GetZ(num, (uint32_t*)&z);
    
    /**update time */
    cur_sec=Time_GetRunTimeSec();
    dt=cur_sec-p_gyro->cap_sec;
    p_gyro->cap_sec=cur_sec;

    /**calculate current roll, pitch, yaw */
    roll=roll + dt*x;
    pitch=pitch + dt*y;
    yaw=yaw + dt*z;

    /**update gyro data */
    p_gyro->gyro_x=x;
    p_gyro->gyro_y=y;
    p_gyro->gyro_z=z;
    p_gyro->roll=roll;
    p_gyro->pitch=pitch;
    p_gyro->yaw=yaw;

    /**move data */
    gyro->gyro_x=p_gyro->gyro_x;
    gyro->gyro_y=p_gyro->gyro_y;
    gyro->gyro_z=p_gyro->gyro_z;
    gyro->roll=p_gyro->roll;
    gyro->pitch=p_gyro->pitch;
    gyro->yaw=p_gyro->yaw;
    gyro->num=p_gyro->num;
    gyro->next=p_gyro->next;
    gyro->cap_sec=p_gyro->cap_sec;

    printf("================================Gyro_UpdateData:\n");
    printf("1. roll: %f, pitch: %f, yaw: %f, x: %d, y: %d, z: %d\n", p_gyro->roll, p_gyro->pitch, p_gyro->yaw, p_gyro->gyro_x, p_gyro->gyro_y, p_gyro->gyro_z);
    printf("2. roll: %f, pitch: %f, yaw: %f, x: %d, y: %d, z: %d\n", gyro->roll, gyro->pitch, gyro->yaw, gyro->gyro_x, gyro->gyro_y, gyro->gyro_z);

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


ret Gyro_SetDataNum(Gyro_dataStruct *gyro, uint8_t num)
{
    gyro->num=num;
    return GYRO_OK;
}

uint8_t Gyro_GetDataNum(Gyro_dataStruct gyro)
{
    return gyro.num;
}


void Gyro_CountIncrement(void)
{
                                printf("\t\tSTART Gyro_CountIncrement();\n ");
    gyro_count+=1;
    printf("count: %d\n", gyro_count);
                                printf("\t\tEND Gyro_CountIncrement();\n ");
}

void Gyro_CountDecrement(void)
{
                                printf("\t\tSTART Gyro_CountDecrement();\n ");
    gyro_count-=1;
    printf("count: %d\n", gyro_count);
                                printf("\t\tEND Gyro_CountDecrement();\n ");
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