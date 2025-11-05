#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Structs.h"
#include "CreateListFunctions.h"
#include "SortListFunctions.h"

// Поиск самой короткой строки в списке
list_element* find_min_length_element(double_linked_list* list) {
    if (list->head == NULL) return NULL;

    list_element* current = list->head;
    list_element* min_element = current;

    while (current != NULL) {
        if (strlen(current->data) < strlen(min_element->data)) {
            min_element = current;
        }
        current = current->next;
    }

    return min_element;
}

// Удаление элемента из списка
void remove_element(double_linked_list* list, list_element* element) {
    if (element == NULL || list->head == NULL) return;

    if (element->prev != NULL) {
        element->prev->next = element->next;
    }
    if (element->next != NULL) {
        element->next->prev = element->prev;
    }

    if (element == list->head) {
        list->head = element->next;
    }
    if (element == list->tail) {
        list->tail = element->prev;
    }
}

// Функция сортировки выбором
void sort_by_length(double_linked_list* original_list, double_linked_list* sorted_list) {
    if (original_list->head == NULL) return;

    while (original_list->head != NULL) {
        list_element* min_element = find_min_length_element(original_list);

        if (min_element != NULL) {
            add_element(sorted_list, min_element->data);
            remove_element(original_list, min_element);
            free(min_element);
        }
    }
}