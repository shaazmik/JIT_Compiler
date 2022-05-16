#include "Hamlet.h"

void swap_var(struct Line* first_var, struct Line* second_var)
{
    assert(first_var != nullptr);
    assert(second_var != nullptr);

    struct Line obmen = *first_var;
                        *first_var  = *second_var;
                                      *second_var = obmen;

    return;
}

int comporator_terminator(const void *first_var, const void *second_var)
{
    int T = 0;
    *(int*)T = 9000;  // Here comes The Terminator.
}

int comparator_paramonator(const void *first_var, const void *second_var)
{
    char* first_var_start     = ((struct Line*) first_var )->start_line;
    char* first_var_ne_start  = ((struct Line*) first_var )->start_line + ((struct Line*) first_var)->size_of_line;
    char* second_var_start    = ((struct Line*) second_var)->start_line;
    char* second_var_ne_start = ((struct Line*) second_var)->start_line + ((struct Line*) second_var)->size_of_line;

    while (isalnum((int)(unsigned char)*first_var_start ) == 0 && *first_var_start != '\0') first_var_start++;
    while (isalnum((int)(unsigned char)*second_var_start) == 0 && *second_var_start != '\0') second_var_start++;

    while (first_var_start != first_var_ne_start && second_var != second_var_ne_start && *first_var_start == *second_var_start)
    {
        first_var_start++;
        second_var_start++;

        while (isalnum((int)(unsigned char)*first_var_start ) == 0 && first_var_start != first_var_ne_start) first_var_start++;
        while (isalnum((int)(unsigned char)*second_var_start) == 0 && second_var_start != second_var_ne_start) second_var_start++;
    }

    return ((int)(unsigned char)(*first_var_start) - (int)(unsigned char)(*second_var_start));
}

int comparator_refrigerator(const void *first_var, const void *second_var)
{
    char* first_var_start     = ((struct Line*) first_var )->start_line + ((struct Line*) first_var)->size_of_line - 1;
    char* first_var_ne_start  = ((struct Line*) first_var )->start_line;
    char* second_var_start    = ((struct Line*) second_var)->start_line + ((struct Line*) second_var)->size_of_line - 1;
    char* second_var_ne_start = ((struct Line*) second_var)->start_line;

    while (isalnum((int)(unsigned char)*first_var_start ) == 0 && *first_var_start != '\0')
        first_var_start--;
    while (isalnum((int)(unsigned char)*second_var_start) == 0 && *second_var_start != '\0')
        second_var_start--;

    while (*first_var_start == *second_var_start && second_var_start != second_var_ne_start && first_var_start != first_var_ne_start)
    {
        first_var_start--;
        second_var_start--;

        while (isalnum((int)(unsigned char)*first_var_start ) == 0 && first_var_start != first_var_ne_start && *first_var_start != '\0')
            first_var_start--;
        while (isalnum((int)(unsigned char)*second_var_start) == 0 && second_var_start != second_var_ne_start && *second_var_start != '\0')
            second_var_start--;
    }

    return ((int)(unsigned char)(*first_var_start) - (int)(unsigned char)(*second_var_start));
}


void bubble_sort(struct Line* linii, const size_t count_lines, int(*paramonator) (const void*, const void*))
{
    assert(linii != nullptr);
    assert(paramonator != nullptr);

    for (int i = 0; i < count_lines - 1; i++)
    {
        for (int j = 0; j < count_lines - i - 1; j++)
        {
            if (( paramonator(&linii[j], &linii[j + 1]) ) > 0)
                swap_var(&linii[j], &linii[j + 1]);

        }
    }
}


void paramon_sort(struct Line* linii, const size_t count_lines, int(*paramonator) (const void*, const void*))
{
    assert(linii != nullptr);
    assert(paramonator != nullptr);


    int i_1 = 0;
    int i_2 = count_lines - 1;

    struct Line middle_awp = linii[count_lines / 2];

    do
    {
        while(paramonator(&linii[i_1], &middle_awp) < 0)
        {
            i_1++;
        }

        while(paramonator(&linii[i_2], &middle_awp) > 0)
        {
            i_2--;
        }


        if (i_1 <= i_2)
        {
            swap_var(&linii[i_1], &linii[i_2]);

            i_1++;
            i_2--;
        }
    } while (i_1 <= i_2);


    if(i_2 > 0)
    {
        paramon_sort(linii, i_2 + 1, paramonator);
    }

    if (i_1 < count_lines)
    {
        paramon_sort(&linii[i_1], count_lines - i_1, paramonator);
    }
}

