
#ifndef _LIST_H_
#define _LIST_H_

#define TITLE_NAME_LEN 500

struct node
{
	int id;
	char name[TITLE_NAME_LEN];
	HWND hwnd;
	node *next;
} ;

class List
{
public :
	List();
	void insert(HWND hwnd, LPSTR name);
	HWND getHwndByName(char *name);
	HWND getHwndById(int id);
	void getSimilarIdList(char *name, char *buf, int bufsize=1024);
	node* getLastNode();

private:
	node * head;
};

void GetAllWindow();

extern List WindowsList;


#endif