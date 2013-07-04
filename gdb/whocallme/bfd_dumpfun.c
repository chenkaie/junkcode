/* bfd_dumpfun.c (GPL)
 *
 * Usage: ./bfd_dumpfun [binary]
 * Note: Dump functions infomation of ELF-binary with BFD Library.
 *     
 * by TimHsu(timhsu@info.sayya.org) 2004/03/31
 * Modified by Jim Huang <jserv.tw@gmail.com>, 2008/07/22
 *   - Bump bfd APIs and build fixes.
 */    

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*#include <bfd.h>*/
#include "bfd.h"

typedef struct function_table FUN_TABLE;

/* 宣告一個包含函式名稱和位址的結構 */
struct function_table {
	char name[80];
	unsigned long addr;
};

static FUN_TABLE *fun_table;
static int table_count = 0;   /* 函式個數 */

static int compare_function(const void *a, const void *b)
{
	FUN_TABLE *aa = (FUN_TABLE *) a, *bb = (FUN_TABLE *) b;
	if (aa->addr > bb->addr)
		return 1;
	else if (aa->addr < bb->addr)
		return -1;
	return 0;  
}

/* 增加一個函式資料至對照表 */
static void add_function_table(char *name, unsigned long address)
{
	strncpy(fun_table[table_count].name, name, 80);
	fun_table[table_count].addr = address;
	table_count++;  
}

static void dump_function_table(void)
{
	int i;
	for (i = 0; i < table_count; i++) {
		printf("%-30s 0x%x\n",
		       fun_table[i].name, fun_table[i].addr);
	}
}

int main(int argc, char *argv[])
{
	bfd *abfd;
	asection *text;
	long storage_needed;
	asymbol **symbol_table;
	long number_of_symbols;
	long i;
	char **matching;
	sec_ptr section;
	char *symbol_name;
	long symbol_offset, section_vma, symbol_address;

	if (argc < 2) 
		return 0;
	printf("Open %s\n", argv[1]);
	bfd_init();
	abfd = bfd_openr(argv[1],NULL);
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
	if ((storage_needed = bfd_get_symtab_upper_bound(abfd)) < 0)
		return -1;
	symbol_table = (asymbol **) xmalloc(storage_needed);
	number_of_symbols = bfd_canonicalize_symtab(abfd, symbol_table);
	if (number_of_symbols < 0)
		return -1;
	fun_table = (FUN_TABLE **)malloc(sizeof(FUN_TABLE)*number_of_symbols);
	bzero(fun_table, sizeof(FUN_TABLE)*number_of_symbols);

	for (i = 0; i < number_of_symbols; i++) {
		if (symbol_table[i]->flags & (BSF_FUNCTION|BSF_GLOBAL)) {
			section = symbol_table[i]->section;
			section_vma = bfd_get_section_vma(abfd, section);
			symbol_name = symbol_table[i]->name;
			symbol_offset = symbol_table[i]->value;
			symbol_address = section_vma + symbol_offset;
			if (section->flags & SEC_CODE) {
				add_function_table(symbol_name,
				                   symbol_address);
			}
		}
	}
	bfd_close(abfd);
	/* 將函式對照表作排序 */
	qsort(fun_table, table_count, sizeof(FUN_TABLE), compare_function);
	dump_function_table();
}
