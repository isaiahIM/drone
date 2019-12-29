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
 * @brief add two matrix
 * 
 * @param mat1 matrix 1
 * @param mat2 matrix 2
 * @param result add matrix1 + matrix2 result
 * @return uint8_t calculate status
 *  @arg MATRIX_OK calculate success
 *  @arg MATRIX_FAIL calculate fail
 */
uint8_t Matrix_Add(const matrix mat1, const matrix mat2, matrix *result);

uint8_t Matrix_Sub(const matrix mat1, const matrix mat2, matrix *result);

uint8_t Matrix_Multi(const matrix mat1, const matrix mat2, matrix *result);

uint8_t Matrix_Div(const matrix mat1, const matrix mat2, matrix *result);

uint8_t Matrix_Inv(const matrix origin, matrix *inv);

uint8_t Matrix_Transpos(const matrix origin, matrix *transpos);

uint8_t Matrix_Det(const matrix mat, matrixData_t result);

uint8_t Matrix_GetData(matrix mat, uint16_t col, uint16_t row, matrixData_t data);

uint8_t Matrix_SetData(matrix *mat, uint16_t col, uint16_t row, matrixData_t data);

uint8_t Matrix_GetStatus(void);

#endif