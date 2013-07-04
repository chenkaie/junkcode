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

/*! take absolute value of input */

#include <stdio.h>
#include <stdlib.h>
#include "../header.h"

double PowerFunc(const double dBaseNum, const int iExponentNum)
{
    
    static double dSum = 0;
    dSum = dBaseNum;

    int i = 0;
    for(i = 0; i< (ABS(iExponentNum)-1) ; i++)
    {
        dSum = dSum * dBaseNum;
    }
    
    return (iExponentNum >= 0)?dSum:(1/dSum);

}


int main (int argc, char const* argv[])
{
    double dBaseNum = 0;
    int    iExponentNum = 0;
    printf("Please input Base Number = ");
    scanf("%lf",&dBaseNum);
    printf("Please input Exponent Number = ");
    scanf("%d",&iExponentNum);

    printf("The Result of PowerFunc(%f,%d) = %f\n", dBaseNum, iExponentNum, PowerFunc(dBaseNum,iExponentNum) );
    return EXIT_SUCCESS;
}

