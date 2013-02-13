#include              <stdlib.h>
#include              <string.h>
#include              <stdio.h>
#include              <ctype.h>
#include              <ELF.h>

#define VERSION       "V1.2"

char *BadWords[] = {"calloc",   "chdir",     "chmod",    "chown",    "close",
		    "closedir", "create",    "dlclose",  "dlerror",  "dlopen",
		    "dlsym",    "dup",       "dupioctl", "environ",  "execl",
		    "execle",   "execlp",    "execv",    "execve",   "execvp",
		    "fchdir",   "fchmod",    "fchown",   "fclose",   "fdopen",
		    "fflush",   "fileno",    "fopen",    "fork",     "fprintf",
		    "fread",    "free",      "freopen",  "fwrite",   "getcwd",
		    "getenv",   "getgid",    "getgrp",   "getpid",   "gets",
		    "getuid",   "ioctl",     "kill",     "killpg",   "lchown",
		    "listen",   "lstat",     "malloc",   "mkdir",    "mkfifo",
		    "mknod",    "mkstemp",   "mktemp",   "mktime",   "mlock",
		    "mlockall", "mmap",      "open",     "opendir",  "pipe",
		    "poll",     "popen",     "pread",    "pselect",  "read",
		    "readdir",  "readlink",  "realloc",  "recv",     "recvfrom",
		    "recvmsg",  "remove",    "rename",   "rewind",   "rewinddir",
		    "rmdir",    "select",    "socket",   "symlink",  "tmpfile",
		    "tmpnam",   "truncate",  "unlink",   "utime",    "vfork",
		    "write",    ""};

void Cleanup(char *Message);

FILE                 *fTAP = NULL;
Elf32_Ehdr           *ELFHeader = NULL;       //The ELF file header
Elf32_Shdr           *SectionHeaders = NULL;  //Array of all section headers
char                 *shstrtab = NULL;        //Section header string table (a list of the names of the sections)
char                 *strtab = NULL;          //String table section
Elf32_Sym            *symtab = NULL;          //Symbol table section
char                 *Hits = NULL;            //A list of all bad words found in the TAP

void Cleanup(char *Message)
{
  if(Message)
  {
    printf("JailBreak: %s", Message);
  }

  if(fTAP)
  {
    fclose(fTAP);
    fTAP = NULL;
  }

  if(ELFHeader)
  {
    free(ELFHeader);
    ELFHeader = NULL;
  }

  if(SectionHeaders)
  {
    free(SectionHeaders);
    SectionHeaders = NULL;
  }

  if(shstrtab)
  {
    free(shstrtab);
    shstrtab = NULL;
  }

  if(strtab)
  {
    free(strtab);
    strtab = NULL;
  }

  if(Hits)
  {
    free(Hits);
    Hits = NULL;
  }
}

