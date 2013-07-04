/*
 *******************************************************************************
 * $Header: /rd_common/osisolate/src/osisolate.h 4     05/10/25 3:22p Joe $
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
 * $History: osisolate.h $
 * 
 * *****************  Version 4  *****************
 * User: Joe          Date: 05/10/25   Time: 3:22p
 * Updated in $/rd_common/osisolate/src
 * 
 * *****************  Version 3  *****************
 * User: Joe          Date: 05/10/25   Time: 3:13p
 * Updated in $/rd_common/osisolate/src
 * Merge fix of PNX1500 and Linux
 * 
 * *****************  Version 2  *****************
 * User: Joe          Date: 05/10/25   Time: 8:45a
 * Updated in $/rd_common/osisolate/src
 * Update with most recent version from farseer
 * 
 * *****************  Version 2  *****************
 * User: Joe          Date: 05/10/24   Time: 3:56p
 * Updated in $/RD_1/Project/PNX1300_PSOS/Farseer/osisolate/src
 * Change OS_Main macro with argc and argv in Windows and Linux version
 * 
 * *****************  Version 1  *****************
 * User: Kate         Date: 05/07/26   Time: 9:10a
 * Created in $/RD_1/Project/PNX1300_PSOS/Farseer/OSISOLATE/src
 * First checkin in new mars
 * 
 * *****************  Version 7  *****************
 * User: Weicheng     Date: 05/05/19   Time: 3:07p
 * Updated in $/RD_1/Project/PNX1300_PSOS/Waternoose/osisolate/src
 * 
 * *****************  Version 6  *****************
 * User: Joe          Date: 05/02/02   Time: 1:23p
 * Updated in $/RD_1/Project/PNX1500_PSOS/Syberia/osisolate/src
 * Add tmMain support
 * 
 * *****************  Version 5  *****************
 * User: Joe          Date: 04/08/13   Time: 8:57a
 * Updated in $/RD_1/Project/PNX1300_PSOS/Farseer/osisolate/src
 * Update OSSleep_MSec more accuracy
 * 
 * *****************  Version 4  *****************
 * User: Joe          Date: 04/07/30   Time: 1:27p
 * Updated in $/RD_1/Project/PNX1300_PSOS/Farseer/osisolate/src
 * Update to fit PNX1500
 * 
 * *****************  Version 3  *****************
 * User: Joe          Date: 04/07/29   Time: 4:58p
 * Updated in $/RD_1/Project/PNX1300_PSOS/Farseer/osisolate/src
 * modify the include to support TCS4.41
 * 
 * *****************  Version 2  *****************
 * User: Joe          Date: 04/06/23   Time: 9:14a
 * Updated in $/RD_1/Project/PNX1300_PSOS/Farseer/osisolate/src
 * Add OSMsgQueue_GetElementCount() function for Windows and Linux
 * 
 * *****************  Version 12  *****************
 * User: Yun          Date: 04/03/10   Time: 11:14a
 * Updated in $/rd_1/Project/TM1300_PSOS/FarSeer/osisolate/src
 * Merge with SOC project
 * 
 * *****************  Version 11  *****************
 * User: Joe          Date: 04/01/26   Time: 9:54a
 * Updated in $/rd_1/Project/TM1300_PSOS/FarSeer/osisolate/src
 * Add #include <assert.h>
 * 
 * *****************  Version 10  *****************
 * User: Jason        Date: 03/10/02   Time: 3:29p
 * Updated in $/rd_1/Project/TM1300_PSOS/FarSeer/osisolate/src
 * Fix semaphore get bug on Linux (assert fail when count = 0)
 * 
 * *****************  Version 9  *****************
 * User: Yun          Date: 03/09/24   Time: 4:35p
 * Updated in $/rd_1/Project/TM1300_PSOS/FarSeer/osisolate/src
 * Remove OSConstQueue_GetEmptyQueueCount and
 * OSConstQueue_GetFullQueueCount
 * 
 * *****************  Version 8  *****************
 * User: Joe          Date: 03/09/22   Time: 4:52p
 * Updated in $/rd_1/Project/TM1300_PSOS/FarSeer/osisolate/src
 * Add #include "common.h" in linux
 * 
 * *****************  Version 7  *****************
 * User: Joe          Date: 03/09/17   Time: 4:00p
 * Updated in $/rd_1/Project/TM1300_PSOS/FarSeer/osisolate/src
 * Add OSTime_Init() prototypes.
 * 
 * *****************  Version 6  *****************
 * User: Joe          Date: 03/09/17   Time: 3:33p
 * Updated in $/rd_1/Project/TM1300_PSOS/FarSeer/osisolate/src
 * Support high precision OSTime function.
 * 
 * *****************  Version 5  *****************
 * User: Joe          Date: 03/08/26   Time: 8:47a
 * Updated in $/rd_1/Project/TM1300_PSOS/FarSeer/osisolate/src
 * Add OSTick_GetCyclesPerSecond() in OS_Main() on _WIN32_ platform.
 * 
 * *****************  Version 4  *****************
 * User: Joe          Date: 03/08/20   Time: 4:06p
 * Updated in $/rd_1/Project/TM1300_PSOS/FarSeer/osisolate/src
 * define _CQ_USEMSGQUEUE.
 * 
 * *****************  Version 3  *****************
 * User: Joe          Date: 03/06/18   Time: 5:36p
 * Updated in $/rd_1/Project/TM1300_PSOS/FarSeer/osisolate/src
 * add OSTime object
 *
 * *****************  Version 2  *****************
 * User: Joe          Date: 03/04/30   Time: 2:46p
 * Updated in $/rd_1/Project/TM1300_PSOS/FarSeer/osisolate/src
 * 1. Fix bug when using OSThread_GetCurrentHandle() will return NULL in
 * Trimedia.
 *
 * *****************  Version 1  *****************
 * User: Joe          Date: 03/03/10   Time: 10:59a
 * Created in $/rd_1/Project/TM1300_PSOS/FarSeer/OSISOLATE/src
 * OS isolation layer for FarSeer
 *
 * *****************  Version 6  *****************
 * User: Joe          Date: 03/02/17   Time: 3:10p
 * Updated in $/rd_1/System/FIRMWARE/osisolate/src
 * Version 1.1.0.0
 * 1. Change OSConstQueue & OSVarQueue name by Bill
 * 2. Add one initial option of OSConstQueue object
 *
 * *****************  Version 5  *****************
 * User: Joe          Date: 02/12/30   Time: 1:14p
 * Updated in $/rd_1/System/FIRMWARE/osisolate/src
 * Add compatiable to VC++
 *
 * *****************  Version 4  *****************
 * User: Joe          Date: 02/12/18   Time: 1:59p
 * Updated in $/rd_1/System/FIRMWARE/osisolate/src
 * Add #ifndef _OSISOLATEXXX_H_ at beginning of file.
 *
 * *****************  Version 3  *****************
 * User: Joe          Date: 02/11/13   Time: 9:52a
 * Updated in $/rd_1/System/FIRMWARE/osisolate/src
 * Separate Trimedia's defines and Windows, linux defines
 *
 * *****************  Version 2  *****************
 * User: Joe          Date: 02/11/06   Time: 4:08p
 * Updated in $/rd_1/System/FIRMWARE/osisolate/src
 * Add OSThread_Yield function call
 *
 * *****************  Version 1  *****************
 * User: Joe          Date: 02/11/06   Time: 2:55p
 * Created in $/rd_1/System/FIRMWARE/osisolate/src
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * Copyright 2000-2002 Vivotek, Inc. All rights reserved.
 *
 * \file
 * osisolate.h
 *
 * \brief
 * OS isolation layer header file
 *
 * \date
 * 2002/10/16
 *
 * \author
 * Joe Wu
 *
 *
 *******************************************************************************
 */

#ifndef _OSISOLATE_H_
#define _OSISOLATE_H_

