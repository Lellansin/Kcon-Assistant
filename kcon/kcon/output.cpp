
#include <windows.h>
#include "main.h"
#include "resource.h"

void Cout(char* msg)
{
	SendMessage(GetDlgItem(hDialogHwnd,IDC_CONSOLE),EM_REPLACESEL, NULL,(LPARAM)msg); // ²åÈëÎÄ×Ö
}

void Clear()
{
	SendMessage(GetDlgItem(hDialogHwnd,IDC_CONSOLE),WM_SETTEXT, NULL,NULL);
}

void UpdateConsole()
{
	SetFocus(GetDlgItem(hDialogHwnd, IDC_CONSOLE));
	SetFocus(GetDlgItem(hDialogHwnd, IDC_EDIT_LINE));
}