#pragma warning(disable:4996)

#include <stdio.h>

#include "main.h"

#include <Windows.h>

void RoginMenu()
{
	int choice = 0;

	printf("****로그인 메뉴**** \n");
	printf("1. 로그인 \n");
	printf("2. 회원가입 \n");
	printf("------------------- \n");
	printf("선택 : ");

	scanf("%d", &choice);

	switch (choice)
	{
	case 1:
		system("cls");
		SignIn();
		break;

	case 2:
		system("cls");
		SignUp();
		break;

	default:
		break;
	}
}

void SignIn()
{
	char ID[20];
	char password[20];

	printf("아이디 : ");
	scanf("%s", &ID);

	printf("비밀번호 : ");
	scanf("%s", &password);
	system("cls");
}

void SignUp()
{
	printf("20자 이내의 아이디를 써 주세요. \n");
	printf("ID : ");
	scanf("%s", &member.ID);
	system("cls");

	printf("20자 이내의 비밀번호를 써 주세요. \n");
	printf("Password: ");
	scanf("%s", &member.password);
	system("cls");

	SignIn();
}