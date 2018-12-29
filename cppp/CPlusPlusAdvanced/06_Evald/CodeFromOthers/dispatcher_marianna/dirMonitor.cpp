/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      2013-12-18
    Last modified date: 2013-12-21
    Description : Direction Monitor
***************************************************************************************/
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>
#include <iostream>
using namespace std;

#include "dirMonitor.h"
#include "errormsg.h"
using namespace error_m7;

DirMonitor::DirMonitor(LPCWSTR _path):m_path(_path){}

void DirMonitor::Monitor()
{
/*
 typedef struct _FILE_NOTIFY_INFORMATION {
  ULONG                   NextEntryOffset;
  ULONG                   Action;
  ULONG                   FileNameLength;
  WCHAR                   FileName[1];
} FILE_NOTIFY_INFORMATION, *PFILE_NOTIFY_INFORMATION;
    FileName member of FILE_NOTIFY_INFORMATION has only one WCHAR according to definition. Most likely, this field will have more characters. 
    So the expected size of one item is (sizeof(FILE_NOTIFY_INFORMATION) + MAX_PATH * sizeof(WCHAR)).
    Prepare buffer for 256 items.
    */
    char buf[256 * (sizeof(FILE_NOTIFY_INFORMATION) + MAX_PATH * sizeof(WCHAR))] = {0};
    DWORD bytesReturned = 0;
    BOOL result = FALSE;
    FILE_NOTIFY_INFORMATION *fni = NULL;

    HANDLE hDir = CreateFile(m_path,					//  _In_      LPCTSTR lpFileName
        FILE_LIST_DIRECTORY | STANDARD_RIGHTS_READ, //  _In_      DWORD dwDesiredAccess
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, //  _In_      DWORD dwShareMode
        NULL, 			//  _In_opt_  LPSECURITY_ATTRIBUTES lpSecurityAttributes
        OPEN_EXISTING,  //  _In_      DWORD dwCreationDisposition
        FILE_FLAG_BACKUP_SEMANTICS,  //  _In_      DWORD dwFlagsAndAttributes
         NULL);			//  _In_opt_  HANDLE hTemplateFile

    if (hDir == INVALID_HANDLE_VALUE)
    {
        ErrorMsg(TEXT("Error Create File"));
        return;
    }

    while (1)
    {
        result = ReadDirectoryChangesW(hDir, //  _In_         HANDLE hDirectory,
            buf, //  _Out_        LPVOID lpBuffer,
            sizeof(buf) / sizeof(*buf),  //  _In_         DWORD nBufferLength,
            TRUE, // monitor the entire subtree
            FILE_NOTIFY_CHANGE_FILE_NAME |
                FILE_NOTIFY_CHANGE_DIR_NAME |
                FILE_NOTIFY_CHANGE_ATTRIBUTES |
                FILE_NOTIFY_CHANGE_SIZE | 
                FILE_NOTIFY_CHANGE_LAST_WRITE | 
                FILE_NOTIFY_CHANGE_LAST_ACCESS |
                FILE_NOTIFY_CHANGE_CREATION |
                FILE_NOTIFY_CHANGE_SECURITY, //  _In_         DWORD dwNotifyFilter - which changes watch
            &bytesReturned,	//  _Out_opt_    LPDWORD lpBytesReturned,
            NULL, //  _Inout_opt_  LPOVERLAPPED lpOverlapped,
            NULL); //  _In_opt_     LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine

        if (result && bytesReturned)
        {
            wchar_t filename[MAX_PATH];
            wchar_t action[256];
            for (fni = (FILE_NOTIFY_INFORMATION*)buf; fni; )
            {
                switch (fni->Action)
                {
                case FILE_ACTION_ADDED:
                    wcscpy_s(action, sizeof(action) / sizeof(*action), L"File added:");
                    break;

                case FILE_ACTION_REMOVED:
                    wcscpy_s(action, sizeof(action) / sizeof(*action), L"File removed:");
                    break;

                case FILE_ACTION_MODIFIED:
                    wcscpy_s(action, sizeof(action) / sizeof(*action), L"File modified:");
                    break;

                case FILE_ACTION_RENAMED_OLD_NAME:
                    wcscpy_s(action, sizeof(action) / sizeof(*action), L"File renamed, was:");
                    break;

                case FILE_ACTION_RENAMED_NEW_NAME:
                    wcscpy_s(action, sizeof(action) / sizeof(*action), L"File renamed, now is:");
                    break;

                default:
                    swprintf_s(action, sizeof(action) / sizeof(*action), L"Unkonwn action: %ld. File name is:", fni->Action);
                }

                if (fni->FileNameLength)
                {
                    wcsncpy_s(filename, MAX_PATH, fni->FileName, fni->FileNameLength / 2);
                    filename[fni->FileNameLength / 2] = 0;
					wcscat_s(action, sizeof(action) / sizeof(*action), filename);				
                    //wprintf(L"%s '%s'\n", action, filename); //call notify
                }
                else
                {
					wcscat_s(action, sizeof(action) / sizeof(*action), L"%s <EMPTY>\n");
                   // wprintf(L"%s <EMPTY>\n", action); // call notify
                }                

				Dispatch(action);

                if (fni->NextEntryOffset)
                {
                    char *p = (char*)fni;
                    fni = (FILE_NOTIFY_INFORMATION*)(p + fni->NextEntryOffset);
                }
                else
                {
                    fni = NULL;
                }
            }
        }
        else
        {
			ErrorMsg(TEXT("ReadDirectoryChangesW failed"));
        }
    }

    CloseHandle(hDir);
}


//int main()
//{
//	//error_m7::ErrorMsg(TEXT("ReadDirectoryChangesW failed"));
//	dirMonitor_m7::DirMonitor(L"C:\\Users\\Marianna\\Desktop\\TestWind\\");
//	return 0;
//
//}

