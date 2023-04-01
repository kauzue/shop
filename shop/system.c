#pragma warning(disable:4996)

#include <stdio.h>

#include "main.h"

void menu()
{
	int choice = 0;

	printf("1.로그인 \n");
	printf("2.회원가입 \n");

	scanf("%d", &choice);

	switch (choice)
	{
	case 1:
		rogin();
		break;

	case 2:
		signup();
		break;

	default:
		break;
	}
}

void rogin()
{

}

void signup()
{
	printf("ID :");
}