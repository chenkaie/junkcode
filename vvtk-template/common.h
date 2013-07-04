/*
 *******************************************************************************
 * $Header: /RD_1/Project/VVTK1000/Warden/apps/webcam/COMMON/src/common.h 1     05/02/03 17:20 Cchuang $
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
 * $History: common.h $
 * 
 * *****************  Version 1  *****************
 * User: Cchuang      Date: 05/02/03   Time: 17:20
 * Created in $/RD_1/Project/VVTK1000/Warden/apps/webcam/COMMON/src
 * Warden Project
 * 
 * *****************  Version 14  *****************
 * User: Yun          Date: 04/03/10   Time: 10:57a
 * Updated in $/rd_1/Project/TM1300_PSOS/FarSeer/common/src
 * Merge with SOC project
 * 
 * *****************  Version 13  *****************
 * User: Joe          Date: 03/12/30   Time: 5:51p
 * Updated in $/rd_1/Project/TM1300_PSOS/FarSeer/common/src
 * Add assert message to telnet console
 * 
 * *****************  Version 12  *****************
 * User: Joe          Date: 03/12/17   Time: 1:27p
 * Updated in $/rd_1/Project/TM1300_PSOS/FarSeer/common/src
 * #define snprintf & vsnprintf for VC++
 * 
 * *****************  Version 11  *****************
 * User: Joe          Date: 03/09/25   Time: 3:00p
 * Updated in $/rd_1/Project/TM1300_PSOS/FarSeer/common/src
 * Support telnet debug
 * 
 * *****************  Version 10  *****************
 * User: Joe          Date: 03/09/09   Time: 3:13p
 * Updated in $/rd_1/Project/TM1300_PSOS/FarSeer/common/src
 * support some new prototol type in common.h
 * 
 * *****************  Version 9  *****************
 * User: Joe          Date: 03/07/30   Time: 5:42p
 * Updated in $/rd_1/Project/TM1300_PSOS/FarSeer/common/src
 * Modify DLAPI declarations
 *
 * *****************  Version 8  *****************
 * User: Joe          Date: 03/07/29   Time: 8:52a
 * Updated in $/rd_1/Project/TM1300_PSOS/FarSeer/common/src
 * 1. Add DLLAPI definition.
 *
 * *****************  Version 7  *****************
 * User: Joe          Date: 03/07/21   Time: 4:14p
 * Updated in $/rd_1/Project/TM1300_PSOS/FarSeer/common/src
 * Change S_OK, S_FAIL definition
 *
 * *****************  Version 6  *****************
 * User: Joe          Date: 03/06/03   Time: 3:41p
 * Updated in $/rd_1/Project/TM1300_PSOS/FarSeer/common/src
 * fix memicmp() function
 *
 * *****************  Version 4  *****************
 * User: Joe          Date: 03/06/03   Time: 10:09a
 * Updated in $/rd_1/Project/TM1300_PSOS/FarSeer/common/src
 * add stricmp() function.
 *
 * *****************  Version 3  *****************
 * User: Joe          Date: 03/05/30   Time: 10:45a
 * Updated in $/rd_1/Project/TM1300_PSOS/FarSeer/common/src
 * Enable the debug level can be adjust at run time.
 *
 * *****************  Version 2  *****************
 * User: Joe          Date: 03/03/10   Time: 11:32a
 * Updated in $/rd_1/Project/TM1300_PSOS/FarSeer/common/src
 * 1. Add some debug level definitions
 * 2. Add a DbgLog_SetLevel() function to enable
 *     changing debug level at run time.
 *
 * *****************  Version 1  *****************
 * User: Joe          Date: 03/03/10   Time: 10:54a
 * Created in $/rd_1/Project/TM1300_PSOS/FarSeer/COMMON/src
 * common used source. Including debug macros, type definitions, error
 * code definitions.
 *
 * *****************  Version 4  *****************
 * User: Albus        Date: 03/03/05   Time: 12:13p
 * Updated in $/rd_1/System/FIRMWARE/common/src
 * 1. debug level definition changed.
 * 2. using macro instead of function for DbgLog.
 *
 * *****************  Version 3  *****************
 * User: Joe          Date: 02/11/12   Time: 9:08a
 * Updated in $/rd_1/System/FIRMWARE/common/src
 * 1. Change DbgInit() will be compiled always
 * 2. Change __inline to inline in Trimedia
 * 3. reverse the link libraries order
 *
 * *****************  Version 2  *****************
 * User: Joe          Date: 02/11/06   Time: 4:08p
 * Updated in $/rd_1/System/FIRMWARE/common/src
 * Add OSThread_Yield function call
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
 * common.h
 *
 * \brief
 * Useful macros, also include debug macros.
 * To use debug macros, you should define two definitions.
 *
 * 1. \b DBGLEVEL. Each bit of DBGLEVEL represents a level of debug. You can
 *    define the meaning of each bit.
 *
 * 2. \b DBGFILE.  If you want the DbgLog send message to file not console, you
 *    should set this define as the debug output file name.
 *
 * \date
 * 2002/07/04
 *
 * \author
 * Joe Wu
 *
 *******************************************************************************
 */

