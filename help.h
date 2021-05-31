#pragma once

// Функция нахождения минимума из 2 чисел
int min(int a, int b){
	if(a < b) return a;
	else return b;
};

// Функция нахождения максимума из 2 чисел
int max(int a, int b){
	if(a > b) return a;
	else return b;
};

// Функция перестановки двух элементов (необязательно внутри массива)
void swap(int* a, int* b){
	int c = *a;
	*a = *b;
	*b = c;
};
