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
#define NAME_COUNT 10

int compare (const void * a, const void * b)
{
    return strcmp((char*)a, (char*)b);
}


int main (int argc, char const* argv[])
{
    char String[][BUFFER] = {"abc","abd","123","1a214","cc...",",aaaladfo","zefo","3c3dd","389cz","234za3"};
    memset(String,'\0',sizeof(String));
    
    char (*pcString)[BUFFER] = String;

    printf("Please input %d Names, seperated by space => ",NAME_COUNT);

//    scanf("%s %s %s %s %s %s %s %s %s %s", \
          pcString  ,pcString+1,pcString+2,pcString+3,pcString+4,  \
          pcString+5,pcString+6,pcString+7,pcString+8,pcString+9);
    
    printf("Before NameSorting\n");
    int i;
    for(i = 0; i < NAME_COUNT; i++)
    {
        printf("Name[%d] = %s\n", i, String[i]);
    }
    printf("After NameSorting\n");
   
    qsort(pcString, NAME_COUNT, sizeof(pcString[0]), compare);
  

    for(i = 0; i < NAME_COUNT; i++)
    {
        printf("Name[%d] = %s\n", i, String[i]);
    }
    return EXIT_SUCCESS;
}

