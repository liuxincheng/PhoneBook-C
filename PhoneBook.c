#include "phoneBook.h"

int main()
{
	char input;
	Node* beginList = NULL;
	Node* endList = NULL;
	Page *page;

	InitNode(11,&beginList,&endList);
	page = PageInfo(beginList,10);

	while(1)
	{
		printf("1.查看通讯录\n");
		printf("2.添加通讯录\n");
		printf("3.查询通讯录\n");
		printf("4.修改通讯录\n");
		printf("5.删除通讯录\n");
		printf("6.退出通讯录\n");

		input = GetKey();
		switch (input)
		{
		case '1':
			g_menu_type = 1;
			CheckPhoneBook(beginList);
			break;
		case '2':
			AddNode(&beginList,&endList,GetNodeIn());
			break;
		case '3':
			g_menu_type = 3;
			QueryPhoneBook(beginList);
			break;
		case '4':
			g_menu_type = 4;
			UpdataPhoneBook(beginList);
			break;
		case '5':
			g_menu_type = 5;
			DeletePhoneBook(&beginList, &endList);
			break;
		case '6':
			return 0;
			break;
		default:
			printf("请根据提示输入正确按键！\n\n");
			break;
		}
	}

	return 0;
}

void AddNode(Node** beginList,Node** endList,Node* node)
{
	if(NULL == *beginList)
	{
		*beginList = node;
	}
	else
	{
		(*endList)->pNext = node;
	}
	*endList = node;
}

Node* GetNode(char* name, char* phone)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->num = GetNum();
	node->name = name;
	node->phone = phone;
	node->pNext = NULL;

	return node;
}

void InitNode(int count,Node** beginList,Node** endList)
{
	int i;
	srand((unsigned int) time(NULL));
	for (i = 0; i < count; i++)
	{
		AddNode(beginList,endList,GetNode(GetName(),GetPhone()));
	}
}

void DelNode(int num, Node** beginList,Node** endList)
{
	Node* beginList_flag = *beginList;
	Node* del = NULL;

	if (num == (*beginList)->num)
	{
		*beginList = (*beginList)->pNext;
		free(del);
		del = NULL;

		return;
	}

	while(beginList_flag->pNext != NULL)
	{
		if (num == beginList_flag->pNext->num)
		{
			del = beginList_flag->pNext;
			beginList_flag->pNext = beginList_flag->pNext->pNext;
			free(del);
			del = NULL;

			if (NULL == beginList_flag->pNext)
			{
				*endList = beginList_flag;
			}

			return;
		}
		beginList_flag = beginList_flag->pNext;
	}
}

int GetNum()
{
	static int i = 1;
	return i++;
}

char* GetName()
{
	char* name = (char*)malloc(9);
	char str[2] = {0};
	int i;
	*name = 0;

	for (i = 0; i < 8; i++)
	{
		str[0] = rand()%(122-97)+97;
		strcat_s(name,9,str);
	}

	return name;
}

char* GetPhone()
{
	char* phone = (char*)malloc(12);
	char str[2];
	int i;

	switch (rand()%5)
	{
	case 0:
		strcpy_s(phone,12,"137");
		break;
	case 1:
		strcpy_s(phone,12,"138");
		break;
	case 2:
		strcpy_s(phone,12,"139");
		break;
	case 3:
		strcpy_s(phone,12,"170");
		break;
	case 4:
		strcpy_s(phone,12,"189");
		break;
	default:
		strcpy_s(phone,12,"188");
		break;
	}

	for (i = 0; i < 8; i++)
	{
		_itoa_s(rand()%10,str,2,10);
		strcat_s(phone,12,str);
	}

	return phone;
}

char* GetString()
{
	char c;
	int size = 5;
	int count = 0;
	char* str = (char*)malloc(size);
	char* bjStr = str;
	char* newStr = NULL;

	while((c = getchar()) != '\n')
	{
		count++;
		*str++ = c;

		if ((count + 1) == size)
		{
			*str = '\0';
			size += 5;

			newStr = (char*)malloc(size);
			strcpy_s(newStr,size,bjStr);
			free(bjStr);

			bjStr = newStr;
			str = newStr + count;
		}
	}

	*str = '\0';
	return bjStr;
}

char GetKey()
{
	char c = -1;
	char v = -1;
	while((v = getchar()) != '\n' || c == -1)
	{
		c = v;
	}

	return c;
}

Node* GetNodeIn()
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->num = GetNum();

	while(1)
	{
		printf("请输入姓名： \n");
		node->name = GetString();
		printf("请输入电话： \n");
		node->phone = GetString();
		node->pNext = NULL;

		printf("您确定添加编号： %d 姓名：%s 电话：%s\n\n",node->num,node->name,node->phone);
		printf("y键确认，其他键重新输入\n");
		if (GetKey() != 'y')
		{
			continue;
		}
		else
		{
			printf("添加成功！\n");
			return node;
		}
	}
	return node;
}

Page* PageInfo(Node* beginList,int onePageItem)
{
	Page* page = (Page*)malloc(sizeof(Page));
	page->totalItem = 0;
	page->totalPage = 0;
	page->currentPage =0;
	page->onePageItem = onePageItem;

	while(beginList != NULL)
	{
		page->totalItem++;
		beginList = beginList->pNext;
	}

	page->totalPage = page->totalItem % onePageItem ? page->totalItem / onePageItem + 1 : page->totalItem / onePageItem;

	return page;
}

