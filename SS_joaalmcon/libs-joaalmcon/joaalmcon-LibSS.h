#pragma once
#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include <tchar.h>

BOOL CheckError(BOOL ErrorCondition, LPCTSTR userMessage, DWORD exitCode);
double MideRetraso(LPCTSTR pMensaje);