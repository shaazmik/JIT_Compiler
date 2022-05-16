
DEF_CMD_(0x11, PUSH, 1, 
{   
    type_array argument = 0;

    argument = *(type_array*)( &(CPPU->code[ip + 1]) ); 

    stack_pushka(&(CPPU->stk), argument);

    ip += 1 + 1 * sizeof(type_array);
}
)

DEF_CMD_(0x12, PUSH_X, 1, 
{   
    int mem_cell_num = 0;

    mem_cell_num = CPPU->code[ip + 1];

    stack_pushka( &(CPPU->stk), CPPU->register_cpu[mem_cell_num]  );

    ip += 1 + 1 * sizeof(char);
} 
)

DEF_CMD_(0x13, PUSH_MEM, 1,
{   
    int mem_cell_num = 0;

    mem_cell_num = *(int*)( &(CPPU->code[ip + 1]) );

    stack_pushka( &(CPPU->stk), CPPU->RAM[mem_cell_num] );

    ip += 1 + 1 * sizeof(int);
}
)


DEF_CMD_(0x21, POP, 1, 
{
    stack_popka(&(CPPU->stk));
    ip += 1 + 1 * sizeof(type_array);
}
)


DEF_CMD_(0x22, POP_X, 1, 
{
    int mem_cell_num = 0;

    mem_cell_num = CPPU->code[ip + 1];

    CPPU->register_cpu[mem_cell_num] = stack_popka( &(CPPU->stk) );

    ip += 1 + 1 * sizeof(char);
}
)

DEF_CMD_(0x23, POP_MEM, 1, 
{
    int mem_cell_num = 0;

    mem_cell_num = *(int*)( &(CPPU->code[ip + 1]) ); 

    CPPU->RAM[mem_cell_num] = stack_popka( &(CPPU->stk) );

    ip += 1 + 1 * sizeof(int);

}
)

DEF_CMD_(0x06, ADD, 0,
{  
    stack_pushka( &(CPPU->stk), stack_popka( &(CPPU->stk) ) + stack_popka( &(CPPU->stk) ) );
    ip += 1;
}
)


DEF_CMD_(0x07, SUB, 0,
{   
    type_array arg1 = stack_popka( &(CPPU->stk));
    type_array arg2 = stack_popka( &(CPPU->stk));

    stack_pushka( &(CPPU->stk),  arg2 - arg1);
    ip += 1;
}
)


DEF_CMD_(0x08, MUL, 0,
{
    stack_pushka( &(CPPU->stk), stack_popka( &(CPPU->stk) ) * stack_popka( &(CPPU->stk) ) );
    ip += 1;
}
)


DEF_CMD_(0x09, DIV, 0, 
{
    type_array arg1 = stack_popka(&(CPPU->stk));
    type_array arg2 = stack_popka(&(CPPU->stk));

    stack_pushka ( &(CPPU->stk), ( arg2 / arg1));
    ip += 1;
}
)

DEF_CMD_(0x10, SQRT, 0,
{
    type_array arg1 = stack_popka(&(CPPU->stk));

    stack_pushka( &(CPPU->stk), sqrt(arg1));

    ip += 1;
}
)

DEF_CMD_(0x16, SHOW, 0, 
{
    printf(type_array_format, stack_popka( &(CPPU->stk) ) ); 
    printf("\n");
    ip += 1;
}
)

DEF_CMD_(0x17, IN, 0,
{
    type_array arg = 0;

    scanf(type_array_format, &arg);

    stack_pushka( &(CPPU->stk), arg);

    ip += 1;
}
)


DEF_CMD_(0x0A, JMP, 1, 
{
    int jmp_ip = *(int*)( &(CPPU->code[ip + 1]) );
    ip = jmp_ip;
}
)

DEF_CMD_(0x0B, JMP_X, 1, 
{
    int jmp_ip = CPPU->code[ip + 1];
    ip = CPPU->register_cpu[jmp_ip];
}
)

DEF_CMD_(0x0C, JMP_MEM, 1, 
{
    int jmp_ip = *(int*)( &(CPPU->code[ip + 1]) );
    ip = CPPU->RAM[jmp_ip];
}
)

DEF_CMD_(0x0D, JMP_POINTER, 1, 
{
    int jmp_ip = *(int*)( &(CPPU->code[ip + 1]) );
    ip = jmp_ip;
}
)

