#include <limits.h>                 // LLONG_MAX

#include "local_improvements.h"     
#include "order_strategies.h"       

/*
    Вспомогательная функция: меняет местами два индекса.
    Используется для перестановки соседей в массиве orderIndices[].
*/
static void swap_indices(int* leftIndex, int* rightIndex) {
    // Временная переменная
    int tmp = *leftIndex;
    // Меняем
    *leftIndex = *rightIndex;
    // Завершаем обмен
    *rightIndex = tmp;
}

/*
    Улучшает порядок соседними перестановками.
*/
long long improve_adjacent_swaps(const Telegram* telegrams,
    int* orderIndices,
    int telegramCount,
    long long maxAllowedPenalty,
    int maxPasses) {

    // Считаем текущий штраф (точно, без ограничения)
    long long bestPenalty = compute_penalty(telegrams, orderIndices, telegramCount, LLONG_MAX);

    // Если уже удовлетворяет <= K, улучшение не нужно
    if (bestPenalty <= maxAllowedPenalty) {
        return bestPenalty;
    }

    // Делаем несколько проходов по массиву
    for (int pass = 0; pass < maxPasses; pass++) {
        // Флаг: было ли хоть одно улучшение в этом проходе
        int improvedThisPass = 0;

        // Пробуем все соседние пары i и i+1
        for (int i = 0; i < telegramCount - 1; i++) {
            // Пробуем перестановку
            swap_indices(&orderIndices[i], &orderIndices[i + 1]);

            // Считаем новый штраф (с потолком bestPenalty для ускорения)
            long long newPenalty = compute_penalty(telegrams, orderIndices, telegramCount, bestPenalty);

            // Если стало лучше — фиксируем перестановку
            if (newPenalty < bestPenalty) {
                // Обновляем лучший штраф
                bestPenalty = newPenalty;
                // Отмечаем, что улучшение было
                improvedThisPass = 1;

                // Если уже <= K — можно сразу возвращать успех
                if (bestPenalty <= maxAllowedPenalty) {
                    return bestPenalty;
                }
            }
            else {
                // Если не улучшили — откатываем перестановку обратно
                swap_indices(&orderIndices[i], &orderIndices[i + 1]);
            }
        }

        // Если за проход не было улучшений, дальше обычно смысла нет
        if (!improvedThisPass) {
            break;
        }
    }

    // Возвращаем лучший достигнутый штраф (может быть > K)
    return bestPenalty;
}
