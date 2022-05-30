# JIT_Compiler
## JIT compiler my programming specific language (PSL) to x86 architecture

### Introduction:

**JIT-compiler** translates my **PSL (Programming Specific Language)** architecture<br/>
into binary code for **the x86-64** processor architecture.<br/>


### To compilie:

- Processor input data should be in the ```Assembler_PSL/Assembler/commands.txt``` file
- [PSL processor command table](#Processor_command_table)


___.JIT_compiler/Assembler_PSL/Assembler___
- ```make```
- ```./assembler.out```
- the PSL binary code is in the ```assembler.bin``` file


___./JIT_compiler/Assembler_PSL/CPU___
- ```make```
- to run our processor emulator in C
- ```./processor.out```


___./JIT_compiler___
- firstly, the ```assembler.bin``` file must be prepared 
- start ```makefile``` on Linux (```Bash```).
- ```make```
- ```./a.out```




### Processor_command_table
