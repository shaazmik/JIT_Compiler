// MAIN REGISTERS: rax, rbx, rcx, rdx
// CAN BE USED: rdi, rsi, r8, r9, r10
// r11 saves register of return
// CAN'T BE USED: rsp, rbp, r12, r13, r14, r15
// WARNING! SAVE rbx register.


DEF_CMD_(0x0F, HLT, 0, 
{

}
)

DEF_CMD_(0x11, PUSH, 1, 
{   
    //0x68 0x5 !PUSH 5 //unnamed pointer on integer 
}
)

DEF_CMD_(0x12, PUSH_X, 1, 
{   
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
    // pop rdi   //0x5F
    // pop rsi   // 0x5E
    // add rdi, rsi //0x4801F7
    // push rdi     //0x57
}
)


DEF_CMD_(0x07, SUB, 0,
{   
    //pop rdi //0x5F
    //pop rsi //0x5E
    //sub rdi, rsi // 0x4829F7
    //push rdi    //0x57
}
)


DEF_CMD_(0x08, MUL, 0,
{
    // !2 * 5!
    //push 2
    //push 5
    //mul

    //push 2
    //push 5
    //mov rdi, rax   ; 0x4889C7
    //mov rsi, rdx   ; 0x4889D6
    //pop rdx
    //pop rax
    //mul rdx        ; 0x48F7E2
    //push rax
    //mov rax, rdi   ; 0x4889F8
    //mov rdx, rsi   ; 0x4889F2
}
)


DEF_CMD_(0x09, DIV, 0, 
{
    // !2 / 5!
    //push 2
    //push 5
    //div

    //push 2
    //push 5
    //mov rdi, rax   ; 0x4889C7
    //mov rsi, rdx   ; 0x4889D6
    //pop rdx
    //pop rax
    //div rdx        ; 0x48F7F2
    //push rax
    //mov rax, rdi   ; 0x4889F8
    //mov rdx, rsi   ; 0x4889F2
}
)

DEF_CMD_(0x10, SQRT, 0,
{

}
)