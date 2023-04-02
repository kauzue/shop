#pragma warning(disable:4996)

#include <stdio.h>

#include "main.h"

#include <Windows.h>

void RoginMenu()
{
	int choice = 0;
	printf("*****로그인 메뉴***** \n");
	printf("1. 로그인 \n");
	printf("2. 회원가입 \n");
	printf("--------------------- \n");
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

void Menu()
{

}

void SignIn()
{
	char ID[100];
	char password[100];

	printf("*****로그인***** \n \n");
	printf("ID : ");
	scanf("%s", &ID);

	printf("Password : ");
	scanf("%s", &password);
	system("cls");
}

void SignUp()
{
	int choice = 0;
	printf("*****회원가입***** \n \n");
	printf("ID : ");
	scanf("%s", &member.ID);

	printf("Password: ");
	scanf("%s", &member.password);
	system("cls");

	printf("계좌번호를 등록하시곘습니까? \n");
	printf("1. 예 \n");
	printf("2. 아니요 \n");
	printf("---------------------------- \n");
	printf("선택 : ");

	scanf("%d", &choice);
	system("cls");

	switch (choice)
	{
	case 1:
		printf("*****계좌번호***** \n \n");
		printf("Account : ");
		scanf("%s", member.account);
		break;

	default:
		break;
	}

	system("cls");

	RoginMenu();
}