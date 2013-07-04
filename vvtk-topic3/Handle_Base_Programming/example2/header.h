/*
 **********************************************************************
 * $Header: /home/kent/Training/Topic3/JPEG/src/jpeg_info.h
 *
 *  Copyright (c) 2000-2008 Vivotek Inc. All rights reserved.
 *
 * *  +-----------------------------------------------------------------+
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
 * $History: jpeg_info.h
 *
 * *****************  Version 1  *****************
 * User: Kent         Date: 08/03/31   Time: 21:35
 * Created in /home/kent/Training/Topic3/JPEG/src/ 
 * 
 ***********************************************************************
 */

/*!
 *******************************************************************************
 * Copyright 2000-2004 Vivotek, Inc. All rights reserved.
 *
 * \file
 * jpeg_info.h
 *
 * \brief
 * fetch the jpeg info from jpeg header
 *
 * \date
 * 2008/03/31
 *
 * \author
 * Kent Chen
 *
 *
 *******************************************************************************
 */

#ifndef	_HEADER_H_
#define	_HEADER_H_

#ifndef NDEBUG
    #define DBG_PRINT(fmt, ...) printf("%s:%d: " fmt, __FILE__, __LINE__, __VA_ARGS__)
    //Usage: DBG_PRINT("%d: %s: %s\n", conf_num, conf_name[conf_num], conf_value[conf_num]);
#else
    #define DBG_PRINT(fmt, ...) 
#endif


/*! take absolute value of input */
#define ABS(a)          (((a) >= 0) ? (a) : (-a))
/*! return maximum value of two given inputs */
#define MAX(a, b)       (((a) > (b)) ? (a) : (b))
/*! return minimum value of two given inputs */
#define MIN(a, b)       (((a) < (b)) ? (a) : (b))

#define SWAP(T, a, b)   {T _tmp; (_tmp) = (T)(a); (T)(a) = (T)(b); (T)(b) = _tmp;}


// readded for backward compatiable
#if !defined(__wtypes_h__) && !defined(_SCODE_)
    typedef unsigned int SCODE;
#define _SCODE_
#endif


#ifndef S_OK
#define S_OK                           ((SCODE)  0)
#endif
#ifndef S_FAIL
#define S_FAIL                         ((SCODE) -1)
#endif

#if !defined(false) && !defined(__cplusplus)
    /*! define boolean constant - false */
    #define false 0

    /*! define boolean constant - true */
    #define true  (!false)
#endif

/*#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif*/

#ifndef BOOLEAN // b
typedef unsigned int    BOOLEAN;
#endif

#ifndef BOOL    // b
typedef BOOLEAN         BOOL;
#endif

#endif //_HEADER_H_

