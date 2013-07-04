hello.c: 
	此為source code
hello.cpp:
	此為前置處理器處理完後的檔案(將檔頭含入)
	可以用gcc -E hello.c -o hello.cpp產生
hello.o:
	此為目的檔(object file)
	可以用gcc -c hello.c -o hello.o產生
	如果想跳過前置處理的步驟(直接由hello.cpp產生hello.o)，
	可以用gcc -x cpp-output -c hello.cpp -o hello.o
hello.s:
	此用assembly code
	可以用gcc -S hello.c -o hello.s產生
