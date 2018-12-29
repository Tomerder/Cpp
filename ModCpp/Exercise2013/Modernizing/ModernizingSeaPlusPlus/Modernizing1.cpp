// Adapted from FileZilla
// https://github.com/BruceZhang/FileZilla/blob/master/FileZillaServer/source/FileLogger.cpp#L45

#include "Modernizing1.h"

char* ConvToNetwork(LPCSTR msg)
{
	return _strdup(msg);
}

HANDLE OpenLogFile()
{
	return CreateFile(L"log.tmp", GENERIC_READ | GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, 0, nullptr);
}

BOOL Log(LPCSTR msg)
{
	HANDLE hLogFile = OpenLogFile();
	if (hLogFile == INVALID_HANDLE_VALUE)
		return TRUE;

	char* utf8 = ConvToNetwork(msg);
	if (!utf8)
		return FALSE;

	DWORD numwritten;
	if (!WriteFile(hLogFile, utf8, strlen(utf8), &numwritten, 0) || !WriteFile(hLogFile, "\r\n", 2, &numwritten, 0))
	{
		delete[] utf8;
		CloseHandle(hLogFile);
		return FALSE;
	}
	delete[] utf8;

	return TRUE;
}