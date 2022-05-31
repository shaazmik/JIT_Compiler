# JIT_Compiler
## JIT compiler my programming specific language (PSL) to x86 architecture

## Introduction:

**JIT-compiler** translates my **PSL (Programming Specific Language)** architecture<br/>
into binary code for **the x86-64** processor architecture.<br/>
For illustration let's compare running time of my virtual processor  <br/>
with running time of program on **x86-64**. <br/>
The basic idea behind a **JIT compiler** is to translate the binary code of one architecture into the binary code of another architecture. <br/>
The main difference is that the program is executed from a buffer stored in the JIT compiler program. <br/>
In this case, creating an **OS-specific** **executable** is irrelevant, which is more cross-platform than <br/>
creating an **executable** for each OS. Only the **architecture** of the processor matters. <br/>

___

## To compilie:

- Processor input data should be in the ```Assembler_PSL/Assembler/commands.txt``` file
- [PSL processor command table](#Processor_command_table)

#### For PSL_assembler

___.JIT_compiler/Assembler_PSL/Assembler___
- ```make```
- ```./assembler.out```
- the PSL binary code is in the ```assembler.bin``` file


#### For CPU_emulator

___./JIT_compiler/Assembler_PSL/CPU___
- ```make```
- to run our processor emulator in C
- ```./processor.out```


#### For JIT_compiler

___./JIT_compiler___
- firstly, the ```assembler.bin``` file must be prepared 
- start ```makefile``` on Linux (```Bash```).
- ```make```
- ```./a.out```

___

## Main page:
- The registers were used to transfer data.
- System V Calling Convention.
- The memory is used to save registers according to convention and to return and transfer arguments.
- The processor commands are written to the ```Assembler_PSL\commands.txt``` file.

___Perfomance tests:___
* factorial
* Fibonacci number
* quadratic equation


## Processor_command_table

___All PSL  commands have some kind of wrapper in x86-64, so tabular data may be different___<br/>
___For more information see the ```Commands_JIT.h``` file___<br/>


|**COMMAND**  |**PSL**      |**x86-64**|
|-------------|-------------|-------------|
|```PUSH```   |0x11         |0x68         |
|```PUSH AX```|0x1200       |0x50         |
|```PUSH BX```|0x1201       |0x53         |
|```PUSH CX```|0x1202       |0x51         |
|```PUSH DX```|0x1203       |0x52         |
|```POP  AX```|0x2200       |0x58         |
|```POP  BX```|0x2201       |0x5B         |
|```POP  CX```|0x2202       |0x59         |
|```POP  DX```|0x2203       |0x5A         |
|```ADD    ```|0x06         |0x4801F7     |
|```SUB    ```|0x07         |0x4829F7     |
|```MUL    ```|0x08         |0x48F7EA     |
|```DIV    ```|0x09         |0x48F7F9     |
|```JMP    ```|0x0D         |0xE9         |
|```JE     ```|0x1D         |0x0F84       |
|```JNE    ```|0x2D         |0x75         |
|```JA     ```|0x3D         |0x0F8F       |
|```JB     ```|0x4D         |0x0F8C       |
|```CALL   ```|0x5D         |0xE8         |
|```RET    ```|0x6A         |0xC3         |
|```SHOW   ```|0x16         |[SHOW](#SHOW)|
|```IN     ```|0x17         |[IN](#IN)    |
|```SQRT   ```|0x10         |[SQRT](#SQRT)|
|```HLT    ```|0x0F         |0xC3         |


## Description of functions(```SHOW, IN, SQRT```)

**The commands described have a DSL (Domain Specific Language). Their description can be found in the ```JIT_DSL.h``` file.** <br/>
___These functions work by calling the standard functions ```Printf```, ```Scanf```, ```sqrt```.___

### SHOW
```cpp

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

```


### IN 
```cpp
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
```


### SQRT
```cpp
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
```
## Results 
