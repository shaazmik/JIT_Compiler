// MAIN REGISTERS: rax, rbx, rcx, rdx
// CAN BE USED: rdi, rsi, r8, r9, r10
// r11 saves register of return
// CAN'T BE USED: rsp, rbp, r12, r13, r14, r15
// WARNING! SAVE rbx register.


DEF_CMD_(0x0F, HLT, 0, 
{
    PUT_IP;

    fprintf(stderr, "IT IS HLT\n"
                    "SOMETHING WENT WRONG\n");
}
)

DEF_CMD_(0x11, PUSH, 1, 
{   
    PUT_IP;

    ip_PSL++;
    
    *(x86struct->x86_code + ip_x86++)       = char(0x68);
    *(int*)(x86struct->x86_code + ip_x86)   = *(int*)(x86struct->PSL_code + ip_PSL);
   
    ip_x86 += sizeof(int) / sizeof(char);
    ip_PSL += sizeof(int) / sizeof(char);
}
)

DEF_CMD_(0x12, PUSH_X, 1, 
{   
    PUT_IP;

    ip_PSL++;

    switch (*(x86struct->PSL_code + ip_PSL))
    {
    case 0x00: //rax
        *(x86struct->x86_code + ip_x86++) = (char)0x50;
        ip_PSL++;
        break;

    case 0x01: //rbx
        *(x86struct->x86_code + ip_x86++) = (char)0x53;
        ip_PSL++;
        break;
    
    case 0x02: //rcx
        *(x86struct->x86_code + ip_x86++) = (char)0x51;
        ip_PSL++;    
        break;

    case 0x03: //rdx
        *(x86struct->x86_code + ip_x86++) = (char)0x52;
        ip_PSL++;
        break;

    default:
        fprintf(stderr, "DEFAULT CASE IN POP\n");
        break;
    }

    //rax 0x50
    //rbx 0x53
    //rcx 0x51
    //rdx 0x52
}
)




DEF_CMD_(0x22, POP_X, 1, 
{
    PUT_IP;

    ip_PSL++;

    switch (*(x86struct->PSL_code + ip_PSL))
    {
    case 0x00: //rax
        *(x86struct->x86_code + ip_x86++) = (char)0x58;
        ip_PSL++;
        break;

    case 0x01: //rbx
        *(x86struct->x86_code + ip_x86++) = (char)0x5B;
        ip_PSL++;
        break;
    
    case 0x02: //rcx
        *(x86struct->x86_code + ip_x86++) = (char)0x59;
        ip_PSL++;    
        break;

    case 0x03: //rdx
        *(x86struct->x86_code + ip_x86++) = (char)0x5A;
        ip_PSL++;
        break;

    default:
        fprintf(stderr, "DEFAULT CASE IN POP\n");
        break;
    }


    //rax 0x58
    //rbx 0x5B
    //rcx 0x59
    //rdx 0x5A
}
)


DEF_CMD_(0x06, ADD, 0,
{
    PUT_IP;

    ip_PSL++;

    POP_RDI;
    POP_RSI;

    *(x86struct->x86_code + ip_x86++) = (char)(0x48);
    *(x86struct->x86_code + ip_x86++) = (char)(0x01);   //ADD RDI, RSI
    *(x86struct->x86_code + ip_x86++) = (char)(0xF7);

    PUSH_RDI;

    // pop rdi       //0x5F
    // pop rsi       //0x5E
    // add rdi, rsi  //0x4801F7
    // push rdi      //0x57
}
)


DEF_CMD_(0x07, SUB, 0,
{   
    PUT_IP;

    ip_PSL++;

    POP_RSI;
    POP_RDI;

    *(x86struct->x86_code + ip_x86++) = (char)(0x48);
    *(x86struct->x86_code + ip_x86++) = (char)(0x29);  //SUB RDI, RSI
    *(x86struct->x86_code + ip_x86++) = (char)(0xF7);

    PUSH_RDI;

    //pop rdi       //0x5F
    //pop rsi       //0x5E
    //sub rdi, rsi  //0x4829F7
    //push rdi      //0x57
}
)


