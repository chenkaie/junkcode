/*
 *******************************************************************************
 * $Header: /RD_1/Project/PNX1300_PSOS/Farseer/COMMON/src/typedef.h 1     05/07/25 4:13p Kate $
 *
 *  Copyright (c) 2000-2002 Vivotek Inc. All rights reserved.
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
 * $History: typedef.h $
 * 
 * *****************  Version 1  *****************
 * User: Kate         Date: 05/07/25   Time: 4:13p
 * Created in $/RD_1/Project/PNX1300_PSOS/Farseer/COMMON/src
 * First checkin in new mars
 * 
 * *****************  Version 3  *****************
 * User: Joe          Date: 03/07/15   Time: 4:42p
 * Updated in $/rd_1/Project/TM1300_PSOS/FarSeer/common/src
 * Update SCODE definition.
 *
 * *****************  Version 2  *****************
 * User: Yun          Date: 03/07/14   Time: 11:35a
 * Updated in $/rd_1/Project/TM1300_PSOS/FarSeer/common/src
 * Add SOCKET type definition
 *
 * *****************  Version 1  *****************
 * User: Joe          Date: 03/03/10   Time: 10:54a
 * Created in $/rd_1/Project/TM1300_PSOS/FarSeer/COMMON/src
 * common used source. Including debug macros, type definitions, error
 * code definitions.
 *
 * *****************  Version 1  *****************
 * User: Joe          Date: 03/01/13   Time: 3:56p
 * Created in $/rd_common/common_header
 * first add typedef.h to common_header folder
 *
 * *****************  Version 3  *****************
 * User: Joe          Date: 02/12/25   Time: 4:29p
 * Updated in $/rd_1/System/FIRMWARE/common/src
 * Update some naming rules
 *
 * *****************  Version 2  *****************
 * User: Joe          Date: 02/12/19   Time: 2:09p
 * Updated in $/rd_1/System/FIRMWARE/common/src
 * change SCODE definition
 *
 * *****************  Version 1  *****************
 * User: Joe          Date: 02/11/06   Time: 2:54p
 * Created in $/rd_1/System/FIRMWARE/common/src
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * Copyright 2000-2002 Vivotek, Inc. All rights reserved.
 *
 * \file
 * typedef.h
 *
 * \brief
 * Define some useful types, this file should include after OS related include
 * files, such as windows.h, psos.h. currently support windows & psos only
 *
 * \date
 * 2002/07/03
 *
 * \author
 * Joe Wu
 *
 *
 *******************************************************************************
 */

#ifndef _TYPEDEF_H_
#define _TYPEDEF_H_

#if defined(WIN32) || defined(_WIN32) || defined(_WIN32WCE)
#if !defined (_WINDOWS_)
#ifndef __AFXWIN_H__
#include <windows.h>
#endif // __AFXWIN_H__
#endif // !_WINDOWS_
#endif // WIN32 || _WIN32 || _WIN32WCE

// to avoid confliction if including "windows.h"
#if !defined (_WINDOWS_) && !defined (__WINDOWS__) // __WINDOWS__ for WINCE
// modify by allatin 2004/12/16 --------------------------------------------
// the following types are already define in windows.h

#ifndef __TYPES_H__		// for psos
// the following types are already define in psos.h

#ifndef UCHAR	// uc
typedef unsigned char   UCHAR;
#endif

#ifndef ULONG	// ul
typedef unsigned long   ULONG;
#endif

#ifndef USHORT	// us
typedef unsigned short  USHORT;
#endif

#ifndef UINT	// ui
typedef unsigned int    UINT;
#endif

#endif	// end of __TYPES_H__	// for psos

//  1 byte
#ifndef CHAR	// c
typedef char            CHAR;
#endif

//  1 byte
#ifndef TCHAR	// c
typedef char           TCHAR;
#endif

#ifndef PCHAR	// pc
typedef char            *PCHAR;
#endif

#ifndef PUCHAR	// puc
typedef unsigned char   *PUCHAR;
#endif

#ifndef BYTE	// by
typedef unsigned char   BYTE;
#endif

#ifndef PBYTE	// pby
typedef BYTE*           PBYTE;
#endif

//  2 bytes
#ifndef short	// s
typedef short           SHORT;
#endif

#ifndef PSHORT	// ps
typedef short           *PSHORT;
#endif

#ifndef PUSHORT	// pus
typedef unsigned short  *PUSHORT;
#endif

#ifndef WORD	// w
typedef unsigned short  WORD;
#endif

#ifndef PWORD	// pw
typedef WORD*           PWORD;
#endif

//  4 bytes
#ifndef DWORD	// dw
typedef unsigned int   DWORD;
#endif

#ifndef PDWORD	// pdw
typedef DWORD*          PDWORD;
#endif

#ifndef PUINT	// pui
typedef UINT*           PUINT;
#endif

#ifndef LONG	// l
typedef long            LONG;
#endif

#ifndef PLONG	// pl
typedef long            *PLONG;
#endif

#ifndef PULONG	// plu
typedef unsigned long   *PULONG;
#endif


#ifndef BOOLEAN	// b
typedef unsigned int    BOOLEAN;
#endif

#ifndef BOOL	// b
typedef BOOLEAN         BOOL;
#endif

// bool is keyword in C++
#if !defined(bool) && !defined(__cplusplus)
typedef BOOLEAN         bool;
#endif

#ifndef PVOID	// pv
typedef void *          PVOID;
#endif

#ifndef HANDLE	// h
typedef void *          HANDLE;
#endif

