#pragma warning(disable:4996)

#include <stdio.h>
#include <Windows.h>
#include <stddef.h>

#include "main.h"

static Member s_members[NUM_MAX_MEMBERS];
static Item s_items[NUM_MAX_ITEMS];
static int s_num_members;
static int s_num_items;

int r_num;
int menu;

void Init()
{
	FILE* it = fopen("item.bin", "rb");
	FILE* mb = fopen("member.bin", "rb");

	if (it == NULL || mb == NULL) {
		puts("파일오픈 실패!");
		return;
	}

	s_num_items = fread(s_items, sizeof(Item), NUM_MAX_ITEMS, it);
	s_num_members = fread(s_members, sizeof(Member), NUM_MAX_MEMBERS, mb);

	/*
	int ch = 0;

	while (fgetc(mb) != EOF) {
		if (fgetc(mb) == '\n') {
			ch++;
		}
	}		

	fseek(mb, 0, SEEK_SET);

	s_num_members = ch / 3;

	for (int i = 0; i < s_num_members; ++i) {
		fseek(mb, 4, SEEK_CUR);
		for (ch = 1; fgetc(mb) != '\n'; ch++);
		fseek(mb, -ch, SEEK_CUR);
		fgets(s_members[i].ID, ch -1, mb);

		fseek(mb, 12, SEEK_CUR);
		for (ch = 1; fgetc(mb) != '\n'; ch++);
		fseek(mb, -ch, SEEK_CUR);
		fgets(s_members[i].password, ch -1, mb);

		fseek(mb, 11, SEEK_CUR);
		for (ch = 1; fgetc(mb) != '\n'; ch++);
		fseek(mb, -ch, SEEK_CUR);
		fgets(s_members[i].account, ch -1, mb);
	}
	*/

	fclose(it);
	fclose(mb);
}

void OpenRoginMenu()
{
	int choice = 0;

	printf("로그인 메뉴 \n \n");
	printf("1. 로그인 \n");
	printf("2. 회원가입 \n");
	printf("3. 취소 \n \n");
	printf("선택: ");

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
		menu = 0;
		return;

	default:
		system("cls");
		break;
	}
}

void OpenMenu()
{
	int choice = 0;

	printf("메인 메뉴 \n \n");
	printf("1. 물건 \n");
	printf("2. 자산 \n");
	printf("3. 로그인 메뉴 \n \n");
	printf("선택: ");

	scanf("%d", &choice);

	switch (choice)
	{
	case 1:
		system("cls");
		printf("물건 \n \n");
		printf("1. 물건 등록 \n");
		printf("2. 물건 구매 \n");
		printf("3. 취소 \n \n");
		printf("선택: ");

		scanf("%d", &choice);

		system("cls");

		switch (choice)
		{
		case 1:
			RegistItem();
			break;

		case 2:
			PurchaseItem();
			break;

		case 3:
			menu = 2;
			return;
		}
		break;

	case 2:
		system("cls");
		printf("자산 \n \n");
		printf("%s님의 자산은 %d원입니다.", s_members[r_num].ID, s_members[r_num].balance);
		Sleep(2000);
		system("cls");
		break;

	case 3:
		system("cls");
		menu = 1;
		return;

	default:
		break;
	}


}

void RegistItem()
{
	FILE* it = fopen("item.bin", "ab");

	if (it == NULL) {
		puts("파일오픈 실패!");
		return;
	}

	Item item;

	printf("물건 등록 \n \n");
	printf("name: ");
	scanf("%s", item.name);
	printf("quantity: ");
	scanf("%d", &item.quantity);
	printf("amount: ");
	scanf("%d", &item.amount);

	strcpy(item.shopername, s_members[r_num].ID);

	item.number = s_num_items;

	memcpy(&s_items[s_num_items], &item, sizeof(Item));
	++s_num_items;


	fwrite(&item, sizeof(Item), 1, it);

	fclose(it);
	system("cls");
}

