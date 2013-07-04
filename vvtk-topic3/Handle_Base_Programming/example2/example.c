//#define NDEBUG

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "header.h"

typedef void*   HANDLE;

/*****************************************
*  Structure
*****************************************/
typedef struct
{
    char acIn_msg[128];
        int (*Send)(HANDLE, const char *);
        int  (*Get)(HANDLE,       char *);
} TCommunication;

typedef struct 
{
    TCommunication ComFunction;
    char acTelnetdAddress[128];  //char, different from TCOM
} TTelnet;

typedef struct
{
    TCommunication ComFunction;
    int iComPortNumber;         //int, different from TTelnet
} TCOM;

typedef struct 
{
    HANDLE hType;   
    TCommunication *hCommunication;
} TShell;

/*****************************************
*  Telnet Send/Get
*****************************************/
int Send_With_Telnet(HANDLE hTelnet, const char *acMsg)
{
    TTelnet *pT = (TTelnet *)hTelnet;
    printf("SEND %s to %s with telnet!\n",acMsg, pT->acTelnetdAddress);
    return 0;
}
int Get_From_Telnet(HANDLE hTelnet, char *acIn_msg)
{
    TTelnet *pT = (TTelnet *)hTelnet;
    char acMsg[128];
    sprintf(acMsg, "GET MESSAGE FROM Tetlnetd %s",pT->acTelnetdAddress);
    strncpy(acIn_msg,acMsg,sizeof(acMsg));
    return 0;
}

/*****************************************
*  COM Send/Get
*****************************************/
int Send_With_COM(HANDLE hCOM, const char *acMsg)
{
    TCOM *pC = (TCOM *)hCOM;
    printf("send %s to COM %d!\n",acMsg,pC->iComPortNumber);
    return 0;
}

int Get_From_COM(HANDLE hCOM, char *acIn_msg)
{
    TCOM *pC = (TCOM *)hCOM;
    char acMsg[128];
    sprintf(acMsg, "GET MESSAGE FROM COM %d",pC->iComPortNumber);
    strncpy(acIn_msg,acMsg,sizeof(acMsg));
    return 0;
}

/*****************************************
*  Initial
*****************************************/
#define _PTR

#ifdef _PTR
void TelnetInitial(HANDLE *hTelnet)
#else
void TelnetInitial(HANDLE hTelnet)
#endif
{

#ifdef _PTR
    TTelnet *pT = (TTelnet *)*hTelnet;
#else
    TTelnet *pT = (TTelnet *)hTelnet;
#endif
    pT->ComFunction.Send = Send_With_Telnet;
    pT->ComFunction.Get = Get_From_Telnet;
    //strncpy(pT->acTelnetdAddress, "vvtk.com", sizeof(pT->acTelnetdAddress));  <--buggy statement
    const char address[] = "vvtk.com";
    strncpy(pT->acTelnetdAddress, address, sizeof(address));
#ifdef _PTR
	printf("........... %x, %x, %x\n", hTelnet, &hTelnet, *hTelnet);
	*hTelnet = NULL;
	printf("........... %x, %x, %x\n", hTelnet, &hTelnet, *hTelnet);
#else
	printf("........... %x, %x\n", hTelnet, &hTelnet);
	hTelnet = NULL;
	printf("........... %x, %x\n", hTelnet, &hTelnet);
#endif
}
void COMInitial(HANDLE hCOM)
{
    TCOM *pC = (TCOM *)hCOM;
    pC->ComFunction.Send = Send_With_COM;
    pC->ComFunction.Get = Get_From_COM;
    pC->iComPortNumber = 2;
}

/*****************************************
*  Shell Behavior
*****************************************/
void runShell(TShell *hShell)
{
    int iCounter;
    for(iCounter = 0;iCounter<1;iCounter++)
    {
        char acMsg[128];    
        sprintf(acMsg, "%d-th Hello World!", iCounter);
        hShell->hCommunication->Send(hShell->hType,(const char *)acMsg);
        hShell->hCommunication->Get(hShell->hType,hShell->hCommunication->acIn_msg);
        printf("Get Message:%s\n",hShell->hCommunication->acIn_msg);
    }
}


int main(int argc, char const* argv[])
{
    // initial telnet and COM
    TTelnet task_telnet;
    TCOM task_COM;
    TShell shellTelnet, shellCOM;
    shellTelnet.hType = &task_telnet;
    shellCOM.hType = &task_COM;
    
#ifdef _PTR
    TelnetInitial(&shellTelnet.hType);   
	printf("...... %x\n", shellTelnet.hType);
#else
    TelnetInitial(shellTelnet.hType);   
	printf("...... %x\n", shellTelnet.hType);
#endif
    COMInitial(shellCOM.hType);
    shellTelnet.hCommunication = &task_telnet.ComFunction;
    shellCOM.hCommunication = &task_COM.ComFunction;

    // Initial two shells: Telnet shell and COM shell
    runShell(&shellTelnet);
    runShell(&shellCOM);

    DBG_PRINT("strlen = %d, sizeof = %d\n",strlen("123456789"),sizeof("123456789"));
    return 0;
}
