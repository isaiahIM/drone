#include "kalman_filter.h"
// TODO: 
// implement kalman filter library


void Kalman_SetSystemMatrix(Kalman_struct *p_kalman, matrix sys)
{
    p_kalman->A=sys;
}

void Kalman_SetEstimateMatrix(Kalman_struct *p_kalman, matrix est)
{
    p_kalman->X=est;
}

void Kalman_SetEstimateCovarianceMatrix(Kalman_struct *p_kalman, matrix covariance)
{
    p_kalman->Q=covariance;
}

void Kalman_SetMeasureCovarianceMatrix(Kalman_struct *p_kalman, matrix covariance)
{
    p_kalman->R=covariance;
}

void Kalman_SetErrorCovarianceMatrix(Kalman_struct *p_kalman, matrix covariance)
{
    p_kalman->P=covariance;
}

void Kalman_SetOutputMatrix(Kalman_struct *p_kalman, matrix output)
{
    p_kalman->H=output;
}

typedef struct kalmanfiltet_Structure
{
    matrix X;///< estimate data matrix
    matrix A;///< system matrix
    matrix Q;///< estimate covariance matrix
    matrix R;///< measure covariance matrix
    matrix P;///< Error covariance matrix
    matrix H;///< output matrix
} Kalman_struct;

matrix Kalman_Calculate(Kalman_struct *p_kalman, matrix measure_data)
{
    matrix buf, buf2;

    /**calculate estimate data matrix */
    p_kalman->X=Matrix_Multi(p_kalman->A, p_kalman->X);

    /**calculate estimate covariance matrix */
    buf=Matrix_Multi(Matrix_Multi(p_kalman->A, p_kalman->P), Matrix_Transpos(p_kalman->A) );
    p_kalman->P=Matrix_Add(buf, p_kalman->Q);

    /**calculate kalman gain */
}