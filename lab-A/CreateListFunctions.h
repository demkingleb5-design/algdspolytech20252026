#ifndef LIST_FUNCTIONS_H
#define LIST_FUNCTIONS_H

#include "Structs.h"

// Создание элемента
list_element* create_element(const char* data);

// Инициализация пустого списка
void initialize_list(double_linked_list* list);

// Добавление элемента в конец списка
void add_element(double_linked_list* list, const char* data);

// Печать списка
void print_list(double_linked_list* list);

// Удаление списка и освобождение памяти
void delete_list(double_linked_list* list);

#endif
