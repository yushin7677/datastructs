#pragma once
#include "list.h"

/////////////////////////////////////////////////////////////////
//                                                             //
//                           ����                              //
//                                                             //
/////////////////////////////////////////////////////////////////

//-----------------//
// ��������� ����� //
//-----------------//
typedef struct{

	Node *first;
	
} Stack;

//----------------------------------------------------------------------------------------------------------------------//
// ������� �������� �����([��������� �� Stack]) // ���������� 0
//----------------------------------------------------------------------------------------------------------------------//
Stack createStack(){ 

	Stack stack;
	stack->first = NULL;

	return stack;
	
};

//------------------------------------------------------//
// ������� ������ ����� � �������([��������� �� Stack]) //
//------------------------------------------------------//
int printStack(Stack *stack){ 

	Node *node = stack->first;

	// ���� ���� �������������, �� ������� ���
	if(stack->first != NULL){
		while(node != NULL){

			printf("value = %d\n", node->value);
			node = node->next;

		};
	}

	// � ��������� ������ ������� ��������� � ���, ��� ���� ����
	else printf("printStack: This is void stack\n");
	
};

//----------------------------------------------------------------------------------------------------------------------//
// ������� ������� �������� � ����([��������� �� Stack],[��������]) // ���������� 0 - ������, -1 - ������
//----------------------------------------------------------------------------------------------------------------------//
int pushToStack(Stack *stack, int value){ 

	Node *node = malloc(sizeof(Node));
	node->value = value;
	node->next = stack->first;
	stack->first = node;

	return 0;
	
};

//----------------------------------------------------------------------------------------------------------------------//
// ������� �������� �������� ����� ([��������� �� Stack]) // ���������� �������� ���������� ��������
//----------------------------------------------------------------------------------------------------------------------//
int popFromStack(Stack *stack){ 

	// ���� ���� �������������, �� ������ ������ �������
	if(stack->first != NULL){
		Node *node = stack->first;
		stack->first = stack->first->next;
		free(node);
		return 1;
	}

	// � ��������� ������ ������� ��������� � ���, ��� ���� ����
	else return 0;
	
};
