#ifndef ESC_DRIVER__H
#define ESC_DRIVER__H

#include <stdio.h>
#include <stdint.h>

#define BSP_ESC_SUCCESS 0
#define BSP_ESC_FAIL 1

uint8_t BSP_ESC_HW_Initalize(void);
void BSP_ESC_Initalize(uint8_t esc_num, uint16_t min_speed, uint16_t max_speed);
void BSP_ESC_Deinitalize(uint8_t esc_num);
void BSP_ESC_RotateCW(uint8_t esc_num, uint16_t speed);
void BSP_ESC_RotateCCW(uint8_t esc_num, uint16_t speed);

static uint16_t speed;
#endif