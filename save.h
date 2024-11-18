#ifndef SAVE_H
#define SAVE_H

char ** getQuantList();

int save_string_array_in_file(char ** words, int length, char * file_name);
int restore_string_array_from_file(char ** words, int length, char * file_name);

#endif

