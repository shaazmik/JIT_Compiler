
   

enum commands
{
    #define DEF_CMD_(number, name, arg, code) CMD_##name = number,

    #include "../Commands_JIT.h"

    #undef DEF_CMD_
};


const char Version_of_programm = 3;

const int Size_of_stack = 40;

const double Epsilon = 0.00001;





