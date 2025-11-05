#include <gtest/gtest.h>
#include <string.h>

#include "Structs.h"
#include "CreateListFunctions.h"
#include "SortListFunctions.h"

// Вспомогательные функции для тестов
double_linked_list create_test_list_with_three_elements() {
    double_linked_list list;
    initialize_list(&list);
    add_element(&list, "First");
    add_element(&list, "Second");
    add_element(&list, "Third");
    return list;
}

// ТЕСТ 1: Создание элемента
TEST(CreateElementTest, NormalString_ReturnValidElement_no1) {
    list_element* element = create_element("Hello");

    ASSERT_NE(element, nullptr);
    EXPECT_STREQ(element->data, "Hello");
    EXPECT_EQ(element->next, nullptr);
    EXPECT_EQ(element->prev, nullptr);

    free(element);
}

// ТЕСТ 2: Создание элемента с граничным случаем
TEST(CreateElementTest, EmptyString_ReturnValidElement_no2) {
    list_element* element = create_element("");

    ASSERT_NE(element, nullptr);
    EXPECT_STREQ(element->data, "");

    free(element);
}

// ТЕСТ 3: Инициализация списка
TEST(InitializeListTest, AnyCase_HeadAndTailNull_no3) {
    double_linked_list list;

    initialize_list(&list);

    EXPECT_EQ(list.head, nullptr);
    EXPECT_EQ(list.tail, nullptr);
}

// ТЕСТ 4: Добавление в пустой список
TEST(AddElementTest, EmptyList_HeadAndTailEqual_no4) {
    double_linked_list list;
    initialize_list(&list);

    add_element(&list, "Test");

    EXPECT_EQ(list.head, list.tail);
    EXPECT_STREQ(list.head->data, "Test");

    delete_list(&list);
}

// ТЕСТ 5: Добавление в непустой список
TEST(AddElementTest, NonEmptyList_TailUpdated_no5) {
    double_linked_list list;
    initialize_list(&list);
    add_element(&list, "First");

    add_element(&list, "Second");

    EXPECT_STREQ(list.tail->data, "Second");
    EXPECT_STREQ(list.head->data, "First");

    delete_list(&list);
}

// ТЕСТ 6: Удаление списка
TEST(DeleteListTest, NonEmptyList_HeadAndTailNull_no6) {
    double_linked_list list = create_test_list_with_three_elements();

    delete_list(&list);

    EXPECT_EQ(list.head, nullptr);
    EXPECT_EQ(list.tail, nullptr);
}

// ТЕСТ 7: Поиск минимума в пустом списке
TEST(FindMinLengthElementTest, EmptyList_ReturnNull_no7) {
    double_linked_list list;
    initialize_list(&list);

    list_element* result = find_min_length_element(&list);

    EXPECT_EQ(result, nullptr);
}

// ТЕСТ 8: Поиск минимума с одним элементом
TEST(FindMinLengthElementTest, SingleElement_ReturnElement_no8) {
    double_linked_list list;
    initialize_list(&list);
    add_element(&list, "Single");

    list_element* result = find_min_length_element(&list);

    EXPECT_STREQ(result->data, "Single");

    delete_list(&list);
}

// ТЕСТ 9: Поиск минимума с разными длинами
TEST(FindMinLengthElementTest, DifferentLengths_ReturnShortest_no9) {
    double_linked_list list;
    initialize_list(&list);
    add_element(&list, "Long string");
    add_element(&list, "X");
    add_element(&list, "Medium");

    list_element* result = find_min_length_element(&list);

    EXPECT_STREQ(result->data, "X");

    delete_list(&list);
}

// ТЕСТ 10: Удаление единственного элемента
TEST(RemoveElementTest, SingleElement_HeadAndTailNull_no10) {
    double_linked_list list;
    initialize_list(&list);
    add_element(&list, "Only");

    remove_element(&list, list.head);

    EXPECT_EQ(list.head, nullptr);
    EXPECT_EQ(list.tail, nullptr);
}

// ТЕСТ 11: Удаление головы
TEST(RemoveElementTest, HeadElement_NewHeadCorrect_no11) {
    double_linked_list list = create_test_list_with_three_elements();
    list_element* old_head = list.head;

    remove_element(&list, list.head);

    EXPECT_STREQ(list.head->data, "Second");
    EXPECT_EQ(list.head->prev, nullptr);

    free(old_head);
    delete_list(&list);
}

// ТЕСТ 12: Удаление хвоста
TEST(RemoveElementTest, TailElement_NewTailCorrect_no12) {
    double_linked_list list = create_test_list_with_three_elements();
    list_element* old_tail = list.tail;

    remove_element(&list, list.tail);

    EXPECT_STREQ(list.tail->data, "Second");
    EXPECT_EQ(list.tail->next, nullptr);

    free(old_tail);
    delete_list(&list);
}

// ТЕСТ 13: Сортировка пустого списка
TEST(SortByLengthTest, EmptyList_SortedListEmpty_no13) {
    double_linked_list original;
    double_linked_list sorted;
    initialize_list(&original);
    initialize_list(&sorted);

    sort_by_length(&original, &sorted);

    EXPECT_EQ(sorted.head, nullptr);
    EXPECT_EQ(sorted.tail, nullptr);

    delete_list(&sorted);
}

// ТЕСТ 14: Сортировка одного элемента
TEST(SortByLengthTest, SingleElement_SameElementInSorted_no14) {
    double_linked_list original;
    double_linked_list sorted;
    initialize_list(&original);
    initialize_list(&sorted);
    add_element(&original, "Test");

    sort_by_length(&original, &sorted);

    EXPECT_STREQ(sorted.head->data, "Test");
    EXPECT_EQ(sorted.head, sorted.tail);

    delete_list(&sorted);
}

// ТЕСТ 15: Сортировка по длине
TEST(SortByLengthTest, MixedLengths_SortedByLength_no15) {
    double_linked_list original;
    double_linked_list sorted;
    initialize_list(&original);
    initialize_list(&sorted);
    add_element(&original, "Long");
    add_element(&original, "X");
    add_element(&original, "Medium");

    sort_by_length(&original, &sorted);

    // Проверяем только первый элемент (самый короткий)
    EXPECT_STREQ(sorted.head->data, "X");

    delete_list(&sorted);
}


