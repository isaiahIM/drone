#ifndef MATRIX__H
#define MATRIX__H

#define MATRIX_OK 0
#define MATRIX_FAIL 1

typedef float matrixData_t;
/**
 * @brief matrix structure
 * 
 */
typedef struct matrix_structure
{
    uint16_t col;///< column
    uint16_t row;///< row
    matrixData_t *matrix_addr;///< matrix address
} matrix;

/**
 * @brief add new matrix
 * 
 * @param col column size
 * @param row row size
 * @param mat matrix pointer
 * @return uint16_t add result
 *  @arg MATRIX_OK matrix add success
 *  @arg MATRIX_FAIL add matrix fail
 */
uint8_t Matrix_AddMatrix(uint16_t col, uint16_t row, matrix *mat);

/**
 * @brief delete matrix
 * 
 * @param mat matrix pointer
 */
void Matrix_Delete(matrix *mat);

/**
 * @brief add matrix
 * 
 * @param mat1 matrix 1
 * @param mat2 matrix 2
 * @return matirx matrix1+matrix2
 *  @arg MATRIX_FAIL matrix calculate fail
 */
matrix Matrix_Add(const matrix mat1, const matrix mat2);

/**
 * @brief subtraction matrix
 * 
 * @param mat1 matrix1
 * @param mat2 matrix2
 * @return matrix matrix1-matrix2
 *  @arg MATRIX_FAIL matrix calculate fail
 */
matrix Matrix_Sub(const matrix mat1, const matrix mat2);

/**
 * @brief multiply matrix
 * 
 * @param mat1 matrix1
 * @param mat2 matrix2
 * @return matrix matrix1*matrix2
 *  @arg MATRIX_FAIL matrix calculate fail
 */
matrix Matrix_Multi(const matrix mat1, const matrix mat2);

/**
 * @brief calculate inverse matrix
 * 
 * @param mat matrix
 * @return matrix inverse matrix
 *  @arg MATRIX_FAIL matrix calculate fail
 */
matrix Matrix_Inv(const matrix mat);

/**
 * @brief calculate transpose matrix
 * 
 * @param mat matrix
 * @return matrix transpose matrix
 *  @arg MATRIX_FAIL matrix calculate fail
 */
matrix Matrix_Transpose(const matrix mat);

/**
 * @brief calculate determinant matrix
 * 
 * @param mat matrix
 * @return matrixData_t determinant matrix
 */
matrixData_t Matrix_Det(const matrix mat);

/**
 * @brief get matrix element in position
 * 
 * @param mat matrix
 * @param col column position
 * @param row row position
 * @return matrixData_t position element data
 */
matrixData_t Matrix_GetData(matrix mat, uint16_t col, uint16_t row);

/**
 * @brief set matrix element in position
 * 
 * @param mat matrix position
 * @param col column position
 * @param row row position
 * @param data setting data
 * @return uint8_t setting result
 *  @arg MATRIX_OK element add success
 *  @arg MATRIX_FAIL element add fail
 */
uint8_t Matrix_SetData(matrix *mat, uint16_t col, uint16_t row, matrixData_t data);

uint16_t Matrix_GetColumnSize(matrix mat);

uint16_t Matrix_GetRowSize(matrix mat);

#endif