/* using GetMemoryInfo we can we the physical memory used by each process */

// physical memory used




#include <iomanip> 
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

using namespace std;
int memoryInformation(DWORD processID)
{
	const char separator = ' ';
	const int nameWidth = 6;
	const int numWidth = 8;
	HANDLE tmpHandle = OpenProcess(PROCESS_ALL_ACCESS, TRUE, processID);         //open process
	PROCESS_MEMORY_COUNTERS pmc = { 0 };   //Contains the memory statistics for a process.


	///////////////////////////////////////////////////////////////////
	if (GetProcessMemoryInfo(tmpHandle, &pmc, sizeof(pmc))) {}               //  Retrieves memory usage of specified process
   /////////////////////////////////////////////////////////////////


	SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
	//SIZE_T num = physMemUsedByMe * 0.000000125;
	//cout   <<"\t\t|"   ;    //The current working set size of physical memory, in bytes.
	int mem = static_cast<int>(physMemUsedByMe * 0.000000125);
	//memusage = physMemUsedByMe*0.000000125;
	//cout << right << setw(numWidth) << setfill(separator) << setprecision(2) << physMemUsedByMe * 0.000000125;
	return mem;





	//bytes to mb
}