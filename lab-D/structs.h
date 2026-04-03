#ifndef STRUCTS_H 
#define STRUCTS_H

#include <stdio.h>

typedef struct {
    int id;   // Исходный номер (индекс телеграммы)
    int l;    // Длительность
    int d;    // Дедлайн
    int w;    // Штраф за единицу опоздания
} Telegram;

#endif
