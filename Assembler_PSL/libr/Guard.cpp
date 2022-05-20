#include "Stack.h"

#ifdef Double_t
    void dump_top_el (double value)    { printf ("STACK'S TOP ELEMENT  %lg\n", value); }
#endif

#ifdef Int_t
    void dump_top_el (int value)       { printf ("STACK'S TOP ELEMENT  %d\n",  value); }
#endif // Int_t

#ifdef Str_t
    void dump_top_el (const char* str) { printf ("STACK'S TOP ELEMENT  %s\n",  str);   }
#endif // Str_t

void check_nullptr(struct pstack_info* pstack)
{
    if (pstack == nullptr)
    {
            FILE* log = fopen("log.txt", "a");
            assert(log != nullptr);

            fprintf(log, "Stack [NULL_PTR_ERROR #%d] [0x000000]\n ", ERROR_NULLPTR);

            fflush(log);

            FATAL_ERROR;

    }
}

int check_memory(type_array* data)
{
    if (data == nullptr)
    {
        return ERROR_MEMORY_RESIZE_FAILED;
    }
    return OK;
}



static long long rotl (long long n)
{
    unsigned d = 13;
    n *= d;
    return (n << d)|(n >> (32 - d));
}

long long hash_calc (struct pstack_info* pstack)
{

    check_nullptr(pstack);

    long long phash = 0x1488;

    phash ^= rotl (pstack->golub_left);
    phash ^= rotl (pstack->pstack_error);
    phash ^= rotl (pstack->pstack_size);
    phash ^= rotl (pstack->pstack_capacity);
    phash ^= rotl (pstack->con_status);
    phash ^= rotl (pstack->des_status);
    phash ^= rotl (pstack->inc_counter);


    if (pstack->pstack_pointer != nullptr)
    {
        phash ^= *((long long*)((char*)pstack->pstack_pointer - 1 * sizeof (long long)));
        phash ^= *((long long*)(pstack->pstack_pointer + pstack->pstack_capacity));
    }

    if (pstack->pstack_size > 0 && pstack->pstack_pointer != nullptr)
        for (int i = 0; i < pstack->pstack_size; ++i)
            phash ^= rotl (*(pstack->pstack_pointer + i));


    phash ^= rotl (pstack->golub_right);


    phash ^= (phash >> 16);
    phash *= 0x85ebca6b;
    phash ^= (phash >> 13);
    phash *= 0xc2b2ae35;
    phash ^= (phash >> 16);

    return phash;
}


int check_construct(struct pstack_info* pstack)
{
    check_nullptr(pstack);

    if (pstack->con_status != CON_STATUS_OK)
    {
        printf("\nERROR #%d: check 'log.txt'\n\n", ERROR_DOUBLE_CONSTRUCT);

        FILE* log = fopen("log.txt", "a");
        assert(log != nullptr);

        fprintf(log, "Stack [RE-CREATING_STACK_ERROR OR NOT INITILIZATION!!!!! ___OMGWTF___ #%d] \n", ERROR_DOUBLE_CONSTRUCT);

        fflush(log);

        #ifdef DEBUG_MOD

        FATAL_ERROR;

        #endif // DEBUG_MOD

        #ifndef DEBUG_MOD

        return ERROR_UNKNOWN;

        #endif // DEBUG_MOD
    }

    return OK;
}




int check_destruct(struct pstack_info* pstack)
{
    check_nullptr(pstack);

    if (pstack->des_status != DES_STATUS_OK)
    {
        printf("ERROR #%d: check 'log.txt'\n\n", ERROR_DOUBLE_DESTRUCT);

        FILE* log = fopen("log.txt", "a");
        assert(log != nullptr);

        fprintf(log, "Stack [RE-DESTRUCTING_STACK_ERROR OR EMPTY DESTRUCTING #%d] \n", ERROR_DOUBLE_DESTRUCT);

        fflush(log);

        #ifdef DEBUG_MOD

        FATAL_ERROR;

        #endif // DEBUG_MOD

        #ifndef DEBUG_MOD

        return ERROR_UNKNOWN;

        #endif // DEBUG_MOD
    }

    return OK;
}

