#pragma once

#include "pch.h"

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
#include <pdh.h>
#include <iomanip>
#include <string>
#include <string.h>

#include <shellapi.h>
#include "terminate.h"
#include "printpname.h"
#include "memoryinfo.h"
#include "cpuUsage.h"
#include "diskUsage.h"
#include "netUsage.h"
#include "findUser.h"
#pragma comment(lib,"pdh.lib")

#include "ProcessManagementHash.h"
#include <map>
#include "jni.h"
#include "JNITest.h"

using namespace std;

DWORD cProcesses;
DWORD pid[1000];
double cpuusage[1000] ;



	

extern "C" JNIEXPORT jobject JNICALL Java_JNITest_getMap
(JNIEnv* env, jclass obj)
{


//void print() {
	//cout << " 1: view all process\n 2: To start a new process\n 3: To terminate a process from listed\n";
	//tuple <int, int, float> processInfo;
	//processInfo = make_tuple(1 , 10, 15.5);
	map<string, string> map;
	
	//while (1)
	//{
		//int getOption;
		//cout << "\nChoose your option : ";
		//cin >> getOption;

		switch (1)
		{


			// case 1 to view all process
		case 1:
		{

			DWORD aProcesses[1024], cbNeeded;
			//DWORD cProcesses;
			unsigned int i;

			////////////////////////////////////////////////////////////////////
			if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))               //     to get all the process ID [ array, size, number of bytes ]
			///////////////////////////////////////////////////////////////////
			{
				//return 1;
			}


			int f = 0;
			cProcesses = cbNeeded / sizeof(DWORD);   //to find no. of 
			
			
			//int index = 0;
			//HashMap hash;



			for (i = 1; i < cProcesses; i++)
			{
				pid[i] = aProcesses[i];
				init(pid[i]);

				Sleep(1000);
				
				cpuusage[i] = getCurrentValue(pid[i]);
				//cout << cpuusage[i] << endl;

			}

			int j, k;

			for (j = 1; j < cProcesses; j++)
			{
				for (k = j + 1; k < cProcesses; k++)
				{
					if (cpuusage[j] < cpuusage[k])
					{
						double temp = cpuusage[j];
						cpuusage[j] = cpuusage[k];
						cpuusage[k] = temp;

						int temporary = pid[j];
						pid[j] = pid[k];
						pid[k] = temporary;
					}
				}
			}
			
			const char separator = ' ';
			const int nameWidth = 4;
			const int numWidth = 8;
			/*cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
			cout << left << setw(4) << setfill(separator) << "PID\t ";
			cout << left << setw(nameWidth) << setfill(separator) << " PName\t ";
			cout << left << setw(nameWidth) << setfill(separator) << " \tMemoryUsed ";
			cout << left << setw(nameWidth) << setfill(separator) << " CPUused ";
			cout << left << setw(nameWidth) << setfill(separator) << " DiskUsed ";
			cout << left << setw(nameWidth) << setfill(separator) << " NetUsed\t\t\t";
			cout << left << setw(nameWidth) << setfill(separator) << " User handles " << endl;
			cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
			*/


			for (i = 1; i < cProcesses; i++)
			{
				if (aProcesses[i] != 0)
				{
					//cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

				  ///////////////////////////////////////////////////////
					//cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
					string pname = PrintProcessNameAndID(pid[i]);



					int memusage = memoryInformation(pid[i]);

					//cout << cpuusage[i] <<"\t| ";
					//cout << right << setw(numWidth) << setfill(separator) << cpuusage[i];

					int diskusage = findDiskUsage(pid[i]);


					double netusage = activeNet(pid[i]) ;


					string s = openProcessToken(pid[i]);

					//cout << "-----------------------------------------------------------------------------------" << endl;
					//cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl<<endl;
				//////////////////////////////////////////////////////


					

				}
				
			}


			for (int x = 0; x < cProcesses; x++) {
				string processInfo = to_string(pid[x]) + '\t' + PrintProcessNameAndID(pid[x]) + '\t' + to_string(cpuusage[x]) + '\t' + to_string(memoryInformation(pid[x])) + '\t' + to_string(findDiskUsage(pid[x])) + '\t' + to_string(activeNet(pid[x])) + '\t' + openProcessToken(pid[x]) + '\t';
				//cout << processInfo << endl;
				map[to_string(x)] = processInfo;
			}

			
			break;
		}



		//case 2 to start new process
		case 2:
		{



			///////////////////////////////////////////////////////////////////
			string processName;
			cout << "Enter the process name : ";
			cin >> processName;
			std::wstring ws;                                                   // convert string to LPCWSTR
			ws.assign(processName.begin(), processName.end());
			LPWSTR pwst = &ws[0];
			LPCWSTR pcwstr = ws.c_str();
			///////////////////////////////////////////////////////////////////




			/////////////////////////////////////////////////////////////////////
			ShellExecute(0, L"open", pcwstr, NULL, 0, SW_SHOW);                  //   to open the process  [ message, whatToDo, fileName, parameter, directory, how to open]
			  ////////////////////////////////////////////////////////////////////

			break;

		}




		case 3:
		{


			cout << "Enter the process ID to be deleted : ";
			DWORD processID;
			cin >> processID;


			//////////////////////////////////////
			Terminate(processID);             //   terminate process function
			//////////////////////////////////////


			break;


		}



		}

	//}
		
		

	//printf("JNI call from java\n");
	
		//map[x] = to_string(pid[x]);
	
	
	
	/*jclass mapClass = env->FindClass("java/util/HashMap");


	jclass integerClass = env->FindClass("java/lang/Integer");



	jmethodID mapConstructorID = env->GetMethodID(mapClass, "<init>", "()V");


	jmethodID putMethodID = env->GetMethodID(mapClass, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");


	jmethodID integerConstructorID = env->GetMethodID(integerClass, "<init>", "(I)V");


	// We can now create HashMap object
	jobject hashMap = env->NewObject(mapClass, mapConstructorID);


	for (auto const& pair : map) {

		const char* secondStr = pair.second.c_str();
		jobject key = env->NewObject(integerClass, integerConstructorID, pair.first);
		jobject value = env->NewStringUTF(secondStr);

		env->CallObjectMethod(hashMap, putMethodID, key, value);
	}

	env->DeleteLocalRef(mapClass);
	env->DeleteLocalRef(integerClass);

	return hashMap;*/


	// Creating HashMap - we have to instantiate object of class HashMap
		jclass hashMapClass = env->FindClass("java/util/HashMap");

		// Get the constructor of HashMap
		jmethodID hashMapConstructorID = env->GetMethodID(hashMapClass, "<init>", "()V");

		jobject hashMap = env->NewObject(hashMapClass, hashMapConstructorID);

		// Get id of 'put' method
		jmethodID putMethodID
			= env->GetMethodID(
				hashMapClass,
				"put",
				"(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");

		// For each pair inside 'map' I will call 'put' of Java based HashMap
		for (auto const& pair : map) {
			jstring key = env->NewStringUTF(pair.first.c_str());
			jstring value = env->NewStringUTF(pair.second.c_str());

			env->CallObjectMethod(hashMap, putMethodID, key, value);
		}
		return hashMap;

}






int main(int argc, TCHAR* argv[])
{
	

	
	JNIEXPORT jobject JNICALL Java_newjni_JNITest_getMap(JNIEnv * env, jclass obj);

	return 0;
}