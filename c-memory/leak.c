/*
 * setenv MALLOC_TRACE  /home/karthik/temp/trace.txt // 設定 mtrace 的環境變數 MALLOC_TRACE
 * $ gcc -g -Wall -ansi -pedantic leak.c -o leak.o   // 編譯
 * $ ./leak                                          // 執行
 * $ mtrace leak.o /home/karthik/temp/trace.txt      // 追蹤記憶體漏洞
 * Memory not freed:
 * -----------------
 *    Address     Size     Caller
 * 0x08049910      0x4  at /home/karthik/tips/leak.c:9
 * 
 */
#include <stdlib.h>
#include <mcheck.h> // mtrace header

int main() {
	int *a;
	mtrace();
	a = malloc(sizeof(int));
	*a = 7;
	// Forget to free()
	return EXIT_SUCCESS;
}
