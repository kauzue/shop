#pragma once
struct Member
{
	char ID[100];
	char password[100];
	char account[20];
	int balance;

}member;

void RoginMenu();
void SignIn();
void SignUp();
void Menu();