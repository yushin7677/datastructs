#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datastructs.h"

void demoArray(void){

	printf("\n--- Arrays ---\n\n");

	Array arr = createArray();
	insertToEndArray(&arr, 3);
	insertToEndArray(&arr, 5);
	insertToEndArray(&arr, 8);
	printArray(&arr);

	printf("\n*setValueArray(&arr, 1, 6)\n\n");
	setValueArray(&arr, 1, 6);
	printArray(&arr);

	printf("\n*insertValueArray(&arr, 1, 2)\n\n");
	insertToArray(&arr, 1, 2);
	printArray(&arr);

	printf("\n*setSizeArray(&arr, 6)\n\n");
	setSizeArray(&arr, 6);
	printArray(&arr);

	printf("\n*deleteElementArray(&arr, 2)\n\n");
	deleteElementArray(&arr, 2);
	printArray(&arr);

	printf("\n*arr2 = subArray(&arr, 0, 3)\n\n");
	Array arr2 = subArray(&arr, 0, 3);
	printArray(&arr2);

	printf("\n*createArray {9,7,6}\n\n");
	Array arr3 = createArray();
	insertToEndArray(&arr3, 9);
	insertToEndArray(&arr3, 7);
	insertToEndArray(&arr3, 6);
	printArray(&arr3);

	printf("\n*mergeArray(&arr2, &arr3)\n\n");
	mergeArray(&arr2, &arr3);
	printArray(&arr2);

};

void demoList(void){

	printf("\n--- Lists ---\n\n");

	List list = createList();
	insertFirst(&list, 1);
	insertFirst(&list, 2);
	insertFirst(&list, 3);
	printList(&list);

	printf("\n*insertFirst(&list, 4)\n\n");
	insertFirst(&list, 4);
	printList(&list);

	printf("\n*insertLast(&list, 5)\n\n");
	insertLast(&list, 5);
	printList(&list);

	printf("\n*deleteFirst(&list)\n\n");
	deleteFirst(&list);
	printList(&list);

	printf("\n*deleteLast(&list)\n\n");
	deleteLast(&list);
	printList(&list);

	printf("\nlist.first = %d\n",list.first->value);
	printf("list.last = %d\n",list.last->value);

};

void demoGraph(void){

	printf("\n--- Graphs ---\n\n");

	// Создадим граф с 6 вершинами:
	Graph graph = createGraph();
	addGraphVertex(&graph);
	addGraphVertex(&graph);
	addGraphVertex(&graph);
	addGraphVertex(&graph);
	addGraphVertex(&graph);
	addGraphVertex(&graph);

	// Соединим ребра в слеующем порядке:
	//
	//  0 --> 1 --> 2
	//  ^           |
	//  |           |
	//  |           |
	//  |           |
	//  5 <-- 4 <-- 3
	//
	// (ребро 2-3 двунаправленное)
	addEdge(graph.gVertexes[0], graph.gVertexes[1]);
	addEdge(graph.gVertexes[1], graph.gVertexes[2]);
	addEdge(graph.gVertexes[2], graph.gVertexes[3]);
	addEdge(graph.gVertexes[3], graph.gVertexes[2]);
	addEdge(graph.gVertexes[3], graph.gVertexes[4]);
	addEdge(graph.gVertexes[4], graph.gVertexes[5]);
	addEdge(graph.gVertexes[5], graph.gVertexes[0]);

	printf("broad 0->1: %d\n",broadSearch(&graph, graph.gVertexes[0], graph.gVertexes[1]));
	printf("depth 0->1: %d\n",depthSearch(&graph, graph.gVertexes[0], graph.gVertexes[1]));
	printf("broad 0->5: %d\n",broadSearch(&graph, graph.gVertexes[0], graph.gVertexes[5]));
	printf("depth 0->5: %d\n",depthSearch(&graph, graph.gVertexes[0], graph.gVertexes[5]));
	printf("broad 3->2: %d\n",broadSearch(&graph, graph.gVertexes[3], graph.gVertexes[2]));
	printf("depth 3->2: %d\n",depthSearch(&graph, graph.gVertexes[3], graph.gVertexes[2]));

	printf("\n*deleteEdge(3, 2)\n\n");
	deleteEdge(graph.gVertexes[3], graph.gVertexes[2]);
	printf("broad 3->2: %d\n",broadSearch(&graph, graph.gVertexes[3], graph.gVertexes[2]));
	printf("depth 3->2: %d\n",depthSearch(&graph, graph.gVertexes[3], graph.gVertexes[2]));

};

void demoTrie(void){

	printf("\n--- Trie ---\n\n");

	// Создадим префиксное дерево:
	Vertex vertex = *createVertex();
	addWord(&vertex, "adress");
	addWord(&vertex, "eye");
	addWord(&vertex, "bas");
	addWord(&vertex, "basket");
	addWord(&vertex, "basketball");
	addWord(&vertex, "basta");
	addWord(&vertex, "cat");
	printTrie(&vertex);

	printf("\n*vertex.children[1]:\n\n");
	printTrie(vertex.children[1]);
	printf("have 'cat'? - %d\n", checkWord(&vertex, "cat"));
	printf("have 'dog'? - %d\n", checkWord(&vertex, "dog"));

	printf("\n*delete bas\n\n");
	deleteWord(&vertex, "bas");
	printTrie(&vertex);

	printf("\n*delete basketball\n\n");
	deleteWord(&vertex, "basketball");
	printTrie(&vertex);


};