DEF_CMD_(0x1A, JE, 1,
{
    int jmp_ip = *(int*)( &(CPPU->code[ip + 1]) );

    type_array arg1 = stack_popka( &(CPPU->stk) );
    type_array arg2 = stack_popka( &(CPPU->stk) );

    if ( srav(arg1, arg2) != -1 )
    {
        ip = jmp_ip;
    }
    else
    {
        ip += 1 + sizeof(type_array);
    }
}
)

DEF_CMD_(0x1B, JE_X, 1,
{
    int jmp_ip = CPPU->code[ip + 1];

    type_array arg1 = stack_popka( &(CPPU->stk) );
    type_array arg2 = stack_popka( &(CPPU->stk) );

    if (srav(arg1, arg2) != -1 )
    {
        ip = CPPU->register_cpu[jmp_ip];
    }
    else
    {
        ip += 1 + sizeof(char);
    }
}
)

DEF_CMD_(0x1C, JE_MEM, 1,
{
    int jmp_ip = *(int*)( &(CPPU->code[ip + 1]) );

    type_array arg1 = stack_popka( &(CPPU->stk) );
    type_array arg2 = stack_popka( &(CPPU->stk) );

    if (srav(arg1, arg2) != -1 )
    {
        ip = CPPU->RAM[jmp_ip];
    }
    else
    {
        ip += 1 + sizeof(int);
    }
}
)

DEF_CMD_(0x1D, JE_POINTER, 1,
{
    int jmp_ip = *(int*)( &(CPPU->code[ip + 1]) );

    type_array arg1 = stack_popka( &(CPPU->stk) );
    type_array arg2 = stack_popka( &(CPPU->stk) );

    if (srav(arg1, arg2) != -1 )
    {
        ip = jmp_ip;
    }
    else
    {
        ip += 1 + sizeof(int);
    }
}
)

DEF_CMD_(0x2A, JNE, 1,
{
    int jmp_ip = *(int*)( &(CPPU->code[ip + 1]) );

    type_array arg1 = stack_popka( &(CPPU->stk) );
    type_array arg2 = stack_popka( &(CPPU->stk) );

    if (arg1 != arg2 )
    {
        ip = jmp_ip;
    }
    else
    {
        ip += 1 + sizeof(type_array);
    }
}
)

DEF_CMD_(0x2B, JNE_X, 1,
{
    int jmp_ip = CPPU->code[ip + 1];

    type_array arg1 = stack_popka( &(CPPU->stk) );
    type_array arg2 = stack_popka( &(CPPU->stk) );

    if (arg1 != arg2 )
    {
        ip = CPPU->register_cpu[jmp_ip];
    }
    else
    {
        ip += 1 + sizeof(char);
    }
}
)

DEF_CMD_(0x2C, JNE_MEM, 1,
{
    int jmp_ip = *(int*)( &(CPPU->code[ip + 1]) );

    type_array arg1 = stack_popka( &(CPPU->stk) );
    type_array arg2 = stack_popka( &(CPPU->stk) );

    if (arg1 != arg2 )
    {
        ip = CPPU->RAM[jmp_ip];
    }
    else
    {
        ip += 1 + sizeof(int);
    }
}
)

DEF_CMD_(0x2D, JNE_POINTER, 1,
{
    int jmp_ip = *(int*)( &(CPPU->code[ip + 1]) );

    type_array arg1 = stack_popka( &(CPPU->stk) );
    type_array arg2 = stack_popka( &(CPPU->stk) );

    if (arg1 != arg2 )
    {
        ip = jmp_ip;
    }
    else
    {
        ip += 1 + sizeof(int);
    }
}
)


DEF_CMD_(0x3A, JA, 1,
{
    int jmp_ip = *(int*)( &(CPPU->code[ip + 1]) );

    type_array arg1 = stack_popka( &(CPPU->stk) );
    type_array arg2 = stack_popka( &(CPPU->stk) );

    if (arg1 < arg2 )
    {
        ip = jmp_ip;
    }
    else
    {
        ip += 1 + sizeof(type_array);
    }
}
)

DEF_CMD_(0x3B, JA_X, 1,
{
    int jmp_ip = CPPU->code[ip + 1];

    type_array arg1 = stack_popka( &(CPPU->stk) );
    type_array arg2 = stack_popka( &(CPPU->stk) );

    if (arg1 < arg2 )
    {
        ip = CPPU->register_cpu[jmp_ip];
    }
    else
    {
        ip += 1 + sizeof(char);
    }
}
)

