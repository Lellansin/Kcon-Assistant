
#include <Windows.h>
#include "output.h"

int console(LPSTR cmdstr)
{
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead, hWrite;

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	if (!CreatePipe(&hRead,&hWrite,&sa,0))
	{
		MessageBox(NULL, "Error On CreatePipe()", NULL, MB_OK);
		return 1;
	}

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hWrite;
	si.hStdOutput = hWrite;
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	char command[MAX_PATH];
	wsprintf(command, "cmd.exe /c %s", cmdstr);

	if (!CreateProcess(NULL,command,NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi)) 
	{
		MessageBox(NULL, "Error on CreateProcess()", NULL, MB_OK);
		return 1;
	}
	CloseHandle(hWrite);

	char buffer[4096] = {0};
	// char text[4096];
	DWORD bytesRead;

	while (true) 
	{
		if (ReadFile(hRead,buffer,4095,&bytesRead,NULL) == NULL)
			break;
		Cout(buffer);
		Sleep(200);
	}

	return 0;
}