void showInfo(Node* beginList, Page* page)
{
	int begin = (page->currentPage - 1) * 10 + 1;
	int end = page->currentPage * 10;
	int count = 0;

	printf("编号\t 姓名\t\t 电话\t\n");
	while(beginList != NULL)
	{
		count++;
		if (count >= begin && count <= end)
		{
			printf("%d\t %s\t %s\t\n",beginList->num,beginList->name,beginList->phone);
		}
		beginList = beginList->pNext;
	}
}
void showMenu(Page* page)
{
	switch (g_menu_type)
	{
	case 1:
		printf("共%d页 共%d条数据 当前第%d页 w上一页 s下一页 b返回\n",page->totalPage,page->totalItem,page->currentPage);
		break;
	case 3:
		printf("共%d页 共%d条数据 当前第%d页 c重新查询 w上一页 s下一页 b返回\n",page->totalPage,page->totalItem,page->currentPage);
		break;
	case 4:
		printf("共%d页 共%d条数据 当前第%d页 u修改信息 w上一页 s下一页 b返回\n",page->totalPage,page->totalItem,page->currentPage);
		break;
	case 5:
		printf("共%d页 共%d条数据 当前第%d页 d删除信息 w上一页 s下一页 b返回\n",page->totalPage,page->totalItem,page->currentPage);
		break;
	default:
		printf("共%d页 共%d条数据 当前第%d页 w上一页 s下一页 b返回\n",page->totalPage,page->totalItem,page->currentPage);
		break;
	}
}

void OpeartPage(Node* beginList,Page* page)
{
	char key = 's';
	while(key != 'b')
	{
		switch (key)
		{
		case 's':
			if (page->currentPage == page->totalPage)
			{
				printf("当前已经是最后一页！！！\n");
			} 
			else
			{
				system("cls");
				page->currentPage++;
				showInfo(beginList,page);
				showMenu(page);
			}
			break;
		case 'w':
			if (page->currentPage == 1)
			{
				printf("当前已经是第一页！！！\n");
			} 
			else
			{
				system("cls");
				page->currentPage--;
				showInfo(beginList,page);
				showMenu(page);
			}
			break;
		case 'u':
		case 'c':
		case 'd':
			return;
			break;
		default:
			printf("按键错误！！\n");
			break;
		}
		g_key = key = GetKey();
	}
}

void CheckPhoneBook(Node* beginList)
{
	Page* page = PageInfo(beginList,10);
	OpeartPage(beginList,page);
}

void QueryPhoneBook(Node* beginList)
{
	char* keyword = NULL;
	char key = 0;
	Node* node = NULL;
	Node* beginList_flag = NULL;
	Node* newBegin = NULL;
	Node* newEnd = NULL;
	Node* del;

	while(1)
	{

		while(1)
		{
			printf("请输入查询的关键字： \n");
			keyword = GetString();
			printf("请确认查询的关键字： %s 确认请按a 其他键重新查询\n",keyword);
			key = GetKey();
			if (key == 'a')
			{
				break;
			} 
			else
			{
				free(keyword);
				keyword = NULL;
			}
		}

		beginList_flag = beginList;
		while(beginList_flag != NULL)
		{
			if (strncmp(beginList_flag->name,keyword,strlen(keyword)) == 0
				|| strncmp(beginList_flag->phone,keyword,strlen(keyword)) == 0)
			{
				node = (Node*)malloc(sizeof(Node));
				node->num = beginList_flag->num;
				node->name = beginList_flag->name;
				node->phone = beginList_flag->phone;
				node->pNext = NULL;

				AddNode(&newBegin,&newEnd,node);
			}
			beginList_flag = beginList_flag->pNext;
		}

		if (newBegin != NULL)
		{
			CheckPhoneBook(newBegin);

			while(newBegin)
			{
				del = newBegin;
				newBegin = newBegin->pNext;
				free(del);
				del = NULL;
			}
		}
		else
		{
			printf("没有该关键字！！\n");
		}

		if (g_key == 'b' || g_key == 'u' || g_key == 'd')
		{
			return;
		}
	}
}

void UpdataPhoneBook(Node* beginList)
{
	int num = 0;
	Node *beginList_flag = NULL;
	QueryPhoneBook(beginList);

	if (g_key == 'b')
	{
		return;
	}

	if (g_key == 'u')
	{
		while(1)
		{
			printf("请输入要修改的编号： \n");
			num = atoi(GetString());

			beginList_flag = beginList;
			while(beginList_flag != NULL)
			{
				if (num == beginList_flag->num)
				{
					printf("请输入姓名： \n");
					beginList_flag->name = GetString();
					printf("请输入电话： \n");
					beginList_flag->phone = GetString();
					printf("修改成功！\n");
				}
				beginList_flag = beginList_flag->pNext;
			}

			printf("按y键继续修改，其他键返回\n");
			if (GetKey() != 'y')
			{
				return;
			}
		}
	}
}

void DeletePhoneBook(Node** beginList, Node** endList)
{
	int num = 0;
	Node *beginList_flag = NULL;
	QueryPhoneBook(*beginList);

	if (g_key == 'b')
	{
		return;
	}

	if (g_key == 'd')
	{
		while(1)
		{
			printf("请输入要删除的编号： \n");
			num = atoi(GetString());
			printf("确认删除编号%d? 确认请按y 其他键重新输入 \n",num);
			if (GetKey() == 'y')
			{
				DelNode(num,beginList,endList);
				printf("删除成功！\n");
			}
			else
			{
				continue;
			}

			printf("按y键继续删除，其他键返回\n");
			if (GetKey() != 'y')
			{
				return;
			}
		}
	}
}