DEF_CMD_(0x3C, JA_MEM, 1,
{
    int jmp_ip = *(int*)( &(CPPU->code[ip + 1]) );

    type_array arg1 = stack_popka( &(CPPU->stk) );
    type_array arg2 = stack_popka( &(CPPU->stk) );

    if (arg1 < arg2 )
    {
        ip = CPPU->RAM[jmp_ip];
    }
    else
    {
        ip += 1 + sizeof(int);
    }
}
)

DEF_CMD_(0x3D, JA_POINTER, 1,
{
    int jmp_ip = *(int*)( &(CPPU->code[ip + 1]) );

    type_array arg1 = stack_popka( &(CPPU->stk) );
    type_array arg2 = stack_popka( &(CPPU->stk) );

    if (arg1 < arg2 )
    {
        ip = jmp_ip;
    }
    else
    {
        ip += 1 + sizeof(int);
    }
}
)


DEF_CMD_(0x4A, JB, 1,
{
    int jmp_ip = *(int*)( &(CPPU->code[ip + 1]) );

    type_array arg1 = stack_popka( &(CPPU->stk) );
    type_array arg2 = stack_popka( &(CPPU->stk) );

    if (arg1 > arg2 )
    {
        ip = jmp_ip;
    }
    else
    {
        ip += 1 + sizeof(type_array);
    }
}
)

DEF_CMD_(0x4B, JB_X, 1,
{
    int jmp_ip = CPPU->code[ip + 1];

    type_array arg1 = stack_popka( &(CPPU->stk) );
    type_array arg2 = stack_popka( &(CPPU->stk) );

    if (arg1 > arg2 )
    {
        ip = CPPU->register_cpu[jmp_ip];
    }
    else
    {
        ip += 1 + sizeof(char);
    }
}
)

DEF_CMD_(0x4C, JB_MEM, 1,
{
    int jmp_ip = *(int*)( &(CPPU->code[ip + 1]) );

    type_array arg1 = stack_popka( &(CPPU->stk) );
    type_array arg2 = stack_popka( &(CPPU->stk) );

    if (arg1 > arg2 )
    {
        ip = CPPU->RAM[jmp_ip];
    }
    else
    {
        ip += 1 + sizeof(int);
    }
}
)

DEF_CMD_(0x4D, JB_POINTER, 1,
{
    int jmp_ip = *(int*)( &(CPPU->code[ip + 1]) );

    type_array arg1 = stack_popka( &(CPPU->stk) );
    type_array arg2 = stack_popka( &(CPPU->stk) );

    if (arg1 > arg2 )
    {
        ip = jmp_ip;
    }
    else
    {
        ip += 1 + sizeof(int);
    }
}
)


DEF_CMD_(0x5A, CALL, 1,
{
    int jmp_ip = *(int*)( &(CPPU->code[ip + 1]) );

    int back_ip = ip + 1 + sizeof(int);
    
    stack_pushka( &(CPPU->stk_back), back_ip);

    ip = jmp_ip;
}
)

DEF_CMD_(0x5D, CALL_POINTER, 1,
{
    int jmp_ip = *(int*)( &(CPPU->code[ip + 1]) );

    int back_ip = ip + 1 + sizeof(int);
    
    stack_pushka( &(CPPU->stk_back), back_ip);

    ip = jmp_ip;
}
)

DEF_CMD_(0x6A, RET, 0,
{
    ip = stack_popka( &(CPPU->stk_back) );
}
)

DEF_CMD_(0x7F, PRINT_CADR, 0,
{
    char cadr[(len_line_cadr + 1) * lines_in_cadr] = {};                   //  101 * 30 3030

    int i_mem = 0;

    for (int y = 0; y < lines_in_cadr; y++)
    {
        for (int x = 0; x < len_line_cadr; x++)
        {
            cadr[i_mem++] = CPPU->RAM[y * (len_line_cadr) + x] ? '$' : ' ' ; // ****\n   
        }

        cadr[i_mem++] = '\n';
    }


    cadr[i_mem - 1] = '\0';

    puts(cadr);

    Sleep(Cadr_time);

    ip++;
}
)

DEF_CMD_(0x0F, HLT, 0, 
{
    printf("The program is completed\n\n.");
}
)