# array_of_structs.c

Example of a custom, dynamically grown array for storing custom data structures. Demonstrated on a `ContactBook` storing custom `Contact` structures with contact names and their respective addresses.

Contains functions that initialize the `ContactBook`, add new `Contact` structures to this book, dynamically grow it and after being done writing done reallocating it to it's minimal possible size to free up memory.

Tested with **Valgrind** for potential memory leaks.

## Example usage

```c
// Initialize new contact book
ContactBook* contact_book = initialize_contact_book();

// Add some contacts to the book
// Array begins with size 4 and is automatically regrown (reallocated) to double it's size when space runs up.
Contact contact1 = {"Pavel Fesenko", "Development Street 12"};
Contact contact2 = {"Harry Potter", "Hogwarts, room 164"};
Contact contact3 = {"Joshamie Gibbs", "Tortuga 322"};
Contact contact4 = {"Captain Picard", "Starfleet HQ"};
Contact contact5 = {"Ron Weasley", "Hogwarts, room 164"};
add_contact(contact_book, contact1);
add_contact(contact_book, contact2);
add_contact(contact_book, contact3);
add_contact(contact_book, contact4);
add_contact(contact_book, contact5);

// As we are done writing data into the book, we can now shrink it dynamically to free up additional memory.
// This can be done simply by calling the method below.
realloc_contact_book(contact_book);

// Print the contacts in the book
Contact contact;
for(int i = 0; i < contact_book->size; i++) {
    contact = contact_book->contacts[i];
    printf("%s - %s\n", contact.name, contact.address);
}

// Finally free all the memory
free_contact_book(contact_book);
```