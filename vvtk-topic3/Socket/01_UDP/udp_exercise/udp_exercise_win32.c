/*
 *******************************************************************************
 * $Header: /RD_1/home/kevin/Lab/SocketProgramming/udp_exercise/udp_exercise.c 1	07/05/01 2:56p Kevin $
 *
 *  Copyright (c) 2000-2006 Vivotek Inc. All rights reserved.
 *
 *  +-----------------------------------------------------------------+
 *  | THIS SOFTWARE IS FURNISHED UNDER A LICENSE AND MAY ONLY BE USED |
 *  | AND COPIED IN ACCORDANCE WITH THE TERMS AND CONDITIONS OF SUCH  |
 *  | A LICENSE AND WITH THE INCLUSION OF THE THIS COPY RIGHT NOTICE. |
 *  | THIS SOFTWARE OR ANY OTHER COPIES OF THIS SOFTWARE MAY NOT BE   |
 *  | PROVIDED OR OTHERWISE MADE AVAILABLE TO ANY OTHER PERSON. THE   |
 *  | OWNERSHIP AND TITLE OF THIS SOFTWARE IS NOT TRANSFERRED.        |
 *  |                                                                 |
 *  | THE INFORMATION IN THIS SOFTWARE IS SUBJECT TO CHANGE WITHOUT   |
 *  | ANY PRIOR NOTICE AND SHOULD NOT BE CONSTRUED AS A COMMITMENT BY |
 *  | VIVOTEK INC.                                                    |
 *  +-----------------------------------------------------------------+
 *
 * $History: udp_exercise.c $
 * 
 * *****************  Version 1  *****************
 * User: Kevin      Date: 07/05/01   Time: 10:56a
 * Created in $/RD_1/home/kevin/Lab/SocketProgramming/udp_exercise/
 * Kevin, 2007/05/01, created in VS.Net 2003 first time
 * 
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * Copyright 2000-2006 Vivotek, Inc. All rights reserved.
 *
 * \file
 * udp_exercise.c
 *
 * \brief
 * Socket programming Exercise 1
 *
 * \date
 * 2007/04/26
 *
 * \author
 * Kevin Chang
 *
 *******************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#define BUFSIZE 1460	//Stand TCP package size

//Error message founction
void Error_Message(char *pcMesg)
{
	printf("\n Error->%s\n", pcMesg);
	exit(0);
}

//Socket initial(Initial UDP/IP for socket, set port & address) & socket error handle founction
void Socket_Initial(SOCKET *ptSockName, struct sockaddr_in *ptAddrName, char *pcPort, unsigned long ulAddr)
{
	*ptSockName = socket(AF_INET, SOCK_DGRAM, 0);//create SOCKET,AF_INET代表用IP,SOCK_STREAM代表用TCP,SOCK_DGRAM代表用UDP,0代表使用預設的通訊協定
	if (*ptSockName == SOCKET_ERROR)
	{
		Error_Message("socket() Failed");
	}
	if (ptAddrName != NULL)
	{
		memset(ptAddrName, 0, sizeof(struct sockaddr_in));
		ptAddrName->sin_family = AF_INET;
		ptAddrName->sin_port = htons(atoi(pcPort));
		ptAddrName->sin_addr.s_addr = ulAddr;
	}
}

//main founction send & recv data
int main(int argc, char *argv[])
{
	WSADATA wsaData;	//Windows only

	SOCKET SendSocket;
	SOCKET RecvSocket;

    int iSockAddrSize;
	char acSendBuffer[BUFSIZE];
	char acRecvBuffer[BUFSIZE];
	struct sockaddr_in tSendAddr;
	struct sockaddr_in tRecvAddr;

	iSockAddrSize = sizeof(struct sockaddr_in);
	
	//Check input param, tell user how to use this program
    if (argc != 4)
	{
		Error_Message("usage:udp_exercise <remote_ip_address> <send_port> <receive_port>");
	}

	//WSAStartup windows only
    if (WSAStartup(0x0101, &wsaData) != 0)
	{
		Error_Message("Could not open Windows connection");
	}
	
	//SendSocket Initial, set send IP & port
	Socket_Initial(&SendSocket, &tSendAddr, argv[2], inet_addr(argv[1]));

	//RecvSocket Initial, set receive port & any IP
	Socket_Initial(&RecvSocket, &tRecvAddr, argv[3], INADDR_ANY);

	//Give RecvSocket name, bind IP port to RecvSocket 
	if (bind(RecvSocket, (struct sockaddr *)&tRecvAddr, sizeof(struct sockaddr_in)) == -1)
	{
		closesocket(RecvSocket);
		WSACleanup();	//Windows only
		Error_Message("Could not bind name to RecvSocket");
	}

	//Send & receive data loop
	while(1)
	{

		//Send "SednData" to target & print send data then sleep 1 sec.
		memset(acSendBuffer, 0, BUFSIZE);
		strcpy(acSendBuffer, "SednData");
		if (sendto(SendSocket, acSendBuffer, (int)strlen(acSendBuffer) + 1, 0, (struct sockaddr *)&tSendAddr, iSockAddrSize) == -1)
		{			
			closesocket(SendSocket);
			WSACleanup();	//Windows only
			Error_Message("Error transmitting data");
		}
		else
		{
			printf("Send Data = %s !!\n", acSendBuffer);
			Sleep(1000);
		}

		//Receive data & print out received data, remote ip and port
		memset(acRecvBuffer, 0, BUFSIZE);
		if (recvfrom(RecvSocket, acRecvBuffer, BUFSIZE, 0, (struct sockaddr *)&tRecvAddr, &iSockAddrSize) == -1)
		{
			closesocket(RecvSocket);
			WSACleanup();	//Windows only
			Error_Message("Error Received data");
		}
		printf("Recive Data=%s Remote IP=%s Port=%d\n", acRecvBuffer, inet_ntoa(tRecvAddr.sin_addr), atoi(argv[2]));
	}//while(1)

}//main