#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdarg.h>
#include "typedef.h"

//! debug level enumerators
typedef enum {
	//! send debug message via Telnet
	dfTELNET  		= 0x80000000,
	//! send debug message via DP buffer
	dfDP 			= 0x40000000,
	//! send debug message via com port
	dfCOMPORT 		= 0x20000000,
	//! send debug message via console
	dfCONSOLE 		= 0x10000000,
	//! critical error debug message
	dfCRITICAL 		= 0x00800000,
	//! internal testing debug message
	//! will not be shown in release mode
	dfINTERNAL		= 0x00000001,
	//! application level message,
	//! can be shown in release mode
	dfAPPLICATION	= 0x00000002,
} TDebugFlags;

#ifdef _PSOS_TRIMEDIA
#define __inline inline
//! compare the string case insensitive
int stricmp(const char *s1, const char *s2);
//! Compares n bytes of two character arrays, ignoring case.
int memicmp(const void *s1, const void *s2, size_t n);
//! Format a string and place it in a buffer with upper limit
int vsnprintf(char *buf, size_t size, const char *fmt, va_list args);
//! Format a string and place it in a buffer with upper limit
int snprintf(char * buf, size_t size, const char *fmt, ...);

//! read mac address from eerom
BOOLEAN ReadMacAddress(UCHAR *_Ptr);
//! write mac adress to eerom
void    WriteMacAddress(UCHAR *_Ptr);

#if defined(NDEBUG) && defined(_TELNETASSERT)
// redefine our assert macro
#undef 	assert(p)
#define assert(p)   ((p) ? (void)0 : __Telnet_AssertFail( \
        			"Assertion failed: %s, file %s, line %d\n", \
				#p, __FILE__, __LINE__ ) )

void	__Telnet_AssertFail(char *__msg, ...);
#endif

#endif

/* add by CCH 2004/02/10 */
#ifdef _LINUX
//! compare the string case insensitive
int stricmp(const char *s1, const char *s2);
//! Compares n bytes of two character arrays, ignoring case.
int memicmp(const void *s1, const void *s2, size_t n);
#endif

#ifdef _MSC_VER	// add by Joe 2003/12/15 for Visual C++
#define snprintf	_snprintf
#define	vsnprintf	_vsnprintf
#endif

/*! Use for generate dynamic link library for Windows */
#ifndef DLLAPI
#ifdef _WIN32
  #ifdef _USRDLL
    #define DLLAPI __declspec(dllexport) __stdcall
  #else
    #define DLLAPI __stdcall
  #endif //defined(_USRDLL)
#else
  #define DLLAPI
#endif //defined(_WIN32)
#endif //defined(DLLAPI)

/*! external variable used as the debug file pointer */
extern FILE *_db_fptr;
/*! external variable used to judge the printing of debug message. */
extern DWORD dwDbgLevel;

typedef int (* FTelnetDbgPrint)(const char *pszFormat, va_list args);

/*! external dbg print function pointer */
extern FTelnetDbgPrint	g_pfnTelnetDbgPrint;

/*! change debug level online */
void DbgLog_SetLevel(DWORD dwLevel);

/*! Initialize DbgLog Function */
void DbgLogInit(DWORD dwLevel, char *pszDbgFile);

