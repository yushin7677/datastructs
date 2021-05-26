#ifndef LIST_H
#define LIST_H
#endif

/////////////////////////////////////////////////////////////////
//                                                             //
//                          ������                             //
//                                                             //
/////////////////////////////////////////////////////////////////

//-----------------------------//
// ��������� ������������ ���� //
//-----------------------------//
typedef struct Node_tag{

	int value;
	struct Node_tag *next;
	
} Node;

//-------------------------------//
// ��������� ������������ ������ //
//-------------------------------//
typedef struct List_tag{

	Node *head;
	
} List;

//----------------------------------------------------------------------------------------------------------------------//
// ������� ��������� 1-������ ([��������� �� List]) // ���������� 0
//----------------------------------------------------------------------------------------------------------------------//
int clearList(List *list){ 

	list->head = NULL;
	return 0;
	
};

//----------------------------------------------------------------------------------------------------------------------//
// ������� ������ 1-������ ([��������� �� List]) // ���������� 0
//----------------------------------------------------------------------------------------------------------------------//
int printList(List *list){

	// ���� ������ �� ������, ������� ������ ��� ����
	if(list->head != NULL){

		Node *tmp = list->head;  // ������� ��������� �� ������ ����
		while(tmp != NULL){ 	 // ���� ��������� ��������, �������� ��������:

			printf("List-node = %d\n",tmp->value); // ������� �������� ����, �� ������� ��������� tmp
			tmp = tmp->next;					   // ���������� tmp �� ��������� ����. ���� ��� ���, ���� ����������

		};

	}

	// � ��������� ������ ������� ��������� � ���, ��� ������ ����
	else printf("printList: This is void list\n");

	return 0;
	
};

//----------------------------------------------------------------------------------------------------------------------//
// ������� ���������� ���� � ������ 1-������ ([��������� �� List], [��������]) // ���������� 0
//----------------------------------------------------------------------------------------------------------------------//
int InsertToBeginList(List *list, int value){ 

	Node *tmp = (Node*) malloc(sizeof(Node)); //������� ����
	tmp->value = value;                       //������ ��� ��������

	if(list->head != NULL) tmp->next = list->head; //���� ������ �� ������, �������� ����->next ������ �� ������ ���� ������
	else tmp->next = NULL;						   //����� �������� ��� NULL

	list->head = tmp;
	return 0;
	
};

//----------------------------------------------------------------------------------------------------------------------//
// ������� �������� ���� �� ������ 1-������ ([��������� �� List]) // ���������� �������� ���������� ����
//----------------------------------------------------------------------------------------------------------------------//
int deleteFromBeginList(List *list){ 

	// ���� ������ �� ������, ������ ������ ����
	if(list->head != NULL){
		Node *tmp = list->head;   		// �������� ����� ��������� �� ������ �������
		list->head = list->head->next;  // ������������� head �� 2-� ����

		int a = tmp->value;
		free(tmp);						// ��������� ������ ����
		return a;
	}

	// � ��������� ������ ������� ��������� � ���, ��� ������ ����
	else printf("deleteFromBeginList: This is void list\n");	
	return 0;
	
};

//----------------------------------------------------------------------------------------------------------------------//
// ������� ���������� ���� � ����� 1-������ ([��������� �� List], [��������]) // ���������� 0
//----------------------------------------------------------------------------------------------------------------------//
int InsertToEndList(List *list, int value){ 

	// ���� ������ �� ������, ������ ��� ��������� ����
	if(list->head != NULL){

		Node *tmp = list->head;   				  // ������� ��������� �� ������ ����
		while(tmp->next != NULL) tmp = tmp->next; // ���� ��������� tmp->next ��������, ������������� ��� �� ��������� ����.
		
		// ������ tmp ��������� �� ��������� ���� ������

		Node *tmp2 = (Node*) malloc(sizeof(Node)); // ������� ����� ����
		tmp2->value = value;					   // ������ ��� ��������
		tmp->next = tmp2;						   // �������� ��������� ���������� ���� �� ���� tmp2

	}

	// ����� ������ �������� ���� � ������� ��� � ������ ������
	else{

		Node *tmp = (Node*) malloc(sizeof(Node)); // ������� ����� ����
		tmp->value = value;					   	  // ������ ��� ��������
		list->head = tmp;						  // ������� ��� ������ ����� ������

	};

	return 0;
	
};

//----------------------------------------------------------------------------------------------------------------------//
// ������� �������� ���� �� ����� 1-������ ([��������� �� List]) // ���������� �������� ���������� ����
//----------------------------------------------------------------------------------------------------------------------//
int deleteFromEndList(List *list){ 

	// ���� ������ �� ������, ������ ������ ����
	if(list->head != NULL){
		Node *tmp = list->head;   				  // �������� ����� ��������� �� ������ �������
		while(tmp->next != NULL) tmp = tmp->next; // ���� ��������� tmp->next ��������, ������������� ��� �� ��������� ����.

		// ������ tmp ��������� �� ��������� ���� ������

		// ���� head ��������� �� ��������� ����, �.�. � ������ ����� 1 ����, �� ������� head
		if(list->head == tmp) list->head = NULL;

		// ����� ������ ������������� ������� � ������� ��� ���������
		else{

			Node *tmp2 = list->head; 						   // �������� ����� ��������� �� ������ �������
			while(tmp2->next->next != NULL) tmp2 = tmp2->next; // ���� ��������� tmp2->next->next ��������, ������������� ��� �� ��������� ����.

			// ������ tmp2 ��������� �� ������������� ���� ������
			tmp2->next = NULL;

		};

		return tmp->value;
		free(tmp);
	}

	// � ��������� ������ ������� ��������� � ���, ��� ������ ����
	else printf("deleteFromEndList: This is void list\n");	
	return 0;
	
};
