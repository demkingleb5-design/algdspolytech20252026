#include <stdlib.h> //qsort и size_t

#include "order_strategies.h"

/*
    qsort-компаратор по стандарту C имеет только (const void*, const void*),
    туда нельзя просто так передать массив telegrams[].
    Поэтому кладём указатель на массив в глобальную переменную.
*/
static const Telegram* g_telegrams = NULL;

/*
    Заполняет массив индексов: [0, 1, 2, ..., telegramCount-1].
*/
void init_identity_order(int* orderIndices, int telegramCount) {
    for (int i = 0; i < telegramCount; i++) {
        orderIndices[i] = i;
    }
}

/*
    Компаратор по дедлайну: d по возрастанию, затем l по возрастанию, затем id.
*/
static int cmp_deadline(const void* leftPtr, const void* rightPtr) {
    int leftIndex = *(const int*)leftPtr;
    int rightIndex = *(const int*)rightPtr;

    const Telegram* leftTelegram = &g_telegrams[leftIndex];
    const Telegram* rightTelegram = &g_telegrams[rightIndex];

    if (leftTelegram->d < rightTelegram->d) {
        return -1;
    }
    else if (leftTelegram->d > rightTelegram->d) {
        return 1;
    }

    if (leftTelegram->l < rightTelegram->l) {
        return -1;
    }
    else if (leftTelegram->l > rightTelegram->l) {
        return 1;
    }

    if (leftTelegram->id < rightTelegram->id) {
        return -1;
    }
    else if (leftTelegram->id > rightTelegram->id) {
        return 1;
    }

    return 0;
}

/*
    Компаратор по весу: w по убыванию, затем d по возрастанию, затем id.
*/
static int cmp_weight(const void* leftPtr, const void* rightPtr) {
    int leftIndex = *(const int*)leftPtr;
    int rightIndex = *(const int*)rightPtr;

    const Telegram* leftTelegram = &g_telegrams[leftIndex];
    const Telegram* rightTelegram = &g_telegrams[rightIndex];

    if (leftTelegram->w > rightTelegram->w) {
        return -1;
    }
    else if (leftTelegram->w < rightTelegram->w) {
        return 1;
    }

    if (leftTelegram->d < rightTelegram->d) {
        return -1;
    }
    else if (leftTelegram->d > rightTelegram->d) {
        return 1;
    }

    if (leftTelegram->id < rightTelegram->id) {
        return -1;
    }
    else if (leftTelegram->id > rightTelegram->id) {
        return 1;
    }

    return 0;
}

/*
    Компаратор по (w/l): по убыванию, через перекрёстное умножение.
    tie: d по возр., w по убыв., id по возр.
*/
static int cmp_w_over_l(const void* leftPtr, const void* rightPtr) {
    int leftIndex = *(const int*)leftPtr;
    int rightIndex = *(const int*)rightPtr;

    const Telegram* leftTelegram = &g_telegrams[leftIndex];
    const Telegram* rightTelegram = &g_telegrams[rightIndex];

    // Заменяем деление на умножение по правилу крест-на-крест, чтобы избежать потери значений после запятой
    long long leftValue = (long long)leftTelegram->w * (long long)rightTelegram->l;
    long long rightValue = (long long)rightTelegram->w * (long long)leftTelegram->l;

    if (leftValue > rightValue) {
        return -1;
    }
    else if (leftValue < rightValue) {
        return 1;
    }

    if (leftTelegram->d < rightTelegram->d) {
        return -1;
    }
    else if (leftTelegram->d > rightTelegram->d) {
        return 1;
    }

    if (leftTelegram->w > rightTelegram->w) {
        return -1;
    }
    else if (leftTelegram->w < rightTelegram->w) {
        return 1;
    }

    if (leftTelegram->id < rightTelegram->id) {
        return -1;
    }
    else if (leftTelegram->id > rightTelegram->id) {
        return 1;
    }

    return 0;
}

/*
    Компаратор гибрид: d по возр., затем w по убыв., затем l по возр., затем id.
*/
static int cmp_hybrid(const void* leftPtr, const void* rightPtr) {
    int leftIndex = *(const int*)leftPtr;
    int rightIndex = *(const int*)rightPtr;

    const Telegram* leftTelegram = &g_telegrams[leftIndex];
    const Telegram* rightTelegram = &g_telegrams[rightIndex];

    if (leftTelegram->d < rightTelegram->d) {
        return -1;
    }
    else if (leftTelegram->d > rightTelegram->d) {
        return 1;
    }

    if (leftTelegram->w > rightTelegram->w) {
        return -1;
    }
    else if (leftTelegram->w < rightTelegram->w) {
        return 1;
    }

    if (leftTelegram->l < rightTelegram->l) {
        return -1;
    }
    else if (leftTelegram->l > rightTelegram->l) {
        return 1;
    }

    if (leftTelegram->id < rightTelegram->id) {
        return -1;
    }
    else if (leftTelegram->id > rightTelegram->id) {
        return 1;
    }

    return 0;
}

/*
    Строит порядок по дедлайну (EDD).
*/
void build_order_dates(const Telegram* telegrams, int* orderIndices, int telegramCount) {
    init_identity_order(orderIndices, telegramCount);
    g_telegrams = telegrams;
    qsort(orderIndices, (size_t)telegramCount, sizeof(int), cmp_deadline);
}

/*
    Строит порядок по весу (w).
*/
void build_order_weight(const Telegram* telegrams, int* orderIndices, int telegramCount) {
    init_identity_order(orderIndices, telegramCount);
    g_telegrams = telegrams;
    qsort(orderIndices, (size_t)telegramCount, sizeof(int), cmp_weight);
}

/*
    Строит порядок по отношению (w/l).
*/
void build_order_w_over_l(const Telegram* telegrams, int* orderIndices, int telegramCount) {
    init_identity_order(orderIndices, telegramCount);
    g_telegrams = telegrams;
    qsort(orderIndices, (size_t)telegramCount, sizeof(int), cmp_w_over_l);
}

/*
    Строит гибридный порядок.
*/
void build_order_hybrid(const Telegram* telegrams, int* orderIndices, int telegramCount) {
    init_identity_order(orderIndices, telegramCount);
    g_telegrams = telegrams;
    qsort(orderIndices, (size_t)telegramCount, sizeof(int), cmp_hybrid);
}

/*
    Считает суммарный штраф для текущего порядка.
*/
long long compute_penalty(const Telegram* telegrams,
    const int* orderIndices,
    int telegramCount,
    long long Kcap) {
    long long currentTime = 0;
    long long totalPenalty = 0;

    for (int position = 0; position < telegramCount; position++) {
        int telegramIndex = orderIndices[position];

        currentTime += (long long)telegrams[telegramIndex].l;

        if (currentTime > (long long)telegrams[telegramIndex].d) {
            long long lateTime = currentTime - (long long)telegrams[telegramIndex].d;
            totalPenalty += lateTime * (long long)telegrams[telegramIndex].w;

            if (totalPenalty > Kcap) {
                return totalPenalty;
            }
        }
    }

    return totalPenalty;
}
