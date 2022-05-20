#include "Stack.h"

#ifdef Double_t
    void dump_value  (double value)            {printf ("%lg ", value);     }
    void fdump_value (double value, FILE* log) {fprintf (log, "%ld", value); }
#endif

#ifdef Int_t
    void dump_value  (int value)                {printf ("%d ", value);     }
    void fdump_value (int value, FILE* log)     {fprintf (log, "%d", value); }

#endif

#ifdef Str_t
    void dump_value (const char* str)             {printf ("%s ", str);       }
    void fdump_value (const char* str, FILE* log) {fprintf (log, "%s", value);}

#endif

int stack_constructor(struct pstack_info* pstack, int pstack_user_size)
{
    #ifdef PROTECTION

    check_nullptr(pstack);

    if (check_construct(pstack) == ERROR_UNKNOWN)
    {
        return ERROR_UNKNOWN;
    }

    #endif

    if (pstack_user_size < 0)
    {
        printf("Negative value, take the number module\n\n");
        pstack_user_size = abs(pstack_user_size);
    }

    pstack->golub_left  = Dog;
    pstack->golub_right = Dog;

    pstack->des_status  = DES_STATUS_OK;

    pstack->pstack_size = 0;
    pstack->pstack_capacity = pstack_user_size;

    pstack->pstack_error = 0;

    pstack->pstack_pointer = (type_array*)calloc(pstack->pstack_capacity * sizeof(type_array) + 2 * sizeof(long long),
                                                 sizeof(char));

    if (check_memory(pstack->pstack_pointer))
    {
        printf("SIZE ERROR: TOO MUCH REQUESTED MEMORY\n"
               "DEFAULT SIZE OF STACK:%d\n\n ", Default_size_of_pstack);

        pstack->pstack_capacity = Default_size_of_pstack;

        pstack->pstack_pointer = (type_array*)calloc(pstack->pstack_capacity * sizeof(type_array) + 2 * sizeof(long long),
                                                     sizeof(char));
    }

    *( (long long*) (pstack->pstack_pointer) ) = pstack->golub_left;

    pstack->pstack_pointer = (type_array*)((char*)pstack->pstack_pointer + 1 * sizeof(long long));

    *( (long long*) (pstack->pstack_pointer + pstack->pstack_capacity) ) = pstack->golub_right;

    pstack->con_status = STACK_IS_CONSTURCTED;

    pstack->hash_var = hash_calc(pstack);

    #ifdef PROTECTION
    
    verification_stack(pstack);
    
    #endif

    return OK;
}


void print_stack(struct pstack_info* pstack)
{
    printf("STACK: ");

    for (int i = 0; i < pstack->pstack_size; i++)
    {
        dump_value(pstack->pstack_pointer[i]);
    }
    printf("\n");
}

void fprint_stack(struct pstack_info* pstack, FILE* log)
{
    fprintf(log,"STACK: ");

    for (int i = 0; i < pstack->pstack_size; i++)
    {
        fdump_value(pstack->pstack_pointer[i], log);
    }
    fprintf(log, "\n");
}

int stack_pushka(struct pstack_info* pstack, type_array new_element)
{       
    check_nullptr(pstack);

    #ifdef PROTECTION

    verification_stack(pstack);

    #endif

    if ((pstack->pstack_size == pstack->pstack_capacity) && (pstack->inc_counter <= Pstack_inc_max))
    {
        pstack->pstack_error = pstack_resizemo(pstack);
        pstack->pstack_pointer[pstack->pstack_size] = new_element;
        pstack->pstack_size++;
        dump_stack(pstack);
    }
    else
    {
        pstack->pstack_pointer[pstack->pstack_size] = new_element;
        pstack->pstack_size++;
    }

    pstack->hash_var = hash_calc(pstack);

    #ifdef PROTECTION

    verification_stack(pstack);

    #endif

    return OK;
}


type_array stack_popka(struct pstack_info* pstack)
{
    check_nullptr(pstack);

    #ifdef PROTECTION

    verification_stack(pstack);

    #endif

    pstack->pstack_size--;
    type_array pop_result = pstack->pstack_pointer[pstack->pstack_size];

    pstack->hash_var = hash_calc(pstack);

    #ifdef PROTECTION

    verification_stack(pstack);

    #endif

    if ( (pstack->pstack_size == pstack->pstack_capacity - 2 * Pstack_multiplier) && (pstack->inc_counter > 1))
    {
        pstack->pstack_error = pstack_resizele(pstack);
        pstack->hash_var = hash_calc(pstack);
        dump_stack(pstack);
    }


    return pop_result;
}


int pstack_resizemo(struct pstack_info* pstack)
{
    *(long long*)( (char*)pstack->pstack_pointer + sizeof(type_array) * pstack->pstack_capacity) = 0;

    pstack->pstack_capacity += Pstack_multiplier;

    type_array* temp_pointer = pstack->pstack_pointer;

    pstack->pstack_pointer = (type_array*)realloc( (char*)pstack->pstack_pointer - 1 * sizeof(long long),
                                                   pstack->pstack_capacity * sizeof(type_array)
                                                   + 2 * sizeof(long long) );

    if (pstack->pstack_pointer == nullptr)
    {
        pstack->pstack_pointer = temp_pointer;

        printf("ERROR REALLOCATION, EXTENSION FAILED\n\n");
        return ERROR_MEMORY_RESIZE_FAILED;
    }

    pstack->pstack_pointer = (type_array*)((char*)pstack->pstack_pointer + 1 * sizeof(long long));

    *(long long*)( (char*)pstack->pstack_pointer + sizeof(type_array) * pstack->pstack_capacity) = Dog;

    pstack->inc_counter++;

    return WARNING_SIZE_INC;
}


int pstack_resizele(struct pstack_info* pstack)
{
    *(long long*)( (char*)pstack->pstack_pointer + sizeof(type_array) * pstack->pstack_capacity) = 0;

    pstack->pstack_capacity -= Pstack_multiplier;

    type_array* temp_pointer = pstack->pstack_pointer;

    pstack->pstack_pointer = (type_array*)realloc( (char*)pstack->pstack_pointer - 1 * sizeof(long long),
                                                   pstack->pstack_capacity * sizeof(type_array)
                                                   + 2 * sizeof(long long) );
    if (pstack->pstack_pointer == nullptr)
    {
        pstack->pstack_pointer = temp_pointer;

        printf("ERROR REALLOCATION, EXTENSION FAILED\n\n");
        return ERROR_MEMORY_RESIZE_FAILED;
    }

    pstack->pstack_pointer = (type_array*)((char*)pstack->pstack_pointer + 1 * sizeof(long long));

    *(long long*)( (char*)pstack->pstack_pointer + sizeof(type_array) * pstack->pstack_capacity) = Dog;


    pstack->inc_counter--;

    return WARNING_SIZE_DEC;
}

int stack_destructor(struct pstack_info* pstack)
{
    check_nullptr(pstack);

    #ifdef PROTECTION

    if (check_destruct(pstack) == ERROR_UNKNOWN)
    {
        return ERROR_UNKNOWN;
    }

    #endif

    free((char*)pstack->pstack_pointer - 1 * sizeof(long long));
    pstack->pstack_pointer = nullptr;
    pstack->pstack_size = 0;
    pstack->pstack_error = 0;
    pstack->pstack_capacity = 0;

    FILE* log = fopen("log.txt", "w");
    fclose(log);

    pstack->des_status++;

    return OK;
}
