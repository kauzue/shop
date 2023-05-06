#include "main.h"
int menu = 1;

enum menu {
	MENU_LOGIN = 1,
	MENU_OPEN_MENU
};

int main(void)
{
	Init();

	while (menu) {
		switch (menu) {
		case MENU_LOGIN:
			OpenRoginMenu();
			break;

		case 2:
			OpenMenu();
			break;

		default:
			break;
			
		}
	}
	return 0;
}