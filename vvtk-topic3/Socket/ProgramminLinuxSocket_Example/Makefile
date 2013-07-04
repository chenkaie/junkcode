#---------------------------------------------------------------------
# #  Copyright (c) 2000-2008 Vivotek Inc. All rights reserved.
#
#  +-----------------------------------------------------------------+
#  | THIS SOFTWARE IS FURNISHED UNDER A LICENSE AND MAY ONLY BE USED |
#  | AND COPIED IN ACCORDANCE WITH THE TERMS AND CONDITIONS OF SUCH  |
#  | A LICENSE AND WITH THE INCLUSION OF THE THIS COPY RIGHT NOTICE. |
#  | THIS SOFTWARE OR ANY OTHER COPIES OF THIS SOFTWARE MAY NOT BE   |
#  | PROVIDED OR OTHERWISE MADE AVAILABLE TO ANY OTHER PERSON. THE   |
#  | OWNERSHIP AND TITLE OF THIS SOFTWARE IS NOT TRANSFERRED.        |
#  |                                                                 |
#  | THE INFORMATION IN THIS SOFTWARE IS SUBJECT TO CHANGE WITHOUT   |
#  | ANY PRIOR NOTICE AND SHOULD NOT BE CONSTRUED AS A COMMITMENT BY |
#  | VIVOTEK INC.                                                    |
#  +-----------------------------------------------------------------+
#
#  Project name         :   jpegapp
#  Module name          :   jpeglib
#  Module description   :   get the width and height of image from buffer
#  Author               :   Kent Chen
#  Created at           :   2008/03/31
#  $ History: $
#
#---------------------------------------------------------------------

######################################################################
# Toolchains
######################################################################

# CROSS_COMPILE = arm-elf-
CROSS_COMPILE = 

CC      = $(CROSS_COMPILE)gcc
AS      = $(CROSS_COMPILE)as
AR      = $(CROSS_COMPILE)ar
LD      = $(CROSS_COMPILE)ld
NM      = $(CROSS_COMPILE)nm
RM      = rm -f
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump


########################################################################
# project management
########################################################################

#flag
#CFLAGS  = -O3 -Wall -ansi -g
CFLAGS  = -Wall -ansi -pedantic -Wextra -std=c99
AFLAGS  = 
LDFLAGS =

#project name
PROJECT = 

#path
SRC_PATH  = .
#OBJ_PATH  = obj
#INC_PATH  = inc
#LIB_PATH  = ../lib

#C_FILES = jpegapp.c
#O_FILES = $(C_FILES:.c=.o)
#A_FILES = jpeglib.a

#LINK_O  = $(addprefix $(OBJ_PATH)/, $(O_FILES))
#LINK_A  = $(addprefix $(LIB_PATH)/, $(A_FILES))

all: tcpserver tcpclient

tcpserver : TcpEchoServer.c
	$(CC) $(CFLAGS) -o TcpEchoServer.out TcpEchoServer.c

tcpclient : TcpEchoClient.c
	$(CC) $(CFLAGS) -o TcpEchoClient.out TcpEchoClient.c
	
udpserver : UdpEchoServer.c
	$(CC) $(CFLAGS) -o UdpEchoServer.out UdpEchoServer.c

udpclient : UdpEchoClient.c
	$(CC) $(CFLAGS) -o UdpEchoClient.out UdpEchoClient.c
clean :
	$(RM) TcpEchoClient.out TcpEchoServer.out UdpEchoServer.out UdpEchoClient.out

.PHONY:all clean install
