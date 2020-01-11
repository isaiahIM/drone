#ifndef MATRIX__H
#define MATRIX__H

#include <stdlib.h>

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
 * @param p_mat matrix pointer
 * @return uint8_t add matrix result
 *  @arg MATRIX_OK matrix add success
 *  @arg MATRIX_FAIL add matrix fail
 */
uint8_t Matrix_AddMatrix(uint16_t col, uint16_t row, matrix *p_mat);


/**
 * @brief delete matrix
 * 
 * @param p_mat matrix pointer
 */
void Matrix_Delete(matrix *p_mat);

/**
 * @brief add matrix
 * 
 * @param mat1 matrix 1
 * @param mat2 matrix 2
 * @param p_result matrix1+matrix2
 * @return uint8_t calculate status
 *  @arg MATRIX_OK calculate success
 *  @arg MATRIX_FAIL calculate fail
 */
uint8_t Matrix_Add(const matrix mat1, const matrix mat2, matrix *p_result);

/**
 * @brief subtraction matrix
 * 
 * @param mat1 matrix1
 * @param mat2 matrix2
 * @param p_result matrix1-matrix2
 * @return uint8_t calculate status
 *  @arg MATRIX_OK calculate success
 *  @arg MATRIX_FAIL calculate fail
 */
uint8_t Matrix_Sub(const matrix mat1, const matrix mat2, matrix *p_result);

/**
 * @brief multiply matrix
 * 
 * @param mat1 matrix1
 * @param mat2 matrix2
 * @param p_result matrix1*matrix2
 * @return uint8_t calculate status
 *  @arg MATRIX_OK calculate success
 *  @arg MATRIX_FAIL calculate fail
 */
uint8_t Matrix_Multi(const matrix mat1, const matrix mat2, matrix *p_result);

/**
 * @brief calculate inverse matrix
 * 
 * @param mat matrix
 * @param p_result inverse matrix
 * @return uint8_t calculate status
 *  @arg MATRIX_OK calculate success
 *  @arg MATRIX_FAIL calculate fail
 */
uint8_t Matrix_Inv(const matrix mat, matrix *p_result);

/**
 * @brief calculate transpose matrix
 * 
 * @param mat matrix
 * @param p_result transpose matrix
 * @return uint8_t calculate status
 *  @arg MATRIX_OK matrix add success
 *  @arg MATRIX_FAIL add matrix fail
 */
uint8_t Matrix_Transpose(const matrix mat, matrix *p_result);

/**
 * @brief calculate determinant matrix
 * 
 * @param mat matrix
 * @param p_result  determinant matrix
 * @return uint8_t calculate status
 *  @arg MATRIX_OK calculate success
 *  @arg MATRIX_FAIL calculate fail
 */
uint8_t Matrix_Det(const matrix mat, matrix *p_result);

/**
 * @brief get matrix component in position
 * 
 * @param mat matrix
 * @param col column position
 * @param row row position
 * @param p_component get p_component pointer
 * @return uint8_t component get status
 *  @arg MATRIX_OK component get success
 *  @arg MATRIX_FAIL component get fail
 */
uint8_t Matrix_GetData(matrix mat, uint16_t col, uint16_t row, matrixData_t *p_component);

/**
 * @brief set matrix component in position
 * 
 * @param p_mat matrix pointer
 * @param col column position
 * @param row row position
 * @param component setting component
 * @return uint8_t setting result
 *  @arg MATRIX_OK component setting success
 *  @arg MATRIX_FAIL component setting fail
 */
uint8_t Matrix_SetData(matrix *p_mat, uint16_t col, uint16_t row, matrixData_t component);

uint16_t Matrix_GetColumnSize(matrix mat);

uint16_t Matrix_GetRowSize(matrix mat);

#endif