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
#include <string>
#include <string.h>
#include "MainVariables.h"
#include "ProcessManagementHash.h"





using namespace std;
static int index = 0;
//int pid[1000] = { 1 };


class HashEntry {

private:

    int key;

    int value;

    string name;

    int memusage;

    int cpuusage;

    double diskusage;

    double netusage;

    string uname;

public:

    HashEntry(int ke, int valu, string nam, int memusag, int cpuusag, double diskusag, double netusag, string unam) {
        
        this->key = ke;

        this->value = valu;

        this->name = nam;

        this->memusage = memusag;

        this->cpuusage = cpuusag;

        this->diskusage = diskusag;

        this->netusage= netusag;

        this->uname= unam;
    }

    int getKey() {

        return key;

    }

    int getValue() {
        
        return value;
        
    }
    string getName() {
       
        return  name;

    }
    int getUsage() {
        return  memusage;
    }

    int cpuUsage() {
        return  cpuusage;
    }

    double diskUsage() {
        return  diskusage;
    }

    double netUsage() {
        return  netusage;
    }
    string getuName() {

        return uname;

    }


};



const int TABLE_SIZE = 1000;



class HashMap {

private :

    HashEntry **table;
    
  

public:
    

    HashMap() {

        table = new HashEntry * [TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; i++)
            table[i] = NULL;
        

    }

   

    int get(int key) {

        int hash = key;
      
        return table[hash]->getValue();
      

    }

    string getname(int key) {

        int hash = key;
        
        return table[hash]->getName();

    }

    int getusage(int key) {

        int hash = key;
      
        return table[hash]->getUsage();

    }


    int cpuusage(int key) {

        int hash = key;
        
        return table[hash]->cpuUsage();

    }
    double diskusage(int key) {

        int hash = key;
       
        return table[hash]->diskUsage();

    }

    double netusage(int key) {

        int hash = key;
   
        return table[hash]->netUsage();

    }

    string getuname(int key) {

        int hash = key;
     
        return table[hash]->getuName();

    }

    void put(int ke, int valu, string nam, int memusag, int cpuusag, double diskusag, double netusag, string use) {

        int hash = ke;

        table[hash] = new HashEntry(ke, valu, nam, memusag, cpuusag, diskusag, netusag, use);

    }

    

   






};