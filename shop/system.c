#pragma warning(disable:4996)

#include <stdio.h>

#include "main.h"

#include <Windows.h>

void RoginMenu()
{
	int choice = 0;
	printf("*****�α��� �޴�***** \n");
	printf("1. �α��� \n");
	printf("2. ȸ������ \n");
	printf("--------------------- \n");
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

void Menu()
{

}

void SignIn()
{
	char ID[100];
	char password[100];

	printf("*****�α���***** \n \n");
	printf("ID : ");
	scanf("%s", &ID);

	printf("Password : ");
	scanf("%s", &password);
	system("cls");
}

void SignUp()
{
	int choice = 0;
	printf("*****ȸ������***** \n \n");
	printf("ID : ");
	scanf("%s", &member.ID);

	printf("Password: ");
	scanf("%s", &member.password);
	system("cls");

	printf("���¹�ȣ�� ����ϽÁٽ��ϱ�? \n");
	printf("1. �� \n");
	printf("2. �ƴϿ� \n");
	printf("---------------------------- \n");
	printf("���� : ");

	scanf("%d", &choice);
	system("cls");

	switch (choice)
	{
	case 1:
		printf("*****���¹�ȣ***** \n \n");
		printf("Account : ");
		scanf("%s", member.account);
		break;

	default:
		break;
	}

	system("cls");

	RoginMenu();
}