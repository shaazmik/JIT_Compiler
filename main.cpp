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

   if (mprotect(x86struct->x86_code, x86struct->capacity, PROT_EXEC | PROT_WRITE))
   {
      perror("Can't make mprotect\n");
      abort();
   }

   return 0;
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

   compile(&x86struct); 

   print_x86_file(x86struct.x86_code, x86struct.capacity);   

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