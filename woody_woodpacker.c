#include "includes/woody_woodpacker.h"

typedef enum {
    ELF_H,
    PROGRMAM_H,
    SECTION_H
} HeaderType;

void e_header_handling(Elf64_Ehdr *e_header, FILE *f) {
    reading_handling(e_header, sizeof(Elf64_Ehdr), f, 0);
    print_e_header(e_header);
}

void p_header_handling(Elf64_Ehdr *e_header, Elf64_Phdr *p_header, FILE *f) {
    for (int i=0; i < (*e_header).e_phnum; i++) {
        reading_handling(p_header, sizeof(Elf64_Phdr), f, i);
        print_p_header(p_header, i);
    }
}

void s_header_handling(Elf64_Ehdr *e_header, Elf64_Shdr *s_header, FILE *f) {
    for (int i=0; i < (*e_header).e_shnum; i++) {
        reading_handling(s_header, sizeof(Elf64_Shdr), f, i);
        print_s_header(s_header, i);
    }
}

int main(int argc, char **argv) {

    FILE        *f;
    Elf64_Ehdr  e_header; 
    Elf64_Phdr  p_header;
    Elf64_Shdr  s_header;
    unsigned char e_ident[EI_NIDENT];
    size_t bytes_read;

    if (argc != MIN_ARGUMENTS_REQUIRED) {
        error_handling(ERROR_STARTING_MSG);
    }

    f = fopen(ELFILE, "rb");
    if (!f) { 
        error_handling(ERROR_OPENING_MSG); 
    }

    bytes_read = fread(e_ident, 1, EI_NIDENT, f);
    if (bytes_read == EI_NIDENT) {
        if (e_ident[EI_CLASS] == ELFCLASS32) {
            printf("32");
        } else if (e_ident[EI_CLASS] == ELFCLASS64) {
            printf("64");
        } else {
            error_handling("Stop");
        }
    }
    
    exit(0);


    e_header_handling(&e_header, f);
    p_header_handling(&e_header, &p_header, f);
    s_header_handling(&e_header, &s_header, f);


    
    return EXIT_SUCCESS;
}