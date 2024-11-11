#ifndef WOODY_WOODPACKER_H
#define WOODY_WOODPACKER_H

#define ELFILE (argv[1])
#define MIN_ARGUMENTS_REQUIRED 2
#define ERROR_STARTING_MSG "Failed to fetch ELF file"
#define ERROR_OPENING_MSG "Failed to open ELF file"
#define ERROR_READING_MSG "Failed to read ELF file"

#define PRINT_HDR(header, type, index)

#include <stdlib.h>
#include <stdio.h>
#include <elf.h>

void error_handling(char *e) {
    perror(e);
    exit(EXIT_FAILURE);
}

void e_handling();
void p_handling();
void s_handling();

void print_e_header(Elf64_Ehdr *elf_header) {
    printf("ELF Header:\n");
    printf("  Magic:   %.4s\n", (*elf_header).e_ident);
    printf("  Class:                             %u\n", (*elf_header).e_ident[EI_CLASS]);
    printf("  Data:                              %u\n", (*elf_header).e_ident[EI_DATA]);
    printf("  Version:                           %u\n", (*elf_header).e_ident[EI_VERSION]);
    printf("  OS/ABI:                            %u\n", (*elf_header).e_ident[EI_OSABI]);
    printf("  ABI Version:                       %u\n", (*elf_header).e_ident[EI_ABIVERSION]);
    printf("  Type:                              %u\n", (*elf_header).e_type);
    printf("  Machine:                           %u\n", (*elf_header).e_machine);
    printf("  Version:                           0x%x\n", (*elf_header).e_version);
    printf("  Entry point address:               0x%lx\n", (*elf_header).e_entry);
    printf("  Start of program headers:          %lu (bytes into file)\n", (*elf_header).e_phoff);
    printf("  Start of section headers:          %lu (bytes into file)\n", (*elf_header).e_shoff);
    printf("  Flags:                             0x%x\n", (*elf_header).e_flags);
    printf("  Size of this header:               %u (bytes)\n", (*elf_header).e_ehsize);
    printf("  Size of program headers:           %u (bytes)\n", (*elf_header).e_phentsize);
    printf("  Number of program headers:         %u\n", (*elf_header).e_phnum);
    printf("  Size of section headers:           %u (bytes)\n", (*elf_header).e_shentsize);
    printf("  Number of section headers:         %u\n", (*elf_header).e_shnum);
    printf("  Section header string table index: %u\n", (*elf_header).e_shstrndx);
    printf("\n");
}

void print_p_header(Elf64_Phdr *program_header, int i) {
    printf("Program Header \033[93m%d\033[0m:\n", i);
    printf("  Type:             %u\n", (*program_header).p_type);
    printf("  Flags:            0x%x\n", (*program_header).p_flags);
    printf("  Offset:           0x%lx\n", (*program_header).p_offset);
    printf("  Virtual Address:  0x%lx\n", (*program_header).p_vaddr);
    printf("  Physical Address: 0x%lx\n", (*program_header).p_paddr);
    printf("  File Size:        0x%lx\n", (*program_header).p_filesz);
    printf("  Memory Size:      0x%lx\n", (*program_header).p_memsz);
    printf("  Align:            0x%lx\n", (*program_header).p_align);
    printf("\n");
}

void print_s_header(Elf64_Shdr *section_header, int i) {
    printf("Section \033[93m%d\033[0m:\n", i);
    printf("  Name Offset:      %u\n", (*section_header).sh_name);
    printf("  Type:             %u\n", (*section_header).sh_type);
    printf("  Flags:            0x%lx\n", (*section_header).sh_flags);
    printf("  Address:          0x%lx\n", (*section_header).sh_addr);
    printf("  Offset:           0x%lx\n", (*section_header).sh_offset);
    printf("  Size:             0x%lx\n", (*section_header).sh_size);
    printf("  Link:             %u\n", (*section_header).sh_link);
    printf("  Info:             %u\n", (*section_header).sh_info);
    printf("  Address Align:    0x%lx\n", (*section_header).sh_addralign);
    printf("  Entry Size:       0x%lx\n", (*section_header).sh_entsize);
    printf("\n");
}

void reading_handling(void *header, size_t nmemb, FILE *f, int i) {
    size_t     bytes_read;

    bytes_read = fread(header, 1, nmemb, f);
    printf("Bytes read for header %d: \033[34m%zu\033[0m\n", i, bytes_read);
    if (bytes_read != nmemb) {
        fclose(f);
        error_handling(ERROR_READING_MSG);
    }
}

#endif