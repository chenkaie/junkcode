/* whocallme.c (GPL)
 *
 * A runtime backtrace of function. 
 * 
 * by Timhsu(timhsu@chroot.org) 2004/03/31
 * Modified by Jim Huang <jserv.tw@gmail.com>, 2008/07/22
 *   - Bump bfd APIs.
 *   - Eliminate compiler errors.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*#include <bfd.h>*/
#include "bfd.h"
#include "whocallme.h"

/* forward declarations */
char *find_function_by_addr(unsigned long addr);

typedef struct function_table FUN_TABLE;
/* 宣告一個包含函式名稱和位址的結構 */
struct function_table {
	char name[FUNCTION_NAME_MAXLEN];
  	unsigned long addr;
};

static FUN_TABLE *fun_table;
static int table_count = 0;	/* 函式個數 */

static int compare_function(const void *a, const void *b)
{
        FUN_TABLE *aa = (FUN_TABLE *) a;
        FUN_TABLE *bb = (FUN_TABLE *) b;
	if (aa->addr > bb->addr)
		return 1;
	else if (aa->addr < bb->addr)
		return -1;
	return 0;
}

/* 增加一個函式資料至對照表 */
static void add_function_table(char *name, unsigned long address)
{
	strncpy(fun_table[table_count].name, name, FUNCTION_NAME_MAXLEN);
	fun_table[table_count].addr = address;
	table_count++;
}

/* 取得目前正在執行的函式名稱 */
char * who_am_i(void)
{
        unsigned long *stack;   \
	asm ("movl %%ebp, %0\n"  \
		: "=g"(stack));         
	return find_function_by_addr(*(stack + 1));
}

/* 依照位址取得函式名稱 */
char *find_function_by_addr(unsigned long addr)
{
	int i;
	for (i = 0; i < table_count; i++) {
		if (addr > fun_table[i].addr) {
			if (addr < fun_table[i + 1].addr)
				return fun_table[i].name;
		}
	}
	return NULL;
}

/* 初始化函式對照表 */
int init_function_table(char *file)
{
	bfd *abfd;
	long storage_needed;
	asymbol **symbol_table;
	long number_of_symbols;
	long i;
	char **matching;
	sec_ptr section;
	char *symbol_name;
	long symbol_offset, section_vma, symbol_address;

	bfd_init();
	abfd = bfd_openr(file, NULL);
	if (abfd == (bfd *) 0) {
		bfd_perror("bfd_openr");
		return -1;
	}
	if (!bfd_check_format_matches(abfd, bfd_object, &matching)) {
		return -1;
	}	
	if (!(bfd_get_file_flags (abfd) & HAS_SYMS)) {
		printf("ERROR flag!\n");
		return -1;
	}
	/* 取得符號表大小 */
	storage_needed = bfd_get_symtab_upper_bound(abfd);
	if (storage_needed < 0)
		return -1;
	symbol_table = (asymbol **) malloc(storage_needed);
	/* 將符號表讀進所配置的記憶體裡(symbol_table), 並傳回符號表個數 */
	number_of_symbols = bfd_canonicalize_symtab(abfd, symbol_table);
	if (number_of_symbols < 0)
		return -1;
	/* 配置空間給函式對照表 */
	fun_table = (FUN_TABLE *) malloc(sizeof(FUN_TABLE) * number_of_symbols);
	bzero(fun_table, sizeof(FUN_TABLE)*number_of_symbols);
		
	for (i = 0; i < number_of_symbols; i++) {
		/* 檢查此符號是否為函式 */
		if (symbol_table[i]->flags & (BSF_FUNCTION|BSF_GLOBAL)) {
			/* 反查此函式所處的區段(section) 及區段位址(section_vma)*/
			section = symbol_table[i]->section;
			section_vma = bfd_get_section_vma(abfd, section);
			/* 取得此函式的名稱(symbol_name), 偏移位址(symbol_offset) */
			
			symbol_name = (char *) symbol_table[i]->name;
			symbol_offset = symbol_table[i]->value;
			/* 將此函式的偏移位址加上區段位址，則為此函式
			 * 在執行時的記憶體位址 (symbol_address) */
			symbol_address = section_vma + symbol_offset;
			/* 檢查此函式是否處在程式本文區段 */
			if (section->flags & SEC_CODE) {
				/* 將此函式名稱和位址加入至對照表 */
				add_function_table(symbol_name, 
						   symbol_address);
			}
		}
	}
	free(symbol_table);
	bfd_close(abfd);
	/* 將函式對照表作排序 */
	qsort(fun_table, table_count, sizeof(FUN_TABLE), compare_function);
	return 0;
}