#ifndef SOCKET	//sck
typedef int             SOCKET;
#endif

// readded for backward compatiable
#if !defined(__wtypes_h__) && !defined(_SCODE_)
typedef unsigned int SCODE;
#define	_SCODE_
#endif // !__wtypes_h__ && !_SCODE_

// --------- for floating point -------------
#define _DOUBLE_PRECISION

#ifndef FLOAT	// fl
#ifdef _DOUBLE_PRECISION
	typedef double FLOAT;
#else
	typedef float  FLOAT;
#endif // _DOUBLE_PRECISION

#endif // !FLOAT

// 2004/06/09 added by perkins
#ifndef LPCSTR
#define	LPCSTR		const char *
#endif // LPCSTR

#ifndef LPSTR
#define	LPSTR		char *
#endif // LPSTR

#ifndef LPCTSTR
#define	LPCTSTR		const char *
#endif // LPCTSTR

#ifndef LPTSTR
#define	LPTSTR		char *
#endif // LPTSTR

#ifndef LPWSTR
#define	LPWSTR		char *
#endif // LPWSTR

#ifndef LPCWSTR
#define	LPCWSTR		const char *
#endif // LPCWSTR

#if !defined(_WIN32) && !defined(_WIN32_WCE)
#ifndef __stdcall
#define	__stdcall
#endif // __stdcall
#ifndef __cdecl
#define	__cdecl
#endif // __cdecl
#endif // !_WIN32 || !_WIN32_WCE

// perkins 2006/7/13 to help to convert between pointer and long, int
#define HandleToULong( h ) ((unsigned long)(h) )
#define HandleToLong( h )  ((long)(h) )
#define ULongToHandle( ul ) ((HANDLE (ul) )
#define LongToHandle( h )   ((HANDLE)(h) )
#define PtrToUlong( p ) ((unsigned long)(p) )
#define PtrToLong( p )  ((long) (p) )
#define PtrToUint( p ) ((unsigned int) (long)(p) )
#define PtrToInt( p )  ((int) (long)(p) )
#define PtrToUshort( p ) ((unsigned short)(unsigned long)(p) )
#define PtrToShort( p )  ((short)(long)(p) )
#define IntToPtr( i )    ((void *)(long)((int)i))
#define UIntToPtr( ui )  ((void *)(unsigned long)((unsigned int)ui))
#define LongToPtr( l )   ((void *)((long)l))
#define ULongToPtr( ul ) ((void *)((unsigned long)ul))


#endif // !_WINDOWS_ && !__WINDOWS__

#if _MSC_VER >= 1400 && !defined(__wtypes_h__) && !defined(_SCODE_)
	typedef unsigned int SCODE;
#define	_SCODE_
#endif // _MSC_VER >= 1400 && !__wtypes_h__ && !_SCODE_

// non-window conflict types
#ifndef SWORD	// sw
typedef signed short    SWORD;
#endif

#ifndef SDWORD	// sdw
typedef signed int     SDWORD;
#endif

#ifndef TASK
typedef void            TASK;
#endif

// for 64 bit data types
#if defined(_WIN32)
	typedef unsigned __int64 	QWORD;	// qw
	typedef __int64				SQWORD;	// sqw
#elif defined(_EQUATOR_X_)
	typedef unsigned long long	QWORD;	// qw
    typedef long long           SQWORD;	// sqw
#elif defined(_LINUX)
	typedef unsigned long long	QWORD;	// qw
    typedef long long           SQWORD;	// sqw
#elif defined(_TMS320C6X)
	typedef unsigned long long	QWORD;	// qw
	typedef long long	SQWORD;	// sqw
#endif

#include <float.h>
// --------- for floating point -------------
#ifndef VFLOAT	// fl
#ifdef _SINGLE_PRECISION
	typedef float  VFLOAT;
#else
	typedef double VFLOAT;
#endif // _DOUBLE_PRECISION

#endif // !VFLOAT

// --------- for fix point -------------
typedef signed short     FIX16;
typedef unsigned short   UFIX16;
typedef signed long      FIX;
typedef unsigned long    UFIX;

#if defined(_FIXED_POINT)

#define SFIXED		SDWORD
#define UFIXED		DWORD
#define SFIXED64	SQWORD
#define UFIXED64	QWORD
#define UFIXMAX		0xFFFFFFFFUL
#define SFIXMAX		0x7FFFFFFFL
#define UFIX64MAX	0xFFFFFFFFFFFFFFFFULL
#define SFIX64MAX	0x7FFFFFFFFFFFFFFFLL

#elif defined(_SINGLE_PRECISION)

#define SFIXED		float
#define UFIXED		float
#define SFIXED64	float
#define UFIXED64	float
#define UFIXMAX		FLT_MAX
#define SFIXMAX		FLT_MAX
#define UFIX64MAX	FLT_MAX
#define SFIX64MAX	FLT_MAX

#else
#define SFIXED		double
#define UFIXED		double
#define SFIXED64	double
#define UFIXED64	double
#define UFIXMAX		DBL_MAX
#define SFIXMAX		DBL_MAX
#define UFIX64MAX	DBL_MAX
#define SFIX64MAX	DBL_MAX

#endif 


#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL 0
#endif

#define ON  1
#define OFF 0

#ifndef S_OK
#define S_OK 0
#endif

#ifndef S_FAIL
#define S_FAIL (SCODE)(-1)
#endif

#ifndef S_INVALID_VERSION
#define S_INVALID_VERSION (SCODE)(-2)
#endif

#endif // _TYPEDEF_H_