int verification(struct pstack_info* pstack)
{
    check_nullptr(pstack);

    if (pstack->pstack_pointer == nullptr)
    {
        pstack->pstack_error = ERROR_NULLPTR;
        return ERROR_NULLPTR;
    }


    if (pstack->pstack_capacity < 0)
    {
        pstack->pstack_error = ERROR_WRONG_CAPACITY;
        return ERROR_WRONG_CAPACITY;
    }

    if (pstack->pstack_size > pstack->pstack_capacity)
    {
        pstack->pstack_error = ERROR_FULL_STACK;
        return ERROR_FULL_STACK;
    }

    if (pstack->pstack_size < 0 )
    {
        pstack->pstack_error = ERROR_OUT_RANGE;
        return ERROR_OUT_RANGE;
    }

    if (pstack->golub_left != Dog)
    {
        pstack->pstack_error = LEFT_STRUCT_CANAREA_DEAD;
        return LEFT_STRUCT_CANAREA_DEAD;
    }

    if (pstack->golub_right != Dog)
    {
        pstack->pstack_error = RIGHT_STRUCT_CANAREA_DEAD;
        return RIGHT_STRUCT_CANAREA_DEAD;
    }

    if ( *(long long*)( (char*)pstack->pstack_pointer - sizeof(long long) ) != Dog )
    {
        pstack->pstack_error = LEFT_STACK_CANAREA_DEAD;
        return LEFT_STACK_CANAREA_DEAD;
    }

    if ( *(long long*)( (char*)pstack->pstack_pointer + sizeof(type_array) * pstack->pstack_capacity) != Dog )
    {
        pstack->pstack_error = RIGHT_STACK_CANAREA_DEAD;
        return RIGHT_STACK_CANAREA_DEAD;
    }

    if (hash_calc(pstack) != pstack->hash_var)
    {
        pstack->pstack_error = ERROR_WRONG_HASH;
        return ERROR_WRONG_HASH;
    }

    return OK;
}


void dump_whisper(struct pstack_info* pstack)
{
    check_nullptr(pstack);

    if (pstack->pstack_error == WARNING_SIZE_INC)
    {
        printf("\nWARNING STACK SIZE INCREASED\n");
    }

    if (pstack->pstack_error == WARNING_SIZE_DEC)
    {
        printf("\nWARNING STACK SIZE DECREASED\n");
    }

    if (pstack->pstack_error == ERROR_OUT_RANGE)
    {
        pstack->pstack_size++;
    }

    printf("\n\n"
           "STACK CAPACITY:      %ld\n"
           "STACK SIZE:          %d\n", pstack->pstack_capacity, pstack->pstack_size);

    if (pstack->pstack_error != ERROR_NULLPTR)
    {
        dump_top_el(pstack->pstack_pointer[pstack->pstack_size - 1]);
        print_stack(pstack);
    }
    else
    {
        printf("STACK HASN'T TOP ELEMENT : NULLPTR\n");
    }

    if (pstack->pstack_error == ERROR_WRONG_HASH)
    {
        printf("WRONG HASH, DATA LOST, PLEASE TURN ON DEBUG MODE\n\n");
    }

    if (pstack->pstack_error != OK && pstack->pstack_error != WARNING_SIZE_INC && pstack->pstack_error != WARNING_SIZE_DEC)
    {
        printf("SOMETHING WENT WRONG, TURN ON DEBUG MODE\n\n");
    }
}

