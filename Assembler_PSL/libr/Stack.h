#ifndef STACK_H
#define STACK_H

#include <math.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

//========================================

#define FATAL_ERROR        assert(0)

#define stack_name(value)  #value

//========================================

//!*

#define DEBUG_MOD

//!*

//========================================

#ifdef DEBUG_MOD

#define dump_stack(value) dump_loud(value, __FILE__, __PRETTY_FUNCTION__)

#define verification_stack(value) if (verification(value))                                \
                                   {                                                      \
                                       dump_stack(value);                                 \
                                   }

#define stack_construct(pstack_address, capacity) if (stack_constructor(pstack_address, capacity))         \
                                                    {                                                      \
                                                        printf("Program ended.\n");                        \
                                                        return ERROR_UNKNOWN;                              \
                                                    }

#define stack_destruct(pstack_address)            if (stack_destructor(pstack_address))                    \
                                                    {                                                      \
                                                        printf("Program ended.\n");                        \
                                                        return ERROR_UNKNOWN;                              \
                                                    }

#endif // DEBUG_MOD


//========================================


#ifndef DEBUG_MOD

#define dump_stack(value)         dump_whisper(value)

#define verification_stack(value) if (verification(value))   \
                                  {                          \
                                      dump_stack(value);     \
                                      return ERROR_UNKNOWN;  \
                                  }


#define stack_construct(pstack_address, capacity) if (stack_constructor(pstack_address, capacity))         \
                                                    {                                                      \
                                                        printf("Program ended.\n");                        \
                                                        return ERROR_UNKNOWN;                              \
                                                    }


#define stack_destruct(pstack_address)            if (stack_destructor(pstack_address))                    \
                                                    {                                                      \
                                                        printf("Program ended.\n");                        \
                                                        return ERROR_UNKNOWN;                              \
                                                    }


#endif // DEBUG_MOD




//========================================

//!**

#define Int_t

//========================================

#ifdef Double_t

typedef double type_array;

#define type_array_format "%lg"

#endif

//========================================

#ifdef Int_t

typedef int type_array;

#define type_array_format "%d"

#endif


//========================================

#ifdef Str_t

typedef char* type_array;

#endif

//========================================

enum errors
{
    OK                   = 0,
    CON_STATUS_OK        = 3,
    STACK_IS_CONSTURCTED = 4,
    DES_STATUS_OK        = 13,

    ERROR_OUT_RANGE            = 1488,
    ERROR_FULL_STACK           = 1945,
    ERROR_NULLPTR              = 228,
    ERROR_DOUBLE_CONSTRUCT     = 1555,
    ERROR_DOUBLE_DESTRUCT      = 1337,
    ERROR_WRONG_CAPACITY       = 1861,
    ERROR_WRONG_HASH           = 0xF,
    ERROR_MEMORY_RESIZE_FAILED = 0xBABADED,
    ERROR_UNKNOWN              = 0xDEADFAAC,


    WARNING_SIZE_INC = 666,
    WARNING_SIZE_DEC = 999,

    LEFT_STRUCT_CANAREA_DEAD  = 0xB1EA,
    RIGHT_STRUCT_CANAREA_DEAD = 0xB2EA,
    LEFT_STACK_CANAREA_DEAD   = 0xB1EA2,
    RIGHT_STACK_CANAREA_DEAD  = 0xB2EA2
};


//========================================


struct pstack_info
{
    long long golub_left;

    type_array* pstack_pointer;
    int         pstack_size;
    ssize_t     pstack_capacity;

    int pstack_error   = 0;
    size_t con_status  = CON_STATUS_OK;
    size_t des_status;
    size_t inc_counter = 1;
    char*  name_of_stack;

    long long hash_var;

    long long golub_right;
};

//========================================


const int Pstack_inc_max = 3;

static const long long Dog = 0x0DED1ABE0DED1ABE;

const int Pstack_multiplier = 3;

const int Default_size_of_pstack = 100;


//========================================


int stack_constructor(struct pstack_info* pstack, int pstack_user_size);


int check_construct(struct pstack_info* pstack);


int check_memory(type_array* data);


static long long rotl (long long n);


long long hash_calc (struct pstack_info* pstack);


void check_nullptr(struct pstack_info* pstack);


int stack_pushka(struct pstack_info* pstack, type_array new_element);


type_array stack_popka(struct pstack_info* pstack);


int verification(struct pstack_info* pstack);


int pstack_resizemo(struct pstack_info* pstack);


int pstack_resizele(struct pstack_info* pstack);


int dump_loud(struct pstack_info* pstack, const char* name_of_file, const char* name_of_function);


void dump_whisper(struct pstack_info* pstack);


void print_stack(struct pstack_info* pstack);


void fprint_stack(struct pstack_info* pstack, FILE* log);


void print_err_loud(int err_num, const char* name_of_file, const char* name_of_function, pstack_info* pstack, int line_number);


int stack_destructor(struct pstack_info* pstack);


int check_destruct(struct pstack_info* pstack);


#endif // STACK_H
