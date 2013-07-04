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
PROJECT = jpeglib

#path
SRC_PATH  = .
OBJ_PATH  = obj
INC_PATH  = inc
LIB_PATH  = ../lib

C_FILES = FileToBinaryStream.c jpeginfo_width_height.c jpeginfo_component_number.c
O_FILES = $(C_FILES:.c=.o)
STATIC_LIB = lib$(PROJECT)-static.a
#A_FILES = 

LINK_O  = $(addprefix $(OBJ_PATH)/, $(O_FILES))
#LINK_A  = $(addprefix $(LIB_PATH)/, $(A_FILES))

all:
	make $(STATIC_LIB)

$(STATIC_LIB) : $(O_FILES)
	@if (test ! -d $(LIB_PATH)); then \
	    mkdir $(LIB_PATH); \
	fi
	@if (test -f $(STATIC_LIB)); then \
	    $(RM) $(STATIC_LIB); \
	fi
	$(AR) rcs $(LIB_PATH)/$(STATIC_LIB) $(LINK_O) 

%.o : $(SRC_PATH)/%.c
	$(CC) $(CFLAGS) -c -o $(OBJ_PATH)/$@ $<

clean :
	$(RM) $(OBJ_PATH)/*.*
	$(RM) $(STATIC_LIB)

print :
	@echo print test
	@echo $(O_FILES)

.PHONY:all clean install test cleantest
