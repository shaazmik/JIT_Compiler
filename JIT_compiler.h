#ifndef JIT_PROTECTION
#define JIT_PROTECTION

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include "./Assembler_PSL/enum.h"
#include "./Assembler_PSL/libr/Stack.h"


#include "./JIT_DSL.h"

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