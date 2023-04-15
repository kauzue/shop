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
	char shoper[100];
	int amount;
	int quantity;
} Item;

extern int menu;

void Init();
void OpenRoginMenu();
void OpenMenu();
void RegistItem();
void PurchaseItem();
void SignIn();
void SignUp();