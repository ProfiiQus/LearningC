#include <stdio.h>
#include <stdlib.h>

/// @brief Custom structure representing an example contact with name and address.
typedef struct Contact {
    /// @brief Contact's name
    char* name;
    /// @brief Contact's address
    char* address;
} Contact;

/// @brief Custom structure representing a contact book (array of contacts).
typedef struct ContactBook {
    /// @brief Pointer to the contact array
    Contact* contacts;
    /// @brief Maximum current size of the contact array
    /// @details Dynamically regrown with grow_contact_book method
    size_t max_size;
    /// @brief Current size of the contact array (how many are added)
    /// @details Increases automatically whenever new contacts are added
    size_t size;
} ContactBook;

const int DEFAULT_ARRAY_SIZE = 4;

/// @brief Initializes a new contact book in the memory.
/// @details Sets the starting maximum size to the value of constant DEFAULT_ARRAY_SIZE.
///          Sets the current array size to 0.
/// @return Pointer to the newly initialized contact book.
ContactBook* initialize_contact_book() {
    ContactBook* contact_book = malloc(sizeof(ContactBook));
    contact_book->max_size = DEFAULT_ARRAY_SIZE;
    contact_book->contacts = malloc(contact_book->max_size * sizeof(Contact));
    contact_book->size = 0;

    return contact_book;
}

/// @brief Grows the given contact book to double of it's current size.
/// @param contact_book Contact book to grow
void grow_contact_book(ContactBook* contact_book) {
    contact_book->max_size *= 2;
    contact_book->contacts = realloc(contact_book->contacts, contact_book->max_size * sizeof(Contact));
}

/// @brief Adds new contact to the provided contact book.
/// @details When size runs out in the contact_book, calls the grow_contact_book to automatically create new space.
///          After done writing to the book, the realloc_contact_book method should be called to free all unused memory.
/// @param contact_book The contact book to add new contact to
/// @param contact The new contact to add
void add_contact(ContactBook* contact_book, Contact contact) {
    // Check if the book is big enough.
    // If not, grow it to double it's size.
    if(contact_book->size == contact_book->max_size) {
        grow_contact_book(contact_book);
    }

    // Add the new contact and increase the current size.
    contact_book->contacts[contact_book->size] = contact;
    contact_book->size++;
}

/// @brief Reallocates the given contact book to the smallest possible memory neeeded.
/// @details Should be called after done writing to the given contact book.
/// @param contact_book Contact book to reallocate
void realloc_contact_book(ContactBook* contact_book) {
    contact_book->max_size = contact_book->size;
    contact_book->contacts = realloc(contact_book->contacts, contact_book->max_size * sizeof(Contact));
}

/// @brief Frees the given contact book and all of it's content from the memory.
/// @param contact_book Contact book to free from memory
void free_contact_book(ContactBook* contact_book) {
    free(contact_book->contacts);
    free(contact_book);
}

/// @brief Example usage in the main method.
/// @return True as the output should be always successful :-).
int main() {
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
    return 0;
}