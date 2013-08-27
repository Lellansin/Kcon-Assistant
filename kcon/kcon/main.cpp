#include <windows.h>
#include <Richedit.h> 
#include "resource.h" 
#include "console.h"
#include "list.h"
#include "output.h"

#define ON_ENTER 100
#define TOGGLE 200

const char g_szClassName[] = "myWindowClass";

HMODULE hRichEdit;
HWND hDialogHwnd;
List WindowsList;

INT flag = 1; // 1 显示，0 隐藏

void echo(LPSTR str)
{
	MessageBox(NULL, str, TEXT("信息"), MB_OK);
}

void getInput(LPSTR str)
{
	GetDlgItemText(hDialogHwnd,IDC_EDIT_LINE,str,250);
}

BOOL CALLBACK DlgConsoleProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
		case WM_INITDIALOG:			
			hDialogHwnd = hwnd;
			RegisterHotKey(hwnd, TOGGLE, MOD_CONTROL | MOD_ALT, 'Z');
			GetAllWindow();
			Cout("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		break;

		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDOK:
					CHAR text[4068], list[4068];
					Clear();
					getInput(text);
					//console(text);
					//UpdateConsole();
					WindowsList.getSimilarIdList(text, list);
					// Cout(list);
					UpdateConsole();
				break;
			}
		break;

		case WM_HOTKEY:
			//char text[50];
			//wsprintf(text, "wParam: %x  lParam:%x", wParam, lParam);
			//MessageBox(hwnd, text, NULL, MB_OK);
			switch(wParam)
			{
			case TOGGLE:
				if (flag)
				{
					ShowWindow(hDialogHwnd, SW_HIDE);
					flag = 0;
				}else{
					ShowWindow(hDialogHwnd, SW_SHOW);
					SetFocus(GetDlgItem(hDialogHwnd, IDC_EDIT_LINE));
					flag = 1;
				}
				break;
			}
			break;

		case WM_MOUSEMOVE:
			echo("hello key down");
			break;

		case WM_SETFOCUS:
			// MessageBox(hwnd, (LPCSTR)"WM_SETFOCUS", NULL, MB_OK);
		break;

		case WM_CLOSE:
			EndDialog(hwnd, 0);
			break;
		
		case WM_DESTROY:
			FreeLibrary(hRichEdit);		
			PostQuitMessage(0);
		break;

		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	hRichEdit = LoadLibrary("RICHED20.DLL");

	DialogBox(
		hInstance, //GetModuleHandle返回指定模块名的句柄，为NULL返回本模块的句柄
		MAKEINTRESOURCE(IDD_MAIN), 
		NULL, 
		DlgConsoleProc
	);
	return 0;
}