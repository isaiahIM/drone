#include "matrix.h"

uint8_t Matrix_AddMatrix(int col, int row, matrix *mat)
{
    /**Matrix_AddMatrix() sequence: */

    /**declare values */
    ret ret_val=MATRIX_OK;
    matrixData_t *buf;
    
    /**allocate matrix array */
    buf=calloc(col*row, sizeof(matrixData_t));
    if(buf==NULL)
    {
        return MATRIX_FAIL;
    }

    /**linking matrix array in structure */
    mat->matrix_addr=buf;

    /**return result */
    return ret_val;
}

void Matrix_Delete(matrix *mat)
{
    free(mat->matrix_addr);
}

matrix Matrix_Add(const matrix mat1, const matrix mat2;

matrix Matrix_Sub(const matrix mat1, const matrix mat2);

matrix Matrix_Multi(const matrix mat1, const matrix mat2);

matrix Matrix_Div(const matrix mat1, const matrix mat2);

matrix Matrix_Inv(const matrix mat);

matrix Matrix_Transpos(const matrix mat);

matrixData_t Matrix_Det(const matrix mat);

matrixData_t Matrix_GetData(matrix mat, uint16_t col, uint16_t row, matrixData_t data);

uint8_t Matrix_SetData(matrix *mat, uint16_t col, uint16_t row);

uint8_t Matrix_GetStatus(void);