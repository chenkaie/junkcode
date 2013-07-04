test.c:
	請先看test.c的程式碼，注意裡面#ifdef #else #endif等directives
	然後將test.c編譯(gcc -o test test.c)後執行看看結果
	再用指令gcc -o test test.c -DHAVE_MMAP編譯一次，再次執行看結果
	有什麼不同	
test2.c:
	此source code會用到test.h這個header檔，但是該檔案與test2.c並不
	在同一目錄，因此直接下gcc test2.c 會得到找不到test.h的錯誤訊息
	解決方法為告知gcc在哪裡可以找到該header檔，請試看看下列指令
	gcc -o test2 test2.c -I include/
test3.c:
	此source code除了用到test.h這個header檔外，還用到一個稱為test()
	的函示，其中test()函示在lib/libtest.a中，因此我們必須告訴gcc要連
	結libtest，因此我們可以下 gcc -o test3 test3.c -I include/ -ltest
	最後的-ltest就是告訴gcc跟libtest做連結，但是執行後gcc卻說找不到
	libtest，因此跟找不到header檔一樣，我們必須告訴gcc哪裡可以找到
	libtest.a，因此完整的指令如下：
	gcc -o test3 test3.c -I include/ -L lib/ -ltest

