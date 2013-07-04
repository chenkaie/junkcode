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

//#define NDEBUG


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../header.h"

#define ARRAY_ROW_SIZE 3
#define ARRAY_COLUMN_SIZE 5

SCODE Set2DArrayData(double pd2DArray[][ARRAY_COLUMN_SIZE])
{
    assert(pd2DArray != NULL);
    double *pd2DArrayR0 = pd2DArray[0];
    double *pd2DArrayR1 = pd2DArray[1];
    double *pd2DArrayR2 = pd2DArray[2];
    
    printf("Please input %d sets of %d double type numbers, seperated by a space character :\nSet 1:",ARRAY_ROW_SIZE,ARRAY_COLUMN_SIZE);
    //scanf("%lf %lf %lf %lf %lf",&d2DArray[0][0],&d2DArray[0][1],&d2DArray[0][2],&d2DArray[0][3],&d2DArray[0][4]);
    if(scanf("%lf %lf %lf %lf %lf",pd2DArrayR0,pd2DArrayR0+1,pd2DArrayR0+2,pd2DArrayR0+3,pd2DArrayR0+4) != ARRAY_COLUMN_SIZE)
    {
        return S_FAIL;
    }

   
    printf("Set 2:");
    //scanf("%lf %lf %lf %lf %lf",pd2DArrayR0,pd2DArrayR0+1,pd2DArrayR0+2,pd2DArrayR0+3,pd2DArrayR0+4);
    if(scanf("%lf %lf %lf %lf %lf",&pd2DArray[1][0],&pd2DArray[1][1],&pd2DArray[1][2],&pd2DArray[1][3],&pd2DArray[1][4]) != ARRAY_COLUMN_SIZE)
    {
        return S_FAIL;
    }
   
    printf("Set 3:");
    if(scanf("%lf %lf %lf %lf %lf",pd2DArrayR2,pd2DArrayR2+1,pd2DArrayR2+2,pd2DArrayR2+3,pd2DArrayR2+4) != ARRAY_COLUMN_SIZE)
    {
        return S_FAIL;
    }

    return S_OK;
}

SCODE GetAvgValuePerSet(const double (*pdArray)[ARRAY_COLUMN_SIZE], double *pdAvgValueArray)
{
    assert(pdArray != NULL && pdAvgValueArray != NULL);
    int i = 0, j = 0;
    double iSum = 0;
    for(i = 0; i < ARRAY_ROW_SIZE; i++)
    {
        iSum = 0;
        for(j = 0; j < ARRAY_COLUMN_SIZE; j++)
        {
            iSum += pdArray[i][j];
        }
        pdAvgValueArray[i] = iSum/ARRAY_COLUMN_SIZE;
    }
    return S_OK;
}

SCODE GetAvgValOfTatoalSet(const double (*pdArray)[ARRAY_COLUMN_SIZE], double *pdAvgValue)
{
    assert(pdArray != NULL && pdAvgValue != NULL);
    int i = 0, j = 0;
    double iSum = 0;
    for(i = 0; i < ARRAY_ROW_SIZE; i++)
    {
        for(j = 0; j < ARRAY_COLUMN_SIZE; j++)
        {
            iSum += pdArray[i][j];
        }
    }
    *pdAvgValue = iSum/(ARRAY_ROW_SIZE*ARRAY_COLUMN_SIZE);
    return S_OK;
}

SCODE GetMaxNumOfTatalSet(const double (*pdArray)[ARRAY_COLUMN_SIZE], double *pdMaxNum)
{
    assert(pdArray != NULL && pdMaxNum != NULL);
    int i = 0, j = 0;
    *pdMaxNum = pdArray[0][0];
    for(i = 0; i < ARRAY_ROW_SIZE; i++)
    {
        for(j = 0; j < ARRAY_COLUMN_SIZE; j++)
        {
            *pdMaxNum = (*pdMaxNum < pdArray[i][j])?pdArray[i][j]:*pdMaxNum;
        }
    }
    return S_OK;
}


int main (int argc, char const* argv[])
{
    double d2DArray [ARRAY_ROW_SIZE][ARRAY_COLUMN_SIZE];
    memset(d2DArray,0,sizeof(d2DArray));
    double (*pTemp)[ARRAY_COLUMN_SIZE] = d2DArray;

    DBG_PRINT("Sizeof(pTemp) = %d\n",sizeof(pTemp));
    DBG_PRINT("Sizeof(d2DArray) = %d\n",sizeof(d2DArray));

    int i = 0, j = 0;
    for(i = 0; i < ARRAY_ROW_SIZE; i++)
    {
        for(j = 0; j < ARRAY_COLUMN_SIZE; j++)
        {
            DBG_PRINT("Address of d2DArray[%d][%d]=0x%X\n",i,j,&d2DArray[i][j]);
        }
    }

    if(Set2DArrayData(pTemp) == S_FAIL)
    {
        printf("Get2DArrayData Failed\n");
        exit(EXIT_FAILURE);
    }

    for(i = 0; i < ARRAY_ROW_SIZE; i++)
    {
        for(j = 0; j < ARRAY_COLUMN_SIZE; j++)
        {
            printf("d2DArray[%d][%d]=%f\n",i,j,d2DArray[i][j]);
        }
    }
#if 0
    for(i = 0; i <= 2; i++)
    {
        for(j = 0; j <= 4; j++)
        {
            DBG_PRINT("Address of d2DArray[%d][%d]=0x%X\n",i,j,&d2DArray[i][j]);
        }
    }
#endif
    
    pTemp = d2DArray;
#if 0    
    for(i = 0; i <= 2; i++)
    {
        for(j = 0; j <= 4; j++)
        {
            DBG_PRINT("value of pTemp[%d][%d]=%f\n",i,j,*pTemp++);
        }
    }
#endif
    
    double dAvgValArray[ARRAY_ROW_SIZE];
    memset(dAvgValArray,0,sizeof(dAvgValArray));
    
    GetAvgValuePerSet(pTemp,dAvgValArray);
    for(i = 0; i < ARRAY_ROW_SIZE; i++)
    {
        printf("Avg value of Row[%d] of d2DArray = %f \n",i,dAvgValArray[i]);
    }

    double dAvgVal = 0;
    GetAvgValOfTatoalSet(pTemp,&dAvgVal);
    printf("Avg value of Total elements = %f\n", dAvgVal);

    double dMaxNum = 0;
    GetMaxNumOfTatalSet(pTemp,&dMaxNum);
    printf("The Maximum Number of Total elements = %f\n", dMaxNum);

    return EXIT_SUCCESS;
}
