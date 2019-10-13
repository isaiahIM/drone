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

static Accel_dataStruct *data_prev=NULL, *data_cur=NULL, *data_head=NULL;
static Accel_initStruct *init_prev=NULL, *init_cur=NULL, *init_head=NULL;
static uint8_t accel_count=0;

ret Accel_Init(void)
{
    /**Accel_Init() sequence: */

    ret ret_val=ACCEL_OK;
                                printf("\t\tSTART Accel_Init();\n ");
    /**accel h/w initalize */
    ret_val|=BSP_Accel_HW_Initalize();
    if(ret_val!=ACCEL_OK)
    {
        ret_val|=ACCEL_HW_INIT_FAIL;
    }

    /**accel application initalize */

    /*make initalize structure dummy node */
    init_head=(Accel_initStruct*)malloc(sizeof(Accel_initStruct));
    if(init_head==NULL)
    {
                                        printf("Accel_Init(); fail1!!\n ");
        ret_val|=ACCEL_AP_INIT_FAIL;
        return ret_val;
    }
    init_cur=init_head;
    init_head->next=NULL;

    /*make data structure dummy node */
    data_head=(Accel_dataStruct*)malloc(sizeof(Accel_dataStruct));
    if(data_head==NULL)
    {
                                        printf("Accel_Init(); fail2!!\n ");
        ret_val|=ACCEL_AP_INIT_FAIL;
        return ret_val;
    }
    data_cur=data_head;
    data_head->next=NULL;

    /**accel count reset */
    accel_count=0;

                                printf("\t\tEXIT Accel_Init();\n ");
    /**return result */
    return ret_val;
}

uint8_t Accel_ConnectCheck(uint8_t num)
{
                                printf("\t\tSTART Accel_ConnectCheck();\n ");
    uint8_t connect_status=ACCEL_DISCONNECTED;

    connect_status=BSP_Accel_ChkConnect(num);
                                printf("\t\tEXIT Accel_ConnectCheck();\n ");
    return connect_status;
}


ret Accel_AddAccel(Accel_initStruct accel)
{
    /**Accel_AddAccel() sequence: */
                                printf("\t\tSTART Accel_AddAccel();\n ");
    Accel_dataStruct accel_data;
    ret ret_val=ACCEL_OK;
    uint8_t num, resolution;
    uint32_t capture_freq, com_freq;

    num=Accel_GetInitNum(accel);
    Accel_SetDataNum(&accel_data, num);

    resolution=Accel_GetResolution(accel);
    capture_freq=Accel_GetCaptureFreq(accel);
    com_freq=Accel_GetCommunicateFreq(accel);
                                printf("num: %d, res: %d, cap_freq: %d, com_freq: %d\n", num, resolution, capture_freq, com_freq);
    /**accel H/W setting */
    ret_val|=BSP_Accel_SetReolution(num, resolution);
    ret_val|=BSP_Accel_SetCaptureFreq(num, capture_freq);
    ret_val!=BSP_Accel_SetCommunicateFreq(num, com_freq);

    /**accel add informaion in list */
    ret_val|=Accel_AddInitalizeInfo(accel);
    ret_val|=Accel_AddDataInfo(accel_data);

    /**increment accel count */
    Accel_CountIncrement();

                                printf("\t\tEND Accel_AddAccel();\n ");
    /**return result */
    return ret_val;
}

ret Accel_DeleteAccel(uint8_t num)
{
    /**Accel_DeleteAccel() sequence: */
                                printf("\t\tSTART Accel_DeleteAccel();\n ");
    /**delcare and initalize values */
    ret ret_val=ACCEL_OK;
                                printf("delete num: %d\n", num);
    ret_val|=Accel_DeleteDataInfo(num);
    ret_val|=Accel_DeleteInitalizeInfo(num);
    
                                printf("\t\tEND Accel_DeleteAccel();\n ");
    return ret_val;
}


ret Accel_AddInitalizeInfo(Accel_initStruct accel)
{
    /**Accel_AddInitalizeInfo() sequence: */

                                printf("\t\tSTART Accel_AddInitalizeInfo();\n ");

    /**declare and initalize values */
    ret ret_val=ACCEL_OK;
    Accel_initStruct *buf;
    uint8_t num, resolution;
    uint32_t cap_freq, com_freq;

    /**get data in structure */
    cap_freq=Accel_GetCaptureFreq(accel);
    resolution=Accel_GetResolution(accel);
    com_freq=Accel_GetCommunicateFreq(accel);
    num=Accel_GetInitNum(accel);

    /**node allocate */
    buf=(Accel_initStruct*)malloc(sizeof(Accel_initStruct));
    if(buf==NULL)
    {
        ret_val=ACCEL_ADD_FAIL;
        return ret_val;
    }

    /**structure data copy */
    buf->num=num;
    buf->resolution=resolution;
    buf->capture_freq=cap_freq;
    buf->communication_freq=com_freq;

    /**add node in list */
    init_prev=init_cur;
    buf->next=init_cur->next;
    init_cur->next=buf;
    init_cur=buf;
                                printf("num: %d, res: %d, cap_freq: %d, com_freq: %d\n", init_cur->num, init_cur->resolution, init_cur->capture_freq, init_cur->communication_freq);
                                printf("\t\tEND Accel_AddInitalizeInfo();\n ");

    /**return result */
    return ret_val;
}

