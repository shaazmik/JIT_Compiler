#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include ".\libr\Hamlet.h"



int main()
{
    FILE* in = fopen("play.txt", "rb");

    struct Text text_struct = {};

    input_struct(in, &text_struct);

    fclose(in);

    int cht = 0;

    FILE* out = fopen("play_video.txt", "wb");

    for (int i = 0; i < text_struct.size_of_text; i++)
    {   
        if (text_struct.text_array[i] == '\n' || text_struct.text_array[i] == '\0') continue;

        if (text_struct.text_array[i] == ' ')
        {
            fprintf(out, "PUSH 0\nPOP [%d]\n", cht);
        }
        else
        {
            fprintf(out, "PUSH 1\nPOP [%d]\n", cht);        
        }
        
        cht++;

        if (cht == 3000) 
        {
            cht = 0;
            fprintf(out, "PRINT_CADR\n");
        }
        
    }

    fprintf(out, "HLT");

    fclose(out);    
}