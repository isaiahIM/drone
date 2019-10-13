/**
 * @file compass_lib.c
 * @author isaiah IM || isaiahim0214@gmail.com
 * @brief compass HAL Library source file
 * @version 0.1
 * @date 2019-09-22
 * 
 * @copyright Copyright (c) 2019 isaiah IM
 * 
 */
#include "compass_lib.h"

static Compass_dataStruct *data_prev=NULL, *data_cur=NULL, *data_head=NULL;
static Compass_initStruct *init_prev=NULL, *init_cur=NULL, *init_head=NULL;
static uint8_t compass_count=0;

ret Compass_Init(void)
{
    /**Compass_Init() sequence: */

    ret ret_val=COMPASS_OK;
                                printf("\t\tSTART Compass_Init();\n ");
    /**compass h/w initalize */
    ret_val|=BSP_Compass_HW_Initalize();
    if(ret_val!=COMPASS_OK)
    {
        ret_val|=COMPASS_HW_INIT_FAIL;
    }

    /**compass application initalize */

    /*make initalize structure dummy node */
    init_head=(Compass_initStruct*)malloc(sizeof(Compass_initStruct));
    if(init_head==NULL)
    {
                                        printf("Compass_Init(); fail1!!\n ");
        ret_val|=COMPASS_AP_INIT_FAIL;
        return ret_val;
    }
    init_cur=init_head;
    init_head->next=NULL;

    /*make data structure dummy node */
    data_head=(Compass_dataStruct*)malloc(sizeof(Compass_dataStruct));
    if(data_head==NULL)
    {
                                        printf("Compass_Init(); fail2!!\n ");
        ret_val|=COMPASS_AP_INIT_FAIL;
        return ret_val;
    }
    data_cur=data_head;
    data_head->next=NULL;

    /**compass count reset */
    compass_count=0;

                                printf("\t\tEXIT Compass_Init();\n ");
    /**return result */
    return ret_val;
}

uint8_t Compass_ConnectCheck(uint8_t num)
{
                                printf("\t\tSTART Compass_ConnectCheck();\n ");
    uint8_t connect_status=COMPASS_DISCONNECTED;

    connect_status=BSP_Compass_ChkConnect(num);
                                printf("\t\tEXIT Compass_ConnectCheck();\n ");
    return connect_status;
}


ret Compass_AddCompass(Compass_initStruct compass)
{
    /**Compass_AddCompass() sequence: */
                                printf("\t\tSTART Compass_AddCompass();\n ");
    Compass_dataStruct compass_data;
    ret ret_val=COMPASS_OK;
    uint8_t num, resolution;
    uint32_t cap_freq, com_freq;

    num=Compass_GetInitNum(compass);
    Compass_SetDataNum(&compass_data, num);

    resolution=Compass_GetResolution(compass);
    cap_freq=Compass_GetCaptureFreq(compass);
    com_freq=Compass_GetCommunicateFreq(compass);
                                printf("num: %d, res: %d, cap_freq: %d, com_freq: %d\n", num, resolution, cap_freq, com_freq);
    /**compass H/W setting */
    ret_val|=BSP_Compass_SetReolution(num, resolution);
    ret_val|=BSP_Compass_SetCaptureFreq(num, cap_freq);
    ret_val!=BSP_Compass_SetCommunicateFreq(num, com_freq);

    /**compass add informaion in list */
    ret_val|=Compass_AddInitalizeInfo(compass);
    ret_val|=Compass_AddDataInfo(compass_data);

    /**increment compass count */
    Compass_CountIncrement();

                                printf("\t\tEND Compass_AddCompass();\n ");
    /**return result */
    return ret_val;
}

ret Compass_DeleteCompass(uint8_t num)
{
    /**Compass_DeleteCompass() sequence: */
                                printf("\t\tSTART Compass_DeleteCompass();\n ");
    /**delcare and initalize values */
    ret ret_val=COMPASS_OK;
                                printf("delete num: %d\n", num);
    ret_val|=Compass_DeleteDataInfo(num);
    ret_val|=Compass_DeleteInitalizeInfo(num);
    
                                printf("\t\tEND Compass_DeleteCompass();\n ");
    return ret_val;
}


