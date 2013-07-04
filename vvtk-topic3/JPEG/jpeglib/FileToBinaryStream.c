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

#include "jpeginfo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


SCODE FileToBinaryStream (const char* pcFilename, unsigned char** pcBuffer)
{ 
    FILE* pFile;
    long  lSize;
    size_t result;
 
    pFile = fopen (pcFilename , "rb");
    DBG_PRINT("filename = %s\n", pcFilename);
    if (pFile == NULL) 
    {
        printf("File Error\n");
        exit(EXIT_FAILURE); 
    }
    /*else
    {
        fputs("Open Successfully!\n",stderr);
    }*/
    
    // obtain file size:
    fseek (pFile , 0 , SEEK_END);
    lSize = ftell (pFile);
    rewind (pFile);

    // allocate memory to contain the whole file:
    *pcBuffer = (unsigned char*) malloc (sizeof(unsigned char)*lSize);
    if (*pcBuffer == NULL) 
    {
        fputs ("Memory error",stderr); 
        exit(EXIT_FAILURE);
    }

    // copy the file into the pcBuffer:
    result = fread (*pcBuffer,1,lSize,pFile);
    if (result != lSize) 
    {
        fputs ("Reading error",stderr); 
        exit (EXIT_FAILURE);
    }

    //printf("Buffer[0] = %X  " ,(*pcBuffer)[0]);
    //printf("Buffer[1] = %X  " ,(*pcBuffer)[1]);
    //printf("filename = %s\n", pcFilename);
    

    if (((*pcBuffer)[0] == 0xFF) && ((*pcBuffer)[1] == 0xD8))
    {
        //printf("'%s' is A jpeg format file. \n", pcFilename);
    }
    else
    {
        printf("'%s' is not jpeg format file. \n", pcFilename);
        return S_FAIL;
    }


    // terminate
    fclose (pFile);
    
    //free (pcBuffer); remember to free this memory latter
    
    //DBG_PRINT("%s\n","Reutrn pcBuffer Successfully!");
    
    return S_OK;
}

