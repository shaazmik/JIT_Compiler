#ifndef JIT_DEFFEND
#define JIT_DEFFEND

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include "./Assembler_PSL/enum.h"
#include "./Assembler_PSL/libr/Stack.h"


#define POP_R11                                    \
   *(x86struct->x86_code + ip_x86) = (char)(0x41); \
   (ip_x86++);                                     \
   *(x86struct->x86_code + ip_x86) = (char)(0x5B); \
   (ip_x86++);                                     \



#define PUSH_R11                                   \
   *(x86struct->x86_code + ip_x86) = (char)(0x41); \
   (ip_x86++);                                     \
   *(x86struct->x86_code + ip_x86) = (char)(0x53); \
   (ip_x86++);                                     \


// pop 0x415F push 0x4157 --- r15  

const int Page_size    = 4096;
const int Max_x86_cmd_size = 5; // if something went wrong, resize more

typedef struct x86bin_code
{
   char* x86_code;
   char* PSL_code;

   int PSL_size = 0;
   size_t capacity = 0;


}x86bin_code;


int check_PSL_file(FILE* PSL);

void input_PSL_from_file(FILE* ass, x86bin_code* x86struct);

int create_buffer_x86(x86bin_code* x86struct);

#endif