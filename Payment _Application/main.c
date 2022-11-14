#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include"app.h"

int main(void)
{
	printf("Tester name: Hussein Ahmed\n");
	printf("Function Name: app start\n");

	while(1)
	 { 
		 if( appStart() == SERVER_ERROR)
			 break;
	 }
	return 0;

}