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

#ifndef	_JPEGINFO_H_
#define	_JPEGINFO_H_

#ifndef NDEBUG
    #define DBG_PRINT(fmt, ...) printf("%s:%d: " fmt, __FILE__, __LINE__, __VA_ARGS__)
    //Usage: DBG_PRINT("%d: %s: %s\n", conf_num, conf_name[conf_num], conf_value[conf_num]);
#else
    #define DBG_PRINT(fmt, ...) 
#endif

// readded for backward compatiable
#if !defined(__wtypes_h__) && !defined(_SCODE_)
#define _SCODE_
    typedef int SCODE;
#endif

#ifndef S_OK
#define S_OK                           ((SCODE)  0)
#endif
#ifndef S_FAIL
#define S_FAIL                         ((SCODE) -1)
#endif

typedef struct
{
    unsigned int uiWidth;
    unsigned int uiHeight;
    unsigned int uiCmpNum;
} TJPEGInfo;

/*!
 *********************************************************************
 * \brief
 * Get the width and height of a jpeg file.
 *
 * \param pTobject
 * \a (o) Structure pointer to receive the width&height of the input file
 *
 * \param pcFilename
 * \a (i) the filename including path of jpeg file
 *
 * \retval S_OK
 * Initialize \b Module OK.
 * \retval S_FAIL
 * Initialize \b Module failed.
 *
 * \remark
 *  *
 * \see See also to other functions
 * FileToBinaryStream()
 *
 ******************************************************************** 
 */
SCODE GetJPEGWidthHeight (const char* pcFilename, TJPEGInfo* pTobject);


/*!
 *********************************************************************
 * \brief
 * Get the numbers of component  of a jpeg file.
 *
 * \param pTobject
 * \a (o) Structure pointer to receive the component number of the input file
 *
 * \param pcFilename
 * \a (i) the filename including path of jpeg file
 *
 * \retval S_OK
 * Initialize \b Module OK.
 * \retval S_FAIL
 * Initialize \b Module failed.
 *
 * \remark
 *  *
 * \see See also to other functions
 * FileToBinaryStream()
 *
 ******************************************************************** 
 */
SCODE GetJPEGCmpNum (const char* pcFilename, TJPEGInfo* pTobject);


/*!
 *********************************************************************
 * \brief
 * transform the input file to binary stream
 *
 * \param pcBuffer
 * \a (o) buffer to store the transformed binary stream for later use
 *
 * \param pcFilename
 * \a (i) the filename including path of jpeg file
 *
 * \retval S_OK
 * Initialize \b Module OK.
 * \retval S_FAIL
 * Initialize \b Module failed.
 *
 * \remark
 *  *
 * \see See also to other functions
 * 
 *
 ******************************************************************** 
 */
SCODE FileToBinaryStream (const char* pcFilename, unsigned char** pcBuffer);

#endif //_JPEGINFO_H_
