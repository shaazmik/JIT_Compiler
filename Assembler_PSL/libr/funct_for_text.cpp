#include "Hamlet.h"


int check_input_file(FILE *in)
{
    if (!in)
    {
        printf("Error: File not found, time to play CS");
        return -1;
    }
    return 0;
}

int input_struct(FILE* in, struct Text* Denmark_sht)
{
    assert(in != NULL);
    assert(Denmark_sht != NULL);

    Denmark_sht->size_of_text = find_file_size(in);
    Denmark_sht->text_array = fill_text(in, Denmark_sht->size_of_text);

    if (Denmark_sht->text_array == nullptr) return 1;

    Denmark_sht->quantity_lines = count_line_in_text(Denmark_sht->text_array);
    Denmark_sht->linii = navigation_in_line(Denmark_sht->linii, Denmark_sht->text_array, Denmark_sht->quantity_lines);

    return 0;
}

size_t find_file_size(FILE *in)
{
    assert (in != nullptr);

    int size_of_file = 0;

    fseek (in, 0, SEEK_END);

    size_of_file = ftell (in);

    fseek (in, 0, SEEK_SET);

    return (size_of_file);
}

char* fill_text(FILE* in, size_t file_size)
{
    assert(in != nullptr);

    char* text_array = (char*) calloc(file_size + 1, sizeof(char));

    if (text_array)
    {
        fread(text_array, sizeof(char), file_size, in);
        *(text_array + file_size) = '\n';
        //(text_array + file_size + 1) ='\n';
        fseek(in, 0, SEEK_SET);
    }
    else
    {
        fseek(in, 0, SEEK_SET);
        return nullptr;
    }

    return text_array;
}


size_t count_line_in_text(char* text_array)
{
    assert(text_array != nullptr);

    char* line_start = text_array;
    char* line_ne_start = text_array;
    size_t count_line = 0;

    while ((line_ne_start = strchr(line_start, '\n')) != NULL)
    {
        line_start = line_ne_start + 1;
        count_line++;
    }

    return count_line;
}


//}

//{
struct Line* navigation_in_line(struct Line* str_array, char* text_array, size_t quantity_lines)
{
    assert(text_array != nullptr);

    str_array = (struct Line*) calloc(quantity_lines, sizeof(struct Line)); // free()

    char* pointer_start = text_array;
    char* pointer_ne_start = text_array;
    int step_for_next_line = 0;

    for (int i = 0; i < quantity_lines; i++)
    {
        pointer_ne_start = strchr(pointer_start, '\n');

        if (*(pointer_ne_start - 1) == '\r')
        {
            *(pointer_ne_start - 1) = '\0';
            pointer_ne_start = pointer_ne_start - 1;
            step_for_next_line = 2;
        }
        else
        {
            *pointer_ne_start = '\0';
            step_for_next_line = 1;
        }

        str_array[i].start_line = pointer_start;
        str_array[i].size_of_line = pointer_ne_start - pointer_start;

        pointer_start = pointer_ne_start + step_for_next_line;
    }
    return str_array;
}
//}


//{


void output_file(FILE* out, struct Text* Denmark_sht)
{
    assert(out != NULL);
    assert(Denmark_sht != NULL);

    for (int num_of_line = 0; num_of_line < Denmark_sht->quantity_lines; num_of_line++)  //
    {
        fputs(Denmark_sht->linii[num_of_line].start_line, out);
        fputc('\n', out);
    }
    return;
}


void output_text_array(FILE* out, struct Text* Denmark_sht)
{
    assert(out != nullptr);
    assert(Denmark_sht != nullptr);

    char* text_start = Denmark_sht->text_array;

    for (int number_of_line = 0; number_of_line < Denmark_sht->quantity_lines; number_of_line++)
    {
        fputs(text_start, out);

        text_start = strchr(text_start, '\0') + 1;
    }
}

void free_memory(struct Text* Denmark_sht)
{
    free(Denmark_sht->text_array);
    free(Denmark_sht->linii);

    Denmark_sht->linii = nullptr;
    Denmark_sht->text_array = nullptr;
}
//}
