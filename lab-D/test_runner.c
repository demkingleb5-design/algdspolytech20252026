#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "structs.h"
#include "order_strategies.h"
#include "local_improvements.h"

/* Тест 1: init_identity_order на 3 элемента */
void Test_InitIdentityOrder_ThreeElements_Return012_no1(void) {
    printf("Test 1: Test_InitIdentityOrder_ThreeElements_Return012_no1... ");

    int orderIndices[3];
    int expected[3] = { 0, 1, 2 };

    init_identity_order(orderIndices, 3);

    assert(memcmp(orderIndices, expected, sizeof(expected)) == 0);

    printf("PASS\n");
}

/* Тест 2: build_order_dates — разные дедлайны */
void Test_BuildOrderDates_DifferentDeadlines_ReturnSortedByDeadline_no2(void) {
    printf("Test 2: Test_BuildOrderDates_DifferentDeadlines_ReturnSortedByDeadline_no2... ");

    Telegram telegrams[3] = {
        { 1, 1, 10, 1 },  /* index 0 */
        { 2, 1,  5, 1 },  /* index 1 */
        { 3, 1,  7, 1 }   /* index 2 */
    };

    int orderIndices[3];
    int expected[3] = { 1, 2, 0 };

    build_order_dates(telegrams, orderIndices, 3);

    assert(memcmp(orderIndices, expected, sizeof(expected)) == 0);

    printf("PASS\n");
}

/* Тест 3: build_order_dates — одинаковый дедлайн, сортировка по l */
void Test_BuildOrderDates_TieDeadline_SortsByDuration_no3(void) {
    printf("Test 3: Test_BuildOrderDates_TieDeadline_SortsByDuration_no3... ");

    Telegram telegrams[3] = {
        { 1, 3, 5, 1 },  /* index 0 */
        { 2, 1, 5, 1 },  /* index 1 */
        { 3, 1, 6, 1 }   /* index 2 */
    };

    int orderIndices[3];
    int expected[3] = { 1, 0, 2 };

    build_order_dates(telegrams, orderIndices, 3);

    assert(memcmp(orderIndices, expected, sizeof(expected)) == 0);

    printf("PASS\n");
}

/* Тест 4: build_order_weight — разные веса, сортировка по w убыванию */
void Test_BuildOrderWeight_DifferentWeights_ReturnSortedByWeightDesc_no4(void) {
    printf("Test 4: Test_BuildOrderWeight_DifferentWeights_ReturnSortedByWeightDesc_no4... ");

    Telegram telegrams[3] = {
        { 1, 1, 5,  2 },  /* index 0 */
        { 2, 1, 5, 10 },  /* index 1 */
        { 3, 1, 5,  5 }   /* index 2 */
    };

    int orderIndices[3];
    int expected[3] = { 1, 2, 0 };

    build_order_weight(telegrams, orderIndices, 3);

    assert(memcmp(orderIndices, expected, sizeof(expected)) == 0);

    printf("PASS\n");
}

/* Тест 5: build_order_weight — одинаковый вес, tie-break по d (возрастание) */
void Test_BuildOrderWeight_TieWeight_SortsByDeadlineAsc_no5(void) {
    printf("Test 5: Test_BuildOrderWeight_TieWeight_SortsByDeadlineAsc_no5... ");

    Telegram telegrams[3] = {
        { 1, 1, 7, 5 },  /* index 0 */
        { 2, 1, 3, 5 },  /* index 1 */
        { 3, 1, 1, 4 }   /* index 2 */
    };

    int orderIndices[3];
    int expected[3] = { 1, 0, 2 };

    build_order_weight(telegrams, orderIndices, 3);

    assert(memcmp(orderIndices, expected, sizeof(expected)) == 0);

    printf("PASS\n");
}

/* Тест 6: build_order_w_over_l — сортировка по (w/l) убыванию */
void Test_BuildOrderWOverL_RatioComparison_ReturnSortedByRatioDesc_no6(void) {
    printf("Test 6: Test_BuildOrderWOverL_RatioComparison_ReturnSortedByRatioDesc_no6... ");

    Telegram telegrams[3] = {
        { 1, 5, 100, 10 }, /* ratio 2.0, index 0 */
        { 2, 1, 100,  3 }, /* ratio 3.0, index 1 */
        { 3, 4, 100,  4 }  /* ratio 1.0, index 2 */
    };

    int orderIndices[3];
    int expected[3] = { 1, 0, 2 };

    build_order_w_over_l(telegrams, orderIndices, 3);

    assert(memcmp(orderIndices, expected, sizeof(expected)) == 0);

    printf("PASS\n");
}

/* Тест 7: build_order_hybrid — d↑, затем w↓, затем l↑ */
void Test_BuildOrderHybrid_TieDeadline_SortsByWeightThenDuration_no7(void) {
    printf("Test 7: Test_BuildOrderHybrid_TieDeadline_SortsByWeightThenDuration_no7... ");

    Telegram telegrams[3] = {
        { 1, 2, 5,  2 },  /* index 0 */
        { 2, 1, 5, 10 },  /* index 1 */
        { 3, 9, 4,  1 }   /* index 2 */
    };

    int orderIndices[3];
    int expected[3] = { 2, 1, 0 };

    build_order_hybrid(telegrams, orderIndices, 3);

    assert(memcmp(orderIndices, expected, sizeof(expected)) == 0);

    printf("PASS\n");
}

