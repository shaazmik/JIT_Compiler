#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./Assembler_PSL/enum.h"
#include "./Assembler_PSL/libr/Stack.h"


typedef struct x86bin_code
{
   char* x86code;
   char* PSL_code;

   size_t PSL_size = 0;
   size_t capacity = 0;


}x86bin_code;

int check_PSL_file(FILE* PSL)
{
   char sign[5] = {}; 

   fscanf(PSL, "%c%c%c%c", &sign[0], &sign[1], &sign[2], &sign[3]);

   sign[4] = '\0';

   if (strcmp(sign, "SHZ!") != 0) 
   {
      fprintf(stderr, "Wrong signature of file!\n");
      return 0;
   }   

   char version = '\0';

   fscanf(PSL, "%c", &version);

   if (version != Version_of_programm) 
   {
      fprintf(stderr, "You have the new version, swap assembler file\n");
      return 0;
   }

   return 1;
}

int x86bin_code_con(x86bin_code* x86bin_code, size_t capacity)
{

}


int x86bin_code_dec(x86bin_code* x86bin_code)
{

}


void input_code_from_file(FILE* ass, x86bin_code* x86code)
{
   fscanf(ass,"%d", &(x86code->PSL_size));

  // printf("%d", CPPU->len_of_code);

   x86code->PSL_code = (char*)calloc(x86code->PSL_size, sizeof(char));

   fread(x86code->PSL_code, sizeof(char), x86code->PSL_size, ass);
}

int main()
{
   FILE* binary_file = fopen("./Assembler_PSL/assembler.bin", "rb");

   if (!check_PSL_file(binary_file))
   {
      return 1;
   }

   x86bin_code x86code = {};

   input_code_from_file(binary_file, &x86code);

   

   return 0;
}