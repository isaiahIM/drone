#ifndef KALMAN_FILTER__H
#define KALMAN_FILTER__H

#include <math.h>
#include "matrix.h"
#include "common_def.h"
#include "drone_types.h"

/**
 * @brief kalman filter structure
 */
typedef struct kalmanfiltet_Structure
{
    matrix X;///< estimate data matrix
    matrix A;///< system matrix
    matrix Q;///< estimate covariance matrix
    matrix R;///< measure covariance matrix
    matrix P;///< Error covariance matrix
    matrix H;///< output matrix
} Kalman_struct;


void Kalman_SetSystemMatrix(Kalman_struct *kalman, matrix sys);

void Kalman_SetEstimateMatrix(Kalman_struct *kalman, matrix est);

void Kalman_SetEstimateCovarianceMatrix(Kalman_struct *kalman, matrix covariance);

void Kalman_SetMeasureCovarianceMatrix(Kalman_struct *kalman, matrix covariance);

void Kalman_SetErrorCovarianceMatrix(Kalman_struct *kalman, matrix covariance);

void Kalman_SetOutputMatrix(Kalman_struct *kalman, matrix output);

matrix Kalman_Calculate(Kalman_struct *kalman, matrix measure_data);

#endif