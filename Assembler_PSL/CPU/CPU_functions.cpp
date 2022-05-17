#include "./CPU.h"

int check_asm_file(FILE* ass)
{
   char sign[5] = {}; 

   fscanf(ass, "%c%c%c%c", &sign[0], &sign[1], &sign[2], &sign[3]);

   sign[4] = '\0';

   if (strcmp(sign, "SHZ!") != 0) 
   {
      printf("Wrong signature of file!\n");
      return 0;
   }   

   char version = '\0';

   fscanf(ass, "%c", &version);

   if (version != Version_of_programm) 
   {
      printf("You have the new version, swap assembler file\n");
      return 0;
   }

   return 1;
}


void input_code_from_file(FILE* ass, struct CPU* CPPU)
{
   fscanf(ass,"%d", &(CPPU->len_of_code));

  // printf("%d", CPPU->len_of_code);

   CPPU->code = (char*)calloc(CPPU->len_of_code, sizeof(char));

   fread(CPPU->code, sizeof(char), CPPU->len_of_code, ass);
}


int srav(type_array arg1, type_array arg2)
{
   if ( fabs(arg1 - arg2)  <= Epsilon)
   {
      return OK;
   }
   else
   {
      return -1;
   }
}
