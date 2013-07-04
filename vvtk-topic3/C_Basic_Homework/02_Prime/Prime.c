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


#include <stdio.h>
#include <stdlib.h>
#include "../header.h"

int main (int argc, char const* argv[])
{
    unsigned int uiMaxNumber = 0;
    BOOL bIsPrime = true;
    printf("Input an integer\n");
    scanf("%d",&uiMaxNumber);

    const unsigned int MinPrime = 2;
    unsigned int i = 0, j = 0;
    
    printf("The prime numbers smaller than %d are\n", uiMaxNumber);
    
    for(i = MinPrime; i <= uiMaxNumber; i++)
    {
        bIsPrime = true;
        for(j = MinPrime; j*j <= i; j++)
        {
            if(i % j == 0)
            {
                bIsPrime = false;
                break;
            }
        }
        if(bIsPrime)
        {
            printf("%5d",i);
        }
    }
    return EXIT_SUCCESS;
}

