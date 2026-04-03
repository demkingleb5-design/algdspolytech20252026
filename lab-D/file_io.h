#ifndef FILE_IO_H
#define FILE_IO_H

#include "structs.h"

// Читает входной файл и возвращает:
//      telegrams_out -> malloc-массив Telegram
//      telegramCount_out -> количество T
//      maxPenalty_out -> K
int read_input_file(const char* filename,
    Telegram** telegrams_out,
    int* telegramCount_out,
    long long* maxPenalty_out);

// Пишет порядок в файл: выводит telegram.id через пробел.
//      orderIndices[] хранит индексы в telegrams[] (0..T-1).
int write_order_file(const char* filename,
    const Telegram* telegrams,
    const int* orderIndices,
    int telegramCount);

// Пишет "0" в файл.
int write_zero_file(const char* filename);

#endif // FILE_IO_H
