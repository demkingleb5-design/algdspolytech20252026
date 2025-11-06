#include <stdio.h>
#include <locale.h>

#include "Functions.h"
#include "Test_Runner.h"

int main() {
    setlocale(LC_ALL, "Russian");

    printf("### ПРЕОБРАЗОВАНИЕ МАТРИЦЫ СМЕЖНОСТИ ###\n\n");

    Run_All_Tests();

    printf("=== ОСНОВНАЯ ПРОГРАММA ===\n");
    Create_Adjacency_List("Matrix.txt");
    printf("Преобразование завершено! Проверьте файл Adjacency_List.txt\n\n");
    return 0;
}