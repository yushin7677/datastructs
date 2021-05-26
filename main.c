#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"

int main(){

	srand(time(NULL));
	Array arr;
	for(int i = 0; i < 100; i++){
		pushIntoEnd(&arr, rand()%100);
	};
	printArray(&arr);
	printf("\n1111\n\n");
	mergeSort(&arr);
	printArray(&arr);

};