ret Accel_GetInitalizeInfo(uint8_t num, Accel_initStruct **accel)
{
    /**Accel_GetInitalizeInfo() sequence: */

                                printf("\t\tSTART Accel_GetInitalizeInfo();\n ");

    /**declare and reset values */
    ret ret_val=ACCEL_OK;

    /**reset current, preview position */
    Accel_ResetInitPos();

    /**search number in list */
    while(init_cur!=NULL)
    {
        if(Accel_GetInitNum(*init_cur)==num)
        {
            *accel=init_cur;

                                    printf("search num: %d, res: %d, cap_freq: %d, com_freq: %d\n", (*accel)->num, (*accel)->resolution, (*accel)->capture_freq, (*accel)->communication_freq);

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
        ret_val|=ACCEL_UNKNOWN_DATA;
    }

                                printf("\t\tEND Accel_GetInitalizeInfo();\n ");

    return ret_val;
}


ret Accel_DeleteInitalizeInfo(uint8_t num)
{
    /**Accel_DeleteInitalizeInfo() sequence: */

                                printf("\t\tSTART Accel_DeleteInitalizeInfo();\n ");

    /**declare and reset position */
    Accel_initStruct *delete;
    ret ret_val=ACCEL_OK;

    /**get delete node in list */
    ret_val|=Accel_GetInitalizeInfo(num, &delete);

    /**unlink data */
    init_prev->next=delete->next;
    init_cur=delete->next;

    printf("delete num: %d, res: %d, cap_freq: %d, com_freq: %d\n", delete->num, delete->resolution, delete->capture_freq, delete->communication_freq);

    /**delete data in list */
    free(delete);

    /**decrement accel count */
    Accel_CountDecrement();

                                printf("\t\tEND Accel_DeleteInitalizeInfo();\n ");

    /**return result */
    return ret_val;
}


ret Accel_AddDataInfo(Accel_dataStruct accel)
{
    /**Accel_AddDataInfo() sequence: */

                                printf("\t\tSTART Accel_AddDataInfo();\n ");

    /**declare and initlize values */
    Accel_dataStruct *buf;
    ret ret_val=ACCEL_OK;

    printf("PREV num: %d\n", accel.num);
    /**node allocate */
    buf=(Accel_dataStruct*)malloc(sizeof(Accel_dataStruct));
    if(buf==NULL)
    {
                                printf("accel add fail!!\n");
        ret_val=ACCEL_ADD_FAIL;
        return ret_val;
    }

    /**data copy */
    buf->num=accel.num;
    buf->accel_x=accel.accel_x;
    buf->accel_y=accel.accel_y;
    buf->accel_z=accel.accel_z;

    /**add node in list */
    data_prev=data_cur;
    buf->next=data_cur->next;
    data_cur->next=buf;
    data_cur=buf;

    printf("CUR num: %d\n", data_cur->num);

                                printf("\t\tEND Accel_AddDataInfo();\n ");

    /**return result */
    return ret_val;
}

ret Accel_GetDataInfo(uint8_t num, Accel_dataStruct **accel)
{
    /**Accel_GetDataInfo() sequence: */

                                printf("\t\tSTART Accel_GetDataInfo();\n");

    /**declare and reset values */
    ret ret_val=ACCEL_OK;

    /**reset current, preview position */
    Accel_ResetDataPos();

    /**search number in list */
    while(data_cur!=NULL)
    {
        if(Accel_GetDataNum(*data_cur)==num)
        {
            *accel=data_cur;

            printf("search num: %d, accel_x: %d, accel_y: %d, accel_z: %d\n", (*accel)->num, (*accel)->accel_x, (*accel)->accel_y, (*accel)->accel_z);

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
        printf("accel search fail!!\n");
        ret_val|=ACCEL_UNKNOWN_DATA;
    }

                                printf("\t\tEND Accel_GetDataInfo();\n ");

    return ret_val;
}

ret Accel_DeleteDataInfo(uint8_t num)
{
    /**Accel_DeleteDataInfo() sequence: */

                                printf("\t\tSTART Accel_DeleteDataInfo();\n ");

    /**declare and reset position */
    Accel_dataStruct *delete;
    ret ret_val=ACCEL_OK;

    /**get delete node in list */
    ret_val|=Accel_GetDataInfo(num, &delete);

    /**unlink data */
    data_prev->next=delete->next;
    data_cur=delete->next;

    printf("delete num: %d, accel_x: %d, accel_y: %d, accel_z: %d\n", delete->num, delete->accel_x, delete->accel_y, delete->accel_z);

    /**delete data in list */
    free(delete);

                                printf("\t\tEND Accel_DeleteDataInfo();\n ");


    /**return result */
    return ret_val;
}


ret Accel_SetNum(Accel_initStruct *accel, uint8_t num)
{
    ret ret_val=ACCEL_OK;

                                printf("\t\tSTART Accel_SetNum();\n ");

    if(accel==NULL)
    {
        printf("accel set fail!!\n");

        ret_val=ACCEL_SET_DATA_FAIL;
        return ret_val;
    }

    accel->num=num;

    printf("num: %d\n", accel->num);

                                printf("\t\tEND Accel_SetNum();\n ");
    return ret_val;
}

ret Accel_SetResolution(Accel_initStruct *accel, uint8_t resolution_bit)
{
    ret ret_val=ACCEL_OK;

                                printf("\t\tSTART Accel_SetResolution();\n ");

    if(accel==NULL)
    {
        printf("accel set fail!!\n");

        ret_val=ACCEL_SET_DATA_FAIL;
        return ret_val;
    }

    accel->resolution=resolution_bit;

    printf("resolution: %d\n", accel->resolution);

                                printf("\t\tEND Accel_SetResolution();\n ");

    return ret_val;
}

ret Accel_SetCaptureFreq(Accel_initStruct *accel, uint32_t freq)
{
    ret ret_val=ACCEL_OK;
                                printf("\t\tSTART Accel_SetCaptureFreq();\n ");

    if(accel==NULL)
    {
        printf("accel set fail!!\n");

        ret_val=ACCEL_SET_DATA_FAIL;
        return ret_val;
    }

    accel->capture_freq=freq;

    printf("cap_frq: %d\n", accel->capture_freq);

                                printf("\t\tEND Accel_SetCaptureFreq();\n ");

    return ret_val;
}

ret Accel_SetCommunicateFreq(Accel_initStruct *accel, uint32_t freq)
{
    ret ret_val=ACCEL_OK;

                                printf("\t\tSTART Accel_SetCommunicateFreq();\n ");

    if(accel==NULL)
    {
        printf("accel set fail!!\n");

        ret_val=ACCEL_SET_DATA_FAIL;
        return ret_val;
    }

    accel->communication_freq=freq;

    printf("communication_freq: %d\n", accel->communication_freq);

                                printf("\t\tEND Accel_SetCommunicateFreq();\n ");

    return ret_val;
}


uint8_t Accel_GetInitNum(Accel_initStruct accel)
{
    return accel.num;
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

ret Accel_GetAccelData(uint8_t num, Accel_dataStruct *accel)
{
    ret ret_val=ACCEL_OK;
    uint32_t data;

    ret_val|=Accel_GetDataInfo(num, &accel);
    if(ret_val!=ACCEL_OK)
    {
        return ACCEL_GET_DATA_FAIL;
    }

    ret_val|=BSP_Accel_GetX(num, &data);
    accel->accel_x=data;

    ret_val|=BSP_Accel_GetY(num, &data);
    accel->accel_y=data;
    
    ret_val|=BSP_Accel_GetZ(num, &data);
    accel->accel_z=data;

    if(ret_val!=ACCEL_OK)
    {
        return ACCEL_GET_DATA_FAIL;
    }
    else
    {
        return ACCEL_OK;
    }
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


ret Accel_SetDataNum(Accel_dataStruct *accel, uint8_t num)
{
    accel->num=num;
    return ACCEL_OK;
}

uint8_t Accel_GetDataNum(Accel_dataStruct accel)
{
    return accel.num;
}


void Accel_CountIncrement(void)
{
                                printf("\t\tSTART Accel_CountIncrement();\n ");
    accel_count+=1;
    printf("count: %d\n", accel_count);
                                printf("\t\tEND Accel_CountIncrement();\n ");
}

void Accel_CountDecrement(void)
{
                                printf("\t\tSTART Accel_CountDecrement();\n ");
    accel_count-=1;
    printf("count: %d\n", accel_count);
                                printf("\t\tEND Accel_CountDecrement();\n ");
}


void Accel_ResetDataPos(void)
{
    data_cur=data_head->next;
    data_prev=data_head;
}

void Accel_ResetInitPos(void)
{
    init_cur=init_head->next;
    init_prev=init_head;
}