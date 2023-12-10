#include <stdio.h>
#include <stdlib.h>

typedef struct Element {
    int value;
    struct Element* next;
} Element;

Element* first;

void append_element(Element* element) {
    if(first == NULL) {
        first = element;
        first->next = NULL;
        return;
    }

    Element* iterator = first;
    while(iterator->next != NULL) {
        iterator = iterator->next;
    }
    iterator->next = element;
    element->next = NULL;
}

void free_element(Element* element) {
    if(element != NULL) {
        free_element(element->next);
        free(element);
    }
}

int main() {
    Element* element1 = malloc(sizeof(Element));
    element1->next = NULL;
    element1->value = 10;
    append_element(element1);

    Element* element2 = malloc(sizeof(Element));
    element2->next = NULL;
    element2->value = 5;
    append_element(element2);

    Element* element3 = malloc(sizeof(Element));
    element3->next = NULL;
    element3->value = 1;
    append_element(element3);

    Element* element4 = malloc(sizeof(Element));
    element4->next = NULL;
    element4->value = 19;
    append_element(element4);

    Element* iterator = first;
    while(iterator != NULL) {
        printf("%d\n", iterator->value);
        iterator = iterator->next;
    }

    free_element(first);
}