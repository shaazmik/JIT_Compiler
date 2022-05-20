#define $  fprintf(stderr, "\n%d\n", __LINE__);
#define $$ fprintf(stderr, "\nbag\n");

#include "./JIT_compiler.h"
#include <ctime>


int compile(x86bin_code* x86struct)
{
   assert(x86struct != nullptr); 
   
   int ip_x86 = 0;
   int ip_PSL = 0;
   x86struct->number_of_ip = 0;

   while (*(x86struct->PSL_code + ip_PSL) != CMD_HLT)
   {
      switch(x86struct->PSL_code[ip_PSL])
      {

         #define DEF_CMD_(number, name, arg, code)            \
            case CMD_##name:                                  \
               code;                                          \
               break;                                         \


         #include "./Commands_JIT.h"

         default:
            printf("Something went wrong\n");
            fprintf(stderr, "%d\n", ip_PSL);
            abort();
            break;
            
         #undef DEF_CMD_ 

      }   
   }

   PRINT_CMD_HLT;

   x86struct->x86_size = ip_x86;

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