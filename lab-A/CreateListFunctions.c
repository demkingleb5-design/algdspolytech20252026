#define _CRT_SECURE_NO_WARNINGS // чтобы работал strncpy

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Structs.h"
#include "CreateListFunctions.h"

// Создание элемента
list_element* create_element(const char* data) {
    list_element* new_element = (list_element*)malloc(sizeof(list_element));
    if (new_element == NULL) {
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }

    strncpy(new_element->data, data, MAX_STRING_LENGHT - 1);
    new_element->data[MAX_STRING_LENGHT - 1] = '\0';

    new_element->next = NULL;
    new_element->prev = NULL;

    return new_element;
}

// Инициализация пустого списка
void initialize_list(double_linked_list* list) {
    list->head = NULL;
    list->tail = NULL;
}

// Добавление элемента в конец списка
void add_element(double_linked_list* list, const char* data) {
    list_element* new_element = create_element(data);
    if (new_element == NULL) return;

    if (list->head == NULL) {
        list->head = new_element;
        list->tail = new_element;
    }
    else {
        new_element->prev = list->tail;
        list->tail->next = new_element;
        list->tail = new_element;
    }
}

// Печать списка
void print_list(double_linked_list* list) {
    if (list->head == NULL) {
        printf("Список пуст!\n");
        return;
    }

    list_element* current = list->head;
    int index = 1;
    while (current != NULL) {
        printf("%d. [ %s ] (%zu символов)\n", index, current->data, strlen(current->data));
        current = current->next;
        index++;
    }
    printf("\n");
}

// Удаление списка и освобождение памяти
void delete_list(double_linked_list* list) {
    list_element* current = list->head;
    while (current != NULL) {
        list_element* next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
    list->tail = NULL;
}