int dump_loud(struct pstack_info* pstack, const char* name_of_file, const char* name_of_func)
{
    check_nullptr(pstack);

    printf("\n\n"
           "STACK CAPACITY:      %ld\n"
           "STACK SIZE:          %d\n", pstack->pstack_capacity, pstack->pstack_size);

    if (pstack->pstack_error != ERROR_NULLPTR && pstack->pstack_error != ERROR_OUT_RANGE)
    {
        dump_top_el(pstack->pstack_pointer[pstack->pstack_size - 1]);
        print_stack(pstack);
    }
    else
    {
        printf("STACK HASN'T TOP ELEMENT : NULLPTR\n");
    }
    printf("STACK STRUCT LEFT CANARY:   %lld\n",   pstack->golub_left);
    printf("STACK STRUCT RIGHT CANARY:  %lld\n",   pstack->golub_right);

    printf("STACK LEFT CANARY:          %lld\n",
           *(long long*)( (char*)pstack->pstack_pointer - sizeof(long long) ) );

    printf("STACK RIGHT CANARY:         %lld\n",
           *(long long*)( (char*)pstack->pstack_pointer + sizeof(type_array) * pstack->pstack_capacity )  );

    printf("STACK HASH:                 %lld\n\n",   pstack->hash_var);


    switch(pstack->pstack_error)
    {
        case ERROR_OUT_RANGE:
            pstack->pstack_error = 0;
            print_err_loud(ERROR_OUT_RANGE, name_of_file, name_of_func, pstack, __LINE__);
            break;

        case ERROR_WRONG_CAPACITY:
            pstack->pstack_error = 0;
            print_err_loud(ERROR_WRONG_CAPACITY, name_of_file, name_of_func, pstack, __LINE__);
            break;

        case ERROR_FULL_STACK:
            pstack->pstack_error = 0;
            print_err_loud(ERROR_FULL_STACK, name_of_file, name_of_func, pstack, __LINE__);
            break;

        case ERROR_NULLPTR:
            pstack->pstack_error = 0;
            print_err_loud(ERROR_NULLPTR, name_of_file, name_of_func, pstack, __LINE__);
            break;

        case WARNING_SIZE_DEC:
            pstack->pstack_error = 0;
            printf("STACK HAS BEEN DECREASED\n\n");
            break;

        case WARNING_SIZE_INC:
            pstack->pstack_error = 0;
            printf("STACK HAS BEEN INCREASED\n\n");
            break;

        case LEFT_STRUCT_CANAREA_DEAD:
            pstack->pstack_error = 0;
            print_err_loud(LEFT_STRUCT_CANAREA_DEAD, name_of_file, name_of_func, pstack, __LINE__);
            break;

        case RIGHT_STRUCT_CANAREA_DEAD:
            pstack->pstack_error = 0;
            print_err_loud(RIGHT_STRUCT_CANAREA_DEAD, name_of_file, name_of_func, pstack, __LINE__);
            break;

        case LEFT_STACK_CANAREA_DEAD:
            pstack->pstack_error = 0;
            print_err_loud(LEFT_STACK_CANAREA_DEAD, name_of_file, name_of_func, pstack, __LINE__);
            break;

        case RIGHT_STACK_CANAREA_DEAD:
            pstack->pstack_error = 0;
            print_err_loud(RIGHT_STACK_CANAREA_DEAD, name_of_file, name_of_func, pstack, __LINE__);
            break;

        case ERROR_WRONG_HASH:
            pstack->pstack_error = 0;
            print_err_loud(ERROR_WRONG_HASH, name_of_file, name_of_func, pstack, __LINE__);
            break;

        default:
            break;
    }
    return OK;
}


void print_err_loud(int err_num, const char* name_of_file, const char* name_of_function, pstack_info* pstack, int line_number)
{
    printf("\nERROR NUMBER #%d, check 'log.txt' \n\n", err_num);

    FILE* log = fopen("log.txt", "a");
    assert(log != nullptr);

    fprintf(log, "Stack [Error #%d] in  file \"%s\" function \"%s\" dump alerted on \"%d\" line \n",
                                err_num, name_of_file, name_of_function, line_number );

    fprintf(log, "\n\nSTACK CAPACITY: %ld\n", pstack->pstack_capacity);
    fprintf(log, "STACK SIZE: %d\n", pstack->pstack_size);

    if (err_num != ERROR_NULLPTR && err_num != ERROR_OUT_RANGE)
    {
        fprintf(log, "STACK'S TOP ELEMENT: %d\n", pstack->pstack_pointer[pstack->pstack_size - 1]);
        fprint_stack(pstack, log);
    }
    else
    {
        fprintf(log, "STACK HASN'T TOP ELEMENT : NULLPTR\n");
    }

    fprintf(log, "STACK STRUCT LEFT CANARY:   %lld\n",    pstack->golub_left);
    fprintf(log, "STACK STRUCT RIGHT CANARY:  %lld\n",  pstack->golub_right);

    fprintf(log, "STACK LEFT CANARY:          %lld\n",
           *(long long*)( (char*)pstack->pstack_pointer - sizeof(long long) ) );

    fprintf(log, "STACK RIGHT CANARY:         %lld\n",
           *(long long*)( (char*)pstack->pstack_pointer + sizeof(type_array) * pstack->pstack_capacity )  );

    fprintf(log, "STACK HASH:                 %lld\n\n",   pstack->hash_var);


    fflush(log);

    FATAL_ERROR;
}