int main(int argc, char *argv[])
{
  Elf32_Shdr           *pshstrtabSH = NULL;   //Shortcut to speed up access to the .shstrtab section header
  Elf32_Shdr           *pstrtabSH = NULL;     //Shortcut to speed up access to the .strtab section header
  Elf32_Shdr           *psymtabSH = NULL;     //Shortcut to speed up access to the .symtab section header
  Elf32_Sym            *psymtab = NULL;       //Shortcut to speed up access to the .symtab section
  int                   i, j;                 //Counter
  char                 *c;                    //Used for the conversion to upper case

  if(argc != 2)
  {
    printf("JailBreak  " VERSION "\n");
    printf("Copyright (c)2009 by FireBird\n\n");
    printf("Usage: JailBreak <filename.tap>\n\n");
    return 2;
  }

  //Count the string length of all bad words to reserve enough space
  i = 0;
  j = 0;
  while(BadWords[j])
  {
    i += (strlen(BadWords[j]) + 2); //add space and comma
    j++;
  }
  Hits = malloc(i + 5); //Add another 5 characters. Who knows... :-)
  if (!Hits)
  {
    Cleanup("Failed to reserve memory for the result information\n");
    return 1;
  }
  memset(Hits, 0, i + 5);

  //Open the TAP
  if(!(fTAP = fopen(argv[1], "rb+")))
  {
    printf("Failed to open '%s'\n", argv[1]);
    Cleanup(NULL);
    return 1;
  }

  //Read the ELF header. It contains some details about the section headers
  if(!(ELFHeader = malloc(sizeof(Elf32_Ehdr))))
  {
    Cleanup("Failed to reserve memory for the ELF header\n");
    return 1;
  }

  if(fread(ELFHeader, sizeof(Elf32_Ehdr), 1, fTAP) != 1)
  {
    Cleanup("Failed to read the ELF header\n");
    return 1;
  }

  //TODO: Check if this is a valid ELF header

  if(ELFHeader->e_shnum == 0)
  {
    Cleanup("Number of sections in ELF header is 0\n");
    return 1;
  }

  //Read all section headers
  if(!(SectionHeaders = malloc(ELFHeader->e_shnum * sizeof(Elf32_Shdr))))
  {
    Cleanup("Failed to allocate memory for the section headers\n");
    return 1;
  }

  if(fseek(fTAP, ELFHeader->e_shoff, SEEK_SET))
  {
    Cleanup("Failed to seek to the section headers\n");
    return 1;
  }

  if(fread(SectionHeaders, ELFHeader->e_shnum * sizeof(Elf32_Shdr), 1, fTAP) != 1)
  {
    Cleanup("Failed to read the section headers\n");
    return 1;
  }

  //Read the .shstrtab section. It contains a "string database" with the names of all sections
  if(ELFHeader->e_shtrndx >= ELFHeader->e_shnum)
  {
    Cleanup("Invalid shstrtab index\n");
    return 1;
  }

  pshstrtabSH = &SectionHeaders[ELFHeader->e_shtrndx];
  if(pshstrtabSH->sh_type != SHT_STRTAB)
  {
    Cleanup(".shstrtab index doesn't point to a string table\n");
    return 1;
  }

  if(!(shstrtab = malloc(pshstrtabSH->sh_size)))
  {
    Cleanup("Failed to allocate memory for the .shstrtab section\n");
    return 1;
  }

  if(fseek(fTAP, pshstrtabSH->sh_offset, SEEK_SET))
  {
    Cleanup("Failed to seek to the .shstrtab section\n");
    return 1;
  }

  if(fread(shstrtab, pshstrtabSH->sh_size, 1, fTAP) != 1)
  {
    Cleanup("Failed to read the .shstrtab section\n");
    return 1;
  }

  //Loop through all section headers and locate .strtab
  for(i = 1; i < ELFHeader->e_shnum; i++)
  {
    pstrtabSH = &SectionHeaders[i];
    if(pstrtabSH->sh_type == SHT_STRTAB && !strcmp(&shstrtab[pstrtabSH->sh_name], ".strtab"))
    {
      //Read .strtab. It contains the "string database"
      if(pstrtabSH->sh_type != SHT_STRTAB)
      {
        Cleanup(".strtab is not marked as a string table\n");
        return 1;
      }

      if(!(strtab = malloc(pstrtabSH->sh_size)))
      {
        Cleanup("Failed to allocate memory for the .strtab section\n");
        return 1;
      }

      if(fseek(fTAP, pstrtabSH->sh_offset, SEEK_SET))
      {
        Cleanup("Failed to seek to the .strtab section\n");
        return 1;
      }

      if(fread(strtab, pstrtabSH->sh_size, 1, fTAP) != 1)
      {
        Cleanup("Failed to read the .strtab section\n");
        return 1;
      }

      //Loop through all section headers and locate .symtab
      //We may reuse variable i as we'll never reach the outer loop again
      for(i = 1; i < ELFHeader->e_shnum; i++)
      {
        psymtabSH = &SectionHeaders[i];
        if(psymtabSH->sh_type == SHT_SYMTAB &&
           psymtabSH->sh_entsize == sizeof(Elf32_Sym))
        {
          //Read .symbtab. It contains all symbols (variable names, function names, external functions)
          if(!(symtab = malloc(psymtabSH->sh_size)))
          {
            Cleanup("Failed to allocate memory for the .symtab section\n");
            return 1;
          }

          if(fseek(fTAP, psymtabSH->sh_offset, SEEK_SET))
          {
            Cleanup("Failed to seek to the .symtab section\n");
            return 1;
          }

          if(fread(symtab, psymtabSH->sh_size, 1, fTAP) != 1)
          {
            Cleanup("Failed to read the .symtab section\n");
            return 1;
          }

          //Loop through all symtab entries and check if there is a bad one
          //And again, no need to take care about the counter variable
          for(i = 0; i < (int)(psymtabSH->sh_size / psymtabSH->sh_entsize); i++)
          {
            psymtab = &symtab[i];
            if (psymtab->st_shndx == 0 &&
                (psymtab->st_info >> 4) == STB_GLOBAL &&
                (psymtab->st_info & 0x0f) == STT_FUNC)
            {
              j = 0;
              while(BadWords[j])
              {
                if(!strcmp(BadWords[j], &strtab[psymtab->st_name]))
                {
                  //Hit! Add it to the result string
                  if(strlen(Hits) != 0) strcat(Hits, ", ");
                  strcat(Hits, &strtab[psymtab->st_name]);

                  //Convert string to upper case
                  c = &strtab[psymtab->st_name];
                  while(*c)
                  {
                    *c = toupper(*c);
                    c++;
                  }
                }
                j++;
              }
            }
          }

          //We're done. If Hits != "", we've found at least one entry
          if(strlen(Hits))
          {
            //Save the modified .strtab
            if(fseek(fTAP, pstrtabSH->sh_offset, SEEK_SET))
            {
              Cleanup("Failed to seek to the .strtab section for writing back\n");
              return 1;
            }

            if(fwrite(strtab, pstrtabSH->sh_size, 1, fTAP) != 1)
            {
              Cleanup("Failed to write back the modified .strtab section\n");
              return 1;
            }
            strcat(Hits, "\n");
            Cleanup(Hits);
            Cleanup("Successfully patched!\n");
          }
          else
          {
            Cleanup("Jail break not necessary.\n");
          }

          return 0;
        }
      }
      Cleanup("Didn't find the .symtab section\n");
      return 1;
    }
  }


  Cleanup("Didn't find the .strtab section\n");
  return 1;
}
