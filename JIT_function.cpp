#include "./JIT_compiler.h"

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



void input_PSL_from_file(FILE* ass, x86bin_code* x86struct)
{
   assert(x86struct != nullptr);

   fscanf(ass,"%d", &(x86struct->PSL_size));

   x86struct->PSL_code = (char*)calloc(x86struct->PSL_size, sizeof(char));

   fread(x86struct->PSL_code, sizeof(char), x86struct->PSL_size, ass);
}

int create_buffer_x86(x86bin_code* x86struct)
{
   assert(x86struct != nullptr);

   x86struct->capacity  = x86struct->PSL_size * Max_x86_cmd_size;

   x86struct->x86_code  = (char*)aligned_alloc(4096, x86struct->capacity);

   return 0;
}