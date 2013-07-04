process.c:
	呼叫getpid()取得該行程的process id
shell1.c:
	利用fork產生一個新的子行程，然後用execlp讓產生的子行程去執行新的工作，
	此為一簡單的shell程式
