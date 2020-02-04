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
#include <Tcpestats.h>
#include<iomanip>

#include <comdef.h>
#define MAX_NAME 256

using namespace std;

string openProcessToken(DWORD processID)
{
    const char separator = ' ';
    const int nameWidth = 6;
    const int numWidth = 8;

    //string user="";
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, TRUE, processID);
    HANDLE hProcessToken = NULL;

    /////////////////////////////////////////////////////////////////////////////////
    if (!::OpenProcessToken(hProcess, TOKEN_READ, &hProcessToken) || !hProcessToken)
    {

    }
    /////////////////////////////////////////////////////////////////////////////////



    DWORD dwProcessTokenInfoAllocSize = 0;
    if (!GetTokenInformation(hProcessToken, TokenUser, NULL, 0, &dwProcessTokenInfoAllocSize)) {}

    PTOKEN_USER pUserToken = NULL;//  reinterpret_cast<PTOKEN_USER>(new BYTE[dwProcessTokenInfoAllocSize]);
    pUserToken = (PTOKEN_USER)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_PATH);


    /////////////////////////////////////////////////////////////////////////////////
    if (GetTokenInformation(hProcessToken, TokenUser, pUserToken, dwProcessTokenInfoAllocSize, &dwProcessTokenInfoAllocSize))
    {

        SID_NAME_USE   snuSIDNameUse;
        TCHAR          szUser[MAX_PATH] = { 0 };
        DWORD          dwUserNameLength = MAX_PATH;
        TCHAR          szDomain[MAX_PATH] = { 0 };
        DWORD          dwDomainNameLength = MAX_PATH;

        // Retrieve user name and domain name based on user's SID.
        if (LookupAccountSid(NULL,
            pUserToken->User.Sid,
            szUser,
            &dwUserNameLength,
            szDomain,
            &dwDomainNameLength,
            &snuSIDNameUse))
        {


            char szuserString[10000];
            size_t nNumCharConverted;
            wcstombs_s(&nNumCharConverted, szuserString, 10000, szUser, 10000);

            int i;
            string s = "";
            for (i = 0; i < 9; i++) {
                s = s + szuserString[i];
            }

            szuserString[9] = '\0';
            //cout << right << setw(nameWidth) << setfill(separator) << szuserString << " |" << endl;
            return s;
            //strcpy(username, szuserString);
        }

    }
    else {
        //cout << right << setw(nameWidth) << setfill(separator) << "SYSTEM |" << endl;
        int i;
        string s = "SYSTEM";
        return s;
        //strcpy(username, "Sytem");
    }

}
