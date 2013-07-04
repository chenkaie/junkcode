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

void ToCapital(char *pcBuffer)
{
    while((*pcBuffer++ = toupper(*pcBuffer)) != '\0')
    {
    }
}

#define BUFFER 100

int main (int argc, char const* argv[])
{

    char String[BUFFER];
    memset(String,'\0',sizeof(String));
    printf("Please input a string => ");
    scanf("%s",String);
    printf("Original string = %s\n", String);

    char *temp = String;
    ToCapital(temp);
    printf("After ToCapital = %s\n", String);

    return EXIT_SUCCESS;
}

