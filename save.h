#ifndef SAVE_H
#define SAVE_H

void save(int table_len, char *string_table[], char *file_name_to_save);
void restore(int *p_table_len, char ***p_string_table, char *file_name_to_restore);

#endif

