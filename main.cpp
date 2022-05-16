#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <./CPU_emulator/enum.h>
#include <./CPU_emulator/libr/Stack.h>


typedef struct x86bin_code
{
   char* x86code;
   char* PSL_code;

   size_t PSL_size;
   size_t capacity;


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

int main()
{
   FILE* binary_file = fopen("./CPU_emulator/assembler.bin", "rb");

   if (!check_PSL_file(binary_file))
   {
      return 1;
   }

   return 0;
}