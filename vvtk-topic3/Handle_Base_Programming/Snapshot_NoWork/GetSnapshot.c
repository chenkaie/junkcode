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
#include <string.h>
#include <assert.h>
#include <unistd.h>
//#include "header.h"


//http://172.16.7.85/cgi-bin/viewer/video.jpg

int main (int argc, char const* argv[])
{
    
    //execv("/sbin/ls",NULL);

    char *paWeekName[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    char paWeekName1[] = {"Sun"};
    printf("today is %s, %s",paWeekName1,paWeekName[0]);

    int iIndex = 0;
    const int ciMaxNumber = 5;
    char cWgetString[128];
    memset(&cWgetString,'\0',sizeof(cWgetString));
    getchar();
    while(iIndex < 10){
    sprintf(cWgetString,"wget --http-user=root --http-password=e9b8z723 http://172.16.7.85/cgi-bin/viewer/video.jpg -O video%d.jpg",(iIndex % ciMaxNumber)+1);
    iIndex++;
    system(cWgetString);
    sleep(5);
    }

    return EXIT_SUCCESS;
}

