#ifndef JIT_DEFFEND
#define JIT_DEFFEND

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include "./Assembler_PSL/enum.h"
#include "./Assembler_PSL/libr/Stack.h"


#define PRINT_CMD_HLT                                                  \
   *(x86struct->PSL_code_address + x86struct->number_of_ip) = ip_PSL;  \
   *(x86struct->x86_code_address + x86struct->number_of_ip) = ip_x86;  \
   x86struct->number_of_ip++;                                          \
   *(x86struct->x86_code + ip_x86++) = char(0xC3);                     \
   (++ip_PSL);                                                         \


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


#define PUT_IP                                                         \
   *(x86struct->PSL_code_address + x86struct->number_of_ip) = ip_PSL;  \
   *(x86struct->x86_code_address + x86struct->number_of_ip) = ip_x86;  \
   x86struct->number_of_ip++;                                          \
   

#define COMPILE            \
   compile(&x86struct);    \
   x86struct.step++;       \
   compile(&x86struct);    \
   
   
#define PUSH_RDI                                      \
   *(x86struct->x86_code + ip_x86++) = (char)(0x57);  \


#define POP_RDI                                        \
   *(x86struct->x86_code + ip_x86++) = (char)(0x5F);   \


#define PUSH_RSI                                       \
   *(x86struct->x86_code + ip_x86++) = (char)(0x5E);   \


#define POP_RSI                                        \
   *(x86struct->x86_code + ip_x86++) = (char)(0x5E);   \


#define CMP_RDI_RSI                                    \
   *(x86struct->x86_code + ip_x86++) = (char)(0x48);   \
   *(x86struct->x86_code + ip_x86++) = (char)(0x39);   \
   *(x86struct->x86_code + ip_x86++) = (char)(0xF7);   \



#define LAUNCH_PROGRAM                                                        \
   asm("push rbx\n\t push r12\n\t push r13\n\t push r14\n\t push r15\n\t");   \
   prog();                                                                    \
   asm("pop r15\n\t pop r14\n\t pop r13\n\t pop r12\n\t pop rbx\n\t");        \




const int Page_size           = 4096;
const int Max_x86_cmd_size    = 100; // if something went wrong, resize more
const int Addr_array_capacity = 1000;


typedef struct x86bin_code
{
   char* x86_code;
   char* PSL_code;

   int PSL_size = 0;
   int x86_size = 0;
   size_t capacity = 0;

   int step = 0;

   int number_of_ip = 0;
   int* x86_code_address ;
   int* PSL_code_address ;

}x86bin_code;


int check_PSL_file(FILE* PSL);

void x86bin_code_con(FILE* ass, x86bin_code* x86struct);

int compile(x86bin_code* x86struct);

int find_ip(int* PSL_code_address, int cur_ip, int number_of_ip);

void print_x86_file(char* x86_code, int x86_size);

void show(int value);

int in(void);

int p_sqrt(int value);

void push_show_addr(char* x86_code);

void push_in_addr(char* x86_code);

void push_sqrt_addr(char* x86_code);


#endif