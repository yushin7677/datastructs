#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"
#include "graph.h"
#include "hash_table.h"

int main(){

	HashTable hTable = createHashTable();
	addWordToHashTable(&hTable, "qwerty");
	printf("a = %d\n", checkWordInHashTable(&hTable, "qwerty"));
	deleteWordFromHashTable(&hTable, "qwerty");
	printf("a = %d\n", checkWordInHashTable(&hTable, "qwerty"));
	addWordToHashTable(&hTable, "qwerty");
	printf("a = %d\n", checkWordInHashTable(&hTable, "qwerty"));

};
