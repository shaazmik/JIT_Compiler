#include "./Assembler.h"


void input_machine_struct(struct asm_file* machine_code, struct Text* text_struct)
{
    machine_code->version = Version_of_programm;

    machine_code->len_of_code = text_struct->quantity_lines * Max_argc_cmd;

    machine_code->code = (char*)calloc(machine_code->len_of_code, sizeof(char));
}


void navigation_for_comment(struct Text* text_struct)
{
    assert(text_struct != nullptr);

    char* pointer_ne_start = text_struct->linii[0].start_line;
    

    for (int i = 0; i < text_struct->quantity_lines; i++)
    {
        if (strchr(text_struct->linii[i].start_line, ';') != nullptr)
        {
            pointer_ne_start = strchr(text_struct->linii[i].start_line, ';');
            *pointer_ne_start = '\0';
        }
    }
}


int len_name_of_command(char* str)
{
    assert(str != nullptr);

    char* pointer_end = strchr(str, ' ');

    size_t len_of_command = 0;

    if (pointer_end != nullptr) 
    {
        len_of_command =  (pointer_end - str);
    }
    else
    {
        pointer_end = strchr(str, '\0');
        len_of_command =  (pointer_end - str);
    }

    return len_of_command;
}



void get_line_cmd(char* str, char* start_line_of_command)
{       
    assert(str != nullptr);
    assert(start_line_of_command != nullptr);


    int len_command = 0;
    int count_of_space = 0;

    sscanf(start_line_of_command, " %n", &count_of_space);

    start_line_of_command += count_of_space;

    len_command = len_name_of_command(start_line_of_command);

    assert(len_command <= 100);

    strncpy(str, start_line_of_command, len_command);

    str[len_command] = '\0';
    
}



int hash_jmp_pointer(char* cmd)
{
    assert(cmd != nullptr);
    
    char* jmp_name = nullptr; 
    
    if (cmd[0] == ':')
    {
        jmp_name = cmd + 1;                       //  :rar
        char* jmp_name_end = strchr(cmd, ' ');

        if (jmp_name_end == nullptr)
        {
            jmp_name_end = strchr(cmd, '\0');
        }

        int len_jmp_name = jmp_name_end - jmp_name;

        return dl_new_hash(jmp_name, len_jmp_name);
    }

    return WRONG_ARGUMENT;
}


uint32_t dl_new_hash (const char* str, int len)
{
    uint32_t h = 5381;
    int i = 0;

    for (unsigned char c = *str; len > i; c = *++str) 
    {
        h = h * 33 + c;
        i++;
    }
    return h;
}



int insert_hash_name(struct hash_name* cmd_pointer, uint32_t arg_var, int ip)
{
    assert(cmd_pointer != nullptr);

    cmd_pointer->pointer_info[cmd_pointer->count_of_pointer].hash = arg_var;
    cmd_pointer->pointer_info[cmd_pointer->count_of_pointer].ip_cmd = ip;
    cmd_pointer->count_of_pointer++;

    return OK;
}


int find_hash_name(struct hash_name* cmd_pointer, uint32_t arg_var)
{
    assert(cmd_pointer != nullptr);

    for (int i = 0; i < cmd_pointer->count_of_pointer; i++)
    {
        if (cmd_pointer->pointer_info[i].hash == arg_var)
        {
            return cmd_pointer->pointer_info[i].ip_cmd;
        }
    }
    return -1;
}


char* next_argument(char* line_command)
{
    assert(line_command != nullptr);

    char* str = strchr(line_command, ' ');
    if (str == nullptr)
    {
        str = strchr(line_command, '\0');
        return(str);
    }

    int count_of_space = 0;

    sscanf(str, " %n", &count_of_space);

    return (str + count_of_space);
}


int check_register(char* start_of_line)
{
    assert(start_of_line != nullptr);

    char* end_of_line = strchr(start_of_line, ' ');

    if (end_of_line == nullptr)
    {
        end_of_line = strchr(start_of_line, '\0');
    }

    int len_of_arg = end_of_line - start_of_line + 1;
    char* arg_line = (char*)calloc(len_of_arg, sizeof(char));
    int arg = 0; 

    strncpy(arg_line, start_of_line, len_of_arg);  // ax_   ax\0 

    arg_line[len_of_arg - 1] = '\0';

    if (strcmp(arg_line, "ax") == 0)
    {
        arg = 0x00;
    }
    else
    {
        if (strcmp(arg_line, "bx") == 0)
        {
            arg = 0x01;
        }
        else
        {
            if (strcmp(arg_line, "cx") == 0)
            {
                arg = 0x02;
            }
            else 
            {
                if (strcmp(arg_line, "dx") == 0)
                {
                    arg = 0x03;
                }
                else
                {
                    arg = WRONG_ARGUMENT;
                }
            }
        }
    }
    return arg;
}

int check_RAM(char* start_of_line)
{
    assert(start_of_line != nullptr);

    char skobka = '0';
    type_array arg = 0;

    sscanf(start_of_line, "%c", &skobka);

    if (skobka != '[')
    {
        return WRONG_ARGUMENT;
    }
    else
    {
        char* end_of_line = strchr(start_of_line, ']');
        if (end_of_line == nullptr)
        {
            printf("Wrong argument! \n");
            return WRONG_ARGUMENT;
        }

        int len_of_arg = 0;

        len_of_arg =  end_of_line - start_of_line - 1;   //  [143] 
        char* arg_str = (char*)calloc(len_of_arg, sizeof(char));

        strncpy(arg_str, start_of_line + 1, len_of_arg );

        sscanf(arg_str, "%d", &arg);

        free(arg_str);
    }

    return arg;
}

int check_hash_name_struct(struct hash_name* cmd_pointer)
{
    for (int i = 0; i < cmd_pointer->count_of_pointer; i++)
    {
        if (cmd_pointer->pointer_info[i].ip_cmd == -1 )
        {
            printf("LOST POINTER IN JMP\n");
            return EXIT;
        }
    }

    return OK;
}

void write_machine_code(struct asm_file* machine_code, FILE* ass)
{
    assert(machine_code != nullptr);
    assert(ass != nullptr);

    for (int i = 0; i < 4; i++)
    {
        fprintf(ass, "%c", machine_code->sign[i]);
    }

    fprintf(ass, "%c", machine_code->version);

    fprintf(ass, "%d", machine_code->len_of_code);

    fwrite(machine_code->code, sizeof(char), machine_code->len_of_code, ass);
}


void free_asm_struct(struct asm_file* machine)
{
    free(machine->code);
}
