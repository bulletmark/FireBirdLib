#ifndef FBLIB_ELF_H
#define FBLIB_ELF_H

  #include              <string.h>
  #include              <sys/types.h>
  #include              <sys/stat.h>
  #include              <fcntl.h>
  #include              <unistd.h>
  #include              "ELF.h"
  #include              "libFireBird.h"

  extern int            fTAP;
  extern Elf32_Ehdr    *ELFHeader;       //The ELF file header
  extern Elf32_Shdr    *SectionHeaders;  //Array of all section headers
  extern char          *shstrtab;        //Section header string table (a list of the names of the sections)
  extern char          *strtab;          //String table section
  extern Elf32_Sym     *symtab;          //Symbol table section

#endif
