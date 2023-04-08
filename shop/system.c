#pragma warning(disable:4996)

#include <stdio.h>
#include <Windows.h>

#include "main.h"

static Member s_members[NUM_MAX_MEMBERS];
static int s_num_members;

void Init()
{

}

void OpenRoginMenu()
{
	int choice = 0;

	printf("*****�α��� �޴�***** \n");
	printf("1. �α��� \n");
	printf("2. ȸ������ \n");
	printf("3. ��� \n");
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

	case 3:
		system("cls");
		return -2;

	default:
		OpenRoginMenu();
		break;
	}
}

void OpenMenu()
{
	int choice = 0;

	printf("*****���� �޴�***** \n");
	printf("1. ���� \n");
	printf("2. �ڻ� \n");
	printf("3. �α��� �޴� \n");
	printf("4. ��� \n");
	printf("------------------- \n");
	printf("���� : ");

	scanf("%d", &choice);

	switch (choice)
	{
	case 1:
		system("cls");
		printf("*****����***** \n");
		printf("1. ���� ��� \n");
		printf("2. ���� ���� \n");
		printf("-------------- \n");
		printf("���� : ");

		scanf("%d", &choice);
		break;

	case 2:
		system("cls");
		printf("*****�ڻ�***** \n");
		break;

	case 3:
		system("cls");
		OpenRoginMenu();
		break;

	case 4:
		system("cls");
		return -2;

	default:
		break;
	}

	switch (choice)
	{
	case 1:
		RegistItem();
		break;

	case 2:
		PurchaseItem();
		break;
	}

	system("cls");
	OpenMenu();

}

void RegistItem()
{

}

void PurchaseItem()
{

}

void SignIn()
{
	FILE* fp = fopen("rogin.txt", "wt");

	if (fp == NULL) {
		puts("���Ͽ��� ����!");
		return -1;
	}

	char ID[100];
	char Password[100];

	printf("*****�α���***** \n \n");
	printf("ID : ");
	scanf("%s", ID);

	printf("Password : ");
	scanf("%s", Password);
	system("cls");

	int b_login = 0;
	for (int i = 0; i < s_num_members; ++i) {
		if (strcmp(ID, s_members[i].ID) == 0 && strcmp(Password, s_members[i].password) == 0) {
			b_login = 1;
			break;
		}
	}

	if (b_login) {
		OpenMenu();
	}
	else {
		printf("���̵� �Ǵ� ��й�ȣ�� Ʋ�Ƚ��ϴ�. \n");
		printf("�ٽ� �Է����ּ���.");
		Sleep(1250);
		system("cls");
		SignIn();
	}
}

void SignUp()
{
	FILE* fp = fopen("memebr.txt", "at");

	if (fp == NULL) {
		puts("���Ͽ��� ����!");
		return -1;
	}

	int choice = 0;
	int ID = 1;

	Member member;

	printf("*****ȸ������***** \n \n");
	printf("ID : ");
	scanf("%s", member.ID);

	system("cls");

	for (int i = 0; i < s_num_members; ++i) {
		if (strcmp(member.ID, s_members[i].ID) == 0) {
			ID = 0;
			break;
		}
	}

	if (ID) {
		fprintf(fp, "ID : %s\n", member.ID);
	}

	else {
		printf("�ߺ��Ǵ� ���̵� �Դϴ�. \n");
		printf("�ٽ� �Է��� �ּ���.");
		Sleep(1250);
		system("cls");
		SignUp();
	}

	printf("Password: ");
	scanf("%s", member.password);
	fprintf(fp, "password : %s\n", member.password);
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
		fprintf(fp, "account : %s\n", member.account);
		break;

	default:
		break;
	}

	fclose(fp);

	system("cls");

	OpenRoginMenu();
}