/*! Telnet shell debug function */
#ifndef _DISABLE_TELNETSERVER
int   TelnetShell_DbgPrint(const char *pszFormat, ...);
#else
#define TelnetShell_DbgPrint	printf
#endif

#ifndef DBGFILE
/*! Define XDBGFILES() as NULL pointer if not defined */
#define DBGFILES(X)	    NULL
#else
/*! Define DBGFILES(X) as "X", ex: DBGFILES(123)	=> "123"  */
#define DBGFILES(X) 	#X
/*! Define XDBGFILES(X) can use X as another define
 example:
 #define DBGFILE	123
 DBGFILES(DBGFILE)	=> "DBGFILE"
 XDBGFILE(DBGFILE)	=> "123"
 */
#endif

#define XDBGFILE(X) 	DBGFILES(X)

#if defined(DBGLEVEL) && (DBGLEVEL > 0)

void DbgLogFunction(DWORD dwFlags, const char *pFormat, ...);

/*!
 *******************************************************************************
 * \brief
 * Show debug message with given level
 *
 * \param dwFlags
 * \a (i) Flags of debug message, which can be the OR combination of debug flags
 * to select the debug output destination.
 *
 * \param pFormat
 * \a (i) Format of debug messages. The format is the same as \b printf
 * function.
 *
 * \remark
 * You should define DBGLEVEL, and the function will be active.
 * You can also define DBGFILE to send debug message to file, otherwise, it will
 * send to standard output.
 *
 **************************************************************************** */
#define DbgLog(_x_) {DbgLogInit(DBGLEVEL, XDBGFILE(DBGFILE)); DbgLogFunction _x_; }

#else

/*! In release mode, DbgLog is defined as nothing */
#define DbgLog(_x_)

#endif

#if !defined(false) && !defined(__cplusplus)

/*! define boolean constant - false */
#define false 0

/*! define boolean constant - true */
#define true  (!false)
#endif

/*! define function return value - OK */
#ifndef S_OK
#define S_OK	(SCODE)(0)
#endif

/*! define function return value - FAIL */
#ifndef S_FAIL
#define S_FAIL	(SCODE)(1)
#endif

/*! take absolute value of input */
#define ABS(a)			(((a) >= 0) ? (a) : (-a))

/*! return maximum value of two given inputs */
#define MAX(a, b) 		(((a) > (b)) ? (a) : (b))

/*! return minimum value of two given inputs */
#define MIN(a, b) 		(((a) < (b)) ? (a) : (b))

/*! swap two values of the same type T */
#define SWAP(T, a, b)   {T _tmp; (_tmp) = (T)(a); (T)(a) = (T)(b); (T)(b) = _tmp;}

/*! Make from four character codes to one 32-bits DWORD */
#ifndef MAKEFOURCC
    #define MAKEFOURCC(ch0, ch1, ch2, ch3)                          \
                ((DWORD)(BYTE)(ch0) | ((DWORD)(BYTE)(ch1) << 8) |   \
                ((DWORD)(BYTE)(ch2) << 16) | ((DWORD)(BYTE)(ch3) << 24 ))
#endif //defined(MAKEFOURCC)

/*! Macros for version retrival */
#define GET_MAJOR_VER(VER)	((VER) & 0xFF)
#define GET_MINOR_VER(VER)	(((VER) >> 8) & 0xFF)
#define GET_BUILD_VER(VER)	(((VER) >> 16) & 0xFF)
#define GET_REVISE_VER(VER)	(((VER) >> 24) & 0xFF)

/*! 32-bits memory copy macro, nSize must be multiple of 4 */
#define MEMCPY32(pdwDest, pdwSrc, nSize)\
{\
	int i;\
	for(i = 0; i < ((nSize) >> 2); i++)\
		*((long *)pdwDest + i) = *((long *)pdwSrc + i);\
}

/*! 32-bits zero memory macro, nSize must be multiple of 4 */
#define MEMZERO32(pdwDest, nSize)\
{\
	int i;\
	for(i = 0; i < ((nSize) >> 2); i++)\
		*((long *)pdwDest + i) = 0;\
}


#endif