void PurchaseItem()
{
	FILE* it = fopen("item.bin", "wb");
	FILE* mb = fopen("member.bin", "wb");

	if (it == NULL || mb == NULL) {
		puts("파일오픈 실패!");
		return;
	}

	Member member;

	int i = 0, choice;

	if (s_num_items > 0) {

		printf("물건 목록 \n \n");

		while (s_num_items > i) {
			printf("물건 번호: %d \n", s_items[i].number);
			printf("물건 이름: %s \n", s_items[i].name);
			printf("판매자 이름: %s \n", s_items[i].shopername);
			printf("물건 개수: %d \n", s_items[i].quantity);
			printf("물건 가격: %d \n \n", s_items[i].amount);
			++i;
		}

		printf("선택: ");
		scanf("%d", &choice);
		system("cls");

		i = choice;

		printf("물건 번호: %d \n", s_items[i].number);
		printf("물건 이름: %s \n", s_items[i].name);
		printf("판매자 이름: %s \n", s_items[i].shopername);
		printf("이 물건을 구매하시겠습니까? \n \n");

		printf("선택: ");
		scanf("%d", &choice);

		if (choice != 0) {
			s_members[r_num].balance = s_members[r_num].balance - s_items[i].amount;
			if (s_items[i].quantity == 1) {

				while (i <= s_num_items) {
					s_items[i].number--;
					s_items[i - 1] = s_items[i];
					++i;
				}
				--s_num_items;
			}

			else {
				s_items[i].quantity--;
			}

			fwrite(s_items, sizeof(Item), s_num_items, it);
			fwrite(s_members, sizeof(Member), s_num_members, mb);
		}

	}

	fclose(it);
	fclose(mb);
	system("cls");
}

void SignIn()
{
	char ID[100];
	char Password[100];
	int b_login = 0;

	FILE* mb = fopen("rogin.txt", "wt");

	if (mb == NULL) {
		puts("파일오픈 실패!");
		return;
	}

	do {
		printf("로그인 \n \n");
		printf("ID: ");
		scanf("%s", ID);

		printf("Password: ");
		scanf("%s", Password);
		system("cls");

		for (r_num = 0; r_num < s_num_members; ++r_num) {
			if (strcmp(ID, s_members[r_num].ID) == 0 && strcmp(Password, s_members[r_num].password) == 0) {
				b_login = 1;
				break;
			}
		}

		if (b_login) {
			menu = 2;
			return;
		}
		else {
			printf("아이디 또는 비밀번호가 틀렸습니다. \n");
			printf("다시 입력해주세요.");
			Sleep(1250);
			system("cls");
		}
	} while (b_login);
}

void SignUp()
{
	FILE* mb = fopen("member.bin", "ab");

	if (mb == NULL) {
		puts("파일오픈 실패!");
		return;
	}

	int choice = 0;
	int same;

	Member member;

	do {
		printf("회원가입 \n \n");
		printf("ID: ");
		scanf("%s", member.ID);

		same = 0;
		for (int i = 0; i < s_num_members; ++i) {
			if (strcmp(member.ID, s_members[i].ID) == 0) {
				system("cls");
				printf("중복되는 아이디입니다. \n");
				printf("다시 입력해주세요.");
				Sleep(1250);
				system("cls");
				same = 1;
				break;
			}
		}
	} while (same);

	printf("Password: ");
	scanf("%s", member.password);
	system("cls");

	do {
		printf("계좌번호 \n \n");
		printf("account: ");
		scanf("%s", member.account);

		same = 0;
		for (int i = 0; i < s_num_members; ++i) {
			if (strcmp(member.account, s_members[i].account) == 0) {
				system("cls");
				printf("중복되는 계좌번호입니다. \n");
				printf("다시 입력해주세요.");
				Sleep(1250);
				system("cls");
				same = 1;
				break;
			}
		}
	} while (same);

	printf("balance: ");
	scanf("%d", &member.balance);
	system("cls");

	memcpy(&s_members[s_num_members], &member, sizeof(Member));
	++s_num_members;

	fwrite(&member, sizeof(Member), 1, mb);

	fclose(mb);
	system("cls");
}
