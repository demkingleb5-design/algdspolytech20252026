#ifndef SORT_FUNCTIONS_H
#define SORT_FUNCTIONS_H

#include "Structs.h"

// Функция сортировки выбором по длине строки
void sort_by_length(double_linked_list* source_list, double_linked_list* sorted_list);

// Функция удаления элемента
void remove_element(double_linked_list* list, list_element* element);

// Функция поиска самой короткой строки в списке
list_element* find_min_length_element(double_linked_list* list);

#endif
