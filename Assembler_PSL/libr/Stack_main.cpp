#include "Stack.h"

#define $(value)     { printf ("got result: " #value " = %d", value); printf ("\n\n"); }

#ifdef Double_t
    void dump_pop (double value)          {printf ("pop = %lg\n\n", value);  }
#endif

#ifdef Int_t
    void dump_pop (int value)             {printf ("pop = %d\n\n", value);  }
#endif

#ifdef Str_t
    void dump_pop (const char* str)       {printf ("pop = %s\n\n", str);    }
#endif

int main()
{

    struct pstack_info pstack = {};

    int capacity = 0;
    printf ("Input stack capacity:\n");
    scanf  ("%d", &capacity);

    stack_construct(&pstack, capacity);

    stack_pushka(&pstack, 123);
    stack_pushka(&pstack, 124);

    stack_pushka(&pstack, 44);

    dump_pop(stack_popka(&pstack));
    dump_pop(stack_popka(&pstack));

    stack_destruct(&pstack);


    return OK;
}
