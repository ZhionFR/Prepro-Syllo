#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void save(int table_len, char *string_table[], char *file_name_to_save) {
    // Open the file for writing.
    int fd = open(file_name_to_save, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Save : Error opening file for saving");
        return;
    }

    // Write the length of the table
    if (write(fd, &table_len, sizeof(int)) != sizeof(int)) {
        perror("Save : Error writing table length");
        close(fd);
        return;
    }

    // Write each string.
    for (int i = 0; i < table_len; i++) {
        int str_len = strlen(string_table[i]) + 1;
        // Write the length of the string.
        if (write(fd, &str_len, sizeof(int)) != sizeof(int)) {
            perror("Save : Error writing string length");
            close(fd);
            return;
        }
        // Write the string itself.
        if (write(fd, string_table[i], str_len) != str_len) {
            perror("Save : Error writing string");
            close(fd);
            return;
        }
    }
    close(fd);
}

void restore(int *p_table_len, char ***p_string_table, char *file_name_to_restore) {
    // Open the file for reading
    int fd = open(file_name_to_restore, O_RDONLY);
    if (fd == -1) {
        perror("Restore : Error opening file for restoring");
        return;
    }

    // Read the length of the table.
    if (read(fd, p_table_len, sizeof(int)) != sizeof(int)) {
        perror("Restore : Error reading table length");
        close(fd);
        return;
    }

    // Allocate memory for the table of strings.
    *p_string_table = (char **)malloc((*p_table_len + 1) * sizeof(char *));
    if (*p_string_table == NULL) {
        perror("Restore : Error allocating memory for string table");
        close(fd);
        return;
    }

    // Read each string.
    for (int i = 0; i < *p_table_len; i++) {
        int str_len;
        // Read the length of the string.
        if (read(fd, &str_len, sizeof(int)) != sizeof(int)) {
            perror("Restore : Error reading string length");
            close(fd);
            return;
        }

        // Allocate memory for the string.
        (*p_string_table)[i] = (char *)malloc(str_len);
        if ((*p_string_table)[i] == NULL) {
            perror("Restore : Error allocating memory for string");
            close(fd);
            return;
        }

        // Read the string itself.
        if (read(fd, (*p_string_table)[i], str_len) != str_len) {
            perror("Restore : Error reading string");
            close(fd);
            return;
        }
    }

    (*p_string_table)[*p_table_len] = NULL;

    // Close the file.
    close(fd);
}

void restoreAndAdd(int *p_table_len, char ***p_string_table, char *file_name_to_restore, char *string_to_add) {
    // Open the file for reading
    int fd = open(file_name_to_restore, O_RDONLY);
    if (fd == -1) {
        perror("Restore_and_add : Error opening file for restoring");
        return;
    }

    // Read the length of the table.
    if (read(fd, p_table_len, sizeof(int)) != sizeof(int)) {
        perror("Restore_and_add : Error reading table length");
        close(fd);
        return;
    }

    // Allocate memory for the table of strings.
    *p_string_table = (char **)malloc(*p_table_len * sizeof(char *));
    if (*p_string_table == NULL) {
        perror("Restore_and_add : Error allocating memory for string table");
        close(fd);
        return;
    }

    // Read each string.
    for (int i = 0; i < *p_table_len; i++) {
        int str_len;
        // Read the length of the string.
        if (read(fd, &str_len, sizeof(int)) != sizeof(int)) {
            perror("Restore_and_add : Error reading string length");
            close(fd);
            return;
        }

        // Allocate memory for the string.
        (*p_string_table)[i] = (char *)malloc(str_len);
        if ((*p_string_table)[i] == NULL) {
            perror("Restore_and_add : Error allocating memory for string");
            close(fd);
            return;
        }

        // Read the string itself.
        if (read(fd, (*p_string_table)[i], str_len) != str_len) {
            perror("Restore_and_add : Error reading string");
            close(fd);
            return;
        }
    }

    // Close the file.
    close(fd);

    // Add the new string to the table.
    *p_string_table = realloc(*p_string_table, (*p_table_len + 1) * sizeof(char *));
    if (*p_string_table == NULL) {
        perror("Restore_and_add : Error reallocating memory for string table");
        return;
    }

    (*p_string_table)[*p_table_len] = strdup(string_to_add); // Copy the new string
    if ((*p_string_table)[*p_table_len] == NULL) {
        perror("Restore_and_add : Error duplicating string");
        return;
    }

    (*p_table_len)++;
}

// Function to add a new string to the list
char **addstr(char **list, char *new) {

    // Find the current size of the list by checking for NULL pointers.
    int i = 0;
    while (list[i] != NULL) {
        i++;
    }

    int n = strlen(new);
    new[n-1] = '\0';
    list[i] = (char*)malloc(n * sizeof (char));
    strcpy(list[i], new);

    return list;
}



