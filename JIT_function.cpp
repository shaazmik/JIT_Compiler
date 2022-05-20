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
   x86struct->x86_size          = 0;
   x86struct->step              = 0;

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

void print_x86_file(char* x86_code, int x86_size)
{
   FILE* x86_file = fopen("x86_file.bin", "wb");

   if (!x86_file)
   {
      fprintf(stderr, "Can't be opened file x86_file.bin\n");
   }


   for (int i = 0; i < x86_size; i++ )
   {
      fprintf(x86_file, "%c", *(x86_code + i));
   }

   if (*(x86_code + x86_size - 1) != (char)0xC3)
   {
      fprintf(stderr, "END OF FILE NOT FOUND size = %d\n", x86_size);
   }

   fclose(x86_file);
}

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

int p_sqrt(int value)
{
   int result = round(sqrt(value));

   return result;
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

void push_sqrt_addr(char* x86_code)
{
   assert (x86_code != nullptr);

   *(unsigned long*)(x86_code) = (unsigned long)p_sqrt;
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