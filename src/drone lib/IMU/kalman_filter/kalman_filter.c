#include "kalman_filter.h"
// TODO: 
// implement kalman filter library


void Kalman_SetSystemMatrix(Kalman_struct *kalman, matrix sys)
{
    kalman->A=sys;
}

void Kalman_SetEstimateMatrix(Kalman_struct *kalman, matrix est)
{
    kalman->X=est;
}

void Kalman_SetEstimateCovarianceMatrix(Kalman_struct *kalman, matrix covariance)
{
    kalman->Q=covariance;
}

void Kalman_SetMeasureCovarianceMatrix(Kalman_struct *kalman, matrix covariance)
{
    kalman->R=covariance;
}

void Kalman_SetErrorCovarianceMatrix(Kalman_struct *kalman, matrix covariance)
{
    kalman->P=covariance;
}

void Kalman_SetOutputMatrix(Kalman_struct *kalman, matrix output)
{
    kalman->H=output;
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

matrix Kalman_Calculate(Kalman_struct *kalman, matrix measure_data)
{
    matrix buf, buf2;

    /**calculate estimate data matrix */
    kalman->X=Matrix_Multi(kalman->A, kalman->X);

    /**calculate estimate covariance matrix */
    buf=Matrix_Multi(Matrix_Multi(kalman->A, kalman->P), Matrix_Transpos(kalman->A) );
    kalman->P=Matrix_Add(buf, kalman->Q);

    /**calculate kalman gain */
}