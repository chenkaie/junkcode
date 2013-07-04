/*
 * Copyright (C) 2003 www.jollen.org
 *
 * ELF programming. ver 0.5
 *
 * able to handle string table.
 *
 */
#include <stdio.h>
#include <unistd.h>
#include <elf.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int elf_ident(char *ident)
{
   if (*(ident+EI_MAG0) != ELFMAG0) return 0;
   if (*(ident+EI_MAG1) != ELFMAG1) return 0;
   if (*(ident+EI_MAG2) != ELFMAG2) return 0;
   if (*(ident+EI_MAG3) != ELFMAG3) return 0;

   return -1;
}

void parse_ident(char *ident)
{
   printf("ELF Identification\n");

   printf("  Class:	");
   switch (*(ident+EI_CLASS)) {
      case ELFCLASSNONE: printf("Invalid class\n"); break;
      case ELFCLASS32: printf("32-bit objects\n"); break;
      case ELFCLASS64: printf("64-bit objects\n"); break;
   }
}

void parse_machine(Elf32_Half machine)
{
   printf("Machine:	");
   switch (machine) {
      case EM_NONE: printf("No machine\n"); break;
      case EM_M32: printf("AT&T WE 32100\n"); break;
      case EM_SPARC: printf("SPARC\n"); break;
      case EM_386: printf("Intel 80386\n"); break;
      case EM_68K: printf("Motorola 68000\n"); break;
      case EM_88K: printf("Motorola 88000\n"); break;
      case EM_860: printf("Intel 80860\n"); break;
      case EM_MIPS: printf("MIPS RS3000 Big-Endian\n"); break;
       
      default: printf("Unknow\n");
   }
}

void parse_sections(Elf32_Ehdr *hdr, int fd)
{
   int i;
   Elf32_Shdr header_ent[100];
   Elf32_Shdr *sh_strtab;	/* point to section name string table header */
   char strtab[65535];		/* point to section name string table */

   /* file offset of section header table */
   lseek(fd, hdr->e_shoff, SEEK_SET);

   for (i = 0; i < hdr->e_shnum; i++) {
      read(fd, &header_ent[i], sizeof(Elf32_Shdr));

      /* load section name string table */
      if (i == hdr->e_shstrndx) {
         sh_strtab = &header_ent[i];
      }
   }

   lseek(fd, sh_strtab->sh_offset, SEEK_SET);
   read(fd, strtab, sh_strtab->sh_size);

   /* Index 0: undefined */
   printf("Name                Size FileOff\n");
   for (i = 1; i < hdr->e_shnum-1; i++) {
      printf("%-16s%8d%8d\n", 
             &strtab[header_ent[i].sh_name], header_ent[i].sh_size,
             header_ent[i].sh_offset);
   }
}

int main(int argc, char *argv[])
{
   int fd;
   Elf32_Ehdr f_header;

   if (argc != 2) {
      printf("Usage:	loader [filename]\n");
      return -1;
   }

   fd = open(argv[1], S_IRUSR);
   if (fd < 0) {
      printf("\nfile open error\n");
      return -1;
   }

   /* Read ELF Header */
   read(fd, &f_header, sizeof(Elf32_Ehdr));

   /* Parse header information */
   if (elf_ident(f_header.e_ident)) {
      parse_ident(f_header.e_ident);
      parse_machine(f_header.e_machine);
      parse_sections(&f_header, fd);
   } else {
      printf("not a ELF binary file\n");
   }

   close(fd);
}
