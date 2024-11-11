# woody_woodpacker
A logical follow-up project on nm/otools that is designed to modify the headers of a ELF64 file. The goal here is to add a chunk of code and hide a non-stripped part of a file.

ELF File Format (64-bit)
The ELF (Executable and Linkable Format) file 64-bit format is a standard file format for executable files, object files, shared libraries, and core dumps on 64-bit Linux and Unix-like systems. It is used to store compiled code and metadata necessary for linking and execution.

ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, not stripped

Questo output del comando file ci dice che sample.c è stato compilato in un eseguibile ELF a 64 bit, per architettura x86-64, con endianess Little Endian. È un eseguibile dinamicamente collegato che richiede librerie condivise, specificatamente /lib64/ld-linux-x86-64.so.2, e può essere eseguito su un sistema con kernel Linux 2.6.32 o superiore. Inoltre, non è stato "stripped", quindi contiene ancora informazioni utili per il debugging.

Key Components
ELF Header: The first 52 bytes of the file, containing information about the file format, architecture, and other metadata.
Program Headers: A table describing the layout of the file’s segments and memory regions.
Section Headers: A table describing the file’s sections, including their contents, sizes, and offsets.
Sections: Contiguous chunks of data or code, such as .text, .data, .bss, etc.
Symbol Table: A table of symbols (functions, variables, etc.) and their addresses.
ELF File 64 Structure
The ELF file 64-bit format consists of:

ELF header (64 bytes)
Program headers (variable length)
Section headers (variable length)
Sections (variable length)
Symbol table (variable length)

Key Fields
e_type: File type (e.g., executable, shared object, core dump)
e_machine: Architecture (e.g., x86-64)
e_version: ELF version number
p_type: Program header type (e.g., loadable segment, allocation)
p_offset: Offset of the program header in the file
p_vaddr: Virtual address of the program header
st_name: Symbol table index
st_value: Symbol value (address)
st_size: Symbol size

ELF Binary Header Structure
The ELF (Executable and Linkable Format) binary header is the first 52 bytes of an ELF file, containing essential information about the file’s structure and contents. Here’s a breakdown of the ELF header fields, as described in the OSDev Wiki:

Magic number (0-3): 0x7F followed by the ASCII string “ELF” (4 bytes).
Class (4): 0x01 for 32-bit, 0x02 for 64-bit ELF.
Data encoding (5): 0x01 for little-endian, 0x02 for big-endian.
ELF version (6): 0x01 for version 1.
OS/ABI (7): usually 0x00 for System V.
Unused/padding (8-15): reserved bytes.
Type (16-17): identifies the file type (e.g., executable, shared library).
Machine (18-19): specifies the architecture (e.g., x86, ARM).
ELF Version (20-23): version number.
Entry point (24-31): offset to the program’s entry point.
Program header table offset (32-39): offset to the program header table.
Section header table offset (40-47): offset to the section header table.
Flags (48-51): architecture-dependent flags (e.g., relocation, symbol table).
ELF Header size (52): size of the ELF header in bytes.