ret Compass_AddInitalizeInfo(Compass_initStruct compass)
{
    /**Compass_AddInitalizeInfo() sequence: */

                                printf("\t\tSTART Compass_AddInitalizeInfo();\n ");

    /**declare and initalize values */
    ret ret_val=COMPASS_OK;
    Compass_initStruct *buf;
    uint8_t num, resolution;
    uint32_t cap_freq, com_freq;

    /**get data in structure */
    cap_freq=Compass_GetCaptureFreq(compass);
    resolution=Compass_GetResolution(compass);
    com_freq=Compass_GetCommunicateFreq(compass);
    num=Compass_GetInitNum(compass);

    /**node allocate */
    buf=(Compass_initStruct*)malloc(sizeof(Compass_initStruct));
    if(buf==NULL)
    {
        ret_val=COMPASS_ADD_FAIL;
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
                                printf("\t\tEND Compass_AddInitalizeInfo();\n ");

    /**return result */
    return ret_val;
}

ret Compass_GetInitalizeInfo(uint8_t num, Compass_initStruct **compass)
{
    /**Compass_GetInitalizeInfo() sequence: */

                                printf("\t\tSTART Compass_GetInitalizeInfo();\n ");

    /**declare and reset values */
    ret ret_val=COMPASS_OK;

    /**reset current, preview position */
    Compass_ResetInitPos();

    /**search number in list */
    while(init_cur!=NULL)
    {
        if(Compass_GetInitNum(*init_cur)==num)
        {
            *compass=init_cur;

                                    printf("search num: %d, res: %d, cap_freq: %d, com_freq: %d\n", (*compass)->num, (*compass)->resolution, (*compass)->capture_freq, (*compass)->communication_freq);

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
        ret_val|=COMPASS_UNKNOWN_DATA;
    }

                                printf("\t\tEND Compass_GetInitalizeInfo();\n ");

    return ret_val;
}


ret Compass_DeleteInitalizeInfo(uint8_t num)
{
    /**Compass_DeleteInitalizeInfo() sequence: */

                                printf("\t\tSTART Compass_DeleteInitalizeInfo();\n ");

    /**declare and reset position */
    Compass_initStruct *delete;
    ret ret_val=COMPASS_OK;

    /**get delete node in list */
    ret_val|=Compass_GetInitalizeInfo(num, &delete);

    /**unlink data */
    init_prev->next=delete->next;
    init_cur=delete->next;

    printf("delete num: %d, res: %d, cap_freq: %d, com_freq: %d\n", delete->num, delete->resolution, delete->capture_freq, delete->communication_freq);

    /**delete data in list */
    free(delete);

    /**decrement compass count */
    Compass_CountDecrement();

                                printf("\t\tEND Compass_DeleteInitalizeInfo();\n ");

    /**return result */
    return ret_val;
}


ret Compass_AddDataInfo(Compass_dataStruct compass)
{
    /**Compass_AddDataInfo() sequence: */

                                printf("\t\tSTART Compass_AddDataInfo();\n ");

    /**declare and initlize values */
    Compass_dataStruct *buf;
    ret ret_val=COMPASS_OK;

    printf("PREV num: %d\n", compass.num);
    /**node allocate */
    buf=(Compass_dataStruct*)malloc(sizeof(Compass_dataStruct));
    if(buf==NULL)
    {
                                printf("compass add fail!!\n");
        ret_val=COMPASS_ADD_FAIL;
        return ret_val;
    }

    /**data copy */
    buf->num=compass.num;
    buf->compass_x=compass.compass_x;
    buf->compass_y=compass.compass_y;
    buf->compass_z=compass.compass_z;

    /**add node in list */
    data_prev=data_cur;
    buf->next=data_cur->next;
    data_cur->next=buf;
    data_cur=buf;

    printf("CUR num: %d\n", data_cur->num);

                                printf("\t\tEND Compass_AddDataInfo();\n ");

    /**return result */
    return ret_val;
}

ret Compass_GetDataInfo(uint8_t num, Compass_dataStruct **compass)
{
    /**Compass_GetDataInfo() sequence: */

                                printf("\t\tSTART Compass_GetDataInfo();\n");

    /**declare and reset values */
    ret ret_val=COMPASS_OK;

    /**reset current, preview position */
    Compass_ResetDataPos();

    /**search number in list */
    while(data_cur!=NULL)
    {
        if(Compass_GetDataNum(*data_cur)==num)
        {
            *compass=data_cur;

            printf("search num: %d, compass_x: %d, compass_y: %d, compass_z: %d\n", (*compass)->num, (*compass)->compass_x, (*compass)->compass_y, (*compass)->compass_z);

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
        printf("compass search fail!!\n");
        ret_val|=COMPASS_UNKNOWN_DATA;
    }

                                printf("\t\tEND Compass_GetDataInfo();\n ");

    return ret_val;
}

ret Compass_DeleteDataInfo(uint8_t num)
{
    /**Compass_DeleteDataInfo() sequence: */

                                printf("\t\tSTART Compass_DeleteDataInfo();\n ");

    /**declare and reset position */
    Compass_dataStruct *delete;
    ret ret_val=COMPASS_OK;

    /**get delete node in list */
    ret_val|=Compass_GetDataInfo(num, &delete);

    /**unlink data */
    data_prev->next=delete->next;
    data_cur=delete->next;

    printf("delete num: %d, compass_x: %d, compass_y: %d, compass_z: %d\n", delete->num, delete->compass_x, delete->compass_y, delete->compass_z);

    /**delete data in list */
    free(delete);

                                printf("\t\tEND Compass_DeleteDataInfo();\n ");


    /**return result */
    return ret_val;
}


ret Compass_SetNum(Compass_initStruct *compass, uint8_t num)
{
    ret ret_val=COMPASS_OK;

                                printf("\t\tSTART Compass_SetNum();\n ");

    if(compass==NULL)
    {
        printf("compass set fail!!\n");

        ret_val=COMPASS_SET_DATA_FAIL;
        return ret_val;
    }

    compass->num=num;

    printf("num: %d\n", compass->num);

                                printf("\t\tEND Compass_SetNum();\n ");
    return ret_val;
}

ret Compass_SetResolution(Compass_initStruct *compass, uint8_t resolution_bit)
{
    ret ret_val=COMPASS_OK;

                                printf("\t\tSTART Compass_SetResolution();\n ");

    if(compass==NULL)
    {
        printf("compass set fail!!\n");

        ret_val=COMPASS_SET_DATA_FAIL;
        return ret_val;
    }

    compass->resolution=resolution_bit;

    printf("resolution: %d\n", compass->resolution);

                                printf("\t\tEND Compass_SetResolution();\n ");

    return ret_val;
}

ret Compass_SetCaptureFreq(Compass_initStruct *compass, uint32_t freq)
{
    ret ret_val=COMPASS_OK;
                                printf("\t\tSTART Compass_SetCaptureFreq();\n ");

    if(compass==NULL)
    {
        printf("compass set fail!!\n");

        ret_val=COMPASS_SET_DATA_FAIL;
        return ret_val;
    }

    compass->capture_freq=freq;

    printf("cap_frq: %d\n", compass->capture_freq);

                                printf("\t\tEND Compass_SetCaptureFreq();\n ");

    return ret_val;
}

ret Compass_SetCommunicateFreq(Compass_initStruct *compass, uint32_t freq)
{
    ret ret_val=COMPASS_OK;

                                printf("\t\tSTART Compass_SetCommunicateFreq();\n ");

    if(compass==NULL)
    {
        printf("compass set fail!!\n");

        ret_val=COMPASS_SET_DATA_FAIL;
        return ret_val;
    }

    compass->communication_freq=freq;

    printf("communication_freq: %d\n", compass->communication_freq);

                                printf("\t\tEND Compass_SetCommunicateFreq();\n ");

    return ret_val;
}


uint8_t Compass_GetInitNum(Compass_initStruct compass)
{
    return compass.num;
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

ret Compass_GetCompassData(uint8_t num, Compass_dataStruct *compass)
{
    ret ret_val=COMPASS_OK;
    uint32_t data;

    ret_val|=Compass_GetDataInfo(num, &compass);
    if(ret_val!=COMPASS_OK)
    {
        return COMPASS_GET_DATA_FAIL;
    }

    ret_val|=BSP_Compass_GetX(num, &data);
    compass->compass_x=data;

    ret_val|=BSP_Compass_GetY(num, &data);
    compass->compass_y=data;
    
    ret_val|=BSP_Compass_GetZ(num, &data);
    compass->compass_z=data;

    if(ret_val!=COMPASS_OK)
    {
        return COMPASS_GET_DATA_FAIL;
    }
    else
    {
        return COMPASS_OK;
    }
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


ret Compass_SetDataNum(Compass_dataStruct *compass, uint8_t num)
{
    compass->num=num;
    return COMPASS_OK;
}

uint8_t Compass_GetDataNum(Compass_dataStruct compass)
{
    return compass.num;
}


void Compass_CountIncrement(void)
{
                                printf("\t\tSTART Compass_CountIncrement();\n ");
    compass_count+=1;
    printf("count: %d\n", compass_count);
                                printf("\t\tEND Compass_CountIncrement();\n ");
}

void Compass_CountDecrement(void)
{
                                printf("\t\tSTART Compass_CountDecrement();\n ");
    compass_count-=1;
    printf("count: %d\n", compass_count);
                                printf("\t\tEND Compass_CountDecrement();\n ");
}


void Compass_ResetDataPos(void)
{
    data_cur=data_head->next;
    data_prev=data_head;
}

void Compass_ResetInitPos(void)
{
    init_cur=init_head->next;
    init_prev=init_head;
}