void demoBiTree(void){

	printf("\n--- BiTree ---\n\n");

	// Создадим бинарное дерево:
	BiVertex *biVertex = createBiVertex(); //Рекомендуется создавать именно указатель
	addValue(biVertex, 2);
	addValue(biVertex, 4);
	addValue(biVertex, 8);
	addValue(biVertex, 5);
	addValue(biVertex, 9);
	addValue(biVertex, 10);
	addValue(biVertex, 11);
	Array arr = traversalBiVertex(biVertex);
	printArray(&arr);
	
	printf("have 4? - %d\n", checkValue(biVertex, 4));
	printf("have 6? - %d\n", checkValue(biVertex, 6));

	printf("\n*deleteValue(2)\n\n");
	deleteValue(biVertex, 2);
	arr = traversalBiVertex(biVertex);
	printArray(&arr);

	printf("\n*deleteValue(5)\n\n");
	deleteValue(biVertex, 5);
	arr = traversalBiVertex(biVertex);
	printArray(&arr);

	printf("\nhl = %d, hr = %d \n", biVertex->leftHeight, biVertex->rightHeight);
	printf("balancing \n");
	biVertex = balancingBiVertex(biVertex);
	printf("hl = %d, hr = %d \n\n", biVertex->leftHeight, biVertex->rightHeight);
	
	arr = traversalBiVertex(biVertex);
	printArray(&arr);

};

void demoHashTable(void){

	printf("\n--- HashTable ---\n\n");
	HashTable hTable = createHashTable();

	printf("have doll? - %d\n", checkWordInHashTable(&hTable, "doll"));
	printf("have child? - %d\n", checkWordInHashTable(&hTable, "child"));
	printf("have children? - %d\n\n", checkWordInHashTable(&hTable, "children"));

	addWordToHashTable(&hTable, "doll");
	addWordToHashTable(&hTable, "dog");
	addWordToHashTable(&hTable, "air");
	addWordToHashTable(&hTable, "ice");
	addWordToHashTable(&hTable, "hall");
	addWordToHashTable(&hTable, "child");
	addWordToHashTable(&hTable, "children");
	addWordToHashTable(&hTable, "ten");

	printf("have doll? - %d\n", checkWordInHashTable(&hTable, "doll"));
	printf("have child? - %d\n", checkWordInHashTable(&hTable, "child"));
	printf("have children? - %d\n", checkWordInHashTable(&hTable, "children"));

	printf("\n*delete('air')\n");
	printf("*delete('children')\n\n");
	deleteWordFromHashTable(&hTable, "air");
	deleteWordFromHashTable(&hTable, "children");

	printf("have doll? - %d\n", checkWordInHashTable(&hTable, "doll"));
	printf("have child? - %d\n", checkWordInHashTable(&hTable, "child"));
	printf("have children? - %d\n", checkWordInHashTable(&hTable, "children"));

};

void demoHelp(void){

	printf("\n--- Help ---\n\n");
	int x = 2, y = 5;
	printf("max = %d\n", max(x,y));
	printf("max = %d\n", min(x,y));

	printf("\n*swap(x,y)\n\n", x, y);
	swap(&x, &y);
	printf("x = %d, y = %d\n", x, y);

};

void demoSorted(void){

	printf("\n--- Sorting ---\n\n");
	srand(time(NULL));
	Array arr = createArray();
	for(int i = 0; i < 10; i++) insertToEndArray(&arr, rand()%100);
	printArray(&arr);

	printf("\n*bubbleSort\n\n");
	bubbleSort(&arr);
	printArray(&arr);

	printf("\n*createArray()\n\n");
    Array arr2 = createArray();
	for(int i = 0; i < 10; i++) insertToEndArray(&arr2, rand()%100);
	printArray(&arr2);

	printf("\n*combSort\n\n");
	combSort(&arr2);
	printArray(&arr2);

	printf("\n*createArray()\n\n");
    Array arr3 = createArray();
	for(int i = 0; i < 10; i++) insertToEndArray(&arr3, rand()%100);
	printArray(&arr3);

	printf("\n*quickSort\n\n");
	quickSort(&arr3);
	printArray(&arr3);

	printf("\n*createArray()\n\n");
    Array arr4 = createArray();
	for(int i = 0; i < 10; i++) insertToEndArray(&arr4, rand()%100);
	printArray(&arr4);

	printf("\n*mergeSort\n\n");
	mergeSort(&arr4);
	printArray(&arr4);

	printf("\n*createArray()\n\n");
    Array arr5 = createArray();
	for(int i = 0; i < 10; i++) insertToEndArray(&arr5, rand()%100);
	printArray(&arr5);

	printf("\n*pyramidSort (This sorting does not work correctly if there are two identical elements in the array)\n\n");
	pyramidSort(&arr5);
	printArray(&arr5);


};

int main(void){

	demoArray();
	demoList();
	demoGraph();
	demoTrie();
	demoBiTree();
	demoHashTable();
	demoHelp();
	demoSorted();

};
