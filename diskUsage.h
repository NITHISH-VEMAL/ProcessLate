/* DISK USAGE - percentage of computer storage in USE */



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

using namespace std;




double findDiskUsage(DWORD processID)
{
	const char separator = ' ';
	const int nameWidth = 6;
	const int numWidth = 8;

	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, TRUE, processID);
	IO_COUNTERS sticCounter = { 0 };    // I/O accounting information 



	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	GetProcessIoCounters(hProcess, &sticCounter);
	//cout << right << setw(numWidth) << setfill(separator) << setprecision(2) << (double)sticCounter.WriteTransferCount * 0.000001 << '\t';
	//cout << to_string(sticCounter.WriteTransferCount * 0.000001) << endl;// "-" << sticCounter.WriteTransferCount << endl;
	return (sticCounter.WriteTransferCount * 0.000001);
	//cout  << sticCounter.WriteTransferCount * 0.000001 <<endl;       //number of bytes written
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


}