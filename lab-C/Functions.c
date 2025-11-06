#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Functions.h"

// Вспомогательная функция для проверки пустого файла
int Is_File_Empty(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return 1; // Файл не существует или недоступен - считаем пустым
    }

    int first_char = fgetc(file);
    fclose(file);

    if (first_char == EOF) {
        return 1; // Достигнут конец файла сразу - файл пустой
    }
    else {
        return 0; // Найден хотя бы один символ - файл не пустой
    }
}

// Основная функция
void Create_Adjacency_List(const char* Matrix_Input_File) {
    // Проверяем что файл не пустой
    if (Is_File_Empty(Matrix_Input_File)) {
        printf("Файл %s пуст - список смежности не создан\n", Matrix_Input_File);
        return;
    }

    FILE* input_file = fopen(Matrix_Input_File, "r");
    if (input_file == NULL) {
        printf("Ошибка открытия файла %s\n", Matrix_Input_File);
        return;
    }

    // Создаем файл для списка смежности
    const char* output_file_name = "Adjacency_List.txt";

    FILE* output_file = fopen(output_file_name, "w");
    if (output_file == NULL) {
        printf("Ошибка создания файла %s\n", output_file_name);
        fclose(input_file);
        return;
    }

    char line[256];
    int row = 0;

    while (fgets(line, sizeof(line), input_file) != NULL) {
        fprintf(output_file, "%d: ", row);

        char* token = strtok(line, " \t\n");
        int col = 0;
        int hasEdges = 0;

        while (token != NULL) {
            if (strcmp(token, "1") == 0) {
                fprintf(output_file, "%d ", col);
                hasEdges = 1;
            }
            col++;
            token = strtok(NULL, " \t\n");
        }

        if (hasEdges == 0) {
            fprintf(output_file, "нет смежных вершин");
        }

        fprintf(output_file, "\n");
        row++;
    }

    fclose(input_file);
    fclose(output_file);

    printf("Создан файл: %s\n", output_file_name);
}