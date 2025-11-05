#include <stdio.h>
#include <string.h>
#include <locale.h>

#include "Structs.h"
#include "CreateListFunctions.h"
#include "SortListFunctions.h"

int main() {
	setlocale(LC_ALL, "Russian");

	double_linked_list OriginalDoubleLinkedList;
	double_linked_list SortedDoubleLinkedList;

	initialize_list(&OriginalDoubleLinkedList);
	initialize_list(&SortedDoubleLinkedList);


	add_element(&OriginalDoubleLinkedList, "YN@$Mg1_");
	add_element(&OriginalDoubleLinkedList, "t3/ICDе7rewfDLt_");
	add_element(&OriginalDoubleLinkedList, "3$ztzдuU6ZDававф343еывdafa");
	add_element(&OriginalDoubleLinkedList, "*vFSь90!Ufsdgdgh342(*#=!3");
	add_element(&OriginalDoubleLinkedList, "+-CHfьяв6J");
	add_element(&OriginalDoubleLinkedList, "Привет_Я_Очень_Длинная_Строка_На_Русском_Языке");
	add_element(&OriginalDoubleLinkedList, " ");
	add_element(&OriginalDoubleLinkedList, "");
	add_element(&OriginalDoubleLinkedList, "!№;%:?*()*(:%:Ю,ЮБЮЬЮ,><><>?<}{}{AS");
	add_element(&OriginalDoubleLinkedList, "ABC");

	printf("Список до сортировки:\n");
	print_list(&OriginalDoubleLinkedList);

	sort_by_length(&OriginalDoubleLinkedList, &SortedDoubleLinkedList);

	printf("Список после сортировки:\n");
	print_list(&SortedDoubleLinkedList);

	delete_list(&OriginalDoubleLinkedList);
	delete_list(&SortedDoubleLinkedList);
}