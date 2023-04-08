#pragma once

#define NUM_MAX_MEMBERS (100)

typedef struct Member
{
	char ID[100];
	char password[100];
	char account[20];
	int balance;

} Member;



void Init();
void OpenRoginMenu();
void OpenMenu();
void RegistItem();
void PurchaseItem();
void SignIn();
void SignUp();