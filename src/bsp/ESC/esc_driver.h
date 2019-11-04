#ifndef ESC_DRIVER__H
#define ESC_DRIVER__H

#include <stdio.h>
#include <stdint.h>

#define BSP_ESC_OK 0
#define BSP_ESC_FAIL 1

/**
 * @brief ESC peripheral initalize
 * 
 * @return uint8_t initalize result
 *  @arg BSP_ESC_SUCCESS peripheral initalize success
 *  @arg BSP_ESC_FAIL peripheral initalize fail
 */
uint8_t BSP_ESC_HW_Initalize(void);

/**
 * @brief ESC system initalize
 * 
 * @param esc_num esc number
 * @param min_speed minimum speed
 * @param max_speed maximum speed
 */
void BSP_ESC_Initalize(uint8_t esc_num, uint16_t min_speed, uint16_t max_speed);

/**
 * @brief ESC de-initalize(system, peripheral)
 * 
 * @param esc_num 
 */
void BSP_ESC_Deinitalize(uint8_t esc_num);

/**
 * @brief ESC Clock-wise rotate
 * 
 * @param esc_num esc number
 * @param speed rotate speed
 */
void BSP_ESC_RotateCW(uint8_t esc_num, uint16_t speed);

/**
 * @brief ESC Counter-Clock-Wise rotate
 * 
 * @param esc_num esc number
 * @param speed rotate speed
 */
void BSP_ESC_RotateCCW(uint8_t esc_num, uint16_t speed);


#endif