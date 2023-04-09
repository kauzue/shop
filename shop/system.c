#pragma warning(disable:4996)

#include <stdio.h>
#include <Windows.h>

#include "main.h"

static Member s_members[NUM_MAX_MEMBERS];
static int s_num_members;

void Init()
{
	int ch = 0;

	FILE* fp = fopen("member.txt", "rt");

	if (fp == NULL) {
		puts("파일오픈 실패!");
		return -1;
	}

	while (fgetc(fp) != EOF) {
		if (fgetc(fp) == '\n') {
			ch++;
		}
	}

	fseek(fp, 0, SEEK_SET);

	s_num_members = ch / 3;

	for (int i = 0; i < s_num_members; ++i) {
		fseek(fp, 4, SEEK_CUR);
		for (ch = 1; fgetc(fp) != '\n'; ch++);
		fseek(fp, -ch, SEEK_CUR);
		fgets(s_members[i].ID, ch -1, fp);

		fseek(fp, 12, SEEK_CUR);
		for (ch = 1; fgetc(fp) != '\n'; ch++);
		fseek(fp, -ch, SEEK_CUR);
		fgets(s_members[i].password, ch -1, fp);

		fseek(fp, 11, SEEK_CUR);
		for (ch = 1; fgetc(fp) != '\n'; ch++);
		fseek(fp, -ch, SEEK_CUR);
		fgets(s_members[i].account, ch -1, fp);
	}

	fclose(fp);
	OpenRoginMenu();
}

void OpenRoginMenu()
{
	int choice = 0;

	printf("*****로그인 메뉴***** \n");
	printf("1. 로그인 \n");
	printf("2. 회원가입 \n");
	printf("3. 취소 \n");
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

	printf("*****메인 메뉴***** \n");
	printf("1. 물건 \n");
	printf("2. 자산 \n");
	printf("3. 로그인 메뉴 \n");
	printf("4. 취소 \n");
	printf("------------------- \n");
	printf("선택 : ");

	scanf("%d", &choice);

	switch (choice)
	{
	case 1:
		system("cls");
		printf("*****물건***** \n");
		printf("1. 물건 등록 \n");
		printf("2. 물건 구매 \n");
		printf("-------------- \n");
		printf("선택 : ");

		scanf("%d", &choice);
		break;

	case 2:
		system("cls");
		printf("*****자산***** \n");
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
		puts("파일오픈 실패!");
		return -1;
	}

	char ID[100];
	char Password[100];

	printf("*****로그인***** \n \n");
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
		printf("아이디 또는 비밀번호가 틀렸습니다. \n");
		printf("다시 입력해주세요.");
		Sleep(1250);
		system("cls");
		SignIn();
	}
}

void SignUp()
{
	FILE* fp = fopen("member.txt", "at");

	if (fp == NULL) {
		puts("파일오픈 실패!");
		return -1;
	}

	int choice = 0;
	int ID = 1;

	Member member;

	printf("*****회원가입***** \n \n");
	printf("ID : ");
	scanf("%s", member.ID);

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
		system("cls");
		printf("중복되는 아이디입니다. \n");
		printf("다시 입력해주세요.");
		Sleep(1250);
		system("cls");
		SignUp();
	}

	printf("Password: ");
	scanf("%s", member.password);
	fprintf(fp, "password : %s\n", member.password);
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

		for (int i = 0; i < s_num_members; ++i) {
			if (strcmp(member.account, s_members[i].account) == 0) {
				ID = 0;
				break;
			}
		}

		if (ID) {
			fprintf(fp, "account : %s\n", member.account);
		}

		else {
			system("cls");
			printf("중복되는 계좌번호입니다. \n");
			printf("다시 입력해주세요.");
			Sleep(1250);
			system("cls");
			SignUp();
		}
		break;

	default:
		fprintf(fp, "account :\n");
		break;
	}

	fclose(fp);
	system("cls");
	Init();
}