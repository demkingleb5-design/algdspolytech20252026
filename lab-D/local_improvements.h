#ifndef LOCAL_IMPROVEMENT_H
#define LOCAL_IMPROVEMENT_H

#include "structs.h"

/*
    Локальное улучшение соседними перестановку (i и i+1).

    Идея:
      - идём слева направо по всем соседним парам
      - пробуем перестановку
      - если штраф стал меньше — оставляем перестановку
      - иначе откатываем
      - повторяем несколько проходов (maxPasses)
      - если получился штраф <= maxAllowedPenalty — выходим сразу

    Возвращает итоговый штраф.
*/
long long improve_adjacent_swaps(const Telegram* telegrams,
    int* orderIndices,
    int telegramCount,
    long long maxAllowedPenalty,
    int maxPasses);

#endif // LOCAL_IMPROVEMENT_H
