#include <stdio.h>
#include <Windows.h>
#include <tchar.h>
#include "joaalmcon-LibSS.h"

static VOID ReportError(LPCTSTR userMessage, DWORD exitCode, BOOL printErrorMessage);

BOOL CheckError(BOOL ErrorCondition, LPCTSTR userMessage, DWORD exitCode) {
	
	if (ErrorCondition)
		ReportError(userMessage, exitCode, TRUE);

	return ErrorCondition;
}

static VOID ReportError(LPCTSTR userMessage, DWORD exitCode, BOOL printErrorMessage)

/* General-purpose function for reporting system errors.
	Obtain the error number and convert it to the system error message.
	Display this information and the user-specified message to the standard error device.
	userMessage:		Message to be displayed to standard error device.
	exitCode:		0 - Return.
					> 0 - ExitProcess with this code.
	printErrorMessage:	Display the last system error message if this flag is set. */
{
	DWORD eMsgLen, errNum = GetLastError();
	LPTSTR lpvSysMsg;
	_ftprintf(stderr, _T("%s\n"), userMessage);
	OutputDebugString(userMessage);
	OutputDebugString("\n");
	if (0 != errNum && printErrorMessage) {
		eMsgLen = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL, errNum, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpvSysMsg, 0, NULL);
		if (eMsgLen > 0)
		{
			_ftprintf(stderr, _T("%s\n"), lpvSysMsg);
			OutputDebugString(lpvSysMsg);
			OutputDebugString("\n");
		}
		else
		{
			char mensaje[200];
			snprintf(mensaje,200,"Last Error Number; %d.\n", errNum);
			_ftprintf(stderr, _T("Last Error Number; %d.\n"), errNum);
			OutputDebugString(mensaje);
		
		}

		if (lpvSysMsg != NULL) LocalFree(lpvSysMsg); /* Explained in Chapter 5. */
	}

	Beep(440, 500);

	if (exitCode > 0)
		
		printf("\nError en el programa! Pulse tecla RETORNO para terminar\n");
		getchar();
		ExitProcess(exitCode);

	return;
}
