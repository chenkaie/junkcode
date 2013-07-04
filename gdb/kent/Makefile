all:
	$(info "===== Building All ====")
	gcc -g -fno-omit-frame-pointer -o max_crypt max_crypt.c -lcrypt
	gcc -g -fno-omit-frame-pointer -o dump1 dump1.c
	gcc -g -fno-omit-frame-pointer -o ptr1 ptr1.c
	gcc -g -fno-omit-frame-pointer -o backtrace backtrace.c
	gcc -g -fno-omit-frame-pointer ibm_divide_zero.c -o ibm_divide_zero
	gcc -g -fno-omit-frame-pointer thread.c -o thread -lpthread 
	gcc -g -fno-omit-frame-pointer memorylayout.c -o memorylayout
	$(info "==== Stop Here ====")

clean:
	$(info "Clean All")
	rm -f ptr1 max_crypt dump1 backtrace ibm_divide_zero thread
