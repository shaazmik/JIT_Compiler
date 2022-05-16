//!@mainpage
//!This program works with .txt files.
//!It sorts text with 2 types (alphabetical and reverse(rthymes))
//!Input name of file in console
//!You should have saved your file with cpp file in folder
//!After that you have new .txt file in folder
//!Name of .txt file is Text_sorted.txt

#ifndef HAMLET_H
#define HAMLET_H

//#include "C:/coder1337/TX/TXLib.h"
#include <assert.h>
#include <stdint.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//=================================

/*!
 *  \brief it struct of line, need in work with line
 *  \param[in] char pointer start_line - pointer for start line
 *  \param[in] size_of_line - length of line
 */

struct Line
    {
        char* start_line;
        size_t size_of_line;
    };

/*!
 *  \brief It is struct of inputed text, need in work with Name.txt. That done for convenient addressing
 *  \param[in] quantity_lines - count of lines in Name.txt
 *  \param[in] size_of_text - count of all symbols in Name.txt
 *  \param[in] char pointer text_array - array of all char symbols in Name.txt
 *  \param[in] struct Line pointer linii - array of struct line, where will be saved lines of Name.txt
 */

struct Text
    {
        size_t quantity_lines;
        size_t size_of_text;
        char * text_array;
        struct Line* linii;
    };


//==================================

/*!
 *  \brief check pointer in for nullptr
 *  \param[in] file pointer in -
 *  \return -1 if nullptr of text array, else 0
 */

int check_input_file(FILE *in);


/*!
 *  \brief make struct of Text
 *  \param[in] file pointer in - pointer your Name.txt file
 *  \param[in] struct pointer Text - pointer of struct Text
 *  \return 1 if has nullptr, else return 0
 */

int input_struct(FILE* in, struct Text* Denmark_sht);


/*!
 *  \brief function for searching count of all symbols in Name.txt
 *  \param[in] File pointer in - pointer for opened file Name.txt
 *  \param[out] count of all symbols in Name.txt
 *  \return file size
 */

size_t find_file_size(FILE *in);



/*!
 *  \brief
 *  \param[in] File pointer in - pointer for opened file Name.txt
 *  \param[in] size_t file_size - size of inputed file Name.txt
 *  \return array of char
 */

char* fill_text(FILE* in, size_t file_size);



/*!
 *  \brief function for searching count of line in Name.txt
 *  \param[in] char pointer text_array - array of all char symbols in Name.txt
 *  \return count of lines in Name.txt
 */

size_t count_line_in_text(char* text_array);




/*!
 *  \brief stay pointer in line array
 *  \param[in] char pointer text_array - all chars in Name.txt
 *  \param[in] size_t quantity_lines - count of lines in Name.txt
 *  \param[out] struct pointer Line srt_array - struct Line array with pointer in start of line
 */


struct Line* navigation_in_line(struct Line* str_array, char* text_array, size_t quantity_lines);



/*!
 *  \brief typical sort function
 *  \param[in] struct pointer Line linii - array of lines
 *  \param[in] const size_t count_lines - count of lines in Name.txt
 *  \param[in] int pointer paramonator - it is comparator for function
 *  \param[out] struct pointer Line linii - sorted lines of text
 */

void bubble_sort(struct Line* linii, const size_t count_lines, int(*paramonator) (const void*, const void*));


/*!
 *  \brief function for compare two string
 *  \param[in] const void pointer first_var - pointer to get line
 *  \param[in] const void pointer second_var - pointer to get line
 *  \return >0 first_var > second_var ; <0 second_var > first_var; =0 second_var = first_var
 */

int comparator_paramonator(const void *first_var, const void *second_var);



/*!
 *  \brief function to swap 2 values
 *  \param[in] struct Line pointer first_var - line number 1
 *  \param[in] struct Line pointer second_var - line number 2
 */


void swap_var(struct Line* first_var, struct Line* second_var);



/*!
 *  \brief function to reverse compare two lines
 *  \param[in] const void pointer first_var - pointer to get line
 *  \param[in] const void pointer second_var - pointer to get line
 *  \return >0 first_var > second_var ; <0 second_var > first_var; =0 second_var = first_var
 */

int comparator_refrigerator(const void *first_var, const void *second_var);




/*!
 *  \brief quick sort function
 *  \param[in] struct pointer Line linii - array of lines
 *  \param[in] const size_t count_lines - count of lines in Name.txt
 *  \param[in] int pointer paramonator - it is comparator for function
 *  \param[out] struct pointer Line linii - sorted lines of text
 */

void paramon_sort(struct Line* linii, const size_t count_lines, int(*paramonator) (const void*, const void*));


/*!
 *  \brief output text in Text_sorted.txt
 *  \param[in] file pointer out - pointer your Text_sorted.txt file
 *  \param[in] struct pointer Text Denmarl_sht - pointer of struct Text
 */

void output_file(FILE* out, struct Text* Denmark_sht);


/*!
 *  \brief output original text in Text_sorted.txt
 *  \param[in] file pointer outs - pointer your Text_sorted.txt file
 *  \param[in] struct pointer Text Denmarl_sht - pointer of struct Text
 */

void output_text_array(FILE* out, struct Text* Denmark_sht);



/*!
 *  \brief free all using memory
 *  \param[in] struct Text pointer Denmark_sht - using to give all pointers from text and lines
 */


void free_memory(struct Text* Denmark_sht);




/*!
 *  \brief NYYYYYAN
 */

int comporator_terminator(const void *first_var, const void *second_var);


#endif // HAMLET_H
