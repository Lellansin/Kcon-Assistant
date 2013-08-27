
#include <windows.h>
#include <ctype.h>
#include "list.h"
#include "output.h"

node * new_node(LPSTR name, HWND hwnd);

List::List()
{
	// memset(this->head, 0, sizeof(this->head));
	this->head = NULL;
}

void List::insert(HWND hwnd, LPSTR name)
{
	node * newnode = new_node(name, hwnd);

	node *last = this->getLastNode();

	if(last != NULL)
	{
		last->next = newnode;
	}
	else
	{
		this->head = newnode;
	}
};

node * new_node(LPSTR name, HWND hwnd)
{
	static int id = 1;
	node * _node = new node;	
	strcpy(_node->name, strlwr(name));
	_node->id = id++;
	_node->hwnd = hwnd;
	_node->next = NULL;
	return _node;
}

node* List::getLastNode()
{
	node* tmp = this->head;

	if(tmp == NULL)
		return NULL;

	while(tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	return tmp;
}

HWND List::getHwndByName(char *name)
{
	node* tmp = this->head;
	do
	{
		if(strcmp(tmp->name, name) == 0)
		{
			return tmp->hwnd;
		}
		tmp = tmp->next;
	}while(tmp->next != NULL);

	return NULL;
}

HWND List::getHwndById(int id)
{
	node* tmp = this->head;
	do
	{
		if(tmp->id = id)
		{
			return tmp->hwnd;
		}
		tmp = tmp->next;
	}while(tmp->next != NULL);

	return NULL;
}

int equalMost(char *dest, char *src)
{
	int num=0;
	for( ; *dest!='\0' && *src != '\0'; dest++, src++)
	{
		if(*dest != *src)
			return num;
		else
			num++;
	}
}

int analyseSimilarity(char *dest, char *src)
{
	int st = 0;
	//for(char *d = dest; *d != '\0'; d++ )
	//{
	//	for(char *s = src; *s != '\0'; s++ )
	//	{
	//		if(*s == ' ')
	//			continue;

	//		if(*d == *s)
	//		{
	//			st++;
	//			break;
	//		}
	//	}
	//}
	for(char *d = dest; *d != '\0'; d++ )
	{
		for(char *s = src; *s != '\0'; s++ )
		{
			if(int e = equalMost(d,s) > 2)
			{
				st += e;
				d += e;
				break;
			}
		}
	}
	if(strstr(dest,src) != NULL)
	{
		st += 10;
	}
	return st;
}

void List::getSimilarIdList(char *name, char *buf, int bufsize)
{
	node* tmp = this->head;
	int st = 0;
	do
	{
		st = analyseSimilarity(tmp->name, name);

		if(st > 1)
		{
			ZeroMemory(buf, 1024);
			wsprintf(buf, "%02d,%02d,%s \n", st, tmp->id, tmp->name);
			Cout(buf);
		}
		tmp = tmp->next;

	} while(tmp->next != NULL) ;
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd,LPARAM lParam)
{ 
	char text[MAX_PATH];

	if (IsWindowVisible(hwnd))
	{
		GetWindowText(hwnd,text, MAX_PATH);
		if(strlen(text) > 1)
		{
			//wsprintf(text, "%s\n",text);
			//Cout(text);
			WindowsList.insert(hwnd, text);
		}
	}
	return TRUE;
}

void GetAllWindow()
{
	HDESK hDesk = OpenDesktop( TEXT("default"),0,FALSE,DESKTOP_ENUMERATE);
	EnumDesktopWindows(hDesk,EnumWindowsProc,0);
}