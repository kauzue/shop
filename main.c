#include "main.h"
int menu = 1;

int main(void)
{

	Init();

	while (menu) {
		switch (menu)
		{
		case 1:
			OpenRoginMenu();
			break;

		case 2:
			OpenMenu();
			break;

		default:
			break;
		}
	}
}