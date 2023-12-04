#include <stdio.h>
#include <stdlib.h>

const int STRING_INITIAL_SIZE = 4;

typedef struct String {
    char* content;
    size_t size;
    size_t max_size;
} String;

String* initialize_string(char c) {
    // Create initial string with STRING_INITIAL_SIZE size
    // Add extra symbol to facilitate \0.
    char* content = malloc((STRING_INITIAL_SIZE + 1) * sizeof(char));
    String* string = malloc(sizeof(String));
    string->content = content;
    string->content[0] = c;
    string->content[1] = '\0';
    string->max_size = STRING_INITIAL_SIZE;
    string->size = 1;

    return string;
}

void append_to_string(String* string, char c) {
    if(string->size == string->max_size) {
        string->max_size *= 2;
        char* new_content = realloc(string->content, (string->max_size + 1) * sizeof(char));
        string->content = new_content;
    }
    string->content[string->size] = c;
    string->size++;
    string->content[string->size] = '\0';
}

void free_string(String* string) {
    free(string->content);
    free(string);
}

void print_string(String* string) {
    for(int i = 0; i < string->size; i++) {
        printf("%c", string->content[i]);
    }
    printf("\n");
}

int main() {
    String* string = initialize_string('A');
    append_to_string(string, 'h');
    append_to_string(string, 'o');
    append_to_string(string, 'j');
    append_to_string(string, 'k');
    append_to_string(string, 'y');
    print_string(string);
    free_string(string);

    return 0;
}