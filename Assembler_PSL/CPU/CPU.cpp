#include "./CPU.h"
#include <ctime>


int just_do_it(struct CPU* CPPU)
{
   int ip = 0;

   while (*(char*)(&CPPU->code[ip]) != CMD_HLT)
   {
      switch(CPPU->code[ip])
      {

         #define DEF_CMD_(number, name, arg, code_func)       \
            case CMD_##name:                                  \
               code_func;                                     \
               break;                                         \


         #include "../Commands.h"

         default:
            printf("Something went wrong\n");
            abort();
            break;
            
         #undef DEF_CMD_ 

      }
   }
   printf("Program is completed.\n\n");
   return 0;
}


int main()
{
   // system("mode con cols=100 lines=30");

   struct CPU CPPU = {};

   stack_constructor( &(CPPU.stk), Size_of_stack);

   stack_construct( &(CPPU.stk_back), Size_of_stack);

   FILE* ass = fopen("../assembler.bin", "rb");

   if  ( !check_asm_file(ass) ) 
   {
      stack_destructor( &(CPPU.stk) );
      stack_destructor( &(CPPU.stk_back) );
      return 0;
   }

   input_code_from_file(ass, &CPPU);

   fclose(ass);

   just_do_it(&CPPU);

   stack_destructor( &(CPPU.stk) );                                        
   stack_destructor( &(CPPU.stk_back) );

   u_int64_t time_end  = clock();
   fprintf(stderr, "The program lasted = %f seconds\n", ((float)time_end / CLOCKS_PER_SEC));   

   return 0;
}