#ifndef PROTECTION_DLL
#define PROTECTION_DLL

#define PRINT_CMD_HLT                                                  \
   *(x86struct->PSL_code_address + x86struct->number_of_ip) = ip_PSL;  \
   *(x86struct->x86_code_address + x86struct->number_of_ip) = ip_x86;  \
   x86struct->number_of_ip++;                                          \
   *(x86struct->x86_code + ip_x86++) = char(0xC3);                     \
   (++ip_PSL);                                                         \


#define SAVE_RAX                                    \
   *(x86struct->x86_code + ip_x86++) = (char)0x49;  \
   *(x86struct->x86_code + ip_x86++) = (char)0x89;  \
   *(x86struct->x86_code + ip_x86++) = (char)0xC4;  \


#define SAVE_RDX                                   \
   *(x86struct->x86_code + ip_x86++) = (char)0x49; \
   *(x86struct->x86_code + ip_x86++) = (char)0x89; \
   *(x86struct->x86_code + ip_x86++) = (char)0xD5; \


#define SAVE_RCX                                   \
   *(x86struct->x86_code + ip_x86++) = (char)0x49; \
   *(x86struct->x86_code + ip_x86++) = (char)0x89; \
   *(x86struct->x86_code + ip_x86++) = (char)0xDE; \


#define SAVE_RBX                                   \
   *(x86struct->x86_code + ip_x86++) = (char)0x49; \
   *(x86struct->x86_code + ip_x86++) = (char)0x89; \
   *(x86struct->x86_code + ip_x86++) = (char)0xCF; \

#define RET_RAX                                    \
   *(x86struct->x86_code + ip_x86++) = (char)0x4C; \
   *(x86struct->x86_code + ip_x86++) = (char)0x89; \
   *(x86struct->x86_code + ip_x86++) = (char)0xE0; \


#define RET_RDX                                     \
   *(x86struct->x86_code + ip_x86++) = (char)0x4C;  \
   *(x86struct->x86_code + ip_x86++) = (char)0x89;  \
   *(x86struct->x86_code + ip_x86++) = (char)0xEA;  \


#define RET_RCX                                    \
   *(x86struct->x86_code + ip_x86++) = (char)0x4C; \
   *(x86struct->x86_code + ip_x86++) = (char)0x89; \
   *(x86struct->x86_code + ip_x86++) = (char)0xF3; \


#define RET_RBX                                    \
   *(x86struct->x86_code + ip_x86++) = (char)0x49; \
   *(x86struct->x86_code + ip_x86++) = (char)0x89; \
   *(x86struct->x86_code + ip_x86++) = (char)0xF9; \


#define SAVE_RSP                                   \
   *(x86struct->x86_code + ip_x86++) = (char)0x55; \
   *(x86struct->x86_code + ip_x86++) = (char)0x48; \
   *(x86struct->x86_code + ip_x86++) = (char)0x89; \
   *(x86struct->x86_code + ip_x86++) = (char)0xE5; \


#define PUT_IP                                                         \
   *(x86struct->PSL_code_address + x86struct->number_of_ip) = ip_PSL;  \
   *(x86struct->x86_code_address + x86struct->number_of_ip) = ip_x86;  \
   x86struct->number_of_ip++;                                          \
   

#define COMPILE            \
   compile(&x86struct);    \
   x86struct.step++;       \
   compile(&x86struct);    \
   
   
#define PUSH_RDI                                      \
   *(x86struct->x86_code + ip_x86++) = (char)(0x57);  \


#define POP_RDI                                        \
   *(x86struct->x86_code + ip_x86++) = (char)(0x5F);   \


#define PUSH_RSI                                       \
   *(x86struct->x86_code + ip_x86++) = (char)(0x5E);   \


#define POP_RSI                                        \
   *(x86struct->x86_code + ip_x86++) = (char)(0x5E);   \


#define CMP_RDI_RSI                                    \
   *(x86struct->x86_code + ip_x86++) = (char)(0x48);   \
   *(x86struct->x86_code + ip_x86++) = (char)(0x39);   \
   *(x86struct->x86_code + ip_x86++) = (char)(0xF7);   \



#define LAUNCH_PROGRAM                                                        \
   asm("push rbx\n\t push r12\n\t push r13\n\t push r14\n\t push r15\n\t");   \
   prog();                                                                    \
   asm("pop r15\n\t pop r14\n\t pop r13\n\t pop r12\n\t pop rbx\n\t");        \


#define PUSH_RAX                                      \
   *(x86struct->x86_code + ip_x86++) = (char)0x50;    \


#define MOV_R10                                       \
   *(x86struct->x86_code + ip_x86++) = (char)(0x41);  \
   *(x86struct->x86_code + ip_x86++) = (char)(0xBA);  \


#define CALL_R10                                     \
   *(x86struct->x86_code + ip_x86++) = (char)(0x41); \
   *(x86struct->x86_code + ip_x86++) = (char)(0xFF); \
   *(x86struct->x86_code + ip_x86++) = (char)(0xD2); \



#define STACK_ALIGNMENT_16                              \
   *(x86struct->x86_code + ip_x86++) = (char)0x48;      \
   *(x86struct->x86_code + ip_x86++) = (char)0x83;      \
   *(x86struct->x86_code + ip_x86++) = (char)0xE4;      \
   *(x86struct->x86_code + ip_x86++) = (char)0xF0;      \


#define RETURN_RSP                                    \
   *(x86struct->x86_code + ip_x86++) = (char)0x48;    \
   *(x86struct->x86_code + ip_x86++) = (char)0x89;    \
   *(x86struct->x86_code + ip_x86++) = (char)0xEC;    \
   *(x86struct->x86_code + ip_x86++) = (char)0x5D;    \




#endif