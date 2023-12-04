#include <stdio.h>
#include <stdlib.h>

const int STRING_INITIAL_SIZE = 4;

/// @brief Structure representing a string.
/// @param content Pointer to the string's real content.
/// @param size The current size of the string.
/// @param max_size The maximum size the string can hold. Can be dynamically grown. 
typedef struct String {
    char* content;
    size_t size;
    size_t max_size;
} String;

/// @brief Initializes a new instance of a string from an existing character.
/// @details The string is initialized with the default size of STRING_INITIAL_SIZE const.
///          Needs to later be freed using the free_string(String* string) function.
/// @param c Character to initialize the string from (first char).
/// @return Pointer to the newly initialized string.
String* initialize_string(char c) {
    // Create initial string with STRING_INITIAL_SIZE size
    // Add extra symbol to facilitate \0.
    char* content = malloc((STRING_INITIAL_SIZE + 1) * sizeof(char));
    String* string = malloc(sizeof(String));
    string->content = content;

    // Load the first char and string closing character
    string->content[0] = c;
    string->content[1] = '\0';

    // Set size and max_size
    string->max_size = STRING_INITIAL_SIZE;
    string->size = 1;

    return string;
}

/// @brief Function that appends a character to an existing String.
/// @details Function automatically handles string max_size growth.
///          When the size reaches the maximum size, automatically allocates double the space.
///          For bigger strings, realloc_string(String* string) should be later used to allocate the exact required space.
/// @param string Pointer to string to which the char should be appended to.
/// @param c Character to append.
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

/// @brief Function that resizes the string to it's maximum size.
/// @details Frees the memory that is not needed by the rest of the string. Especially useful on large strings.
///          Should be used after done writing to the string.
/// @param string String to dynamically realloc
void realloc_string(String* string) {
    string->max_size = string->size;
    char* new_content = realloc(string->content, (string->max_size + 1) * sizeof(char));
    string->content = new_content;
    string->content[string->size] = '\0';
}

/// @brief Frees the given string from the memory.
/// @details Also frees the string's content.
/// @param string String to free from memory
void free_string(String* string) {
    free(string->content);
    free(string);
}

/// @brief Prints the given string to the console.
/// @param string String to print
void print_string(String* string) {
    for(int i = 0; i < string->size; i++) {
        printf("%c", string->content[i]);
    }
    printf("\n");
}

/// @brief Retrieves the last character of the given string.
/// @param string String to retrieve the last character of.
/// @return Last character of the given string.
char last_char_of_string(String* string) {
    return string->content[string->size-1];
}