DEF_CMD_(0x08, MUL, 0,
{
    PUT_IP;

    ip_PSL++;

    SAVE_RAX;
    SAVE_RDX;

    *(x86struct->x86_code + ip_x86++) = (char)0x5A; // pop rdx 

    *(x86struct->x86_code + ip_x86++) = (char)0x58; // pop rax

    *(x86struct->x86_code + ip_x86++) = (char)0x48;
    *(x86struct->x86_code + ip_x86++) = (char)0xF7; // imul rdx
    *(x86struct->x86_code + ip_x86++) = (char)0xEA;

    PUSH_RAX;

    RET_RAX;
    RET_RDX;
}
)


DEF_CMD_(0x09, DIV, 0, 
{
    PUT_IP;

    ip_PSL++;

    SAVE_RAX;
    SAVE_RCX;
    SAVE_RDX;

    *(x86struct->x86_code + ip_x86++) = (char)0x59; // pop rcx 

    *(x86struct->x86_code + ip_x86++) = (char)0x58; // pop rax

    *(x86struct->x86_code + ip_x86++) = (char)0x48;
    *(x86struct->x86_code + ip_x86++) = (char)0x99;

    *(x86struct->x86_code + ip_x86++) = (char)0x48;
    *(x86struct->x86_code + ip_x86++) = (char)0xF7; // idiv rcx
    *(x86struct->x86_code + ip_x86++) = (char)0xF9;

    PUSH_RAX;

    RET_RAX;
    RET_RCX;
    RET_RDX;
}
)


DEF_CMD_(0x16, SHOW, 0, 
{
    PUT_IP;
    
    (++ip_PSL);
 
    *(x86struct->x86_code + ip_x86++) = (char)(0x5F);       //pop rdi

    MOV_R10;

    push_show_addr(x86struct->x86_code + ip_x86);           //mov r10, address
    ip_x86 += sizeof(int) / sizeof(char);;



    SAVE_RAX;
    SAVE_RBX;
    SAVE_RCX;
    SAVE_RDX;

    CALL_R10;
    
    RET_RAX;
    RET_RBX;
    RET_RCX;
    RET_RDX;
}
)

DEF_CMD_(0x17, IN, 0,
{
    PUT_IP;

    ip_PSL++;

    SAVE_RAX;
    SAVE_RBX;
    SAVE_RCX;
    SAVE_RDX;

    MOV_R10;

    push_in_addr(x86struct->x86_code + ip_x86);            //mov r10, address
    ip_x86 += sizeof(int) / sizeof(char);;


    SAVE_RSP;

    STACK_ALIGNMENT_16;

    CALL_R10;
    
    RETURN_RSP;

    PUSH_RAX;

    RET_RAX;
    RET_RBX;
    RET_RCX;
    RET_RDX;
}
)


DEF_CMD_(0x0D, JMP_POINTER, 1, 
{
    PUT_IP;

    ip_PSL++;
    *(x86struct->x86_code + ip_x86++) = (char)0xE9; //jmp

    int jmp_ip = *(int*)(x86struct->PSL_code + ip_PSL);

    if (x86struct->step != 0)
    {
        int cell   = find_ip(x86struct->PSL_code_address, jmp_ip, x86struct->number_of_ip);

        if (cell != -1)
        {
           *(int*)(x86struct->x86_code + ip_x86) = (int)(x86struct->x86_code_address[cell] - ip_x86 - 4);
        }

    }

    ip_PSL += sizeof(int) / sizeof(char);
    ip_x86 += sizeof(int) / sizeof(char);
}
)


DEF_CMD_(0x1D, JE_POINTER, 1,
{
    PUT_IP;

    ip_PSL++;

    POP_RSI;
    POP_RDI;
    CMP_RDI_RSI;

    *(x86struct->x86_code + ip_x86++) = (char)0x0F;  //je
    *(x86struct->x86_code + ip_x86++) = (char)0x84;

    int jmp_ip = *(int*)(x86struct->PSL_code + ip_PSL);

    if (x86struct->step != 0)
    {
        int cell   = find_ip(x86struct->PSL_code_address, jmp_ip, x86struct->number_of_ip);

        if (cell != -1)
        {
           *(int*)(x86struct->x86_code + ip_x86) = (int)(x86struct->x86_code_address[cell] - ip_x86 - 4);
        }

    }
    else
    {
        *(x86struct->x86_code + ip_x86) = (char)0x00;
    }

    ip_PSL += sizeof(int) / sizeof(char);
    ip_x86 += sizeof(int) / sizeof(char);
}
)

