#define _CRT_SECURE_NO_WARNINGS

#include "file_io.h"                // Наши объявления функций ввода/вывода
#include <stdio.h>                  // fopen, fclose, fscanf, fprintf
#include <stdlib.h>                 // malloc, free

/*
    Читает входной файл и создаёт массив телеграмм.

    Почему много указателей в параметрах:
      - функция должна "вернуть" несколько значений (массив, T и K),
        поэтому отдаём их через параметры-указатели.
*/
int read_input_file(const char* filename,
    Telegram** telegrams_out,
    int* telegramCount_out,
    long long* maxAllowedPenalty_out) {

    // Открываем файл на чтение
    FILE* file = fopen(filename, "r");
    // Если не открылся — ошибка
    if (!file) return 0;

    // Здесь будем хранить T (количество телеграмм)
    int telegramCount = 0;
    // Здесь будем хранить K (максимально допустимый штраф)
    long long maxAllowedPenalty = 0;

    // Читаем первую строку: T и K, проверяем формат
    if (fscanf(file, "%d %lld", &telegramCount, &maxAllowedPenalty) != 2) {
        fclose(file);
        return 0;
    }

    // Выделяем память под массив из telegramCount элементов Telegram
    Telegram* telegrams = malloc(sizeof(*telegrams) * (size_t)telegramCount);
    // Если malloc не смог выделить память — ошибка
    if (!telegrams) {
        // Закрываем файл
        fclose(file);
        // Возвращаем ошибку
        return 0;
    }

    // Читаем T строк вида: l d w
    for (int i = 0; i < telegramCount; i++) {
        // Временные переменные для чтения одной строки
        int duration = 0;
        int deadline = 0;
        int weight = 0;

        // Пытаемся прочитать l d w, проверяем формат
        if (fscanf(file, "%d %d %d", &duration, &deadline, &weight) != 3) {
            free(telegrams);
            fclose(file);
            return 0;
        }

        // Заполняем структуру
        telegrams[i].id = i + 1;    // id = 1...T 
        telegrams[i].l = duration; // l (duration)
        telegrams[i].d = deadline; // d (deadline)
        telegrams[i].w = weight;   // w (weight)
    }

    // Закрываем файл
    fclose(file);

    // Возвращаем указатель на выделенный массив
    *telegrams_out = telegrams;
    // Возвращаем количество
    *telegramCount_out = telegramCount;
    // Возвращаем K
    *maxAllowedPenalty_out = maxAllowedPenalty;

    return 1;
}

/*
    Записывает найденный порядок в файл.
*/
int write_order_file(const char* filename,
    const Telegram* telegrams,
    const int* orderIndices,
    int telegramCount) {

    // Открываем файл на запись (перезаписываем)
    FILE* file = fopen(filename, "w");
    // Если не открылся — ошибка
    if (!file) return 0;

    // Печатаем telegramCount чисел
    for (int pos = 0; pos < telegramCount; pos++) {
        // Берём индекс телеграммы в массиве telegrams[]
        int telegramIndex = orderIndices[pos];

        // Печатаем пробел перед всеми, кроме первого
        if (pos != 0) fprintf(file, " ");

        // Печатаем id телеграммы
        fprintf(file, "%d", telegrams[telegramIndex].id);
    }

    fprintf(file, "\n");
    fclose(file);
    return 1;
}

/*
    Записывает "0" в файл (если решение не нашли).
*/
int write_zero_file(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) return 0;

    fprintf(file, "0\n");

    fclose(file);
    return 1;
}

