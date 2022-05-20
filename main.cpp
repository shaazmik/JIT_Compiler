#define $  fprintf(stderr, "\n%d\n", __LINE__);
#define $$ fprintf(stderr, "\nbag\n");

#include "./JIT_compiler.h"
#include <ctime>




int main()
{
   FILE* binary_file = fopen("./Assembler_PSL/assembler.bin", "rb");

   if (!check_PSL_file(binary_file))
   {
      return 1;
   }

   x86bin_code x86struct = {};
   x86bin_code_con(binary_file, &x86struct);

   fclose(binary_file);

   COMPILE;

   print_x86_file(x86struct.x86_code, x86struct.x86_size);   

   void (*prog) (void) = (void(*) (void)) x86struct.x86_code;

   u_int64_t time_start = clock();

   LAUNCH_PROGRAM;

   u_int64_t time_end  = clock();
    
   fprintf(stderr, "The program lasted = %f seconds\n", ((float)(time_end - time_start)) / CLOCKS_PER_SEC);

   return 0;
}