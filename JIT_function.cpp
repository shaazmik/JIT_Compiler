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



void x86bin_code_con(FILE* ass, x86bin_code* x86struct)
{
   assert(x86struct != nullptr);

   x86struct->x86_code_address  = (int*)calloc(Addr_array_capacity, sizeof(int));
   x86struct->PSL_code_address  = (int*)calloc(Addr_array_capacity, sizeof(int));
   x86struct->number_of_ip      = 0;
   
   x86struct->step = 0;

   fscanf(ass,"%d", &(x86struct->PSL_size));

   x86struct->PSL_code = (char*)calloc(x86struct->PSL_size, sizeof(char));

   fread(x86struct->PSL_code, sizeof(char), x86struct->PSL_size, ass);

   x86struct->capacity  = x86struct->PSL_size * Max_x86_cmd_size;
   x86struct->x86_code  = (char*)aligned_alloc(4096, x86struct->capacity);
}

int find_ip(int* PSL_code_address, int cur_ip, int number_of_ip)
{
   int cell = 0;

   while ((PSL_code_address[cell] != cur_ip))
   {
      cell++;
   }

   return cell;
}

void print_x86_file(char* x86_code, int capacity)
{
   FILE* x86_file = fopen("x86_file.bin", "wb");

   if (!x86_file)
   {
      fprintf(stderr, "Can't be opened file x86_file.bin\n");
   }

   int i = 0;

   while ((*(x86_code + i) != (char)0xC3) && (i < capacity))
   {
      fprintf(x86_file, "%c", *(x86_code + i));
      i++;
   }

   if (*(x86_code + i) != (char)0xC3)
   {
      fprintf(stderr, "END OF FILE NOT FOUND i = %d capacity = %d\n", i, capacity);
   }
   else
   {
      fprintf(x86_file, "%c", (char)0xC3);
   }

   fclose(x86_file);
}