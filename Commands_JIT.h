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

DEF_CMD_(0x13, PUSH_MEM, 1,
{   
    // !push [rax]!

    // ?????? name of bss buffer + rax offset
    //mov r8, [rax]  
    //push rbx             
}
)


DEF_CMD_(0x21, POP, 1, 
{
    //POP 5
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


DEF_CMD_(0x23, POP_MEM, 1, 
{
    // ???
}
)


DEF_CMD_(0x06, ADD, 0,
{
    PUT_IP;

    ip_PSL++;

    POP_RDI;
    POP_RSI;
    *(x86struct->x86_code + ip_x86++) = (char)(0x48);
    *(x86struct->x86_code + ip_x86++) = (char)(0x01);
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

    POP_RDI;
    POP_RSI;
    *(x86struct->x86_code + ip_x86++) = (char)(0x48);
    *(x86struct->x86_code + ip_x86++) = (char)(0x29);
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
    *(x86struct->x86_code + ip_x86++) = (char)0xF7; // mul rdx
    *(x86struct->x86_code + ip_x86++) = (char)0xE2;

    *(x86struct->x86_code + ip_x86++) = (char)0x50; // push rax

    RET_RAX;
    RET_RDX;
}
)


DEF_CMD_(0x09, DIV, 0, 
{
    PUT_IP;

    ip_PSL++;

    SAVE_RAX;
    SAVE_RDX;
    SAVE_RCX;

    *(x86struct->x86_code + ip_x86++) = (char)0x59; // pop rcx 

    *(x86struct->x86_code + ip_x86++) = (char)0x58; // pop rax

    *(x86struct->x86_code + ip_x86++) = (char)0x48;
    *(x86struct->x86_code + ip_x86++) = (char)0xF7; // div rcx
    *(x86struct->x86_code + ip_x86++) = (char)0xF1;

    *(x86struct->x86_code + ip_x86++) = (char)0x50; // push rax

    RET_RAX;
    RET_RCX;
    RET_RDX;
}
)

DEF_CMD_(0x10, SQRT, 0,
{

}
)

DEF_CMD_(0x16, SHOW, 0, 
{
    PUT_IP;
    
    (++ip_PSL);
 
    *(x86struct->x86_code + ip_x86++) = (char)(0x41);       //mov r10,...
    *(x86struct->x86_code + ip_x86++) = (char)(0xBA);

    push_show_addr(x86struct->x86_code + ip_x86);           //mov r10, address
    ip_x86 += 4;

    *(x86struct->x86_code + ip_x86++) = (char)(0x5F);      //pop rdi

    SAVE_RAX;
    SAVE_RBX;
    SAVE_RCX;
    SAVE_RDX;

    *(x86struct->x86_code + ip_x86++) = (char)(0x41);      //call r10
    *(x86struct->x86_code + ip_x86++) = (char)(0xFF);
    *(x86struct->x86_code + ip_x86++) = (char)(0xD2);
    
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

    *(x86struct->x86_code + ip_x86++) = (char)(0x41);      //mov r10,...
    *(x86struct->x86_code + ip_x86++) = (char)(0xBA);

    push_in_addr(x86struct->x86_code + ip_x86);            //mov r10, address
    ip_x86 += 4;

    SAVE_RAX;
    SAVE_RBX;
    SAVE_RCX;
    SAVE_RDX;

    SAVE_RSP;
    *(x86struct->x86_code + ip_x86++) = (char)0x48; 
    *(x86struct->x86_code + ip_x86++) = (char)0x83;   // and rsp, 0xFFFFFFFF0 
    *(x86struct->x86_code + ip_x86++) = (char)0xE4;
    *(x86struct->x86_code + ip_x86++) = (char)0xF0; 

    *(x86struct->x86_code + ip_x86++) = (char)(0x41);      //call r10
    *(x86struct->x86_code + ip_x86++) = (char)(0xFF);
    *(x86struct->x86_code + ip_x86++) = (char)(0xD2);    
    
   *(x86struct->x86_code + ip_x86++) = (char)0x48; 
   *(x86struct->x86_code + ip_x86++) = (char)0x89;    //mov rsp,rbp ; 
   *(x86struct->x86_code + ip_x86++) = (char)0xEC;

    *(x86struct->x86_code + ip_x86++) = (char)0x5D;   // pop rbp

    *(x86struct->x86_code + ip_x86++) = (char)0x50;     // push rax

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
    *(x86struct->x86_code + ip_x86++) = (char)0xEB; //jmp

    int jmp_ip = *(int*)(x86struct->PSL_code + ip_PSL);

    if (x86struct->step != 0)
    {
        int cell   = find_ip(x86struct->PSL_code_address, jmp_ip, x86struct->number_of_ip);

        if (cell != -1)
        {
            *(x86struct->x86_code + ip_x86) = (unsigned char)(x86struct->x86_code_address[cell] - ip_x86 - 1);
        }

    }

    ip_PSL += 4;
    ip_x86++;
}
)

DEF_CMD_(0x1D, JE_POINTER, 1,
{
    PUT_IP;

    ip_PSL++;

    POP_RDI;
    POP_RSI;
    CMP_RDI_RSI;

    *(x86struct->x86_code + ip_x86++) = (char)0x74;  //je

    int jmp_ip = *(int*)(x86struct->PSL_code + ip_PSL);

    if (x86struct->step != 0)
    {
        int cell   = find_ip(x86struct->PSL_code_address, jmp_ip, x86struct->number_of_ip);

        if (cell != -1)
        {
            *(x86struct->x86_code + ip_x86) = (unsigned char)(x86struct->x86_code_address[cell] - ip_x86 - 1);
        }

    }
    else
    {
        *(x86struct->x86_code + ip_x86) = (char)0x00;
    }

    ip_PSL += 4;
    ip_x86++;
}
)

DEF_CMD_(0x2D, JNE_POINTER, 1,
{
    PUT_IP;

    POP_RDI;
    POP_RSI;
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

    ip_PSL += 4;
    ip_x86++;
}
)


DEF_CMD_(0x3D, JA_POINTER, 1,
{
    PUT_IP;

    POP_RDI;
    POP_RSI;
    CMP_RDI_RSI;

    ip_PSL++;
    *(x86struct->x86_code + ip_x86++) = (char)0x77;

    int jmp_ip = *(int*)(x86struct->PSL_code + ip_PSL);

    if (x86struct->step != 0)
    {
        int cell   = find_ip(x86struct->PSL_code_address, jmp_ip, x86struct->number_of_ip);

        if (cell != -1)
        {
            *(x86struct->x86_code + ip_x86) = (unsigned char)(x86struct->x86_code_address[cell] - ip_x86 - 1);
        }

    }

    ip_PSL += 4;
    ip_x86++;
}
)


DEF_CMD_(0x4D, JB_POINTER, 1,
{
    PUT_IP;

    POP_RDI;
    POP_RSI;
    CMP_RDI_RSI;

    ip_PSL++;
    *(x86struct->x86_code + ip_x86++) = (char)0x72;

    int jmp_ip = *(int*)(x86struct->PSL_code + ip_PSL);

    if (x86struct->step != 0)
    {
        int cell   = find_ip(x86struct->PSL_code_address, jmp_ip, x86struct->number_of_ip);

        if (cell != -1)
        {
            *(x86struct->x86_code + ip_x86) = (unsigned char)(x86struct->x86_code_address[cell] - ip_x86 - 1);
        }

    }

    ip_PSL += 4;
    ip_x86++;
}
)


DEF_CMD_(0x5D, CALL_POINTER, 1,
{
    PUT_IP;

    *(x86struct->x86_code + ip_x86++) = (char)0xE8; //adress 4 byte

}
)

DEF_CMD_(0x6A, RET, 0,
{
    PUT_IP;

    ip_PSL++;

    *(x86struct->x86_code + ip_x86++) = (char)0xC3;
}
)