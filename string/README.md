# string.c

Custom implementation of a string structure and surrounding utility functions for a homework, where `std::string` was not allowed. The class does not implement all of the utility functions one might need in a production environment.

The class has been tested with **Valgrind** to prevent the most obvious memory leaks.

## Example usage

```c
// Create a 'Hello!' string
String* string = initialize_string('H');
append_to_string(string, 'e');
append_to_string(string, 'l');
append_to_string(string, 'l');
append_to_string(string, 'o');
append_to_string(string, '!');

// Print the string to console
print_string(string);

// Print the last character
printf("%c\n", last_char_of_string(string));

// Reallocate to free up unused memory
realloc_string(string);

// Free the memory after done using it
free_string(string);
```