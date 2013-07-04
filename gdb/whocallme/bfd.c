#include <stdio.h>
#include "bfd.h"

int main(int argc, char *argv[])
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
	/* 取得符號表大小 */
	storage_needed = bfd_get_symtab_upper_bound(abfd);
	if (storage_needed < 0)
		return -1;
	symbol_table = (asymbol **) xmalloc(storage_needed);
	/* 將符號表讀進所配置的記憶體裡(symbol_table), 並傳回符號表個數 */
	number_of_symbols = bfd_canonicalize_symtab(abfd, symbol_table);
	if (number_of_symbols < 0)
		return -1;
	for (i = 0; i < number_of_symbols; i++) {
		/* 檢查此符號是否為函式 */
		if (symbol_table[i]->flags & (BSF_FUNCTION|BSF_GLOBAL))	{
			/* 反查此函式所處的區段(section) 及
			                   區段位址(section_vma) */
			section = symbol_table[i]->section;
			section_vma = bfd_get_section_vma(abfd, section);
			/* 取得此函式的名稱(symbol_name)、
			               偏移位址(symbol_offset) */
			symbol_name = symbol_table[i]->name;
			symbol_offset = symbol_table[i]->value;
			/* 將此函式的偏移位址加上區段位址，則為此函式在執行時
			   的記憶體位址(symbol_address */
			symbol_address = section_vma + symbol_offset;
			/* 檢查此函式是否處在程式本文區段 */
			if (section->flags & SEC_CODE)
				printf("<%s> 0x%x 0x%x 0x%x\n",
				         symbol_name,  
				               section_vma,  
				                    symbol_offset,
				                         symbol_address);
		}
	}
	bfd_close(abfd);
}
