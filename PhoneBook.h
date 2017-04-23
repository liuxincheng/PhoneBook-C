#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct NODE
{
	int num;
	char* name;
	char* phone;
	struct NODE* pNext;
}Node;

typedef struct PAGE
{
	int totalItem;
	int totalPage;
	int onePageItem;
	int currentPage;
}Page;

void AddNode(Node** beginList,Node** endList,Node* node);
void InitNode(int count,Node** beginList,Node** endList);
void DelNode(int num, Node** beginList,Node** endList);
Node* GetNode(char* name, char* phone);

Page* PageInfo(Node* beginList,int onePageItem);
void showInfo(Node* beginList, Page* page);
void showMenu(Page* page);
void OpeartPage(Node* beginList,Page* page);
Node* GetNodeIn();

void AddPhoneBook(Node** beginList,Node** endList);
void CheckPhoneBook(Node* beginList);
void QueryPhoneBook(Node* beginList);
void UpdataPhoneBook(Node* beginList);
void DeletePhoneBook(Node** beginList, Node** endList);

int GetNum();
char* GetName();
char* GetPhone();
char* GetString();
char GetKey();

int g_menu_type;
char g_key;
