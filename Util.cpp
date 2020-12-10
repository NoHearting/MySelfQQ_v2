#include "Util.h"

#include <windows.h>
#include <tlhelp32.h>
#include <QDebug>

namespace Zsj{

Util::Util()
{

}


int getCurrentProcessId(const QString & processName)
{
    HANDLE hProcess =  CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,NULL);
    if(!hProcess){
        qCritical() << "CreateToolhelp32Snapshot failed";
        return -1;
    }
    PROCESSENTRY32 info;
    info.dwSize = sizeof(PROCESSENTRY32);
    if(!Process32First(hProcess, &info)){

        qCritical() << "Process32First null";
        return -1;
    }

    bool haveNext = true;
    while(haveNext){

        haveNext = Process32Next(hProcess, &info);
        if(haveNext){

            HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, info.th32ProcessID);

            QString pName = QString::fromWCharArray(info.szExeFile);
//            qDebug() << pName << " | " <<pName.split(".")[0];
            if(processName == pName.split(".")[0]){
                return info.th32ProcessID;
            }
        }
    }
    return -1;
}



}
