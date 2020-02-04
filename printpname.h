#include <winsock2.h>
#include <Ws2tcpip.h>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>
#include <iostream>
#include <string>
#include<WinBase.h>
#include <iphlpapi.h>
#include<iomanip>
#include <Tcpestats.h>
//#include "ProjectManagement.h"
#include <string.h>
using namespace std;


string PrintProcessNameAndID(DWORD processID)
{
	const char separator = '  ';
	const int nameWidth = 6;
	const int numWidth = 8;

	TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");  //enter as unknown for all process initially, handles object


  //////////////////////////////////////////////////////////////////////////////////////////////////
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, TRUE, processID);      // provide an abstraction of a resource [ needed , inherit handle , id]
  /////////////////////////////////////////////////////////////////////////////////////////////////

  // token, exit code
  //process vm read - Required to read memory in a process using ReadProcessMemory.

	if (NULL != hProcess)
	{
		HMODULE hMod;
		DWORD cbNeeded;

		///////////////////////////////////////////////////////////////////////////////
		if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {}                  // handle for each module in the specified process, many process present
	//////////////////////////////////////////////////////////////////////////////

		{


			/////////////////////////////////////////////////////////////////////////////////////////////////
			GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));             //   get process name and store in szprocessname
		////////////////////////////////////////////////////////////////////////////////////////////////


		}
	}
	char szString[10000];
	size_t nNumCharConverted;
	wcstombs_s(&nNumCharConverted, szString, 10000, szProcessName, 10000);

	szString[9] = '\0';

	//processid = processID;
	//strcpy(name, szString);

	int i;
	string s = "";
	for (i = 0; i < 9; i++) {
		s = s + szString[i];
	}
	//cout << "|" << left << setw(10) << setfill(separator) << (int)processID;
	//cout << left << setw(nameWidth) << setfill(separator) << szString << '\t';
	return s;

	/*
	;
		/*for (int i = 0; i < 15; i++)
			_tprintf(TEXT("%c"), szProcessName[i]);
		printf(" |");
		DWORD pid = processID;
		int size = 1;
		while (pid != 0) {
			size++;
			pid /= 10;
		}
		_tprintf(TEXT(" %u"), processID);
		for (int i = 0; i < 10 - size; i++) {
			printf(" ");
		}
		printf(" |");*/

		/*if (CloseHandle(hProcess))
		{
			return;
		}*/
}
