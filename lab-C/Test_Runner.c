#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Functions.h"

// Создание тестового файла
void create_test_file(const char* filename, const char* content) {
    FILE* f = fopen(filename, "w");
    fprintf(f, "%s", content);
    fclose(f);
}

// Удаление выходного файла
void delete_output_file() {
    remove("Adjacency_List.txt");
}

// Чтение содержимого файла
char* read_file_content(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (f == NULL) return NULL;

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    char* content = malloc(size + 1);
    fread(content, 1, size, f);
    content[size] = '\0';

    fclose(f);
    return content;
}

// Тест 1: Пустой файл
void Create_Adjacency_List_EmptyFile_ReturnNoOutput_no1() {
    printf("Test 1: Create_Adjacency_List_EmptyFile_ReturnNoOutput... ");
    delete_output_file();
    create_test_file("test_empty.txt", "");
    Create_Adjacency_List("test_empty.txt");

    char* result = read_file_content("Adjacency_List.txt");
    assert(result == NULL);
    free(result);
    printf("PASS\n");
}

// Тест 2: Одна вершина без ребер
void Create_Adjacency_List_SingleVertexNoEdges_ReturnNoAdjacent_no2() {
    printf("Test 2: Create_Adjacency_List_SingleVertexNoEdges_ReturnNoAdjacent... ");
    delete_output_file();
    create_test_file("test_single.txt", "0");
    Create_Adjacency_List("test_single.txt");

    char* result = read_file_content("Adjacency_List.txt");
    assert(result != NULL);
    assert(strstr(result, "0: нет смежных вершин") != NULL);
    free(result);
    printf("PASS\n");
}

// Тест 3: Матрица 2x2
void Create_Adjacency_List_2x2Matrix_ReturnValidAdjacency_no3() {
    printf("Test 3: Create_Adjacency_List_2x2Matrix_ReturnValidAdjacency... ");
    delete_output_file();
    create_test_file("test_2x2.txt", "0 1\n1 0");
    Create_Adjacency_List("test_2x2.txt");

    char* result = read_file_content("Adjacency_List.txt");
    assert(result != NULL);
    assert(strstr(result, "0: 1") != NULL);
    assert(strstr(result, "1: 0") != NULL);
    free(result);
    printf("PASS\n");
}

// Тест 4: Полный граф
void Create_Adjacency_List_CompleteGraph_ReturnAllConnections_no4() {
    printf("Test 4: Create_Adjacency_List_CompleteGraph_ReturnAllConnections... ");
    delete_output_file();
    create_test_file("test_complete.txt", "1 1 1\n1 1 1\n1 1 1");
    Create_Adjacency_List("test_complete.txt");

    char* result = read_file_content("Adjacency_List.txt");
    assert(result != NULL);
    assert(strstr(result, "0: 0 1 2") != NULL);
    assert(strstr(result, "1: 0 1 2") != NULL);
    assert(strstr(result, "2: 0 1 2") != NULL);
    free(result);
    printf("PASS\n");
}

// Тест 5: Нет ребер
void Create_Adjacency_List_NoEdges_ReturnNoAdjacentVertices_no5() {
    printf("Test 5: Create_Adjacency_List_NoEdges_ReturnNoAdjacentVertices... ");
    delete_output_file();
    create_test_file("test_no_edges.txt", "0 0 0\n0 0 0\n0 0 0");
    Create_Adjacency_List("test_no_edges.txt");

    char* result = read_file_content("Adjacency_List.txt");
    assert(result != NULL);
    assert(strstr(result, "0: нет смежных вершин") != NULL);
    assert(strstr(result, "1: нет смежных вершин") != NULL);
    assert(strstr(result, "2: нет смежных вершин") != NULL);
    free(result);
    printf("PASS\n");
}

// Тест 6: Ориентированные ребра (0→1, 1→2)
void Create_Adjacency_List_DirectedEdges_ReturnDirectedAdjacency_no6() {
    printf("Test 6: Create_Adjacency_List_DirectedEdges_ReturnDirectedAdjacency... ");
    delete_output_file();
    create_test_file("test_directed.txt", "0 1 0\n0 0 1\n0 0 0");
    Create_Adjacency_List("test_directed.txt");

    char* result = read_file_content("Adjacency_List.txt");
    assert(result != NULL);
    assert(strstr(result, "0: 1") != NULL);
    assert(strstr(result, "1: 2") != NULL);
    assert(strstr(result, "2: нет смежных вершин") != NULL);
    free(result);
    printf("PASS\n");
}

