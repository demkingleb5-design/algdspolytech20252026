#ifndef STRUCTS_H  
#define STRUCTS_H

#include <stdio.h>

#define MAX_STRING_LENGHT 256

// Элемент (узел) списка
typedef struct list_element {
	struct list_element* next;
	struct list_element* prev;
	char data[MAX_STRING_LENGHT];
} list_element;

// Список
typedef struct double_linked_list {
	list_element* head;
	list_element* tail;
} double_linked_list;

#endif

