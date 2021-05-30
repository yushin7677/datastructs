#pragma once
#include "help.h"
#include "array.h"
#include "tree.h"

/////////////////////////////////////////////////////////////////
//                                                             //
//            ���������� ������������� �������                 //
//                                                             //
/////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------------------------------------------------//
// ���������� ��������� ([��������� �� Array]) //
//----------------------------------------------------------------------------------------------------------------------//
int bubbleSort(Array *arr){ 

	for(int i = 1; i < arr->size; i++)
		for(int j = 0; j < arr->size - i; j++)
			if(arr->p[j] > arr->p[j + 1]) swap(&(arr->p[j]), &(arr->p[j + 1]));

	return 0;
	
};

//----------------------------------------------------------------------------------------------------------------------//
// ���������� ��������� ([��������� �� Array]) //
//----------------------------------------------------------------------------------------------------------------------//
int combSort(Array *arr){ 

	const double f = 1.247; // ���������� ����� ��� ������ ����������
	double r = arr->size/f;

	while(r >= 1){

		for(int j = 0; j + r < arr->size; j++){

			int i = j + r;
			if(arr->p[j] > arr->p[i]) swap(&(arr->p[j]), &(arr->p[i]));
			
		};

		r /= f;

	};

	return 0;
	
};

//-------------------------------------------//
// ������� ���������� ([��������� �� Array]) //
//-------------------------------------------//
int quickSort(Array *arr){ 

	shortQuickSort(arr, 0, arr->size - 1);
	return 0;
	
};

//------------------------------------------------------------------//
// ������� ���������� ���������� ([��������� �� Array],[int],[int]) //
//------------------------------------------------------------------//
int shortQuickSort(Array *arr, int first, int last){ 

	if(0 <= first && first <= last && last <= arr->size){
		int piv = arr->p[(first+ last)/2];
		int l = first;
		int r = last;
		while (l <= r){

		    while (arr->p[l] < piv) l++;
		    while (arr->p[r] > piv) r--;
		    if (l <= r){
				swap(&(arr->p[l]), &(arr->p[r]));
				l++;
				r--;
			};

		};
		if (first < r) shortQuickSort(arr, first, r);
	  	if (last > l) shortQuickSort(arr, l, last);
	};

	return 0;
	
};

//-------------------------------------------------------------------------------//
// C������� 2 �������� � �����������([��������� �� Array], [��������� �� Array]) //
//-------------------------------------------------------------------------------//
Array sortedMerge(Array *arr1, Array *arr2){

	int i = 0, j = 0;
	Array arr3 = createArray();

	while(i < arr1->size && j < arr2->size){

		if(arr1->p[i] < arr2->p[j]){
			pushIntoEnd(&arr3, arr1->p[i]);
			i++;
		}
		else{
			pushIntoEnd(&arr3, arr2->p[j]);
			j++;
		};


	};

	while(i < arr1->size){
		pushIntoEnd(&arr3, arr1->p[i]);
		i++;
	};

	while(j < arr2->size){
		pushIntoEnd(&arr3, arr2->p[j]);
		j++;
	};

	return arr3;
};

//--------------------------------------------//
// C��������� �������� ([��������� �� Array]) //
//--------------------------------------------//
int mergeSort(Array *arr){ 

	Array *arrays = malloc(arr->size * sizeof(Array));

	for(int i = 0; i < arr->size; i++){
		arrays[i] = createArray();
		pushIntoEnd(&(arrays[i]), arr->p[i]);
	};

	int howManyArrays = arr->size;

	while(howManyArrays > 1){

		int i = 0;

		while(i*2 < howManyArrays){
			if((i*2 + 1) < howManyArrays) arrays[i] = sortedMerge(&arrays[i*2], &arrays[i*2 + 1]);
			else arrays[i] = arrays[i*2];
			i++;
		};

		howManyArrays = i;

	};
	*arr = arrays[0];
	free(arrays);
	return 0;
	
};

//----------------------------------------------//
// C��������� ���������� ([��������� �� Array]) //
//----------------------------------------------//
int pyramidSort(Array *arr){ 

	BiVertex biVertex = createBibiVertex();
	if(arr->size > 0) biVertex->value = arr->p[0];
	for(int i = 1; i < arr->size; i++) addValue(&biVertex, arr->p[i]);
	free(arr->p);
	arr->size = 0;
	*arr = traversalBiVertex(&biVertex);
	return 0;
	
};
