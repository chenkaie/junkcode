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
 * jpegapp.c
 *
 * \brief
 * an demo application to take the use of ../libjpeglib-static.a
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

#include "jpeginfo.h"
#include <stdio.h>
#include <stdlib.h>


int main (int argc, char const* argv[])
{

    TJPEGInfo object;

    memset(&object,0,sizeof(TJPEGInfo));

    DBG_PRINT("%d,%d,%d\n", object.uiCmpNum,object.uiHeight,object.uiWidth);
    if (argc != 2)
    {
        fprintf(stderr, "Usage: jpegapp <path>/<filename.jpg>\n");
        exit(EXIT_FAILURE);
    }

    if(GetJPEGCmpNum(argv[1], &object) < 0 )
    {
        printf("Get Jpeg Component Number Error!\n");
        exit(EXIT_FAILURE);
    }

    if(GetJPEGWidthHeight(argv[1], &object) < 0 )
    {
        printf("Get Jpeg Width & Height Error!\n");
        exit(EXIT_FAILURE);
    }
    
    printf("Component Numbers of %s = %d\n", argv[1], object.uiCmpNum);
    printf("Height of %s = %d\n", argv[1], object.uiHeight);
    printf("Width  of %s = %d\n", argv[1], object.uiWidth);
    return EXIT_SUCCESS;
}
