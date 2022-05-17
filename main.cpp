#define $ fprintf(stderr, "%d\n", __LINE__);

#include "./JIT_compiler.h"

int compile(x86bin_code* x86struct)
{
   assert(x86struct != nullptr);
   int ip_x86 = 0;
   int ip_PSL = 0;

   POP_R11;

   while (*(x86struct->PSL_code + ip_PSL) != CMD_HLT)
   {
      
   }

   // push("4153"); push r11

   if (mprotect(x86struct->x86_code, x86struct->capacity, PROT_EXEC | PROT_WRITE))
   {
      perror("Can't make mprotect\n");
      abort();
   }

   return 0;
}

int main()
{
   FILE* binary_file = fopen("./Assembler_PSL/assembler.bin", "rb");

   if (!check_PSL_file(binary_file))
   {
      return 1;
   }

   x86bin_code x86struct = {};
   input_PSL_from_file(binary_file, &x86struct);

   fclose(binary_file);

   create_buffer_x86(&x86struct);

   compile(&x86struct); // save return register

   // void (*prog) (void) = (void(*) (void)) x86struct.x86_code;
   
   // prog;
   
   $
   return 0;
}