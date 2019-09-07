#include "esc_driver.h"

void BSP_ESC_Initalize(uint8_t esc_num, uint16_t min_speed, uint16_t max_speed)
{
    printf("----------------------------------------------START----------------------------------------------------\n");
    printf("esc initalize..\n");
    printf("num: %d\t minimum speed: %d\t maximum speed: %d\n", esc_num, min_speed, max_speed);
    printf("------------------------------------------------END----------------------------------------------------\n");
}

void BSP_ESC_Deinitalize(uint8_t esc_num)
{
    printf("----------------------------------------------START----------------------------------------------------\n");
    printf("esc de-initalize..\n");
    printf("num: %d\n", esc_num);
    printf("------------------------------------------------END----------------------------------------------------\n");
}

void BSP_ESC_RotateCW(uint8_t esc_num, uint16_t speed)
{
    printf("----------------------------------------------START----------------------------------------------------\n");
    printf("esc rotate CW..\n");
    printf("num: %d\t speed: %d\n", esc_num, speed);
    printf("------------------------------------------------END----------------------------------------------------\n");
}

void BSP_ESC_RotateCCW(uint8_t esc_num, uint16_t speed)
{
    printf("----------------------------------------------START----------------------------------------------------\n");
    printf("esc rotate CCW..\n");
    printf("num: %d\t speed: %d\n", esc_num, speed);
    printf("------------------------------------------------END----------------------------------------------------\n");
}