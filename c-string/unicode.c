#include <stdio.h>
#include <locale.h>

int main(void)
{
	if (!setlocale(LC_CTYPE, "")) {
		fprintf(stderr, "Error:Please check LANG, LC_CTYPE, LC_ALL.\n");
		return 1;
	}

	wchar_t *str1=L"Hi!你好"; // 輸出結果 (範例)
	printf("str1=%ls\n", str1); // str1=Hi!你好
	printf("wcslen(str1)=%d\n", wcslen(str1)); // wcslen(str1)=5
	printf("wcschr(str1,%lc)=%d\n", L'好', wcschr(str1, L'好')); // wcschr(str1,好)=4206648
	printf("wcswcs(str1,%ls)=%d\n", L"你好", wcsstr(str1, L"你好")); // wcswcs(str1,你好)=4206646
	printf("wcsspn(str1,aeiou)=%d\n", wcsspn(str1, L"aeiou")); // wcsspn(str1,aeiou)=0
	printf("wcsspn(str1,EFGH)=%d\n", wcsspn(str1, L"EFGH")); // wcsspn(str1,EFGH)=1
	printf("address(str1)=%p\n", str1); // address(str1)=00403030
	printf("wcssbrk(str1,aeiou)=%p\n", wcspbrk(str1, L"aeiou")); // wcssbrk(str1,aeiou)=00403032
	wchar_t str2[20];
	wcscpy(str2, str1);
	printf("str2=%ls\n", str2); // str2=Hi!你好
	printf("wcscmp(str1,str2)=%d\n", wcscmp(str1, str2)); // wcscmp(str1,str2)=0
	wcscat(str2, L",我是John");
	printf("str2=%ls\n", str2); // str2=Hi!你好,我是John
	return 0;
}
