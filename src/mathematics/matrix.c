#include "matrix.h"


uint8_t Matrix_AddMatrix(int col, int row, matrix *p_mat)
{
    /**Matrix_AddMatrix() sequence: */

    /**declare values */
    uint8_t ret_val=MATRIX_OK;
    matrixData_t *p_buf;
    
    /**allocate matrix array */
    p_buf=calloc(col*row, sizeof(matrixData_t));
    if(p_buf==NULL)
    {
        return MATRIX_FAIL;
    }

    /**linking matrix array in structure */
    p_mat->matrix_addr=p_buf;

    /**return result */
    return ret_val;
}

void Matrix_Delete(matrix *p_mat)
{
    p_mat->col=0;
    p_mat->row=0;
    free(p_mat->matrix_addr);
}


uint8_t Matrix_Add(const matrix mat1, const matrix mat2, matrix *p_result);
{
    /**Matrix_Add() sequence: */
    
    /**checking able to matrix calculatng */
    if( (mat1.col!= mat2.col) || (mat1.row!=mat2.row) )
    {
        *p_result=NULL;
        return MATRIX_FAIL;
    }

    /**declare values */
    uint16_t col, row;
    matrix mat_result;
    uint8_t ret_val=MATRIX_OK;
    matrixData_t mat1_data, mat2_data;
    

    /**allocate result matrix */
    if(Matrix_AddMatrix(mat1.col, mat1.row, &mat_result)==MATRIX_FAIL)
    {
        return MATRIX_FAIL;
    }

    /**add mat1 + mat2 */
    for(col=0; col<mat1.col; col++)
    {
        for(row=0; row<mat1.row; row++)
        {
            ret_val|=Matrix_GetData(mat1, col, row, &mat1_data);
            ret_val|=Matrix_GetData(mat2, col, row, &mat2_data);

            ret_val|=Matrix_SetData(&mat_result, col, row, mat1_data + mat2_data);
        }
    }

    /**return mat1 + mat2 */
    *p_result=mat_result;

    /**delete allocated data */
    Matrix_Delete(&mat_result);

    /**return calculate status */
    return ret_val;
}

uint8_t Matrix_Sub(const matrix mat1, const matrix mat2, matrix *p_result);
{
    /**Matrix_Sub() sequence: */

    /**checking able to matrix calculatng */
    if( (mat1.col!= mat2.col) || (mat1.row!=mat2.row) )
    {
        *p_result=NULL;
        return MATRIX_FAIL;
    }

    /**declare values */
    uint16_t col, row;
    matrix mat_result;
    uint8_t ret_val=MATRIX_OK;
    matrixData_t mat1_data, mat2_data;
    

    /**allocate result matrix */
    if(Matrix_AddMatrix(mat1.col, mat1.row, &mat_result)==MATRIX_FAIL)
    {
        return MATRIX_FAIL;
    }

    /**subtraction mat1 - mat2 */
    for(col=0; col<mat1.col; col++)
    {
        for(row=0; row<mat1.row; row++)
        {
            ret_val|=Matrix_GetData(mat1, col, row, &mat1_data);
            ret_val|=Matrix_GetData(mat2, col, row, &mat2_data);

            ret_val|=Matrix_SetData(&mat_result, col, row, mat1_data - mat2_data);
        }
    }

    /**return mat1 + mat2 */
    *p_result=matrix1;

    /**delete allocated data */
    Matrix_Delete(&mat_result);

    /**return calculate status */
    return MATRIX_OK;
}

uint8_t Matrix_Multi(const matrix mat1, const matrix mat2, matrix *p_result);
{
    /**Matrix_Multi() sequence: */

    /**checking able to matrix calculatng */
    if(mat1.row!=mat2.col)
    {
        return MATRIX_FAIL;
    }

    /**declare value */
    uint8_t ret_val=MATRIX_OK;
    uint16_t col, row, calc_row;
    matrixData_t sum, mat1_data, mat2_data;
    matrix mat_result;

    /**allocate result matrix */
    if(Matrix_AddMatrix(mat1.col, mat2.row, &mat_result)==MATRIX_FAIL)
    {
        return MATRIX_FAIL;
    }

    /**calculate mat1 * mat2 */
    for(row=0; row<mat1.row; row++)
    {
        for(col=0; col<mat2.col; col++)
        {
            sum=0;
            for(calc_row=0; calc_row<mat2.row; calc_row++)
            {
                ret_val|=Matrix_GetData(mat1, row, calc_row, &mat1_data);
                ret_val|=Matrix_GetData(mat2, calc_row, col, &mat2_data);

                sum+=mat1_data*mat2_data;
            }
            ret_val|=Matrix_SetData(&mat_result, col, row, sum);
        }
    }

    /**return mat1 + mat2 */
    *p_result=matrix1;

    /**delete allocated data */
    Matrix_Delete(&mat_result);

    /**return calculate status */
    return ret_val;
}


// TODO:
// implement matrix library
uint8_t Matrix_Inv(const matrix mat, matrix *p_result);


uint8_t Matrix_Transpose(const matrix mat, matrix *p_result);


uint8_t Matrix_Det(const matrix mat, matrix *p_result);


uint8_t Matrix_GetData(matrix mat, uint16_t col, uint16_t row, matrixData_t *p_component);


uint8_t Matrix_SetData(matrix *p_mat, uint16_t col, uint16_t row, matrixData_t component);

uint16_t Matrix_GetColumnSize(matrix mat);

uint16_t Matrix_GetRowSize(matrix mat);