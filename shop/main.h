#pragma once
struct Member
{
	char ID[100];
	char password[100];
	int account;
	int balance;

}member;

void RoginMenu();
void SignIn();
void SignUp();
void Menu();