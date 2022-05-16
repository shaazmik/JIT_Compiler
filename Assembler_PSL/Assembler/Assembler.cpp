#include "./Assembler.h"




#define DEF_CMD_(number, name, argc, code_func)                                                                     \
        if (strcmp(cmd, #name) == 0)                                                                                \
        {                                                                                                           \
            machine->code[ip++] = CMD_##name;                                                                       \
                                                                                                                    \
            for (int i = 0; i < argc; i++)                                                                          \
            {                                                                                                       \
                check_var = check_RAM(line_cmd);                                                                    \
                                                                                                                    \
                if (check_var != WRONG_ARGUMENT)                                                                    \
                {                                                                                                   \
                    if (i == 0)                                                                                     \
                    {                                                                                               \
                        machine->code[ip - 1] = CMD_##name + 0x02;                                                  \
                    }                                                                                               \
                    *(type_array*)(machine->code + ip) = check_var;                                                 \
                    ip += sizeof(type_array);                                                                       \
                    line_cmd = next_argument(line_cmd);                                                             \
                }                                                                                                   \
                else                                                                                                \
                {                                                                                                   \
                    check_var = check_register(line_cmd);                                                           \
                                                                                                                    \
                    if (check_var != WRONG_ARGUMENT)                                                                \
                    {                                                                                               \
                        if (i == 0)                                                                                 \
                        {                                                                                           \
                            machine->code[ip - 1] = CMD_##name + 0x01;                                              \
                        }                                                                                           \
                        machine->code[ip++] = check_var;                                                            \
                        line_cmd = next_argument(line_cmd);                                                         \
                    }                                                                                               \
                    else                                                                                            \
                    {                                                                                               \
                        if (sscanf(line_cmd, type_array_format, &arg_var) != 0)                                     \
                        {                                                                                           \
                            *(type_array*)(machine->code + ip) = arg_var;                                           \
                            ip += sizeof(type_array);                                                               \
                            line_cmd = next_argument(line_cmd);                                                     \
                        }                                                                                           \
                        else                                                                                        \
                        {                                                                                           \
                            check_var = hash_jmp_pointer(line_cmd);                                                 \
                            if (check_var != WRONG_ARGUMENT)                                                        \
                            {                                                                                       \
                                if (i == 0)                                                                         \
                                {                                                                                   \
                                    machine->code[ip - 1] = CMD_##name + 0x03;                                      \
                                }                                                                                   \
                                hash_ip = find_hash_name(&(machine->cmd_pointer), check_var);                       \
                                *(int*)(machine->code + ip) = hash_ip;                                              \
                                ip += sizeof(int);                                                                  \
                                line_cmd = next_argument(line_cmd);                                                 \
                            }                                                                                       \
                            else                                                                                    \
                            {                                                                                       \
                                printf("Wrong argument of command!\n\n");                                           \
                                return WRONG_ARGUMENT;                                                              \
                            }                                                                                       \
                        }                                                                                           \
                    }                                                                                               \
                }                                                                                                   \
            }                                                                                                       \
        }                                                                                                           \
        else                                                                                                        \




int compilation(struct Text* text_struct, struct asm_file* machine)
{
    assert(text_struct != nullptr);
    assert(machine != nullptr);
    
    char cmd[100] = "";
    char* line_cmd = nullptr;

    size_t count_of_space = 0;
    int len_cmd = 0;

    uint32_t check_var = 0;
    type_array arg_var = 0;

    int hash_ip = 0;
    int ip = 0;

    for (int j = 0; j < text_struct->quantity_lines; j++)
    {
        line_cmd = text_struct->linii[j].start_line;

        get_line_cmd(cmd, line_cmd);

        check_var = hash_jmp_pointer(cmd);   //7c96fd0e

        if (check_var != WRONG_ARGUMENT)
        {
            insert_hash_name( &(machine->cmd_pointer), check_var, ip);
        }
        else
        {                        
            len_cmd = strlen(cmd);

            sscanf(line_cmd, " %ln", &count_of_space);

            line_cmd += count_of_space + len_cmd;

            line_cmd = next_argument(line_cmd);

            //#define DEF_CMD_...

            #include "../Commands.h" 

            #undef DEF_CMD_ 

            /*else*/ printf( "Error! Wrong command on %d line\n", j + 1 );
        }

    }

    machine->len_of_code = ip;

    return EXIT;
}


int main()
{
    FILE* cmd = fopen("../fac.txt", "rb");

    if (cmd == nullptr) 
    {
        printf("Wrong name of file\n");
        return EXIT;
    }

    struct Text text_struct = {};

    input_struct(cmd, &text_struct);

    fclose(cmd);

    navigation_for_comment(&text_struct);

    struct asm_file machine_code = {};

    input_machine_struct(&machine_code, &text_struct);

    compilation(&text_struct, &machine_code);

    compilation(&text_struct, &machine_code);

    if (check_hash_name_struct( &(machine_code.cmd_pointer) ) == EXIT )
        return EXIT;

    FILE* ass = fopen("../assembler.bin", "wb");

    write_machine_code(&machine_code, ass); 

    fclose(ass);

    free_memory(&text_struct);

    free_asm_struct(&machine_code);

    printf("Gotcha!\n");

    return EXIT;    
}
