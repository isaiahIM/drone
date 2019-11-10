#include "kalman_filter.h"
// TODO: 
// implement kalman filter library

static uint8_t kalman_count=0;
static Kalman_initStruct *cur=NULL;
static Kalman_initStruct *prev=NULL;
static Kalman_initStruct *head=NULL;

ret Kalman_Init(void)
{
    /**Kalman_Init() sequence: */
    ret ret_val=KALMAN_OK;

    /**list initalize.. */
    prev=head;
    head=(Kalman_initStruct*)calloc(1, sizeof(Kalman_initStruct) );
    if(head==NULL)
    {
        ret_val|=KALAMN_FAIL;
                                printf("kalman filter allocate fail!!\n");
        return ret_val;
    }
    cur=head;
    head->next=NULL;

    return ret_val;
}

ret Kalman_Add(uint8_t num, Kalman_initStruct kalman)
{
    /**Kalman_Add() sequence: */

    /**declare values */
    ret ret_val=KALMAN_OK;
    Kalman_initStruct *p_buf;

    /**node allocate */
    buf=(Kalman_initStruct*)calloc(1, sizeof(Kalman_initStruct) );
    if(buf==NULL)
    {
        ret_val|=KALAMN_FAIL;
                                    printf("kalman filter allocate fail!!\n");
        return ret_val;
    }

    /**node data set */
    memcpy(p_buf, &kalman, sizeof(Kalman_initStruct) );

    /**insert node in list */
    prev=cur;
    buf->next=cur->next;
    cur->next=buf;
    cur=buf;

    return ret_val;
}

ret Kalman_Delete(uint8_t num)
{
    /**Kalman_Delete() sequence: */

    /**declare values */
    ret ret_val=KALMAN_OK;
    Kalman_initStruct *del;


    ret_val|=Kalman_GetInfo(num, &del);

    /**unlink node */
    prev->next=cur->next;
    del=cur;
    cur=cur->next;

    /**delete node */
    free(del);

    return ret_val;
}

double Kalman_GetRoll(uint8_t num, double gy_roll, double acc_roll, double comp_roll);
double Kalman_GetPitch(uint8_t num, double gy_pitch, double acc_pitch, double comp_pitch);
double Kalman_GetYaw(uint8_t num, double gy_yaw, double comp_yaw);