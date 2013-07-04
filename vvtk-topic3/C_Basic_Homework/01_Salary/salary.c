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

#define SALARY_PER_HOUR 10
#define PAY_RATIO_OF_OVERWORK 1.5
#define OVERTIME 40 
#define TAX_LEVEL1 300
#define TAX_LEVEL2 450
#define TAX_RATE_LEVEL1 0.15
#define TAX_RATE_LEVEL2 0.20
#define TAX_RATE_LEVEL3 0.50

#include "../header.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char const* argv[])
{
    unsigned int SalaryPerWeek = 0;
    float Tax = 0, NetAmount = 0;

    unsigned int uiWorkHours = 0;
    printf("Please input your working hours per week => ");
    scanf("%d",&uiWorkHours);
    //printf("your working hours is %d\n", uiWorkHours);
    
    if ( uiWorkHours <= OVERTIME )
    {
        SalaryPerWeek = SALARY_PER_HOUR * uiWorkHours;
    }
    else
    {
        SalaryPerWeek = SALARY_PER_HOUR * OVERTIME + SALARY_PER_HOUR * PAY_RATIO_OF_OVERWORK * (uiWorkHours - OVERTIME);
    }

    if(SalaryPerWeek <= TAX_LEVEL1) 
    {
        Tax = SalaryPerWeek * TAX_RATE_LEVEL1;
        NetAmount = SalaryPerWeek - Tax;
    }
    else if(SalaryPerWeek <= TAX_LEVEL2)
    {
        Tax = SalaryPerWeek * TAX_RATE_LEVEL1 + (SalaryPerWeek - TAX_LEVEL1) * TAX_RATE_LEVEL2;
        NetAmount = SalaryPerWeek - Tax;
    }
    else 
    {
        Tax = TAX_LEVEL1 * TAX_RATE_LEVEL1 + 
              (TAX_LEVEL2 - TAX_LEVEL1) * TAX_RATE_LEVEL2 +
              (SalaryPerWeek - TAX_LEVEL2) * TAX_RATE_LEVEL3;
        NetAmount = SalaryPerWeek - Tax;
    }

    printf("Your working hours per week is %d, so that\n", uiWorkHours);
    printf("SalaryPerWeek = %d\n", SalaryPerWeek);
    printf("Tax = %f\n", Tax);
    printf("NetAmount = %f\n", NetAmount);
    return EXIT_SUCCESS;

}

