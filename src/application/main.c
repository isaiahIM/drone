#include <stdio.h>
#include <stdlib.h>

// TODO:
// fix esc rotate direction issue
// fix ESC_AddContoolInfo() memory dump issue
 

/**user include header*/
#include "drone_lib.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[])
{
	ret ret_val;
	ret_val|=Drone_Init();

	Motor_CCW_Rotate(MOTOR1, 30);
	Motor_CCW_Rotate(MOTOR1, 50);

	Motor_CCW_Rotate(MOTOR2, 40);
	Motor_CCW_Rotate(MOTOR3, 60);
	Motor_CCW_Rotate(MOTOR4, 20);
	Motor_CCW_Rotate(MOTOR2|MOTOR3, 56);

	Motor_CW_Rotate(MOTOR1, 30);
	Motor_CW_Rotate(MOTOR1, 50);

	Motor_CW_Rotate(MOTOR2, 40);
	Motor_CW_Rotate(MOTOR3, 60);
	Motor_CW_Rotate(MOTOR2|MOTOR3, 56);

	Motor_Stop(MOTOR2);
	Motor_Stop(MOTOR1|MOTOR3);

	
	return 0;
}