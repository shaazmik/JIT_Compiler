#ifndef JIT_DEFFEND
#define JIT_DEFFEND

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include "./Assembler_PSL/enum.h"
#include "./Assembler_PSL/libr/Stack.h"


#define PRINT_CMD_HLT                                \
   *(x86struct->x86_code + ip_x86++) = char(0xC3);   \
   (++ip_PSL);                                       \


#define SAVE_RAX                                    \
   *(x86struct->x86_code + ip_x86++) = (char)0x49;  \
   *(x86struct->x86_code + ip_x86++) = (char)0x89;  \
   *(x86struct->x86_code + ip_x86++) = (char)0xC4;  \


#define SAVE_RDX                                   \
   *(x86struct->x86_code + ip_x86++) = (char)0x49; \
   *(x86struct->x86_code + ip_x86++) = (char)0x89; \
   *(x86struct->x86_code + ip_x86++) = (char)0xD5; \


#define SAVE_RCX                                   \
   *(x86struct->x86_code + ip_x86++) = (char)0x49; \
   *(x86struct->x86_code + ip_x86++) = (char)0x89; \
   *(x86struct->x86_code + ip_x86++) = (char)0xDE; \


#define SAVE_RBX                                   \
   *(x86struct->x86_code + ip_x86++) = (char)0x49; \
   *(x86struct->x86_code + ip_x86++) = (char)0x89; \
   *(x86struct->x86_code + ip_x86++) = (char)0xCF; \

#define RET_RAX                                    \
   *(x86struct->x86_code + ip_x86++) = (char)0x4C; \
   *(x86struct->x86_code + ip_x86++) = (char)0x89; \
   *(x86struct->x86_code + ip_x86++) = (char)0xE0; \


#define RET_RDX                                     \
   *(x86struct->x86_code + ip_x86++) = (char)0x4C;  \
   *(x86struct->x86_code + ip_x86++) = (char)0x89;  \
   *(x86struct->x86_code + ip_x86++) = (char)0xEA;  \


#define RET_RCX                                    \
   *(x86struct->x86_code + ip_x86++) = (char)0x4C; \
   *(x86struct->x86_code + ip_x86++) = (char)0x89; \
   *(x86struct->x86_code + ip_x86++) = (char)0xF3; \


#define RET_RBX                                    \
   *(x86struct->x86_code + ip_x86++) = (char)0x49; \
   *(x86struct->x86_code + ip_x86++) = (char)0x89; \
   *(x86struct->x86_code + ip_x86++) = (char)0xF9; \


#define SAVE_RSP                                   \
   *(x86struct->x86_code + ip_x86++) = (char)0x55; \
   *(x86struct->x86_code + ip_x86++) = (char)0x48; \
   *(x86struct->x86_code + ip_x86++) = (char)0x89; \
   *(x86struct->x86_code + ip_x86++) = (char)0xE5; \


const int Page_size           = 4096;
const int Max_x86_cmd_size    = 100; // if something went wrong, resize more
const int Addr_array_capacity = 100;


typedef struct x86bin_code
{
   char* x86_code;
   char* PSL_code;

   int PSL_size = 0;
   size_t capacity = 0;

   int  number_of_adress;
   int* x86_code_adress ;
   int* PSL_code_adress ;

}x86bin_code;


int check_PSL_file(FILE* PSL);

void x86bin_code_con(FILE* ass, x86bin_code* x86struct);

int compile(x86bin_code* x86struct);

#endif