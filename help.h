#pragma once

// ������� ���������� �������� �� 2 �����
int min(int a, int b){
	if(a < b) return a;
	else return b;
};

// ������� ���������� ��������� �� 2 �����
int max(int a, int b){
	if(a > b) return a;
	else return b;
};

// ������� ������������ ���� ��������� (������������� ������ �������)
void swap(int* a, int* b){
	int c = *a;
	*a = *b;
	*b = c;
};
