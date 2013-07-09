#Simple Makefile for JunkCode
EXCEPT_FILE = 'chfd_linux|readdevstdin_list_authors|trace'
SINGLE_FILE_JUNKCODE = $(shell find . -maxdepth 1 -iname "*.c" -exec basename {} .c \; | grep -v -E $(EXCEPT_FILE))

all:
	@echo ======== make junk code under this folder ===========
	make $(SINGLE_FILE_JUNKCODE)

clean:
	rm $(SINGLE_FILE_JUNKCODE)
	find . -iname "*.out" -exec rm '{}' \;
	find . -iname "*.o" -exec rm '{}' \;
