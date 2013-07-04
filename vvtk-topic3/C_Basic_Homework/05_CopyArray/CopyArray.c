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

const char* ArrayCopy(char* pDest, const char* pSrc)
{
    assert((pDest != NULL) && (pSrc != NULL));
    const char *address = pSrc;
    while((*pDest++ = *pSrc++) != '\0')
    {
    }
    return address;
}

int main (int argc, char const* argv[])
{
    static const char cArray1[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    unsigned int uiLength = 0;
    const char *tempA1 = cArray1;

    /*******  Note that very important, '\0' != "\0" ***********/
#if 0
    char x='\0';
    char y="\0";
    if(x != y)
        printf("Mother fucker, %c != %c\n",x,y);
#endif
    /***********************************************************/


    while(*tempA1++ != '\0')
    {
        uiLength++;
    }

    printf("Array1 length = %d\n", uiLength);
    printf("Array1 = %s\n", cArray1);

    char *cArray2 = (char*) malloc(sizeof(char) * (uiLength+1));
    if (cArray2 == NULL) 
    {
        printf("Malloc Error\n");
        exit(EXIT_FAILURE);
    }


    int i = 0;
    for(i = 0; i < uiLength; i++)
    {
        cArray2[i] = cArray1[i];
    }
    printf("Array2 = %s\n", cArray2);
    free(cArray2);
    cArray2 = NULL;

    char *cArray3 = (char*) malloc(sizeof(char) * (uiLength+1));

    memset(cArray3, '\0', sizeof(char)*(uiLength+1));
    DBG_PRINT("initial Array3 = %s\n", cArray3);

    if (cArray3 == NULL) 
    {
        printf("Malloc Error\n");
        exit(EXIT_FAILURE);
    }
    
    ArrayCopy(cArray3, cArray1);
    DBG_PRINT("strlen of cArray3 = %d\n",strlen(ArrayCopy(cArray3, cArray1)));

    printf("Array3 = %s\n", cArray3);
    free(cArray3);
    cArray3 = NULL;
    
    return EXIT_SUCCESS;
}

