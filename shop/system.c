#pragma warning(disable:4996)

#include <stdio.h>
#include <Windows.h>
#include <stddef.h>
#include <conio.h>

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
		printf("1. 물건 목록 \n");
		printf("2. 물건 등록 \n");
		printf("3. 물건 삭제 \n");
		printf("4. 물건 구매 \n");
		printf("5. 취소 \n \n");
		printf("선택: ");

		scanf("%d", &choice);

		system("cls");

		switch (choice)
		{
		case 1:
			OpenItemList();
			break;

		case 2:
			RegistItem();
			break;

		case 3:
			DeleteItem();
			break;

		case 4:
			PurchaseItem();
			break;

		case 5:
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

void OpenItemList()
{
	int num = 0;


	if (s_num_items > 0) {
		printf("물건 목록 \n \n");

		while (s_num_items > num) {
			printf("물건 번호: %d \n", s_items[num].number);
			printf("물건 이름: %s \n", s_items[num].name);
			printf("판매자 이름: %s \n", s_members[s_items[num].regist].ID);
			printf("물건 개수: %d \n", s_items[num].quantity);
			printf("물건 가격: %d \n \n", s_items[num].cost);
			++num;
		}

		getch();
	}

	else {
		printf("현재 등록되어있는 물건이 없습니다.");
		Sleep(1250);
	}
	
	system("cls");
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
	printf("물건 이름: ");
	scanf("%s", item.name);
	printf("물건 개수: ");
	scanf("%d", &item.quantity);
	printf("물건 가격: ");
	scanf("%d", &item.cost);

	item.regist = r_num;

	item.number = s_num_items;

	memcpy(&s_items[s_num_items], &item, sizeof(Item));
	++s_num_items;


	fwrite(&item, sizeof(Item), 1, it);

	fclose(it);
	system("cls");
}

void DeleteItem()
{
	FILE* it = fopen("item.bin", "wb");

	if (it == NULL) {
		puts("파일오픈 실패!");
		return;
	}

	int choice = 0;
	char choose[5];

	if (s_num_items > 0) {
		printf("물건 삭제 \n \n");

		while (s_num_items > choice) {
			if (strcmp(s_members[s_items[choice].regist].ID, s_members[r_num].ID) == 0) {
				printf("물건 번호: %d \n", s_items[choice].number);
				printf("물건 이름: %s \n", s_items[choice].name);
				printf("물건 개수: %d \n", s_items[choice].quantity);
				printf("물건 가격: %d \n \n", s_items[choice].cost);
			}
			++choice;
		}

		printf("선택: ");
		scanf("%d", &choice);

		system("cls");

		if (choice >= 0 && choice < s_num_items) {

			printf("물건 번호: %d \n", s_items[choice].number);
			printf("물건 이름: %s \n", s_items[choice].name);
			printf("이 물건을 삭제하시겠습니까? \n \n");

			printf("선택: ");
			scanf("%s", &choose);
		}

		if (strcmp(choose, "예") == 0) {

			while (choice <= s_num_items) {
				s_items[choice].number--;
				s_items[choice - 1] = s_items[choice];
				++choice;
			}
				--s_num_items;
		}
	}

	else {
		printf("현재 등록되어있는 물건이 없습니다.");
		Sleep(1250);
	}

	fwrite(s_items, sizeof(Item), s_num_items, it);

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

	int choice = 0;
	char choose[5];

	if (s_num_items > 0) {

		printf("물건 구매 \n \n");

		while (s_num_items > choice) {
			printf("물건 번호: %d \n", s_items[choice].number);
			printf("물건 이름: %s \n", s_items[choice].name);
			printf("판매자 이름: %s \n", s_members[s_items[choice].regist].ID);
			printf("물건 개수: %d \n", s_items[choice].quantity);
			printf("물건 가격: %d \n \n", s_items[choice].cost);
			++choice;
		}

		printf("선택: ");
		scanf("%d", &choice);
		system("cls");

		if (s_members[r_num].balance < s_items[choice].cost) {
			printf("잔액이 부족합니다.");
			Sleep(1250);
			system("cls");
		}

		else if (choice >= 0 && choice < s_num_items) {

			printf("물건 번호: %d \n", s_items[choice].number);
			printf("물건 이름: %s \n", s_items[choice].name);
			printf("판매자 이름: %s \n", s_members[s_items[choice].regist].ID);
			printf("이 물건을 구매하시겠습니까? \n \n");

			printf("선택: ");
			scanf("%s", &choose);
		}

		if (strcmp(choose, "예") == 0) {
			s_members[r_num].balance = s_members[r_num].balance - s_items[choice].cost;
			s_members[s_items[choice].regist].balance = s_members[s_items[choice].regist].balance + s_items[choice].cost;

			if (s_items[choice].quantity == 1) {

				while (choice <= s_num_items) {
					s_items[choice].number--;
					s_items[choice - 1] = s_items[choice];
					++choice;
				}
				--s_num_items;

			}

			else {
				s_items[choice].quantity--;
			}
		}

	}

	else {
		printf("현재 등록되어있는 물건이 없습니다.");
		Sleep(1250);
	}

	fwrite(s_items, sizeof(Item), s_num_items, it);
	fwrite(s_members, sizeof(Member), s_num_members, mb);

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
		printf("아이디: ");
		scanf("%s", ID);

		printf("비밀번호: ");
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
		printf("아이디: ");
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

	printf("비밀번호: ");
	scanf("%s", member.password);
	system("cls");

	do {
		printf("계좌번호 \n \n");
		printf("계좌번호: ");
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

	printf("보유 금액: ");
	scanf("%d", &member.balance);
	system("cls");

	memcpy(&s_members[s_num_members], &member, sizeof(Member));
	++s_num_members;

	fwrite(&member, sizeof(Member), 1, mb);

	fclose(mb);
	system("cls");
}
