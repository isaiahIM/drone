#include <stdio.h>
#include <stdlib.h>
 
// TODO:
// add doxygen comment
// add code flow comment
// implement log, history system
// implement IMU middleware

/**user include header*/
#include "drone_lib.h"

int main(int argc, char *argv[])
{
	ret ret_val;
	ret_val|=Drone_Init();

	Propeller_CCW_Rotate(PROPELLER_1, 30);
	Propeller_CCW_Rotate(PROPELLER_1, 50);

	Propeller_CCW_Rotate(PROPELLER_2, 40);
	Propeller_CCW_Rotate(PROPELLER_3, 60);
	Propeller_CCW_Rotate(PROPELLER_4, 20);
	Propeller_CCW_Rotate(PROPELLER_2|PROPELLER_3, 56);

	Propeller_CW_Rotate(PROPELLER_1, 30);
	Propeller_CW_Rotate(PROPELLER_1, 50);

	Propeller_CW_Rotate(PROPELLER_2, 40);
	Propeller_CW_Rotate(PROPELLER_3, 60);
	Propeller_CW_Rotate(PROPELLER_2|PROPELLER_3, 56);

	Propeller_Stop(PROPELLER_2);
	Propeller_Stop(PROPELLER_1|PROPELLER_3);

	Propeller_DeInit(PROPELLER_ALL);

	return 0;
}