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
 * ref jpeginfo.h
 *
 * \date
 * 2008/04/07
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
#include "jpeginfo.h"

SCODE GetJPEGCmpNum (const char* pcFilename, TJPEGInfo* pTobject)
{
    
    unsigned char* Buffer = NULL;
    if((FileToBinaryStream(pcFilename, &Buffer)) == -1)
    {
        printf("exec FileToBinaryStream failed\n");
        return S_FAIL;
    }

    
    int i = 0;
    while(!(Buffer[i++] == 0xFF && Buffer[i] == 0xC0 ))
    {
    }
    DBG_PRINT("find it at %d\n",i);
    
    pTobject->uiCmpNum = Buffer[i+8];
    free(Buffer);
    Buffer = NULL;
    return S_OK;

}
