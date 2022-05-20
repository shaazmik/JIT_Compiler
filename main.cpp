#define $  fprintf(stderr, "\n%d\n", __LINE__);
#define $$ fprintf(stderr, "\nbag\n");

#include "./JIT_compiler.h"


void show(int value)
{
   printf("%d\n", value);
}

int in(void)
{      
   int value = 0;

   scanf("%d", &value);
       
   return value;
}

void push_show_addr(char* x86_code)
{
   assert (x86_code != nullptr);

   *(unsigned long*)(x86_code) = (unsigned long)show;
}

void push_in_addr(char* x86_code)
{
   assert (x86_code != nullptr);

   *(unsigned long*)(x86_code) = (unsigned long)in;
}

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

   asm("push rbx\n\t"
       "push r12\n\t"
       "push r13\n\t"
       "push r14\n\t"
       "push r15\n\t");
   prog();
   asm("pop r15\n\t"
       "pop r14\n\t"
       "pop r13\n\t"
       "pop r12\n\t"
       "pop rbx\n\t");

   return 0;
}