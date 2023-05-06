#pragma once

#define NUM_MAX_MEMBERS (100)
#define NUM_MAX_ITEMS (100)

typedef struct Member
{
	char ID[100];
	char password[100];
	char account[20];
	int balance;

} Member;

typedef struct Item
{
	char name[100];
	int regist;
	int cost;
	int quantity;
	int number;
} Item;

extern int menu;

void Init();
void OpenRoginMenu();
void OpenMenu();
void OpenItemList();
void RegistItem();
void DeleteItem();
void PurchaseItem();
void CheckBalance();
void ConfigBalance();
void SignIn();
void SignUp();