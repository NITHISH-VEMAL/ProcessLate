#include <winsock2.h>
#include <iphlpapi.h>
#include <iostream>
#include <vector>
#include<iomanip>


using namespace std;

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x)) 
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

double activeNet(DWORD processID)
{
    const char separator = ' ';
    const int nameWidth = 6;
    const int numWidth = 8;

    vector<unsigned char> buffer;
    DWORD dwSize = sizeof(MIB_TCPTABLE_OWNER_PID);
    DWORD dwRetValue = 0;




    // repeat till buffer is big enough
    do
    {
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        buffer.resize(dwSize, 0);
        dwRetValue = GetExtendedTcpTable(buffer.data(), &dwSize, TRUE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0);  //retrieves a table that contains a list of TCP endpoints
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    } while (dwRetValue == ERROR_INSUFFICIENT_BUFFER);

    if (dwRetValue == ERROR_SUCCESS)
    {

        PMIB_TCPTABLE_OWNER_PID ptTable = reinterpret_cast<PMIB_TCPTABLE_OWNER_PID>(buffer.data());

        int flag = 0;
        DWORD i;

        for (i = 0; i < ptTable->dwNumEntries; i++)
        {


            if ((DWORD)ptTable->table[i].dwOwningPid == processID)
            {

                //cout << ptTable->table[i].dwOwningPid << "=" <<processID<< endl;



                MIB_TCPROW row;
                row.dwLocalAddr = ptTable->table[i].dwLocalAddr;
                row.dwLocalPort = ptTable->table[i].dwLocalPort;
                row.dwRemoteAddr = ptTable->table[i].dwRemoteAddr;
                row.dwRemotePort = ptTable->table[i].dwRemotePort;
                row.dwState = ptTable->table[i].dwState;
                void* processRow = &row;


                if (row.dwRemoteAddr != 0)
                {
                    ULONG rosSize = 0, rodSize = 0;
                    ULONG winStatus;
                    PUCHAR ros = NULL, rod = NULL;
                    rodSize = sizeof(TCP_ESTATS_DATA_ROD_v0);
                    PTCP_ESTATS_DATA_ROD_v0 dataRod = { 0 };


                    if (rosSize != 0) {
                        ros = (PUCHAR)malloc(rosSize);
                        if (ros == NULL) {
                            wprintf(L"\nOut of memory");
                            //return;
                        }
                        else
                            memset(ros, 0, rosSize); // zero the buffer
                    }
                    if (rodSize != 0) {
                        rod = (PUCHAR)malloc(rodSize);
                        if (rod == NULL) {
                            free(ros);
                            wprintf(L"\nOut of memory");
                            // return;
                        }
                        else
                            memset(rod, 0, rodSize); // zero the buffer
                    }




                    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    winStatus = GetPerTcpConnectionEStats((PMIB_TCPROW)&row, TcpConnectionEstatsData, NULL, 0, 0, ros, 0, rosSize, rod, 0, rodSize);
                    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //ccout << right << setw(numWidth) << setfill(separator) << (double)(dataRod->DataBytesIn + dataRod->DataBytesOut) * 0.000001 << "\t" << endl;
                    dataRod = (PTCP_ESTATS_DATA_ROD_v0)rod;



                    PTCP_ESTATS_BANDWIDTH_ROD_v0 bandwidthRod = { 0 };

                    rodSize = sizeof(TCP_ESTATS_BANDWIDTH_ROD_v0);
                    if (rodSize != 0) {
                        rod = (PUCHAR)malloc(rodSize);
                        if (rod == NULL) {
                            free(ros);
                            wprintf(L"\nOut of memory");
                            
                        }
                        else
                            memset(rod, 0, rodSize); // zero the buffer
                    }

                    winStatus = GetPerTcpConnectionEStats((PMIB_TCPROW)&row, TcpConnectionEstatsBandwidth, NULL, 0, 0, ros, 0, rosSize, rod, 0, rodSize);

                    bandwidthRod = (PTCP_ESTATS_BANDWIDTH_ROD_v0)rod;
                    



                    cout << dataRod->DataBytesIn << endl;

                    return dataRod->DataBytesIn * 100.f / bandwidthRod->OutboundBandwidth * 800.f;

                    //wprintf(L" %lu | ", dataRod->DataBytesIn + dataRod->DataBytesOut);
                  //  netusage = (dataRod->DataBytesIn + dataRod->DataBytesOut) * 0.000001;
                    flag = 1;
                    break;

                }

            }
        }
        if (flag == 0)
        {

            // cout << right << setw(numWidth) << setfill(separator) << "No usage\t";
            return 0;
            //netusage = 0;
        }


    }




    }