/* Тест 8: compute_penalty — без опозданий => штраф 0 */
void Test_ComputePenalty_NoLate_Return0_no8(void) {
    printf("Test 8: Test_ComputePenalty_NoLate_Return0_no8... ");

    Telegram telegrams[2] = {
        { 1, 1,  5, 10 },
        { 2, 2, 10,  1 }
    };

    int orderIndices[2] = { 0, 1 };

    long long penalty = compute_penalty(telegrams, orderIndices, 2, 1000000LL);

    assert(penalty == 0);

    printf("PASS\n");
}

/* Тест 9: compute_penalty — одно опоздание, проверка точного штрафа */
void Test_ComputePenalty_SingleLate_CorrectPenalty_no9(void) {
    printf("Test 9: Test_ComputePenalty_SingleLate_CorrectPenalty_no9... ");

    Telegram telegrams[2] = {
        { 1, 5,  3, 2 },  /* late = 2, penalty = 4 */
        { 2, 1, 100, 1 }
    };

    int orderIndices[2] = { 0, 1 };

    long long penalty = compute_penalty(telegrams, orderIndices, 2, 1000000LL);

    assert(penalty == 4);

    printf("PASS\n");
}

/* Тест 10: compute_penalty — ранний выход по Kcap */
void Test_ComputePenalty_KcapEarlyExit_ReturnGreaterThanCap_no10(void) {
    printf("Test 10: Test_ComputePenalty_KcapEarlyExit_ReturnGreaterThanCap_no10... ");

    Telegram telegrams[1] = {
        { 1, 10, 0, 1 }   /* time=10, late=10, penalty=10 */
    };

    int orderIndices[1] = { 0 };

    long long penalty = compute_penalty(telegrams, orderIndices, 1, 5LL);

    assert(penalty == 10);

    printf("PASS\n");
}

/* Тест 11: improve_adjacent_swaps — улучшение через одну соседнюю перестановку */
void Test_ImproveAdjacentSwaps_SwapImproves_Return0AndSwapped_no11(void) {
    printf("Test 11: Test_ImproveAdjacentSwaps_SwapImproves_Return0AndSwapped_no11... ");

    Telegram telegrams[2] = {
        { 1, 5, 100, 1 },  /* длинная, дедлайн большой */
        { 2, 1,   3, 10 }  /* короткая, дедлайн маленький, большой штраф */
    };

    int orderIndices[2] = { 0, 1 };   /* плохой порядок */
    int expected[2] = { 1, 0 };   /* хороший порядок */

    long long penalty = improve_adjacent_swaps(telegrams, orderIndices, 2, 0LL, 5);

    assert(penalty == 0);
    assert(memcmp(orderIndices, expected, sizeof(expected)) == 0);

    printf("PASS\n");
}

/* Тест 12: improve_adjacent_swaps — порядок уже подходит, ранний возврат без изменений */
void Test_ImproveAdjacentSwaps_AlreadyOk_Return0AndUnchanged_no12(void) {
    printf("Test 12: Test_ImproveAdjacentSwaps_AlreadyOk_Return0AndUnchanged_no12... ");

    Telegram telegrams[2] = {
        { 1, 5, 100, 1 },
        { 2, 1,   3, 10 }
    };

    int orderIndices[2] = { 1, 0 };   /* уже хороший порядок */
    int expected[2] = { 1, 0 };

    long long penalty = improve_adjacent_swaps(telegrams, orderIndices, 2, 0LL, 5);

    assert(penalty == 0);
    assert(memcmp(orderIndices, expected, sizeof(expected)) == 0);

    printf("PASS\n");
}

/* Запуск всех тестов */
void Run_All_Tests(void) {
    printf("ЗАПУСКАЮ ЮНИТ-ТЕСТЫ...\n\n");

    Test_InitIdentityOrder_ThreeElements_Return012_no1();
    Test_BuildOrderDates_DifferentDeadlines_ReturnSortedByDeadline_no2();
    Test_BuildOrderDates_TieDeadline_SortsByDuration_no3();
    Test_BuildOrderWeight_DifferentWeights_ReturnSortedByWeightDesc_no4();
    Test_BuildOrderWeight_TieWeight_SortsByDeadlineAsc_no5();
    Test_BuildOrderWOverL_RatioComparison_ReturnSortedByRatioDesc_no6();
    Test_BuildOrderHybrid_TieDeadline_SortsByWeightThenDuration_no7();
    Test_ComputePenalty_NoLate_Return0_no8();
    Test_ComputePenalty_SingleLate_CorrectPenalty_no9();
    Test_ComputePenalty_KcapEarlyExit_ReturnGreaterThanCap_no10();
    Test_ImproveAdjacentSwaps_SwapImproves_Return0AndSwapped_no11();
    Test_ImproveAdjacentSwaps_AlreadyOk_Return0AndUnchanged_no12();

    printf("\nВСЕ ЮНИТ-ТЕСТЫ ПРОЙДЕНЫ!\n\n");
}
