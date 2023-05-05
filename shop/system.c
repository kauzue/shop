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
		puts("���Ͽ��� ����!");
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

	printf("�α��� �޴� \n \n");
	printf("1. �α��� \n");
	printf("2. ȸ������ \n");
	printf("3. ��� \n \n");
	printf("����: ");

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

	printf("���� �޴� \n \n");
	printf("1. ���� \n");
	printf("2. �ڻ� \n");
	printf("3. �α��� �޴� \n \n");
	printf("����: ");

	scanf("%d", &choice);

	switch (choice)
	{
	case 1:
		system("cls");
		printf("���� \n \n");
		printf("1. ���� ��� \n");
		printf("2. ���� ��� \n");
		printf("3. ���� ���� \n");
		printf("4. ���� ���� \n");
		printf("5. ��� \n \n");
		printf("����: ");

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
		printf("�ڻ� \n \n");
		printf("%s���� �ڻ��� %d���Դϴ�.", s_members[r_num].ID, s_members[r_num].balance);
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
		printf("���� ��� \n \n");

		while (s_num_items > num) {
			printf("���� ��ȣ: %d \n", s_items[num].number);
			printf("���� �̸�: %s \n", s_items[num].name);
			printf("�Ǹ��� �̸�: %s \n", s_members[s_items[num].regist].ID);
			printf("���� ����: %d \n", s_items[num].quantity);
			printf("���� ����: %d \n \n", s_items[num].cost);
			++num;
		}

		getch();
	}

	else {
		printf("���� ��ϵǾ��ִ� ������ �����ϴ�.");
		Sleep(1250);
	}
	
	system("cls");
}

void RegistItem()
{
	FILE* it = fopen("item.bin", "ab");

	if (it == NULL) {
		puts("���Ͽ��� ����!");
		return;
	}

	Item item;

	printf("���� ��� \n \n");
	printf("���� �̸�: ");
	scanf("%s", item.name);
	printf("���� ����: ");
	scanf("%d", &item.quantity);
	printf("���� ����: ");
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
		puts("���Ͽ��� ����!");
		return;
	}

	int choice = 0;
	char choose[5];

	if (s_num_items > 0) {
		printf("���� ���� \n \n");

		while (s_num_items > choice) {
			if (strcmp(s_members[s_items[choice].regist].ID, s_members[r_num].ID) == 0) {
				printf("���� ��ȣ: %d \n", s_items[choice].number);
				printf("���� �̸�: %s \n", s_items[choice].name);
				printf("���� ����: %d \n", s_items[choice].quantity);
				printf("���� ����: %d \n \n", s_items[choice].cost);
			}
			++choice;
		}

		printf("����: ");
		scanf("%d", &choice);

		system("cls");

		if (choice >= 0 && choice < s_num_items) {

			printf("���� ��ȣ: %d \n", s_items[choice].number);
			printf("���� �̸�: %s \n", s_items[choice].name);
			printf("�� ������ �����Ͻðڽ��ϱ�? \n \n");

			printf("����: ");
			scanf("%s", &choose);
		}

		if (strcmp(choose, "��") == 0) {

			while (choice <= s_num_items) {
				s_items[choice].number--;
				s_items[choice - 1] = s_items[choice];
				++choice;
			}
				--s_num_items;
		}
	}

	else {
		printf("���� ��ϵǾ��ִ� ������ �����ϴ�.");
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
		puts("���Ͽ��� ����!");
		return;
	}

	int choice = 0;
	char choose[5];

	if (s_num_items > 0) {

		printf("���� ���� \n \n");

		while (s_num_items > choice) {
			printf("���� ��ȣ: %d \n", s_items[choice].number);
			printf("���� �̸�: %s \n", s_items[choice].name);
			printf("�Ǹ��� �̸�: %s \n", s_members[s_items[choice].regist].ID);
			printf("���� ����: %d \n", s_items[choice].quantity);
			printf("���� ����: %d \n \n", s_items[choice].cost);
			++choice;
		}

		printf("����: ");
		scanf("%d", &choice);
		system("cls");

		if (s_members[r_num].balance < s_items[choice].cost) {
			printf("�ܾ��� �����մϴ�.");
			Sleep(1250);
			system("cls");
		}

		else if (choice >= 0 && choice < s_num_items) {

			printf("���� ��ȣ: %d \n", s_items[choice].number);
			printf("���� �̸�: %s \n", s_items[choice].name);
			printf("�Ǹ��� �̸�: %s \n", s_members[s_items[choice].regist].ID);
			printf("�� ������ �����Ͻðڽ��ϱ�? \n \n");

			printf("����: ");
			scanf("%s", &choose);
		}

		if (strcmp(choose, "��") == 0) {
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
		printf("���� ��ϵǾ��ִ� ������ �����ϴ�.");
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
		puts("���Ͽ��� ����!");
		return;
	}

	do {
		printf("�α��� \n \n");
		printf("���̵�: ");
		scanf("%s", ID);

		printf("��й�ȣ: ");
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
			printf("���̵� �Ǵ� ��й�ȣ�� Ʋ�Ƚ��ϴ�. \n");
			printf("�ٽ� �Է����ּ���.");
			Sleep(1250);
			system("cls");
		}
	} while (b_login);
}

void SignUp()
{
	FILE* mb = fopen("member.bin", "ab");

	if (mb == NULL) {
		puts("���Ͽ��� ����!");
		return;
	}

	int choice = 0;
	int same;

	Member member;

	do {
		printf("ȸ������ \n \n");
		printf("���̵�: ");
		scanf("%s", member.ID);

		same = 0;
		for (int i = 0; i < s_num_members; ++i) {
			if (strcmp(member.ID, s_members[i].ID) == 0) {
				system("cls");
				printf("�ߺ��Ǵ� ���̵��Դϴ�. \n");
				printf("�ٽ� �Է����ּ���.");
				Sleep(1250);
				system("cls");
				same = 1;
				break;
			}
		}
	} while (same);

	printf("��й�ȣ: ");
	scanf("%s", member.password);
	system("cls");

	do {
		printf("���¹�ȣ \n \n");
		printf("���¹�ȣ: ");
		scanf("%s", member.account);

		same = 0;
		for (int i = 0; i < s_num_members; ++i) {
			if (strcmp(member.account, s_members[i].account) == 0) {
				system("cls");
				printf("�ߺ��Ǵ� ���¹�ȣ�Դϴ�. \n");
				printf("�ٽ� �Է����ּ���.");
				Sleep(1250);
				system("cls");
				same = 1;
				break;
			}
		}
	} while (same);

	printf("���� �ݾ�: ");
	scanf("%d", &member.balance);
	system("cls");

	memcpy(&s_members[s_num_members], &member, sizeof(Member));
	++s_num_members;

	fwrite(&member, sizeof(Member), 1, mb);

	fclose(mb);
	system("cls");
}
