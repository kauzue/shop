#pragma warning(disable:4996)

#include <stdio.h>

#include "main.h"

#include <Windows.h>

void RoginMenu()
{
	int choice = 0;

	printf("****�α��� �޴�**** \n");
	printf("1. �α��� \n");
	printf("2. ȸ������ \n");
	printf("------------------- \n");
	printf("���� : ");

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

	printf("���̵� : ");
	scanf("%s", &ID);

	printf("��й�ȣ : ");
	scanf("%s", &password);
	system("cls");
}

void SignUp()
{
	printf("20�� �̳��� ���̵� �� �ּ���. \n");
	printf("ID : ");
	scanf("%s", &member.ID);
	system("cls");

	printf("20�� �̳��� ��й�ȣ�� �� �ּ���. \n");
	printf("Password: ");
	scanf("%s", &member.password);
	system("cls");

	SignIn();
}