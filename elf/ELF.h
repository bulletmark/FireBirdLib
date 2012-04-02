#ifndef __ELFH__
#define __ELFH__

#define EI_NIDENT     16
#define Elf32_Half    unsigned short
#define Elf32_Word    unsigned long
#define Elf32_Addr    unsigned long
#define Elf32_Off     unsigned long

#define SHT_NULL      0
#define SHT_PROGBITS  1
#define SHT_SYMTAB    2
#define SHT_STRTAB    3
#define SHT_RELA      4
#define SHT_HASH      5
#define SHT_DYNAMIC   6
#define SHT_NOTE      7
#define SHT_NOBITS    8
#define SHT_REL       9
#define SHT_SHLIB    10
#define SHT_DYNSYM   11

#define STB_GLOBAL    1
#define STT_FUNC      2

#define bool          int
#define true          1
#define false         0

typedef struct
{
  unsigned char   e_ident[EI_NIDENT];
  Elf32_Half      e_type;
  Elf32_Half      e_machine;
  Elf32_Word      e_version;
  Elf32_Addr      e_entry;
  Elf32_Off       e_phoff;
  Elf32_Off       e_shoff;
  Elf32_Word      e_flags;
  Elf32_Half      e_ehsize;
  Elf32_Half      e_phentsize;
  Elf32_Half      e_phnum;
  Elf32_Half      e_shentsize;
  Elf32_Half      e_shnum;
  Elf32_Half      e_shtrndx;
} Elf32_Ehdr;

typedef struct
{
  Elf32_Word      sh_name;
  Elf32_Word      sh_type;
  Elf32_Word      sh_flags;
  Elf32_Addr      sh_addr;
  Elf32_Off       sh_offset;
  Elf32_Word      sh_size;
  Elf32_Word      sh_link;
  Elf32_Word      sh_info;
  Elf32_Word      sh_addralign;
  Elf32_Word      sh_entsize;
} Elf32_Shdr;

typedef struct
{
  Elf32_Word      p_type;
  Elf32_Off       p_offset;
  Elf32_Addr      p_vaddr;
  Elf32_Addr      p_paddr;
  Elf32_Word      p_filesz;
  Elf32_Word      p_memsz;
  Elf32_Word      p_flags;
  Elf32_Word      p_align;
} Elf32_Phdr;

typedef struct
{
  Elf32_Word      st_name;
  Elf32_Addr      st_value;
  Elf32_Word      st_size;
  unsigned char   st_info;
  unsigned char   st_other;
  Elf32_Half      st_shndx;
} Elf32_Sym;

#endif
