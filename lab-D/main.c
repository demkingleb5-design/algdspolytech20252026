#include <stdio.h>              
#include <stdlib.h>                 
#include <locale.h>                 

#include "structs.h"                
#include "file_io.h"                
#include "order_strategies.h"      
#include "local_improvements.h"    
#include "test_runner.h"

/*
    Тип указателя на функцию-стратегию построения порядка.
    Она получает массив telegrams, массив orderIndices и telegramCount.
*/
typedef void (*BuildOrderFunction)(const Telegram* telegrams,
    int* orderIndices,
    int telegramCount);

/*
    Печатает порядок в консоль (для проверки).
    В файл пишем отдельной функцией.
*/
static void print_order_to_console(const Telegram* telegrams,
    const int* orderIndices,
    int telegramCount) {
    // Проходим все позиции в порядке
    for (int pos = 0; pos < telegramCount; pos++) {
        // Печатаем пробел перед всеми, кроме первого
        if (pos) printf(" ");
        // Печатаем id телеграммы, стоящей на этой позиции
        printf("%d", telegrams[orderIndices[pos]].id);
    }
    // Перевод строки в конце
    printf("\n");
}

int main(void) {
    // Подключаем русский язык 
    setlocale(LC_ALL, "Russian");

    // Запуск юнит-тестов
    Run_All_Tests();

    // Имя входного файла
    const char* INPUT_FILE = "input.txt";
    // Имя выходного файла
    const char* OUTPUT_FILE = "output.txt";

    // Указатель на массив телеграмм 
    Telegram* telegrams = NULL;
    // Количество телеграмм T
    int telegramCount = 0;
    // Допустимый порог K
    long long maxAllowedPenalty = 0;

    // Стартовый отчёт в консоль
    printf("=== Запуск программы ===\n");
    printf("Читаю входные данные из файла: %s\n", INPUT_FILE);

    // Читаем вход; если ошибка — завершаем
    if (!read_input_file(INPUT_FILE, &telegrams, &telegramCount, &maxAllowedPenalty)) {
        printf("Ошибка: не удалось прочитать входной файл или неверный формат данных.\n");
        return 0;
    }

    // Печатаем, что прочитали
    printf("Прочитано телеграмм: %d\n", telegramCount);
    printf("Порог штрафа K: %lld\n\n", maxAllowedPenalty);

    // Выделяем память под порядок индексов (0...T-1)
    int* orderIndices = malloc(sizeof(*orderIndices) * (size_t)telegramCount);
    // Если память не выделилась — чистим telegrams и завершаем
    if (!orderIndices) {
        printf("Ошибка: не удалось выделить память под массив порядка.\n");
        free(telegrams);
        return 0;
    }

    // Массив стратегий 
    BuildOrderFunction strategies[4] = {
        build_order_dates,     // по дедлайну 
        build_order_weight,    // по весу w
        build_order_w_over_l,  // по отношению w/l
        build_order_hybrid     // гибрид
    };

    // Названия стратегий для отчёта в консоль
    const char* strategyNames[4] = {
        "Сортировка по дедлайну: d по возрастанию",
        "Сортировка по весу: w по убыванию",
        "Сортировка по отношению: (w/l) по убыванию",
        "Гибридная сортировка: d↑, w↓, l↑"
    };

    // Сколько проходов делать в улучшении перестановками
    const int MAX_IMPROVEMENT_PASSES = 15;

    // Перебираем стратегии по очереди
    for (int strategyIndex = 0; strategyIndex < 4; strategyIndex++) {
        // Печатаем разделитель и какую стратегию пробуем
        printf("--------------------------------------------------\n");
        printf("Шаг %d. Пробую стратегию: %s\n", strategyIndex + 1, strategyNames[strategyIndex]);

        // 1) Строим кандидатный порядок текущей стратегией
        strategies[strategyIndex](telegrams, orderIndices, telegramCount);

        // Сообщаем, что порядок построен
        printf("Порядок построен. Считаю штраф...\n");

        // 2) Быстро считаем штраф с потолком K 
        long long penaltyNow = compute_penalty(telegrams, orderIndices, telegramCount, maxAllowedPenalty);

        // Печатаем значение штрафа 
        printf("Штраф после построения порядка: %lld\n", penaltyNow);

        // 3) Если penaltyNow <= K, решение найдено — печатаем и выходим
        if (penaltyNow <= maxAllowedPenalty) {
            // Сообщаем об успехе
            printf("УСПЕХ: найден подходящий порядок (штраф <= K).\n");
            printf("Ответ (порядок телеграмм):\n");

            // Печатаем порядок в консоль
            print_order_to_console(telegrams, orderIndices, telegramCount);

            // Пишем в output.txt
            write_order_file(OUTPUT_FILE, telegrams, orderIndices, telegramCount);
            printf("Записал ответ в файл: %s\n", OUTPUT_FILE);

            // Освобождаем память
            free(orderIndices);
            free(telegrams);

            // Завершаем программу
            printf("=== Завершение программы ===\n");
            return 0;
        }

        // Если штраф больше K — сообщаем, что порядок не подошёл
        printf("Порядок НЕ подошёл: штраф > K.\n");

        // 4) Иначе пробуем улучшить локальным поиском (соседние перестановки)
        printf("Запускаю улучшение соседними перестановками (макс. проходов: %d)...\n", MAX_IMPROVEMENT_PASSES);

        long long improvedPenalty = improve_adjacent_swaps(
            telegrams,              // данные
            orderIndices,           // текущий порядок 
            telegramCount,          // размер
            maxAllowedPenalty,      // порог K
            MAX_IMPROVEMENT_PASSES  // лимит проходов
        );

        // Печатаем штраф после улучшения
        printf("Штраф после улучшения: %lld\n", improvedPenalty);

        // 5) Если после улучшения стало <= K — печатаем и выходим
        if (improvedPenalty <= maxAllowedPenalty) {
            // Сообщаем об успехе
            printf("УСПЕХ: после улучшения штраф стал <= K.\n");
            printf("Ответ (порядок телеграмм):\n");

            // Печатаем порядок
            print_order_to_console(telegrams, orderIndices, telegramCount);

            // Пишем в файл
            write_order_file(OUTPUT_FILE, telegrams, orderIndices, telegramCount);
            printf("Записал ответ в файл: %s\n", OUTPUT_FILE);

            // Освобождаем память
            free(orderIndices);
            free(telegrams);

            // Завершаем программу
            printf("=== Завершение программы ===\n");
            return 0;
        }

        // 6) Если всё ещё > K — идём к следующей стратегии
        printf("После улучшения всё ещё штраф > K. Перехожу к следующей стратегии.\n\n");
    }

    // Если ни одна стратегия не дала <= K, выводим 0
    printf("--------------------------------------------------\n");
    printf("РЕЗУЛЬТАТ: подходящая последовательность не найдена.\n");
    printf("Вывожу 0.\n");

    // И пишем 0 в файл
    write_zero_file(OUTPUT_FILE);
    printf("Записал 0 в файл: %s\n", OUTPUT_FILE);

    // Освобождаем память
    free(orderIndices);
    free(telegrams);

    // Завершаем
    printf("=== Завершение программы ===\n");
    return 0;
}