// Тест 7: Петли
void Create_Adjacency_List_SelfLoops_ReturnSelfConnections_no7() {
    printf("Test 7: Create_Adjacency_List_SelfLoops_ReturnSelfConnections... ");
    delete_output_file();
    create_test_file("test_self_loops.txt", "1 0\n0 1");
    Create_Adjacency_List("test_self_loops.txt");

    char* result = read_file_content("Adjacency_List.txt");
    assert(result != NULL);
    assert(strstr(result, "0: 0") != NULL);
    assert(strstr(result, "1: 1") != NULL);
    free(result);
    printf("PASS\n");
}

// Тест 8: Большая матрица
void Create_Adjacency_List_LargeMatrix_ReturnValidAdjacency_no8() {
    printf("Test 8: Create_Adjacency_List_LargeMatrix_ReturnValidAdjacency... ");
    delete_output_file();
    create_test_file("test_large.txt", "0 1 0 1\n1 0 1 0\n0 1 0 1\n1 0 1 0");
    Create_Adjacency_List("test_large.txt");

    char* result = read_file_content("Adjacency_List.txt");
    assert(result != NULL);
    assert(strstr(result, "0: 1 3") != NULL);
    assert(strstr(result, "1: 0 2") != NULL);
    assert(strstr(result, "2: 1 3") != NULL);
    assert(strstr(result, "3: 0 2") != NULL);
    free(result);
    printf("PASS\n");
}

// Тест 9: Одно ребро
void Create_Adjacency_List_SingleEdge_ReturnOneConnection_no9() {
    printf("Test 9: Create_Adjacency_List_SingleEdge_ReturnOneConnection... ");
    delete_output_file();
    create_test_file("test_single_edge.txt", "0 1\n0 0");
    Create_Adjacency_List("test_single_edge.txt");

    char* result = read_file_content("Adjacency_List.txt");
    assert(result != NULL);
    assert(strstr(result, "0: 1") != NULL);
    assert(strstr(result, "1: нет смежных вершин") != NULL);
    free(result);
    printf("PASS\n");
}

// Тест 10: Различные пробелы
void Create_Adjacency_List_WhitespaceVariations_ReturnValidAdjacency_no10() {
    printf("Test 10: Create_Adjacency_List_WhitespaceVariations_ReturnValidAdjacency... ");
    delete_output_file();
    create_test_file("test_whitespace.txt", "   0  1   0  \n1  0   1\n\t0\t1\t0\t");
    Create_Adjacency_List("test_whitespace.txt");

    char* result = read_file_content("Adjacency_List.txt");
    assert(result != NULL);
    assert(strstr(result, "0: 1") != NULL);
    assert(strstr(result, "1: 0 2") != NULL);
    assert(strstr(result, "2: 1") != NULL);
    free(result);
    printf("PASS\n");
}

// Запуск всех тестов
void Run_All_Tests() {
    printf("ЗАПУСКАЮ ЮНИТ-ТЕСТЫ...\n\n");

    Create_Adjacency_List_EmptyFile_ReturnNoOutput_no1();
    Create_Adjacency_List_SingleVertexNoEdges_ReturnNoAdjacent_no2();
    Create_Adjacency_List_2x2Matrix_ReturnValidAdjacency_no3();
    Create_Adjacency_List_CompleteGraph_ReturnAllConnections_no4();
    Create_Adjacency_List_NoEdges_ReturnNoAdjacentVertices_no5();
    Create_Adjacency_List_DirectedEdges_ReturnDirectedAdjacency_no6();
    Create_Adjacency_List_SelfLoops_ReturnSelfConnections_no7();
    Create_Adjacency_List_LargeMatrix_ReturnValidAdjacency_no8();
    Create_Adjacency_List_SingleEdge_ReturnOneConnection_no9();
    Create_Adjacency_List_WhitespaceVariations_ReturnValidAdjacency_no10();

    printf("\nВСЕ ТЕСТЫ ПРОЙДЕНЫ!\n\n");
}