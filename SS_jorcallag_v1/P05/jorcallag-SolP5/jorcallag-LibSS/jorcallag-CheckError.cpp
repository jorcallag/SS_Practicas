#include "jorcallag-LibSS.h"

VOID ReportError(LPCTSTR userMessage, DWORD exitCode, BOOL printErrorMessage);

//CheckError funciona igual que ReportError pero sólo cuando ErrorCondition es TRUE. 
//Si es FALSE no hace nada. Devuelve el valor del parámetro ErrorCondition. 
BOOL CheckError(BOOL ErrorCondition, LPCTSTR userMessage, DWORD exitCode){

	if (ErrorCondition) {
		ReportError(userMessage, exitCode, TRUE);
	}
	return ErrorCondition;

}

VOID ReportError(LPCTSTR userMessage, DWORD exitCode, BOOL printErrorMessage){

	DWORD eMsgLen, errNum = GetLastError();
	LPTSTR lpvSysMsg;
	_ftprintf(stderr, _T("%s\n"), userMessage);
	if (printErrorMessage) {
		eMsgLen = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL, errNum, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpvSysMsg, 0, NULL);
		if (eMsgLen > 0)
		{
			_ftprintf(stderr, _T("%s\n"), lpvSysMsg);
		}
		else
		{
			_ftprintf(stderr, _T("Last Error Number; %d.\n"), errNum);
		}
		if (lpvSysMsg != NULL) LocalFree(lpvSysMsg); /* Explained in Chapter 5. */
	}
	Beep(440, 500);
	if (exitCode > 0) {
		MessageBeep(MB_ICONASTERISK);
		OutputDebugString("\nERROR EN EL PROGRAMA!!\nPulse tecla de RETORNO para terminar...");
		printf("\nERROR EN EL PROGRAMA!!\nPulse tecla de RETORNO para terminar...");
		getchar();
		ExitProcess(exitCode);
	}
	return;

}

