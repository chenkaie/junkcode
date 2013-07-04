/*
 **********************************************************************
 * $Header$
 *
 *  Copyright (c) 2000-2008 Vivotek Inc. All rights reserved.
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
 * $History$
 *
 ***********************************************************************
 */

/*!
 * Copyright 2000-2008 Vivotek, Inc. All rights reserved.
 *
 * \file
 * filename
 *
 * \brief
 * Descriptions about this file.
 *
 * \date
 * 2008/xx/xx
 *
 * \author
 * Kent Chen
 *
 *
 **********************************************************************
 */
#define NDEBUG

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../header.h"

#define BUFFER 100

int main (int argc, char const* argv[])
{

    char URL[BUFFER];
    memset(URL,'\0',sizeof(URL));

    printf("If u want to use Default URL, press 'y' followed by an Enter, or press 'n'\n");
    if(getchar() == 'y')
    {
        //static const char URLTemp[] = "http://192.168.0.56:8080/login.cgi?username=root&password=123";
        static const char URLTemp[] = "http://172.16.5.30:8888/user/login.cgi?username=root&password=rootpasswd";
        //printf("Default URL = %s\n", URLTemp);
        strcpy(URL,URLTemp);
    }
    else
    {
        printf("Please input a URL => ");
        scanf("%s",URL);
    }
    printf("URL = %s\n", URL);
    
    char sProtocol[BUFFER],sHostName[BUFFER],sURI[BUFFER],sArg1[BUFFER],sArgVal1[BUFFER],sArg2[BUFFER],sArgVal2[BUFFER];
    int  iPort = 0;
    sscanf(URL,"%[^:]://%[^:]:%d%[^?]?%[^=]=%[^&]&%[^=]=%[^&]",sProtocol,sHostName,&iPort,sURI,sArg1,sArgVal1,sArg2,sArgVal2);

    printf(" Protocol = %s\n HostName = %s\n Port = %d\n URI = %s\n %s = %s\n %s = %s\n",
            sProtocol,sHostName,iPort,sURI,sArg1,sArgVal1,sArg2,sArgVal2);
    
    
    return EXIT_SUCCESS;
}

