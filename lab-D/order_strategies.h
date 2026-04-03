#ifndef ORDER_HEURISTICS_H
#define ORDER_HEURISTICS_H

#include "structs.h"


// Заполняет orderIndices как 0,1,2,...,telegramCount-1.
void init_identity_order(int* orderIndices, int telegramCount);
    
// Стратегия 1: сортировка по дедлайну d по возрастанию.
void build_order_dates(const Telegram* telegrams, int* orderIndices, int telegramCount);

// Стратегия 2: сортировка по весу w по убыванию (более "дорогие" раньше).
void build_order_weight(const Telegram* telegrams, int* orderIndices, int telegramCount);

// Стратегия 3: сортировка по отношению (w/l) по убыванию.
void build_order_w_over_l(const Telegram* telegrams, int* orderIndices, int telegramCount);

// Стратегия 4: гибрид (d ↑, затем w ↓, затем l ↑, затем id ↑).
void build_order_hybrid(const Telegram* telegrams, int* orderIndices, int telegramCount);

// Считает суммарный штраф для порядка orderIndices[].
// Kcap — потолок для раннего выхода:
long long compute_penalty(const Telegram* telegrams,
    const int* orderIndices,
    int telegramCount,
    long long Kcap);

#endif // ORDER_HEURISTICS_H