#ifdef __cplusplus
extern "C" {
#endif

#define OSISOLATE_VERSION MAKEFOURCC(1, 0, 0, 0)

#if 0
// --------------------- function brief ----------------------------------------
// Thread object
SCODE OSThread_Initial(HANDLE *phObject, TOSThreadInitOptions *pInitOptions);
SCODE OSThread_Release(HANDLE *phObject);
SCODE OSThread_Start(HANDLE hObject);
SCODE OSThread_Terminate(HANDLE hObject);
SCODE OSThread_Suspend(HANDLE hObject);
SCODE OSThread_Resume(HANDLE hObject);
SCODE OSThread_SetPriority(HANDLE hObject, DWORD dwPriority);
DWORD OSThread_GetPriority(HANDLE hObject);
SCODE OSThread_WaitFor(HANDLE hObject, DWORD dwTimeOut, DWORD *pdwExitCode);
SCODE OSThread_Yield(HANDLE hObject);
HANDLE OSThread_GetCurrentHandle(void);

// Idle object
void OSSleep_Sec(DWORD dwSecond);
void OSSleep_MSec(DWORD dwMiliSecond);

// tick object
void OSTick_GetCycle(DWORD *pdwHiCycle, DWORD *pdwLoCycle);
void OSTick_GetMSec(DWORD *pdwMilliSecond);
void OSTick_GetCyclesPerSecond(DWORD *pdwHiCycle, DWORD *pdwLoCycle);
void OSTick_RefreshCyclesPerSecond(void);

// time object
void  OSTime_GetTimer(DWORD *pdwec, DWORD *pdwMSec);
void  OSTime_GetDateTime(TOSDateTimeInfo *pOSdt);
void  OSTime_TimerToDateTime(DWORD dwTimer, TOSDateTimeInfo *pOSdt);
DWORD OSTime_DateTimeToTimer(TOSDateTimeInfo *pOSdt);
void OSTime_SetDateTime(TOSDateTimeInfo *pOSdt);
SDWORD OSTime_GetTimeZone(void);
SCODE OSTime_SetTimeZone(SDWORD sdwTimeZone);

// Memory allocation object
SCODE OSMem_Initial(HANDLE *phObject, void **ppMem,
                    DWORD dwSize, DWORD dwAlignment);
SCODE OSMem_Release(HANDLE *phObject);

// Ciritical Section object
SCODE OSCriticalSection_Initial(HANDLE *phObject);
SCODE OSCriticalSection_Release(HANDLE *phObject);
SCODE OSCriticalSection_Enter(HANDLE hObject);
SCODE OSCriticalSection_Leave(HANDLE hObject);
SCODE OSCriticalSection_TryEnter(HANDLE hObject);

// Semaphore object
SCODE OSSemaphore_Initial(HANDLE *phObject,DWORD dwInitCount, DWORD dwMaxCount);
SCODE OSSemaphore_Get(HANDLE hObject, DWORD dwTimeOut);
SCODE OSSemaphore_Post(HANDLE hObject);
SCODE OSSemaphore_Release(HANDLE *phObject);

// event object
SCODE OSEvent_Initial(HANDLE *phObject, BOOL bInitialState);
SCODE OSEvent_Release(HANDLE *phObject);
SCODE OSEvent_Set(HANDLE hObject);
SCODE OSEvent_Reset(HANDLE hObject);
SCODE OSEvent_WaitFor(HANDLE hObject, DWORD dwTimeOut);

// message queue object
SCODE OSMsgQueue_Initial(HANDLE *phObject, DWORD dwMaxCount);
SCODE OSMsgQueue_Release(HANDLE *phObject);
SCODE OSMsgQueue_Send   (HANDLE hObject, DWORD adwMsgBuf[4]);
SCODE OSMsgQueue_SendUrgent(HANDLE hObject, DWORD adwMsgBuf[4]);
SCODE OSMsgQueue_Receive(HANDLE hObject, DWORD adwMsgBuf[4], DWORD dwTimeOut);
SCODE OSMsgQueue_Peek(HANDLE hObject, DWORD aMsgBuf[4]);
DWORD OSMsgQueue_GetElementCount(HANDLE hObject);

// copy-free constant queue object
CODE OSConstQueue_Initial(HANDLE *phObject,TOSConstQueueInitOptions *pOptions);
SCODE OSConstQueue_Release(HANDLE *phObject);

void *OSConstQueue_GetElementFromEmptyQueue(HANDLE hObject, DWORD dwTimeOut); // modified by Bill, 2003/02/12
SCODE OSConstQueue_PutElementToFilledQueue(HANDLE hObject, void *pElement); // modified by Bill, 2003/02/12
void *OSConstQueue_GetElementFromFilledQueue(HANDLE hObject, DWORD dwTimeOut); // modified by Bill, 2003/02/12
SCODE OSConstQueue_PeekElementFromFilledQueue(HANDLE hObject, void *pElement); // modified by Bill, 2003/02/12
SCODE OSConstQueue_PutElementToEmptyQueue(HANDLE hObject, void *pElement); // modified by Bill, 2003/02/12
SCODE OSConstQueue_ClearElement(HANDLE hObject);

// copy-free variable size queue object
SCODE OSVarQueue_Initial(HANDLE *phObject, TOSVarQueueInitOptions *pOptions);
SCODE OSVarQueue_Release(HANDLE *phObject);
void *OSVarQueue_GetElementFromEmptyQueue(HANDLE hObject, DWORD dwLength); // modified by Bill, 2003/02/12
void *OSVarQueue_GetElementFromFilledQueue(HANDLE hObject, DWORD *pdwLen); // modified by Bill, 2003/02/12
SCODE OSVarQueue_PutElementToFilledQueue(HANDLE hObject, void *pElement); // modified by Bill, 2003/02/12
SCODE OSVarQueue_PutElementToEmptyQueue(HANDLE hObject, void *pElement); // modified by Bill, 2003/02/12
SCODE OSVarQueue_ClearElement(HANDLE hObject);
DWORD OSVarQueue_GetEmptyQueueCount(HANDLE hObject); // added by Bill, 2003/02/11
DWORD OSVarQueue_GetFilledQueueCount(HANDLE hObject); // added by Bill, 2003/02/11
#endif

/*! OS layer error code */
typedef enum {
    /*! memory not enough error */
	OSE_MEMORY = 2,
    /*! invalid parameter error */
	OSE_INVALIDPARAM,
} TOSError;

#if defined(_WIN32_)
#include <windows.h>
#include <assert.h>
#include <time.h>
#include "common.h"
#include "typedef.h"

/*! define this if you want ConstQueue using MsgQueue to emulate, it is fast
    in Trimedia platform */
//#define _CQ_USEMSGQUEUE

/*! define thread routine type in windows */
#define THREADAPI	WINAPI

void OSThread_TlsAlloc(void);
void OSThread_TlsFree(void);
void OSTime_Init(void);

// The following functions are for SLEEP object
/*! @defgroup OSSleep Sleep Object
 *  Idle system for an interval
 *  @{
 */

/*!
 ******************************************************************************
 * \brief
 * Idle the calling thread for an interval in seconds
 *
 * \param dwSecond
 * \a (i) Seconds to sleep
 *
 * \retval NONE
 *
 * \remark
 * Using constant in parameter \a dwSecond will speed up the performance in
 * pSOS & Linux platform.
 *
 * \see OSSleep_MSec
 *
 ******************************************************************************
 */
void OSSleep_Sec(DWORD dwSecond);

/*!
 ******************************************************************************
 * \brief
 * Idle the calling thread for an interval in milliseconds
 *
 * \param dwMiliSecond
 * \a (i) Milliseconds to sleep
 *
 * \retval NONE
 *
 * \remark
 * Using constant in parameter \a dwSecond will speed up the performance in
 * pSOS & Linux platform.
 *
 * \see OSSleep_Sec
 *
 ******************************************************************************
 */
void OSSleep_MSec(DWORD dwMiliSecond);

/*! @} End of OSSleep group */

// The following functions are for TICK object

/*! @defgroup OSTick Get System Tick Object
 *  Get the tick count from the system.
 *  @{
 */

/*!
 ******************************************************************************
 * \brief
 * Get the system cycle count from system start
 *
 * \param pdwHiCycle
 * \a (o) pointer to receive the hi-cycle count
 *
 * \param pdwLoCycle
 * \a (o) pointer to receive the low-cycle count
 *
 * \retval NONE
 *
 * \remark
 *  NONE
 *
 * \see OSTick_GetMSec
 *
 ******************************************************************************
 */
void OSTick_GetCycle(DWORD *pdwHiCycle, DWORD *pdwLoCycle);

/*!
 ******************************************************************************
 * \brief
 * Get the system ticks from system start up in milliseconds
 *
 * \param pdwMilliSecond
 * \a (o) pointer to receive the ticks in milliseconds
 *
 * \retval NONE
 *
 * \remark
 *  NONE
 *
 * \see OSTick_GetCycle
 *
 ******************************************************************************
 */
void OSTick_GetMSec(DWORD *pdwMilliSecond);

/*!
 ******************************************************************************
 * \brief
 * Get the system cycles per second
 *
 * \param pdwHiCycle
 * \a (o) pointer to receive the hi-cycle count
 *
 * \param pdwLoCycle
 * \a (o) pointer to receive the low-cycle count
 *
 * \retval NONE
 *
 * \remark
 *  When your CPU or DSP clock rate is below 4GHz, the Hi cycle is always zero.
 *
 *
 ******************************************************************************
 */
void OSTick_GetCyclesPerSecond(DWORD *pdwHiCycle, DWORD *pdwLoCycle);

/*!
 ******************************************************************************
 * \brief
 * Refresh the cycles per second
 *
 * \retval NONE
 *
 * \remark
 *  Call this function when your system cycle has changed. It will recalculate
 *  your system clock. You can re-call \b OSTick_GetCyclesPerSecond to get new
 *  system clock. This function is only useful in Windows platform now.
 *
 ******************************************************************************
 */
void OSTick_RefreshCyclesPerSecond(void);

/*! @} End of OSTick group */

/*!
 ******************************************************************************
 * \brief
 * OS main entry
 *
 * \remark
 * Using this macro instead of the ordinary main for cross-platform c
 * compatibility.
 *
 ******************************************************************************
 */
#define OS_Main()           void main(int argc, char **argv)

/*!
 ******************************************************************************
 * \brief
 * OS initialization
 *
 * \remark
 * Be sure to call this macro before using any OS call.
 *
 ******************************************************************************
 */
//! add by Joe 2003/08/26, add OSTick_RefreshCyclesPerSecond() at initial time
#define OS_Init()           {OSThread_TlsAlloc(); OSTick_RefreshCyclesPerSecond();OSTime_Init();}

/*!
 ******************************************************************************
 * \brief
 * OS exiting
 *
 * \remark
 * Be sure to call this macro before exit program
 *
 ******************************************************************************
 */
#define OS_Exit(dwExitCode) OSThread_TlsFree(); exit(dwExitCode);

// -----------------------------------------------------------------------------
#elif defined(_PSOS_TRIMEDIA)
#include <psos.h>
#include <assert.h>
#include <time.h>
#include <ops/custom_defs.h>
#include "sys_conf.h"
#include "common.h"
#include "typedef.h"
#include "errordef.h"

#if defined(_PSOS_PNX1500_TCS4x)
#include <tmMain.h>
#endif

void PSOSRoot_Init();
void OSTime_Init();

/*! Define this if you want ConstQueue using MsgQueue to emulate.
 *  It it fast in Trimedia, but consume more memory! */
#define _CQ_USEMSGQUEUE

/*! define thread routine type in psos */
#define THREADAPI

/*! define the clock rate of DSP */
//#define OSTICKS_PER_SEC			    297000000
#ifdef _WATERNOOSE
#define OSTICKS_PER_SEC			    192000000
#else
#define OSTICKS_PER_SEC			    100000000
#endif

// Function definitions for ossleep

/*!
 ******************************************************************************
 * \brief
 * Idle the calling thread for an interval in seconds
 *
 * \param dwSecond
 * \a (i) Seconds to sleep
 *
 * \retval NONE
 *
 * \remark
 * Using constant in parameter \a dwSecond will speed up the performance in
 * pSOS & Linux platform.
 *
 ******************************************************************************
 */
#define OSSleep_Sec(dwSecond)       tm_wkafter(KC_TICKS2SEC * (dwSecond))

/*!
 ******************************************************************************
 * \brief
 * Idle the calling thread for an interval in milliseconds
 *
 * \param dwMiliSecond
 * \a (i) Milliseconds to sleep
 *
 * \retval NONE
 *
 * \remark
 * Using constant in parameter \a dwSecond will speed up the performance in
 * pSOS & Linux platform.
 *
 ******************************************************************************
 */
// Modified by Joe 2004/07/30 for more accuracy
#define OSSleep_MSec(dwMiliSecond) \
tm_wkafter((KC_TICKS2SEC * dwMiliSecond) / 1000)
//tm_wkafter((((KC_TICKS2SEC * 1024 / 1000) * (dwMiliSecond) + 4)) >> 10)

/*!
 ******************************************************************************
 * \brief
 * Get the system cycles per second
 *
 * \param pdwHiCycle
 * \a (o) pointer to receive the hi-cycle count
 *
 * \param pdwLoCycle
 * \a (o) pointer to receive the low-cycle count
 *
 * \retval NONE
 *
 * \remark
 *  When your CPU or DSP clock rate is below 4GHz, the Hi cycle is always zero.
 *
 *
 ******************************************************************************
 */
#define OSTick_GetCyclesPerSecond(pdwHiCycle, pdwLoCycle) \
{\
    (*(pdwHiCycle)) = (OSTICKS_PER_SEC >> 30 >> 2);\
    (*(pdwLoCycle)) = (DWORD)(OSTICKS_PER_SEC);\
}

/*!
 ******************************************************************************
 * \brief
 * Refresh the cycles per second
 *
 * \retval NONE
 *
 * \remark
 *  Call this function when your system cycle has changed. It will recalculate
 *  your system clock. You can re-call \b OSTick_GetCyclesPerSecond to get new
 *  system clock. This function is only useful in Windows platform now.
 *
 ******************************************************************************
 */
#define OSTick_RefreshCyclesPerSecond()

/*!
 ******************************************************************************
 * \brief
 * Get the system cycle count from system start
 *
 * \param pdwHiCycle
 * \a (o) pointer to receive the hi-cycle count
 *
 * \param pdwLoCycle
 * \a (o) pointer to receive the low-cycle count
 *
 * \retval NONE
 *
 * \remark
 *  NONE
 *
 ******************************************************************************
 */
#define OSTick_GetCycle(pdwHiCycle, pdwLoCycle) \
{\
    (*(pdwHiCycle)) = HICYCLES(); (*(pdwLoCycle)) = CYCLES();\
}

/*!
 ******************************************************************************
 * \brief
 * Get the system ticks from system start up in milliseconds
 *
 * \param pdwMilliSecond
 * \a (o) pointer to receive the ticks in milliseconds
 *
 * \retval NONE
 *
 * \remark
 *  NONE
 *
 ******************************************************************************
 */
#define OSTick_GetMSec(pdwMilliSecond) \
{\
	DWORD dwHi, dwLo;\
    OSTick_GetCycle(&dwHi, &dwLo);\
	(*(pdwMilliSecond)) = dwHi * (0xFFFFFFFFUL / (OSTICKS_PER_SEC / 1000)) + \
    UMULM(dwLo, (0xFFFFFFFFUL / (OSTICKS_PER_SEC / 1000)));\
}

/*!
 ******************************************************************************
 * \brief
 * OS main entry
 *
 * \remark
 * Using this macro instead of the ordinary main for cross-platform c
 * compatibility.
 *
 ******************************************************************************
 */
#if defined(_PSOS_PNX1500_TCS4x)
#define OS_Main()           tmMain()
#else
#define OS_Main()           TASK root(void)
#endif
/*!
 ******************************************************************************
 * \brief
 * OS initialization
 *
 * \remark
 * Be sure to call this macro before using any OS call.
 *
 ******************************************************************************
 */
#define OS_Init()    {PSOSRoot_Init(); OSTime_Init();}


/*!
 ******************************************************************************
 * \brief
 * OS exiting
 *
 * \remark
 * Be sure to call this macro before exit program
 *
 ******************************************************************************
 */
#define OS_Exit(dwExitCode) _psos_exit(dwExitCode)

#ifndef INFINITE
#define INFINITE    0xFFFFFFFF
#endif

#elif defined(_LINUX)
#include "typedef.h"
#include "common.h"
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <sys/errno.h>
/* Added by CCH, 2004/02/10 */
#include <assert.h>
/* Added by CCH, 2004/09/08 */
#include <sys/times.h>

/*! define thread routine type in psos */
#define THREADAPI

// Function definitions for ossleep

/*!
 ******************************************************************************
 * \brief
 * Idle the calling thread for an interval in seconds
 *
 * \param dwSecond
 * \a (i) Seconds to sleep
 *
 * \retval NONE
 *
 * \remark
 * Using constant in parameter \a dwSecond will speed up the performance in
 * pSOS & Linux platform.
 *
 ******************************************************************************
 */
#define OSSleep_Sec(dwSecond)       sleep((dwSecond))

/*!
 ******************************************************************************
 * \brief
 * Idle the calling thread for an interval in milliseconds
 *
 * \param dwMilliSecond
 * \a (i) Milliseconds to sleep
 *
 * \retval NONE
 *
 * \remark
 * Using constant in parameter \a dwSecond will speed up the performance in
 * pSOS & Linux platform.
 *
 ******************************************************************************
 */
#define OSSleep_MSec(dwMilliSecond) usleep((dwMilliSecond) * 1000)

// Function definitions for ostick

/*! Cycles per seconds of current DSP or CPU */
/* Added by CCH, 2004/09/08 */
//#define OSTICKS_PER_SEC 1000000
#define OSTICKS_PER_SEC	sysconf(_SC_CLK_TCK)

/*!
 ******************************************************************************
 * \brief
 * Get the system cycles per second
 *
 * \param pdwHiCycle
 * \a (o) pointer to receive the hi-cycle count
 *
 * \param pdwLoCycle
 * \a (o) pointer to receive the low-cycle count
 *
 * \retval NONE
 *
 * \remark
 *  When your CPU or DSP clock rate is below 4GHz, the Hi cycle is always zero.
 *
 *
 ******************************************************************************
 */
/* Added by CCH, 2004/09/08 */
/*
#define OSTick_GetCyclesPerSecond(pdwHiCycle, pdwLoCycle) \
{\
    (*(pdwHiCycle)) = (OSTICKS_PER_SEC >> 30 >> 2);\
    (*(pdwLoCycle)) = (DWORD)(OSTICKS_PER_SEC);\
}
*/
#define OSTick_GetCyclesPerSecond(pdwHiCycle, pdwLoCycle) \
{\
    (*(pdwLoCycle)) = (DWORD)(OSTICKS_PER_SEC);\
}


/*!
 ******************************************************************************
 * \brief
 * Refresh the cycles per second
 *
 * \retval NONE
 *
 * \remark
 *  Call this function when your system cycle has changed. It will recalculate
 *  your system clock. You can re-call \b OSTick_GetCyclesPerSecond to get new
 *  system clock. This function is only useful in Windows platform now.
 *
 ******************************************************************************
 */
#define OSTick_RefreshCyclesPerSecond()

/*!
 ******************************************************************************
 * \brief
 * Get the system cycle count from system start
 *
 * \param pdwHiCycle
 * \a (o) pointer to receive the hi-cycle count
 *
 * \param pdwLoCycle
 * \a (o) pointer to receive the low-cycle count
 *
 * \retval NONE
 *
 * \remark
 *  NONE
 *
 ******************************************************************************
 */
/* Added by CCH, 2004/09/08 */
/*
#define OSTick_GetCycle(pdwHiCycle, pdwLoCycle) \
{\
    struct timeval tv;\
    gettimeofday(&tv, NULL);\
    (*(pdwHiCycle)) = 0; (*(pdwLoCycle)) = (DWORD)tv.tv_sec * 1000000 + tv.tv_usec;\
}
*/
#define OSTick_GetCycle(pdwHiCycle, pdwLoCycle) \
{\
	clock_t	cpu_time;\
    struct tms tmsnow;\
    cpu_time = times(&tmsnow);\
    (*(pdwHiCycle)) = 0; (*(pdwLoCycle)) = cpu_time;\
}

/*!
 ******************************************************************************
 * \brief
 * Get the system ticks from system start up in milliseconds
 *
 * \param pdwMilliSecond
 * \a (o) pointer to receive the ticks in milliseconds
 *
 * \retval NONE
 *
 * \remark
 *  NONE
 *
 ******************************************************************************
 */
/* Added by CCH, 2004/09/08 */
/*
#define OSTick_GetMSec(pdwMilliSecond) \
{\
    struct timeval tv;\
    gettimeofday(&tv, NULL);\
	(*(pdwMilliSecond)) =   ((DWORD)tv.tv_sec * 1000000 + tv.tv_usec)\
                          / (OSTICKS_PER_SEC / 1000);\
}
*/
#define OSTick_GetMSec(pdwMilliSecond) \
{\
	clock_t	cpu_time;\
    struct tms tmsnow;\
    DWORD	dwLoCycleH, dwLoCycleL;\
    long	clktck = sysconf(_SC_CLK_TCK);\
    cpu_time = times(&tmsnow);\
    dwLoCycleH = (cpu_time >> 16) & 0xFFFF;\
    dwLoCycleL = cpu_time & 0xFFFF;\
    (*(pdwMilliSecond)) = ((dwLoCycleH * 1000 / clktck) << 16) + \
    					  (dwLoCycleL * 1000 / clktck);\
}



/*!
 ******************************************************************************
 * \brief
 * OS main entry
 *
 * \remark
 * Using this macro instead of the ordinary main for cross-platform c
 * compatibility.
 *
 ******************************************************************************
 */
#define OS_Main()           int main(int argc, char **argv)

/*!
 ******************************************************************************
 * \brief
 * OS initialization
 *
 * \remark
 * Be sure to call this macro before using any OS call.
 *
 ******************************************************************************
 */
#define OS_Init()           OSThread_KeyCreate();

/*!
 ******************************************************************************
 * \brief
 * OS exiting
 *
 * \remark
 * Be sure to call this macro before exit program
 *
 ******************************************************************************
 */
#define OS_Exit(dwExitCode) {OSThread_KeyDestroy(); exit(dwExitCode);}


#ifndef INFINITE
#define INFINITE    0xFFFFFFFF
#endif

/*! defined to use conditional variables to emulate semaphore */
#define _SEMAPHORE_USECV

#elif defined(_UITRON)
#error NOT implement uITRON yet!
#endif

#if defined(_WIN32_) || defined(_LINUX)
/*---------------------------------------------------------------------*/
/* as_catch(), t_mode(), and t_start() Definitions                     */
/*---------------------------------------------------------------------*/
#define T_NOPREEMPT     0x00000001   /* Not preemptible bit */
#define T_PREEMPT       0x00000000   /* Preemptible */
#define T_TSLICE        0x00000002   /* Time-slicing enabled bit */
#define T_NOTSLICE      0x00000000   /* No Time-slicing */
#define T_NOASR         0x00000004   /* ASRs disabled bit */
#define T_ASR           0x00000000   /* ASRs enabled */
#define T_SUPV                   0   /* For compatibility w/ 68K */
#define T_USER                   0   /* For compatibility w/ 68K */
#define T_LEVELMASK0    0x00000000   /* For compatibility w/ 68K */
#define T_LEVELMASK1    0x00000100   /* For compatibility w/ 68K */
#define T_LEVELMASK2    0x00000100   /* For compatibility w/ 68K */
#define T_LEVELMASK3    0x00000100   /* For compatibility w/ 68K */
#define T_LEVELMASK4    0x00000100   /* For compatibility w/ 68K */
#define T_LEVELMASK5    0x00000100   /* For compatibility w/ 68K */
#define T_LEVELMASK6    0x00000100   /* For compatibility w/ 68K */
#define T_LEVELMASK7    0x00000100   /* For compatibility w/ 68K */
#define T_NOISR         0x00000100   /* Interrupts disabled */
#define T_ISR           0x00000000   /* Interrupts enabled */

/*---------------------------------------------------------------------*/
/* t_create() Definitions                                              */
/*---------------------------------------------------------------------*/
#define T_GLOBAL        0x00000001   /* 1 = Global */
#define T_LOCAL         0x00000000   /* 0 = Local */
#define T_NOFPU         0x00000000   /* Not using FPU */
#define T_FPU           0x00000002   /* Using FPU bit */
#endif

// The following functions are for Time object

/*! @defgroup OSTime System Timer Object
 *  Get system time utilities, date/time conversion functions.
 *  @{
 */

/*! Date/time information for data structure */
typedef struct {
    //! year in A.D. from 1970 ~ 2034
    WORD    wYear;
    //! month of year. form 1 ~ 12
    WORD    wMonth;
    //! day of month. from 1 ~ 31
    WORD    wMonthDay;
    //! day of week. from 0(Sun) ~ 6(Sat)
    WORD    wWeekDay;
    //! hour of day. from 0 ~ 23
    WORD    wHour;
    //! minutes of hour. from 0 ~ 59
    WORD    wMinute;
    //! second of minute. from 0 ~ 59
    WORD    wSecond;
} TOSDateTimeInfo;

/*!
 ******************************************************************************
 * \brief
 * Get current system time in seconds elapsed since 00:00:00, January 1, 1970.
 *
 * \param pdwSec
 * current time, in seconds, elapsed since 00:00:00,
 * January 1, 1970.
 *
 * \param pdwMSec
 * current time, milliseconds part, elapsed since 00:00:00,
 * January 1, 1970. range from 
 *
 * \retval
 * NONE
 *
 * \remark
 *  NONE
 *
 * \see OSTime_GetDateTime
 * \see OSTime_TimerToDateTime
 *
 ******************************************************************************
 */
void OSTime_GetTimer(DWORD *pdwSec, DWORD *pdwMSec);

/*!
 ******************************************************************************
 * \brief
 * Get current system time in date/time format
 *
 * \param pOSdt
 * \a (o) pointer to TOSDateTimeInfo to receive the system date/time
 *
 * \retval
 * NONE
 *
 * \remark
 *  NONE
 *
 * \see OSTime_GetTimer
 * \see OSTime_DateTimeToTimer
 *
 ******************************************************************************
 */
void  OSTime_GetDateTime(TOSDateTimeInfo *pOSdt);

/*!
 ******************************************************************************
 * \brief
 * Convert the timer to date/time format
 *
 * \param dwTimer
 * \a (i) The timer to be converted
 *
 * \param pOSdt
 * \a (o) pointer to TOSDateTimeInfo to receive the converted date/time
 *
 * \retval
 * NONE
 *
 * \remark
 *  NONE
 *
 * \see OSTime_GetTimer
 * \see OSTime_DateTimeToTimer
 *
 ******************************************************************************
 */
void  OSTime_TimerToDateTime(DWORD dwTimer, TOSDateTimeInfo *pOSdt);

/*!
 ******************************************************************************
 * \brief
 * Convert date/time format to the timer
 *
 * \param pOSdt
 * \a (i) pointer to TOSDateTimeInfo to be converted
 *
 * \retval
 * The converted timer value
 *
 * \remark
 *  NONE
 *
 * \see OSTime_GetTimer
 * \see OSTime_TimerToDateTime
 *
 ******************************************************************************
 */
DWORD OSTime_DateTimeToTimer(TOSDateTimeInfo *pOSdt);

/*!
 ******************************************************************************
 * \brief
 * Set current system time in date/time format
 *
 * \param pOSdt
 * \a (i) pointer to TOSDateTimeInfo to set the system date/time
 *
 * \retval
 * NONE
 *
 * \remark
 *  NONE
 *
 * \see OSTime_GetTimer
 * \see OSTime_DateTimeToTimer
 *
 ******************************************************************************
 */
void OSTime_SetDateTime(TOSDateTimeInfo *pOSdt);
/*!
 ******************************************************************************
 * \brief
 * Get timezone
 *
 * \retval
 * The number of seconds that you must add to UTC to get local time.
 *
 * \remark
 *  NONE
 *
 * \see OSTime_SetTimeZone
 *
 ******************************************************************************
 */
SDWORD OSTime_GetTimeZone(void);

/*!
 ******************************************************************************
 * \brief
 * Set timezone
 *
 * \param dwTimeZone
 * The number of seconds that you must add to UTC to get local time.
 *
 * \retval
 * NONE
 *
 * \remark
 *  NONE
 *
 * \see OSTime_GetTimeZone
 *
 ******************************************************************************
 */
SCODE OSTime_SetTimeZone(SDWORD sdwTimeZone);
/*! @} End of OSTime group */



// The following functions are for critical section
/*! @defgroup OSCriticalSection Critical Section Object
 *
 * Critical section objects provide synchronization similar to that provided by
 * mutex objects, except that critical section objects can be used only by the
 * threads of a single process. Event, mutex, and semaphore objects can also be
 * used in a single-process application, but critical section objects provide a
 * slightly faster, more efficient mechanism for mutual-exclusion
 * synchronization. Like a mutex object, a critical section object can be owned
 * by only one thread at a time, which makes it useful for protecting a shared
 * resource from simultaneous access. There is no guarantee about the order in
 * which threads will obtain ownership of the critical section, however, the
 * system will be fair to all threads.
 *
 *  @{
 */

/*!
******************************************************************************
* \brief
* Create handle of CriticalSection object
*
* \param phObject
* \a (o) pointer to receive the handle of the critical section object
*
* \retval S_OK
* Create critical section object OK
*
* \retval S_FAIL
* Critical section create FAIL
*
* \remark
* A critical shall be initialized before using it.
*
* \see OSCriticalSection_Release
* \see OSCriticalSection_Enter
* \see OSCriticalSection_TryEnter
* \see OSCriticalSection_Leave
*
******************************************************************************
*/
SCODE OSCriticalSection_Initial(HANDLE *phObject);

/*!
******************************************************************************
* \brief
* Release a CriticalSection object
*
* \param phObject
* \a (i/o) pointer to the handle of the critical section object
*
* \retval S_OK
* Release object ok
*
* \retval S_FAIL
* Release object failed
*
* \remark
* After release the oject, the *phObject will be set to NULL
*
* \see OSCriticalSection_Initial
* \see OSCriticalSection_Enter
* \see OSCriticalSection_TryEnter
* \see OSCriticalSection_Leave
*
******************************************************************************
*/
SCODE OSCriticalSection_Release(HANDLE *phObject);

/*!
******************************************************************************
* \brief
* This function waits for ownership of the specified critical section object.
* The function returns when the calling thread is granted ownership.
*
* \param hObject
* \a (i) handle of the ciritical object
*
* \retval S_OK
* Enter critical section OK.
*
* \retval S_FAIL
* Enter critical section Failed.
*
* \remark
* To enable mutually exclusive access to a shared resource, each thread calls
* the \b OSCriticalSection_Enter or \b OSCriticalSection_TryEnter function
* to request ownership of the critical section before executing any section of
* code that accesses the protected resource. The difference is that
* \b OSCriticalSection_TryEnter returns immediately, regardless of whether it
* obtained ownership of the critical section, while \b OSCriticalSection_Enter
* blocks until the thread can take ownership of the critical section. When it
* has finished executing the protected code, the thread uses the
* \b OSCriticalSection_Leave function to relinquish ownership, enabling another
* thread to become owner and access the protected resource. The thread must call
* \b OSCriticalSection_Leave once for each time that it entered the critical
* section. The thread enters the critical section each time
* \b OSCriticalSection_Enter and \b OSCriticalSection_TryEnter succeed.
*
* \see OSCriticalSection_Initial
* \see OSCriticalSection_Release
* \see OSCriticalSection_TryEnter
* \see OSCriticalSection_Leave
*
******************************************************************************
*/
SCODE OSCriticalSection_Enter(HANDLE hObject);

/*!
******************************************************************************
* \brief
* This function releases ownership of the specified critical section object.
*
* \param hObject
* \a (i) handle of the ciritical object
*
* \retval S_OK
* Leave critical section OK.
*
* \retval S_FAIL
* Leave critical section Failed.
*
* \remark
* Before using a critical section, some thread of the process must call the
* \b OSCriticalSection_Initialize function to initialize the object.
* A thread uses the \b OSCriticalSection_Enter or \b OSCriticalSection_TryEnter
* function to acquire ownership of a critical section object. To release its
* ownership, the thread must call \b OSCriticalSection_Leave once for each time
* that it entered the critical section.
* If a thread calls \b OSCriticalSection_Leave when it does not have ownership
* of the specified critical section object, an error occurs that may cause
* another thread using OSCriticalSection_Enter to wait indefinitely.
* Any thread of the process can use the OSCriticalSection_Delete function to
* release the system resources that were allocated when the critical section
* object was initialized. After this function has been called, the critical
* section object can no longer be used for synchronization.
*
* \see OSCriticalSection_Initial
* \see OSCriticalSection_Release
* \see OSCriticalSection_TryEnter
* \see OSCriticalSection_Enter
*
******************************************************************************
*/
SCODE OSCriticalSection_Leave(HANDLE hObject);

/*!
******************************************************************************
* \brief
* This function attempts to enter a critical section without blocking. If the
* call is successful, the calling thread takes ownership of the critical section
*
* \param hObject
* \a (i) handle of the ciritical object
*
* \retval S_OK
* If the critical section is successfully entered or the current thread already
* owns the critical section.
*
* \retval S_FAIL
* If another thread already owns the critical section.
*
* \remark
* To enable mutually exclusive access to a shared resource, each thread calls
* the \b OSCriticalSection_Enter or \b OSCriticalSection_TryEnter function
* to request ownership of the critical section before executing any section of
* code that accesses the protected resource. The difference is that
* \b OSCriticalSection_TryEnter returns immediately, regardless of whether it
* obtained ownership of the critical section, while \b OSCriticalSection_Enter
* blocks until the thread can take ownership of the critical section. When it
* has finished executing the protected code, the thread uses the
* \b OSCriticalSection_Leave function to relinquish ownership, enabling another
* thread to become owner and access the protected resource. The thread must call
* \b OSCriticalSection_Leave once for each time that it entered the critical
* section. The thread enters the critical section each time
* \b OSCriticalSection_Enter and \b OSCriticalSection_TryEnter succeed.
*
* \see OSCriticalSection_Initial
* \see OSCriticalSection_Release
* \see OSCriticalSection_TryEnter
* \see OSCriticalSection_Enter
*
******************************************************************************
*/
SCODE OSCriticalSection_TryEnter(HANDLE hObject);

/*! @} end of OSCriticalSection group */


// The following functions are for thread object
/*!
******************************************************************************
* \brief
* The \b ThreadProc function is an application-defined function that serves
* as the starting address for a thread. Specify this address when calling the
* \b OSThread_Initial function. The TOSThreadProc type defines a pointer to this
* callback function. ThreadProc is a placeholder for the application-defined
* function name.
*
* \param dwInstance
* \a (i) Receives the thread data passed to the function using the \a dwInstance
* parameter of the \b OSThread_Initial function.
*
* \return
* The function should return a value that indicates its success or failure.
*
* \remark
* NONE
*
* \see OSThread_Initial
*
******************************************************************************
*/
typedef DWORD (THREADAPI * TOSThreadProc)(DWORD dwInstance);

/*! @defgroup OSThread Thread Object
 * All threads of a process share its virtual address space and system
 * resources. In addition, each thread maintains exception handlers, a
 * scheduling priority, and a set of structures the system will use to save the
 * thread context until it is scheduled. The thread context includes the
 * thread's set of machine registers, the kernel stack, a thread environment
 * block, and a user stack in the address space of the thread's process.
 *
 *  @{
 */
/*!
* A structure used in \b OSThread_Initial to initialize a thread
*/
typedef struct
{
    /*! stack size of thread */
	DWORD 			dwStackSize;
	/*! the instance to pass into thread routine */
	DWORD			dwInstance;
	/*! thread priority (from 1 ~ 230, 0 is reserved for idle task,
     *  231 or above is reserved for OS internally)
     */
	DWORD			dwPriority;
	/*!
     * used in psos which can be combination of T_GLOBAL, T_FPU,
     *  T_LOCAL, T_NOFPU, ...( no use in windows, linux)
     */
	DWORD			dwFlags;
	/*!
     * used in psos	which can be combination of T_PREMPT, T_ISR,
     * T_TSLICE, T_NOSLICE, T_NOPREEMPT, T_ASR, T_NOASR
     * ( no use in windows, linux)
     */
	DWORD			dwMode;

	/*! pointer to the thread routine */
	TOSThreadProc	pThreadProc;
} TOSThreadInitOptions;

/*!
******************************************************************************
* \brief
* This function create a thread object and initialize it with given options.
*
* \param phObject
* \a (o) A pointer to receive the handle of thread object
*
* \param pInitOptions
* \a (i) Initialize options for setting thread
*
* \retval S_OK
* Initialize thread successful.
*
* \retval S_FAIL
* Initialize thread failed.
*
* \remark
* NONE
*
* \see OSThread_Release
* \see OSThread_Start
* \see TOSThreadInitOptions
*
******************************************************************************
*/
SCODE OSThread_Initial(HANDLE *phObject, TOSThreadInitOptions *pInitOptions);

/*!
******************************************************************************
* \brief
* Release a thread object
*
* \param phObject
* \a (i/o) A pointer to the handle of thread object
*
* \retval S_OK
* Release thread object successful.
*
* \retval S_FAIL
* Release thread object failed.
*
* \remark
* NONE
*
* \see OSThread_Initial
* \see OSThread_Start
*
******************************************************************************
*/
SCODE OSThread_Release(HANDLE *phObject);

/*!
******************************************************************************
* \brief
* Start executing a thread
*
* \param hObject
* \a (i) handle of thread object
*
* \retval S_OK
* Start executing thread object successful.
*
* \retval S_FAIL
* Start executing thread object failed.
*
* \remark
* You can only start executing thread after it is initialized, or when it is
* terminated. If the thread is running, it will failed when call this function.
*
* \see OSThread_Initial
* \see OSThread_Terminate
*
******************************************************************************
*/
SCODE OSThread_Start(HANDLE hObject);

/*!
******************************************************************************
* \brief
* Force terminate an executing thread
*
* \param hObject
* \a (i) handle of thread object
*
* \retval S_OK
* Terminate a thread successful
*
* \retval S_FAIL
* Terminate a thread failed
*
* \remark
* This is a dangerous function that should only be used in the most extreme
* cases. You should call this function only if you know exactly what the target
* thread is doing, and you control all of the code that the target thread could
* possibly be running at the time of the termination. The better way is using
* \b OSThread_WaitFor function to wait for termination.
*
* \see OSThread_Initial
* \see OSThread_Start
* \see OSThread_WaitFor
*
******************************************************************************
*/
SCODE OSThread_Terminate(HANDLE hObject);

/*!
******************************************************************************
* \brief
* Suspend an executing thread
*
* \param hObject
* \a (i) handle of thread object
*
* \retval S_OK
* Suspend a thread successful
*
* \retval S_FAIL
* Suspend a thread failed
*
* \remark
* This function will suspend the executing thread, if the thread is already
* suspended, it will do nothing and return S_OK. You can use \b OSThread_Resume
* to resume the suspended thread. Try to suspend a thread which is not executing
* will cause fail.
*
* \see OSThread_Initial
* \see OSThread_Start
* \see OSThread_Resume
*
******************************************************************************
*/
SCODE OSThread_Suspend(HANDLE hObject);

/*!
******************************************************************************
* \brief
* Resume an suspended thread
*
* \param hObject
* \a (i) handle of thread object
*
* \retval S_OK
* Resume a thread successful
*
* \retval S_FAIL
* Resume a thread failed
*
* \remark
* This function will resume the suspended thread, if the thread is already
* executing, it will do nothing and return S_OK. You can use \b OSThread_Suspend
* to suspend the executing thread. Try to resume a thread which is not started
* will cause fail.
*
* \see OSThread_Initial
* \see OSThread_Start
* \see OSThread_Suspend
*
******************************************************************************
*/
SCODE OSThread_Resume(HANDLE hObject);

/*!
******************************************************************************
* \brief
* Set priority of a thread
*
* \param hObject
* \a (i) handle of thread object
*
* \param dwPriority
* \a (i) Priority to set (1 ~ 231)
*
* \retval S_OK
* Set priority successful.
*
* \retval S_FAIL
* Set priority failed.
*
* \remark
* The priority should be ranged from 1 ~ 231. 231 ~ 255 are reserved for system.
* 0 is reserved for idle task.
*
* \see OSThread_Initial
* \see OSThread_GetPriority
*
******************************************************************************
*/
SCODE OSThread_SetPriority(HANDLE hObject, DWORD dwPriority);

/*!
******************************************************************************
* \brief
* Get priority of a thread
*
* \param hObject
* \a (i) handle of thread object
*
* \return
* The priority of current thread
*
* \remark
* NONE
*
* \see OSThread_Initial
* \see OSThread_SetPriority
*
******************************************************************************
*/
DWORD OSThread_GetPriority(HANDLE hObject);

/*!
******************************************************************************
* \brief
* Wait a thread for termination
*
* \param hObject
* \a (i) handle of thread object
*
* \param dwTimeOut
* \a (i) wait time in millisecond. Set to \a INFINITE to wait infinitely.
*
* \param pdwExitCode
* \a (o) pointer to receive the exit code of thread, set to NULL if you do not
* want to receive the exit code.
*
* \retval S_OK
* The thread is terminated.
*
* \retval S_FAIL
* The thread is not terminate after \a dwTimeOut.
*
* \remark
* Call this function to wait for thread's termination.
*
* \see OSThread_Initial
* \see OSThread_Terminate
*
******************************************************************************
*/
SCODE OSThread_WaitFor(HANDLE hObject, DWORD dwTimeOut, DWORD *pdwExitCode);

/*!
******************************************************************************
* \brief
* Let the calling thread to yield execution to another thread that is ready to
* run on the current processor. The operating system selects the thread to
* yield to.
*
* \retval S_OK
* If calling to this function causes the operating system to switch execution to
* another thread, the return value is S_OK.
*
* \retval S_FAIL
* If there are no other threads ready to execute, the operating system does not
* switch execution to another thread, and the return value is S_FAIL.
*
* \remark
* The yield of execution is in effect for up to one thread-scheduling time
* slice. After that, the operating system reschedules execution for the yielding
* thread. The rescheduling is determined by the priority of the yielding thread
* and the status of other threads that are available to run. Note that the yield
* of execution is limited to the processor of the calling thread. The operating
* system will not switch execution to another processor, even if that processor
* is idle or is running a thread of lower priority.
*
******************************************************************************
*/
SCODE OSThread_Yield(void);

/*!
******************************************************************************
* \brief
* Get handle of calling thread
*
* \return
* The handle of calling thread.
*
* \remark
* NONE
*
* \see OSThread_Initial
*
******************************************************************************
*/
HANDLE OSThread_GetCurrentHandle(void);

/*! @} End of OSThread group */


// The following functions are for aligned allocation
/*! @defgroup OSMem Aligned Memory Allocation Object
 *  Allocate aligned memory blocks.
 *
 *  @{
 */
/*!
******************************************************************************
* \brief
* Allocate an aligned memory space for usage.
*
* \param phObject
* \a (o) A pointer to receive the handle of memory object
*
* \param ppMem
* \a (o) A pointer to receive the allocated memory pointer.
*
* \param dwSize
* \a (i) The memory size you want to allocate in bytes
*
* \param dwAlignment
* \a (i) The alignment of start address. The start address will aligned at
* (2^dwAlignment) bytes.
*
* \retval S_OK
* Allocate memory successful.
*
* \retval S_FAIL
* Allocate memory failed.
*
* \remark
* NONE
*
* \see OSMem_Release
*
******************************************************************************
*/
SCODE OSMem_Initial(HANDLE *phObject, void **ppMem,
                    DWORD dwSize, DWORD dwAlignment);

/*!
******************************************************************************
* \brief
* Release an allocated memory object
*
* \param phObject
* \a (i/o) A pointer to the handle of memory object
*
* \retval S_OK
* Release memory successful.
*
* \retval S_FAIL
* Release memory failed.
*
* \remark
* NONE
*
* \see OSMem_Initial
*
******************************************************************************
*/
SCODE OSMem_Release(HANDLE *phObject);

/*! @} end of OSMem group */

/*! @defgroup OSSemaphore Semaphore Object
 *  Semaphore object provides a specific number of resources that you can get.
 *  When you call \b OSSemaphore_Get, the resource count will decrease, when the
 *  resource count is zero, the \b OSSemaphore_Get function will be blocked
 *  until the resouce is released by another thread. \b OSSemaphore_Post will
 *  release a resouce and increase the resource count.
 *
 *  @{
 */

// The following functions are for semaphore object
/*!
******************************************************************************
* \brief
* Initialize a semaphore object
*
* \param phObject
* \a (o) A pointer to receive the handle of semaphore object
*
* \param dwInitCount
* \a (i) Initial count of semaphore object. It must be less than or equal than
* dwMaxCount.
*
* \param dwMaxCount
* \a (i) Maximum count of semaphore object. Set to INFINITE of you want to use
* unbounded semaphore object, which is faster in LINUX platform.
*
* \retval S_OK
* Create a semaphore object successful.
*
* \retval S_FAIL
* Create a semaphore object failed.
*
* \remark
* NONE
*
* \see OSSemaphore_Release
*
******************************************************************************
*/
SCODE OSSemaphore_Initial(HANDLE *phObject, DWORD dwInitCount, DWORD dwMaxCount);

/*!
******************************************************************************
* \brief
* Acquire a semaphore resource
*
* \param hObject
* \a (o) handle of semaphore object
*
* \param dwTimeOut
* \a (i) wait time to acquire a semaphore in millisecond. Set to INFINITE if you
* want to wait without timeout.
*
* \retval S_OK
* Acquire a semaphore resource successful.
*
* \retval S_FAIL
* Acquire a semaphore resource failed.
*
* \remark
* Using \b OSSemaphore_Post to release a semaphore resource.
*
* \see OSSemaphore_Post
*
******************************************************************************
*/
SCODE OSSemaphore_Get(HANDLE hObject, DWORD dwTimeOut);

/*!
******************************************************************************
* \brief
* Acquire a semaphore resource
*
* \param hObject
* \a (o) handle of semaphore object
*
* \retval S_OK
* Acquire a semaphore resource successful.
*
* \retval S_FAIL
* Acquire a semaphore resource failed.
*
* \remark
* Using \b OSSemaphore_Post to release a semaphore resource.
*
* \see OSSemaphore_Get
*
******************************************************************************
*/
SCODE OSSemaphore_Post(HANDLE hObject);

/*!
******************************************************************************
* \brief
* Release a semaphore object
*
* \param phObject
* \a (o) A pointer to the handle of semaphore object
*
* \retval S_OK
* Release a semaphore object successful.
*
* \retval S_FAIL
* Release a semaphore object failed.
*
* \remark
* NONE
*
* \see OSSemaphore_Initial
*
******************************************************************************
*/
SCODE OSSemaphore_Release(HANDLE *phObject);

/*! @} end of OSSemaphore group */

// The following functions are for event object

/*! @defgroup OSEvent Event Object
 *  The event provides a machenism to synchronize between threads. One thread
 *  can use \b OSEvent_WaitFor to waiting for an event. Another can use
 *  \b OSEvent_Set to trigger the event and let the waiting thread to continue.
 *  The event will be reset after the wait thread get the event. The Event
 *  object is similiar to the Semaphore object with maxcount equals to 1.
 *
 *  @{
 */
/*!
******************************************************************************
* \brief
* Initialize a event object
*
* \param phObject
* \a (o) A pointer to receive the handle of event object
*
* \param bInitialState
* \a (i) Initial state of event. Can be 1 as triggered or 0 as untriggered.
*
* \retval S_OK
* Create a event object successful.
*
* \retval S_FAIL
* Create a event object failed.
*
* \remark
* NONE
*
* \see OSEvent_Release
*
******************************************************************************
*/
SCODE OSEvent_Initial(HANDLE *phObject, BOOL bInitialState);

/*!
******************************************************************************
* \brief
* Release an event object
*
* \param phObject
* \a (o) A pointer to receive the handle of event object
*
* \retval S_OK
* Release a event object successful.
*
* \retval S_FAIL
* Release a event object failed.
*
* \remark
* NONE
*
* \see OSEvent_Initial
*
******************************************************************************
*/
SCODE OSEvent_Release(HANDLE *phObject);

/*!
******************************************************************************
* \brief
* Trigger an event object
*
* \param hObject
* \a (o) handle of event object
*
* \retval S_OK
* Event is triggered successful.
*
* \retval S_FAIL
* Event is triggered failed.
*
* \remark
* The \b OSEvent_Reset function & \b OSEvent_WaitFor function can untriggered
* the event.
*
* \see OSEvent_Reset
* \see OSEvent_WaitFor
*
******************************************************************************
*/
SCODE OSEvent_Set(HANDLE hObject);

/*!
******************************************************************************
* \brief
* Untrigger an event object
*
* \param hObject
* \a (o) handle of event object
*
* \retval S_OK
* Event is untriggered successful.
*
* \retval S_FAIL
* Event is untriggered failed.
*
* \remark
* NONE
*
* \see OSEvent_Set
* \see OSEvent_WaitFor
*
******************************************************************************
*/
SCODE OSEvent_Reset(HANDLE hObject);

/*!
******************************************************************************
* \brief
* Wait for an event to be triggered, and reset the event after waiting.
*
* \param hObject
* \a (o) handle of event object
*
* \param dwTimeOut
* \a (o) time for waiting event in millisecond. Set to INFINITE to wait
* infinitely.
*
* \retval S_OK
* Waiting for an event successful.
*
* \retval S_FAIL
* Waiting for an event failed.
*
* \remark
* NONE
*
* \see OSEvent_Set
* \see OSEvent_Reset
*
******************************************************************************
*/
SCODE OSEvent_WaitFor(HANDLE hObject, DWORD dwTimeOut);

/*! @} end of OSEvent group */

// The following functions are for message queue object
/*! @defgroup OSMsgQueue Message Queue Object
 *  Message queues provide a highly flexible, general-purpose mechanism to
 *  implement communication and synchronization.
 *
 *  @{
 */

/*!
******************************************************************************
* \brief
* Initialize a message queue object
*
* \param phObject
* \a (o) A pointer to receive the handle of message queue object
*
* \param dwMaxCount
* \a (i) The maximum element number can be queued
*
* \retval S_OK
* Create a message queue object successful.
*
* \retval S_FAIL
* Create a message queue object failed.
*
* \remark
* NONE
*
* \see OSMsgQueue_Release
*
******************************************************************************
*/
SCODE OSMsgQueue_Initial(HANDLE *phObject, DWORD dwMaxCount);

/*!
******************************************************************************
* \brief
* Release a message queue object
*
* \param phObject
* \a (o) A pointer to the handle of message queue object
*
* \retval S_OK
* Release a message queue object successful.
*
* \retval S_FAIL
* Release a message queue object failed.
*
* \remark
* NONE
*
* \see OSMsgQueue_Initial
*
******************************************************************************
*/
SCODE OSMsgQueue_Release(HANDLE *phObject);

/*!
******************************************************************************
* \brief
* Send a message to message queue object
*
* \param hObject
* \a (i) the handle of message queue object
*
* \param adwMsgBuf
* \a (i) The 16 bytes message to send to message queue object
*
* \retval S_OK
* The message is send successful.
*
* \retval S_FAIL
* Unable to send the message, maybe the queue is full.
*
* \remark
* This function will send the message at \b tail of queue. To send the message
* at \b head of queue, using \b OSMsgQueue_SendUrgent instead.
*
* \see OSMsgQueue_SendUrgent
*
******************************************************************************
*/
SCODE OSMsgQueue_Send   (HANDLE hObject, DWORD adwMsgBuf[4]);

/*!
******************************************************************************
* \brief
* Send a urgent message to message queue object
*
* \param hObject
* \a (i) the handle of message queue object
*
* \param adwMsgBuf
* \a (i) The 16 bytes message to send to message queue object
*
* \retval S_OK
* The message is send successful.
*
* \retval S_FAIL
* Unable to send the message, maybe the queue is full.
*
* \remark
* This function will send the message at \b head of queue. To send the message
* at \b head of queue, using \b OSMsgQueue_Send instead.
*
* \see OSMsgQueue_Send
*
******************************************************************************
*/
SCODE OSMsgQueue_SendUrgent(HANDLE hObject, DWORD adwMsgBuf[4]);

/*!
******************************************************************************
* \brief
* Receive a message from message queue object
*
* \param hObject
* \a (i) the handle of message queue object
*
* \param adwMsgBuf
* \a (o) The 16 bytes message buffer to receive from message queue object
*
* \param dwTimeOut
* \a (i) Time out to wait for a message to receive in millisecond. Set to
* INFINITE to wait the message infinitely.
*
* \retval S_OK
* The message is received successful.
*
* \retval S_FAIL
* Unable to receive the message, maybe the queue is empty.
*
* \remark
* This function will receive a message at \b head of queue, and take off the
* message. To receive a message without take off the message, using
* \b OSMsgQueue_Peek instead.
*
* \see OSMsgQueue_Peek
*
******************************************************************************
*/
SCODE OSMsgQueue_Receive(HANDLE hObject, DWORD adwMsgBuf[4], DWORD dwTimeOut);

/*!
******************************************************************************
* \brief
* Peek a message from message queue object
*
* \param hObject
* \a (i) the handle of message queue object
*
* \param adwMsgBuf
* \a (o) The 16 bytes message buffer to peek from message queue object
*
* \retval S_OK
* The message is peeked successful.
*
* \retval S_FAIL
* Unable to peek a message, maybe the queue is empty.
*
* \remark
* This function will peek a message at \b head of queue, and will not take off
* the message. To receive a message, using \b OSMsgQueue_Receive instead.
*
* \see OSMsgQueue_Receive
*
******************************************************************************
*/
SCODE OSMsgQueue_Peek(HANDLE hObject, DWORD adwMsgBuf[4]);

/*!
******************************************************************************
* \brief
* Get the element count in the given message queue
*
* \param hObject
* \a (i) the handle of message queue object
*
* \return 
* The element count in the given message queue
*
* \remark
* This function is only available in the Windows and Linux system
*
* \see 
*
******************************************************************************
*/
DWORD OSMsgQueue_GetElementCount(HANDLE hObject);

/*! @} End of OSMsgQueue group */

// The following functions are for copy-free constant size queue
/*! @defgroup OSConstQueue Constant Size Queue Object
 *  A copy-free constant size queue. Using this queue if you have message or
 *  data larger than 16 bytes.
 *
 *  @{
 */
/*! Initial options for setting \b OSConstQueue object. */
typedef struct
{
    /*! number of elements */
    DWORD dwElementCount;

    /*! size of each element */
    DWORD dwElementSize;

    /*! Elements aligned at (2^dwAlignment) bytes */
    DWORD dwAlignment;

    /*! Initial data set to each element */
    void *pvInitData;

    /*! Initial data size */
    DWORD dwInitDataSize;

} TOSConstQueueInitOptions;

/*!
 ******************************************************************************
 * \brief
 * Create \b OSConstQueue object
 *
 * \param phObject
 * \a (o) Pointer to receive the instance's handle of this object
 *
 * \param pOptions
 * \a (i) Options to initialize \b OSConstQueue, please reference
 * \b TOSConstQueueOptions for detail settings.
 *
 * \retval S_OK
 * Create constant size queue successfully
 *
 * \retval S_FAIL
 * Create constant size queue failed
 *
 * \remark
 * Call this function before using this instance
 *
 * \see OSConstQueue_Release
 * \see TOSConstQueueInitOptions
 *
 ******************************************************************************
 */
SCODE OSConstQueue_Initial(HANDLE *phObject, TOSConstQueueInitOptions *pOptions);

/*!
 ******************************************************************************
 * \brief
 * Release \b OSConstQueue object
 *
 * \param phObject
 * \a (i/o) Pointer to the instance's handle of this object
 *
 * \retval S_OK
 * Release constant size queue successfully
 *
 * \retval S_FAIL
 * Release constant size queue failed
 *
 * \remark
 * NONE
 *
 * \see OSConstQueue_Initial
 *
 ******************************************************************************
 */
SCODE OSConstQueue_Release(HANDLE *phObject);

/*!
 ******************************************************************************
 * \brief
 * acquire an empty element from queue to fill data
 *
 * \param hObject
 * \a (i) the handle of this object
 *
 * \param dwTimeOut
 * \a (i) Time out for getting a empty element. Set to INFINITE to wait
 * infinitely.
 *
 * \return
 * Pointer to the acquired element, if successful. If failed, the return value
 * will be NULL.
 *
 * \remark
 * Besure to call \b OSConstQueue_PutElementToFilledQueue to release the buffer to
 * the queue.
 *
 * \see OSConstQueue_PutElementToFilledQueue
 *
 ******************************************************************************
 */
void *OSConstQueue_GetElementFromEmptyQueue(HANDLE hObject, DWORD dwTimeOut);

/*!
 ******************************************************************************
 * \brief
 * release an empty element from queue
 *
 * \param hObject
 * \a (i) the handle of this object
 *
 * \param pElement
 * \a (i) The pointer return from \b OSConstQueue_GetElementFromEmptyQueue to be released
 *
 * \retval S_OK
 * Release the empty element to the queue successful.
 *
 * \retval S_FAIL
 * Release the empty element to the queue failed.
 *
 * \remark
 * NONE
 *
 * \see OSVarQueue_GetConstElement
 *
 ******************************************************************************
 */
SCODE OSConstQueue_PutElementToFilledQueue(HANDLE hObject, void *pElement);

/*!
 ******************************************************************************
 * \brief
 * acquire an filled element from queue to process data
 *
 * \param hObject
 * \a (i) the handle of this object
 *
 * \param dwTimeOut
 * \a (i) Time out for getting a filled element. Set to INFINITE to wait
 * infinitely.
 *
 * \return
 * Pointer to the acquired element, if successful. If failed, the return value
 * will be NULL.
 *
 * \remark
 * Besure to call \b OSConstQueue_PutElementToEmptyQueue to release the buffer to
 * the queue.
 *
 * \see OSConstQueue_PutElementToEmptyQueue
 *
 ******************************************************************************
 */
void *OSConstQueue_GetElementFromFilledQueue(HANDLE hObject, DWORD dwTimeOut);

/*!
 ******************************************************************************
 * \brief
 * peek an filled element from queue to process data
 *
 * \param hObject
 * \a (i) the handle of this object
 *
 * \param pElement
 * \a (o) Pointer to receive the peeked element
 *
 * \retval S_OK
 * Peek element successful.
 *
 * \retval S_FAIL
 * Peek element failed.
 *
 * \remark
 * Do not need to call \b OSConstQueue_PutElementToEmptyQueue. And the data will
 * not be take off from the queue.
 *
 * \see OSConstQueue_GetElementFromFilledQueue
 *
 ******************************************************************************
 */
SCODE OSConstQueue_PeekElementFromFilledQueue(HANDLE hObject, void *pElement);

/*!
 ******************************************************************************
 * \brief
 * release a filled element from queue
 *
 * \param hObject
 * \a (i) the handle of this object
 *
 * \param pElement
 * \a (i) The pointer return from \b OSConstQueue_GetElementFromFilledQueue to be
 * released.
 *
 * \retval S_OK
 * Release the filled element to the queue successful.
 *
 * \retval S_FAIL
 * Release the filled element to the queue failed.
 *
 * \remark
 * NONE
 *
 * \see OSConstQueue_GetElementFromFilledQueue
 *
 ******************************************************************************
 */
SCODE OSConstQueue_PutElementToEmptyQueue(HANDLE hObject, void *pElement);

/*!
 ******************************************************************************
 * \brief
 * clear all the elements in the queue
 *
 * \param hObject
 * \a (i) the handle of this object
 *
 * \retval S_OK
 * Clear the elements in the queue successful.
 *
 * \retval S_FAIL
 * Clear the elements in the queue failed.
 *
 * \remark
 * Do not call this function while another thread is using the queue.
 *
 * \see OSConstQueue_GetElementFromFilledQueue
 * \see OSConstQueue_GetElementFromEmptyQueue
 * \see OSConstQueue_PutElementToEmptyQueue
 * \see OSConstQueue_PutElementToFilledQueue
 *
 ******************************************************************************
 */
SCODE OSConstQueue_ClearElement(HANDLE hObject);

/*! @} End of OSConstQueue group */

// The following functions are for copy-free variable size queue
/*! @defgroup OSVarQueue Variable Size Queue Object
 *  A copy-free variable size queue. Using this queue if you have variable size
 *  message or data larger than 16 bytes.
 *
 *  @{
 */
//

/*! Initial options for setting \b OSVarQueue object, if dwQueueSize is not zero,
 *  it will initialize with \a dwQueueSize else if will initialize with
 *  \a dwElementSize & \a dwElementNum */
typedef struct {
    /*! Buffer size for the queue in bytes, it zero it will using
     *  \a dwElementSize & \a dwElementNum instead */
    DWORD dwQueueSize;

    /*! number of elements */
    DWORD dwElementCount;

    /*! size of each element */
    DWORD dwElementSize;

    /*! Elements aligned at (2^dwAlignment) bytes */
    DWORD dwAlignment;
} TOSVarQueueInitOptions;

/*!
 ******************************************************************************
 * \brief
 * Create \b OSVarQueue object
 *
 * \param phObject
 * \a (o) Pointer to receive the instance's handle of this object
 *
 * \param pOptions
 * \a (i) Options to initialize \b OSVarQueue, please reference
 * \b TOSVarQueueOptions for detail settings.
 *
 * \retval S_OK
 * Create variable size queue successfully
 *
 * \retval S_FAIL
 * Create variable size queue failed
 *
 * \remark
 * Call this function before using this instance
 *
 * \see OSVarQueue_Release
 * \see TOSVarQueueInitOptions
 *
 ******************************************************************************
 */
SCODE OSVarQueue_Initial(HANDLE *phObject, TOSVarQueueInitOptions *pOptions);

/*!
 ******************************************************************************
 * \brief
 * Release \b OSVarQueue object
 *
 * \param phObject
 * \a (i/o) Pointer to the instance's handle of this object
 *
 * \retval S_OK
 * Release variable size queue successfully
 *
 * \retval S_FAIL
 * Release variable size queue failed
 *
 * \remark
 * NONE
 *
 * \see OSVarQueue_Initial
 *
 ******************************************************************************
 */
SCODE OSVarQueue_Release(HANDLE *phObject);

/*!
 ******************************************************************************
 * \brief
 * acquire an empty element from queue to fill data
 *
 * \param hObject
 * \a (i) the handle of this object
 *
 * \param dwLength
 * \a (i) size of element to acquire in bytes
 *
 * \return
 * Pointer to the acquired element, if successful. If failed, the return value
 * will be NULL.
 *
 * \remark
 * Besure to call \b OSVarQueue_PutElementToFilledQueue to release the buffer to the
 * queue.
 *
 * \see OSVarQueue_PutElementToFilledQueue
 *
 ******************************************************************************
 */
void *OSVarQueue_GetElementFromEmptyQueue(HANDLE hObject, DWORD dwLength);

/*!
 ******************************************************************************
 * \brief
 * acquire a filled element from queue to process data
 *
 * \param hObject
 * \a (i) the handle of this object
 *
 * \param *pdwLen
 * \a (o) a pointer tol receive the size of element in bytes
 *
 * \return
 * Pointer to the acquired element, if successful. If failed, the return value
 * will be NULL.
 *
 * \remark
 * Besure to call \b OSVarQueue_PutElementToEmptyQueue to release the buffer to
 * the queue.
 *
 * \see OSVarQueue_PutElementToEmptyQueue
 *
 ******************************************************************************
 */
void *OSVarQueue_GetElementFromFilledQueue(HANDLE hObject, DWORD *pdwLen);

/*!
 ******************************************************************************
 * \brief
 * release an empty element from queue
 *
 * \param hObject
 * \a (i) the handle of this object
 *
 * \param pElement
 * \a (i) The pointer return from \b OSVarQueue_GetElementFromEmptyQueue to be released
 *
 * \retval S_OK
 * Release the empty element to the queue successful.
 *
 * \retval S_FAIL
 * Release the empty element to the queue failed.
 *
 * \remark
 * NONE
 *
 * \see OSVarQueue_GetElementFromEmptyQueue
 *
 ******************************************************************************
 */
SCODE OSVarQueue_PutElementToFilledQueue(HANDLE hObject, void *pElement);

/*!
 ******************************************************************************
 * \brief
 * release a filled element from queue
 *
 * \param hObject
 * \a (i) the handle of this object
 *
 * \param pElement
 * \a (i) The pointer return from \b OSVarQueue_GetElementFromFilledQueue to be released
 *
 * \retval S_OK
 * Release the filled element to the queue successful.
 *
 * \retval S_FAIL
 * Release the filled element to the queue failed.
 *
 * \remark
 * NONE
 *
 * \see OSVarQueue_GetElementFromFilledQueue
 *
 ******************************************************************************
 */
SCODE OSVarQueue_PutElementToEmptyQueue(HANDLE hObject, void *pElement);

/*!
 ******************************************************************************
 * \brief
 * clear all the elements in the queue
 *
 * \param hObject
 * \a (i) the handle of this object
 *
 * \retval S_OK
 * Clear the elements in the queue successful.
 *
 * \retval S_FAIL
 * Clear the elements in the queue failed.
 *
 * \remark
 * Do not call this function while another thread is using the queue.
 *
 * \see OSVarQueue_GetElementFromFilledQueue
 * \see OSVarQueue_GetElementFromEmptyQueue
 * \see OSVarQueue_PutElementToEmptyQueue
 * \see OSVarQueue_PutElementToFilledQueue
 *
 ******************************************************************************
 */
SCODE OSVarQueue_ClearElement(HANDLE hObject);


// added by Bill, 2003/02/11
/*!
 ******************************************************************************
 * \brief
 * get number of empty elements in queue
 *
 * \param hObject
 * \a (i) the handle of this object
 *
 * \return
 * Number of empty elements in queue
 *
 * \see OSVarQueue_GetFilledQueueCount
 *
 ******************************************************************************
 */
DWORD OSVarQueue_GetEmptyQueueCount(HANDLE hObject);


// added by Bill, 2003/02/11
/*!
 ******************************************************************************
 * \brief
 * get number of filled elements in queue
 *
 * \param hObject
 * \a (i) the handle of this object
 *
 * \return
 * Number of filled elements in queue
 *
 * \see OSVarQueue_GetEmptyQueueCount
 *
 ******************************************************************************
 */
DWORD OSVarQueue_GetFilledQueueCount(HANDLE hObject);


/*! @} End of OSVarQueue group */

#ifdef __cplusplus
}
#endif

#endif
