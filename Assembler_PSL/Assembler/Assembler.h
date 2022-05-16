#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "../libr/Hamlet.h"
#include "../enum.h"
#include "../libr/Stack.h"


const int Max_argc_cmd = 3 * sizeof(double);

enum errors_of_assembler
{
    WRONG_ARGUMENT = 0xF1FA1228,
    EXIT = 0x111111,
};

struct pointer_struct
{
    long long hash = 0;
    int ip_cmd = -1;
};


struct hash_name
{
    int count_of_pointer = 0;
    struct pointer_struct pointer_info[15] = {};
};
                                                                  


struct asm_file
{
    char version;

    const char sign[4] = {'S', 'H', 'Z', '!'};

    int len_of_code = 0;

    char* code;

    struct hash_name cmd_pointer = {};
};


void input_machine_struct(struct asm_file* machine_code, struct Text* text_struct);


void navigation_for_comment(struct Text* text_struct);


int compilation(struct Text* text_struct, struct asm_file* machine);


int len_name_of_command(char* str);


void get_line_cmd(char* str, char* start_line_of_command);


int hash_jmp_pointer(char* cmd);


uint32_t dl_new_hash (const char* str, int len);


int insert_hash_name(struct hash_name* cmd_pointer, uint32_t arg_var, int ip);


int find_hash_name(struct hash_name* cmd_pointer, uint32_t arg_var);


char* next_argument(char* line_command);


int check_register(char* start_of_line);


int check_RAM(char* start_of_line);


int check_hash_name_struct(struct hash_name* cmd_pointer);


void write_machine_code(struct asm_file* machine_code, FILE* ass);


void free_asm_struct(struct asm_file* machine);


#endif