DEF_CMD_(0x2D, JNE_POINTER, 1,
{
    PUT_IP;

    POP_RSI;
    POP_RDI;
    CMP_RDI_RSI;


    ip_PSL++;
    *(x86struct->x86_code + ip_x86++) = (char)0x75;

    int jmp_ip = *(int*)(x86struct->PSL_code + ip_PSL);

    if (x86struct->step != 0)
    {
        int cell   = find_ip(x86struct->PSL_code_address, jmp_ip, x86struct->number_of_ip);

        if (cell != -1)
        {
            *(x86struct->x86_code + ip_x86) = (unsigned char)(x86struct->x86_code_address[cell] - ip_x86 - 1);
        }

    }

    ip_PSL += sizeof(int) / sizeof(char);
    ip_x86++;
}
)


DEF_CMD_(0x3D, JA_POINTER, 1,
{
    PUT_IP;

    POP_RSI;
    POP_RDI;
    CMP_RDI_RSI;

    ip_PSL++;
    *(x86struct->x86_code + ip_x86++) = (char)0x0F;  //near jg 
    *(x86struct->x86_code + ip_x86++) = (char)0x8F;

    int jmp_ip = *(int*)(x86struct->PSL_code + ip_PSL);

    if (x86struct->step != 0)
    {
        int cell   = find_ip(x86struct->PSL_code_address, jmp_ip, x86struct->number_of_ip);

        if (cell != -1)
        {
           *(int*)(x86struct->x86_code + ip_x86) = (int)(x86struct->x86_code_address[cell] - ip_x86 - 4);
        }
    }
    ip_PSL += sizeof(int) / sizeof(char);
    ip_x86 += sizeof(int) / sizeof(char);
}
)


DEF_CMD_(0x4D, JB_POINTER, 1,
{
    PUT_IP;

    POP_RSI;
    POP_RDI;
    CMP_RDI_RSI;


    ip_PSL++;
    *(x86struct->x86_code + ip_x86++) = (char)0x0F;  //jl
    *(x86struct->x86_code + ip_x86++) = (char)0x8C;

    int jmp_ip = *(int*)(x86struct->PSL_code + ip_PSL);

    if (x86struct->step != 0)
    {
        int cell   = find_ip(x86struct->PSL_code_address, jmp_ip, x86struct->number_of_ip);

        if (cell != -1)
        {
           *(int*)(x86struct->x86_code + ip_x86) = (int)(x86struct->x86_code_address[cell] - ip_x86 - 4);        
        }

    }

    ip_PSL += sizeof(int) / sizeof(char);
    ip_x86 += sizeof(int) / sizeof(char);
}
)


DEF_CMD_(0x5D, CALL_POINTER, 1,
{
    PUT_IP;

    ip_PSL++;
    
    *(x86struct->x86_code + ip_x86++) = (char)0xE8; //adress 4 byte

    int jmp_ip = *(int*)(x86struct->PSL_code + ip_PSL);

    if (x86struct->step != 0)
    {
        int cell   = find_ip(x86struct->PSL_code_address, jmp_ip, x86struct->number_of_ip);

        if (cell != -1)
        {
            *(int*)(x86struct->x86_code + ip_x86) = (int)(x86struct->x86_code_address[cell] - ip_x86 - 4);
        }

    }

    ip_PSL += sizeof(int) / sizeof(char);;
    ip_x86 += sizeof(int) / sizeof(char);;
}
)

DEF_CMD_(0x6A, RET, 0,
{
    PUT_IP;

    ip_PSL++;

    *(x86struct->x86_code + ip_x86++) = (char)0xC3;
}
)

DEF_CMD_(0x10, SQRT, 0,
{
    PUT_IP;

    ip_PSL++;

    POP_RDI;

    MOV_R10;

    push_sqrt_addr(x86struct->x86_code + ip_x86);            //mov r10, address
    ip_x86 += sizeof(int) / sizeof(char);

    SAVE_RAX;
    SAVE_RBX;
    SAVE_RCX;
    SAVE_RDX;

    CALL_R10;

    PUSH_RAX;

    RET_RAX;
    RET_RBX;
    RET_RCX;
    RET_RDX;

}
)