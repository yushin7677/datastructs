#pragma once
#include "help.h"
#include "array.h"

/////////////////////////////////////////////////////////////////
//                                                             //
//                     ���������� ������                       //
//                                                             //
/////////////////////////////////////////////////////////////////

//---------------------------//
// ��������� ������� ������� //
//---------------------------//
typedef struct Vertex_Tag{

	_Bool haveEnd;                 //������� �� ����� ����� �����
	char c;						   //������ � �������
	int howManyChildren;		   //����������� ��������
	struct Vertex_Tag **children;  //������ ���������� �� ��������
	
} Vertex;

//----------------------------------------------------------------------------//
// ������� �������� ����� ������� (���������� ��������� �� ��������� �������) //
//----------------------------------------------------------------------------//
Vertex* createVertex(){

	//������� ��������� �� ����� �������. ��� ���� ������� �������� ��� ��� ������
	Vertex *vertex;
	vertex = (Vertex*)malloc(sizeof(Vertex));

	//�������� �� �������� ���������� (��� ��� ������� ������ � �� �������� ��������)
	vertex->c = 0;
	vertex->howManyChildren = 0;
	vertex->children = NULL;
	vertex->haveEnd = 0;

	return vertex;

};

//----------------------//
// �������� ����������� //
//----------------------//
int clearVertex(Vertex *v){

	// ������� ����������, ������ �� �������� ������ �������
	for(int i = 0; i < v->howManyChildren; i++){

		clearVertex(v->children[i]); //���������� ������� ����������, ������ �� i-�� �������
		free(v->children[i]);        //����������� ������, ���������� �� i-�� �������

	};

	v->howManyChildren = 0;
	free(v->children); //����������� ������, ���������� �� ������ ���������� �� ��������

	return 0;

};

//------------------//
// ���������� ����� //
//------------------//
int addWord(Vertex *vertex, char *str){

	int size = strlen(str);      // ������ ������ ������

	// ��������� ����, ������� ������� ��������, ������� �������� � ������ � ������ ������ ������
	for(int i = 0; i < size; i++){

		// ������ �� �� ������� i-� ������� (0-��� ������� - ������)

		// ���� � ������ ������� ���� �������, ���������, ������� �� ����� ��� ������� � ��������, ����������� � str[i]
		if(vertex->howManyChildren > 0){

			// ������ j �����, ��� str[i] > children[j-1]->c � str[i] <= children[j]->c
			int j = 0;
			for(int k = 0; k < vertex->howManyChildren; k++){
				if(str[i] > vertex->children[j]->c) j++;
				else break;
			};

			// ���� ��� �������� � ��������, ����������� � str[i], �� ������� ����� �������
			if(j == vertex->howManyChildren || str[i] < vertex->children[j]->c){

				// �������� ������ ��� ����� ���������
				vertex->children = (Vertex**)realloc(vertex->children, (vertex->howManyChildren + 1) * sizeof(Vertex*));
				vertex->howManyChildren++;

				// � ������� children �������� ��� ��������� �� �������� ����� j ������������ ������
				for(int k = vertex->howManyChildren - 1; k > j; k--) vertex->children[k] = vertex->children[k - 1];

				vertex->children[j] = createVertex(); // ������� ������ �������
				vertex->children[j]->c = str[i];      // ���������� � ��� ������ str[i]
			};

			// ��������� � ������� � �������� str[i]
			vertex = vertex->children[j];

		}

		// ���� �������� ���, ������� ����� �������
		else{

			// �������� ������ ��� ����� ���������
			vertex->children = (Vertex**)malloc(sizeof(Vertex*)); 
			vertex->howManyChildren++;

			vertex->children[0] = createVertex(); // ������� ������ �������
			vertex->children[0]->c = str[i];      // ���������� � ��� ������ str[i]
			vertex = vertex->children[0];         // ��������� � ����� �������

		};
	};

	// ������� ����� �����
	vertex->haveEnd = 1;
	
	return 0;

};

//----------------------------------------------------------------------------//
// �������� ������� ����� � ������� (���������� 0 - ���� ��� � 1 - ���� ����) //
//----------------------------------------------------------------------------//
int chekWord(Vertex *vertex, char *str){

	int size = strlen(str);      // ������ ������ ������
	int haveWord = 1;            // ������������, ��� ����� str ���� � ������

	// ���������� ������ ������ � ���������������, ����:
	// 1) ������, ��� ������ ����� ���
	// 2) ������ ����������
	for(int i = 0; i < size && haveWord; i++){

		// ������ �� �� ������� i-� ������� (0-��� ������� - ������)

		// ���� � ������� ���� �������, ���������, ���� �� ����� ��� �����, � ������� ������ ��������� � str[i]
		if(vertex->howManyChildren > 0){

			// ������ j �����, ��� str[i] > children[j-1]->c � str[i] <= children[j]->c
			int j = 0;
			for(int k = 0; k < vertex->howManyChildren; k++){
				if(str[i] > vertex->children[j]->c) j++;
				else break;
			};

			// ���� ��� �������� � ��������, ����������� � str[i], ������ ����� ��� � ���� ���������������
			if(j == vertex->howManyChildren || str[i] < vertex->children[j]->c) haveWord = 0;

			// ����� ��������� � ������� � �������� str[i]
			else vertex = vertex->children[j];

		}

		// ���� ���, �� ����� � ������ ���
		else haveWord = 0;
	};

	// ���� �������, �� ������� �� ������������, ����� ����� � �� �� ���������, ��� ����� ���, ������ ����� ����
	if(vertex->haveEnd == 1 && haveWord) return 1;

	// ����� ����� ���
	else return 0;

};

//---------------------------------------------------------------------------------//
// �������� ����� (���������� 0 - ���� ����� ��� � 1 - ���� ����� ������� �������) //
//---------------------------------------------------------------------------------//
int deleteWord(Vertex *vertex, char *str){

	Vertex *parent = vertex;  // �������� ��������� �� ��������

	int size = strlen(str);       // ������ ������ ������
	int numb = 0;     			  // ����� ���������� ������� � ������� children ������ �������
	int haveWord = 1; 			  // ������������, ��� ����� str ���� � ������

	// ���������� ������ ������ � ���������������, ����:
	// 1) ������, ��� ������ ����� ���
	// 2) ������ ����������
	for(int i = 0; i < size && haveWord; i++){

		// ������ �� �� ������� i-� ������� (0-��� ������� - ������)

		// ���� � ������� ���� �������, ���������, ���� �� ����� ��� �����, � ������� ������ ��������� � str[i]
		if(vertex->howManyChildren > 0){

			// ������ j �����, ��� str[i] > children[j-1]->c � str[i] <= children[j]->c
			int j = 0;
			for(int k = 0; k < vertex->howManyChildren; k++){
				if(str[i] > vertex->children[j]->c) j++;
				else break;
			};

			// ���� ��� �������� � ��������, ����������� � str[i], ������ ����� ��� � ���� ���������������
			if(j == vertex->howManyChildren || str[i] < vertex->children[j]->c) haveWord = 0;

			// ����� ������ ��������� ��������
			else{

				// ���� � ������ ������� ����� ������ ������� ��� ���� ����� �����,
				// ��, ��������, � ������ ������� ����� ������� ��������� j-�� �������.
				// ����� ���������� ����������� ��������� parent � deleted
				if(vertex->howManyChildren > 1 || vertex->haveEnd){
					parent = vertex;
					numb = j; // �������� ����� ���������� �������
				};
				vertex = vertex->children[j]; // ��������� � ������� � �������� str[i]
			};

		}

		// ���� ���, �� ����� � ������ ���
		else haveWord = 0;
	};

	// ���� �������, �� ������� �� ������������, ����� ����� � �� �� ���������, ��� ����� ���,
	// ������ ����� ���� � ��� ����� �������
	if(vertex->haveEnd == 1 && haveWord){

		// ����� ������� �����, ����� ������� �����, ������� � ����� ������ ����� �����.
		// ������� �� ������� ������� �������� � ����� �������
		clearVertex(parent->children[numb]);  // ������ ���������
		free(parent->children[numb]);         // ����������� ������ 

		// � ������� children �������� ��� ��������� �� �������� ����� numb ������������ �����
		for(int i = numb; i < parent->howManyChildren - 1; i++) parent->children[i] = parent->children[i + 1];

		// ����������� ������, ��� ��� �������� ����� ������, � ������ � ���������� ����� ������
		parent->children = realloc(parent->children, (parent->howManyChildren - 1)*sizeof(Vertex*));
		parent->howManyChildren--;

		return 1;
	}

	// ����� ����� ���
	else return 0;

};

//-----------------------------------------------------------------------------//
// ����� ��������� ���� � ������ ������� � � �� ��������. ����� ���� � ������� //
//-----------------------------------------------------------------------------//
int printVertex(Vertex *vertex, char *str, int size){

	str = realloc(str, (size + 2)*sizeof(char));          // ������� ������ ��� ������ ������ ������������ ������ + �� ����� ������ + �� ������ ���������
	str[size + 1] = 0;                                    // ��������� � ����� ������ ������ ��������� ������

	for(int i = 0; i < vertex->howManyChildren; i++){
		str[size] = vertex->children[i]->c;                      // ��������� ����� ������ � ����� ������
		if(vertex->children[i]->haveEnd == 1) printf("%s\n",str);// ���� ������� ��������� �����, ������� �����, ������� ���������� � ������������ ������
		printVertex(vertex->children[i], str, size + 1);         // ���� ��������� ���� �� ����� �������� ������� ������
	};
	return 0;

};

//---------------//
// ����� ������� //
//---------------//
int printTrie(Vertex *vertex){

	// ������� ������������ ������, � ������� ����� ���������� ����� ��� ������
	// ��� �������� ������ �� �� ����� ��������� ������� ����� �����
	char *str = malloc(sizeof(char)); // ������� ������ ������: �������� ������ ������ ��� ������ ���������
	str[0] = 0;                       // � ������� ���� ������
	printVertex(vetrex, str, 0);	  // ���������� � �������� � ���� ��������� ����. �������� � ������� ��������� �� ���� ������ � ��� ����� ������
	free(str);                        // ������ ��� ������ �� �����, ������� ����������� ������, ���������� ��� ���
	return 0;

};

/////////////////////////////////////////////////////////////////
//                                                             //
//                      �������� ������                        //
//                                                             //
/////////////////////////////////////////////////////////////////

//----------------------//
// ��������� ��-������� //
//----------------------//
typedef struct BiVertex_Tag{

	int value;					     //�������� � �������
	int leftHeight;                  //������ ������ ���������
	int rightHeight;                 //������ ������� ���������
	struct BiVertex_Tag *leftChild;  //��������� �� ������ �������
	struct BiVertex_Tag *rightChild; //��������� �� ������� �������
	
} BiVertex;

//----------------------------------------------------------------------------------//
// ������� �������� ����� ��-������� (���������� ��������� �� ��������� ��-�������) //
//----------------------------------------------------------------------------------//
BiVertex* createBiVertex(){

	//������� ��������� �� ����� ��-�������. ��� ���� ��-������� �������� ������
	BiVertex *biVertex;
	biVertex = (BiVertex*)malloc(sizeof(BiVertex));

	//�������� �� �������� ���������� (��� ��� ��-������� ������ � �� �������� ��������)
	biVertex->value = 0;
	biVertex->leftHeight = 0;
	biVertex->rightHeight = 0;
	biVertex->leftChild = NULL;
	biVertex->rightChild = NULL;

	return biVertex;

};

//------------------//
// ���������� ����� //
//------------------//
int addValue(BiVertex *biVertex, int value){

	BiVertex *root = biVertex; // �������� �������� �������
	_Bool haveEnd = 0;         // ����������, ���������, ��������� �� �� ������ ����� ��� ������ ��������

	// ���� �� �������� ������ ����� ��� value, ��������� ��������:
	while(!haveEnd){

		// ���� ����� ������ �������� ������ ��-�������, �� ������� ������ �������
		if (value < biVertex->value){

			// ���� ������ ������� ���, ��...
			if(biVertex->leftChild == NULL){

				biVertex->leftChild = createBiVertex(); // ...������� ������ �������
				biVertex->leftChild->value = value;     // ����������� ��� �������� value
				haveEnd = 1;                            // � �������, ��� �� ��������� ���������� �����

			}

			// ����� �������� � ������ �������
			else biVertex = biVertex->leftChild;

		}

		// ���� ����� ������ �������� ������ ��-�������, �� ������� ������� �������
		else if (value > biVertex->value){

			// ���� ������� ������� ���, ��...
			if(biVertex->rightChild == NULL){

				biVertex->rightChild = createBiVertex(); // ...������� ������� �������
				biVertex->rightChild->value = value;     // ����������� ��� �������� value
				haveEnd = 1;                             // � �������, ��� �� ��������� ���������� �����

			}
			else biVertex = biVertex->rightChild;
		}

		// ���� ����� ����� �������� � ����, �� � ��������� ��� �� �����
		else haveEnd = 1;

	};

	calcHeights(root); // ����������� ������
	
	return 0;

};

//-------------//
// ����� ����� //
//-------------//
int checkValue(BiVertex *biVertex, int value){

	_Bool haveValue	= 1;			   // �����������, ��� ������ ����� � ������ ����
	_Bool haveEnd = 0;                 // ����������, ���������, ��������� �� �� ������ ����� ��� ������ ��������

	// ���� �� �������� ������ ����� ��� value, ��������� ��������:
	while(!haveEnd){

		// ���� ����� ������ �������� ������ ��-�������, �� ������� ������ �������
		if (value < biVertex->value){

			// ���� ������ ������� ���, ��...
			if(biVertex->leftChild == NULL){

				haveValue = 0; // ����� � ������ ���
				haveEnd = 1;   // � �������, ��� �� ��������� �������� �����

			}

			// ����� �������� � ������ �������
			else biVertex = biVertex->leftChild;

		}

		// ���� ����� ������ �������� ������ ��-�������, �� ������� ������� �������
		else if (value > biVertex->value){

			// ���� ������� ������� ���, ��...
			if(biVertex->rightChild == NULL){

				haveValue = 0; // ����� � ������ ���
				haveEnd = 1;   // � �������, ��� �� ��������� �������� �����

			}
			else biVertex = biVertex->rightChild;
		}

		// ���� ����� ����� ����� ��������, ������ �� ��� �����
		else haveEnd = 1;

	};
	
	return haveValue;

};

//----------------//
// �������� ����� //
//----------------//
int deleteValue(BiVertex *biVertex, int value){

	BiVertex *root = biVertex;     // �������� �������� �������
	BiVertex *parent = biVertex;   // ������� ��������� �� ��������, ������� �������� ������
	_Bool haveValue	= 1;		   // �����������, ��� ������ ����� � ������ ����
	_Bool haveEnd = 0;             // ����������, ���������, ��������� �� �� ������ ����� ��� ������ ��������

	// ���� �� �������� ������ ����� ��� value, ��������� ��������:
	while(!haveEnd){

		// ���� ����� ������ �������� ������ ��-�������, �� ������� ������ �������
		if (value < biVertex->value){

			// ���� ������ ������� ���, ��...
			if(biVertex->leftChild == NULL){

				haveValue = 0; // ����� � ������ ���
				haveEnd = 1;   // � �������, ��� �� ��������� �������� �����

			}

			// ����� �������� � ������ �������, �������� ��� ��������
			else{
				parent = biVertex;
				biVertex = biVertex->leftChild;
			};

		}

		// ���� ����� ������ �������� ������ ��-�������, �� ������� ������� �������
		else if (value > biVertex->value){

			// ���� ������� ������� ���, ��...
			if(biVertex->rightChild == NULL){

				haveValue = 0; // ����� � ������ ���
				haveEnd = 1;   // � �������, ��� �� ��������� �������� �����

			}

			// ����� �������� � ������ �������, �������� ��� ��������
			else{
				parent = biVertex;
				biVertex = biVertex->rightChild;
			};
		}

		// ���� ����� ����� ����� ��������, ������ �� ��� �����
		else haveEnd = 1;

	};

	// ���� ����� ����, �� �������� ��������� ��������:
	if(haveValue){

		_Bool canDelete = 0; // ���� ������� �� �����

		while(!canDelete){

			canDelete = 1; // �����������, ��� ������� �� �����

			if(biVertex->leftChild != NULL && biVertex->rightChild != NULL){

				canDelete = 0; // ���-���� ������� �� �� �����, ��� ��� � ����� ������� ���� 2 �������
				biVertex->value = biVertex->leftChild->value;
				biVertex->leftChild->value = value;
				parent = biVertex;
				biVertex = biVertex->leftChild;

			}
			else if(biVertex->leftChild == NULL && biVertex->rightChild != NULL){
				if(biVertex == biTree->root) biTree->root = biVertex->rightChild;
				else parent->leftChild = biVertex->rightChild;
			}
			else if(biVertex->leftChild != NULL && biVertex->rightChild == NULL){
				if(biVertex == biTree->root) biTree->root = biVertex->leftChild;
				else parent->leftChild = biVertex->leftChild;
			};


		};

		if(parent->leftChild == biVertex) parent->leftChild = NULL;
		else if(parent->rightChild == biVertex) parent->rightChild = NULL;
		free(biVertex);

	};

	calcHeights(root);
	
	return haveValue;

};

//-----------------------//
// ������ �������� ����� //
//-----------------------//
int calcHeights(BiVertex *biVertex){

	if (biVertex->leftChild != NULL){

		calcHeights(biVertex->leftChild);
		biVertex->leftHeight = max(biVertex->leftChild->leftHeight, biVertex->leftChild->rightHeight) + 1;
	
	}
	else biVertex->leftHeight = 0;

	if (biVertex->rightChild != NULL){

		calcHeights(biVertex->rightChild);
		biVertex->rightHeight = max(biVertex->rightChild->leftHeight, biVertex->rightChild->rightHeight) + 1;

	}
	else biVertex->rightHeight = 0;

	return 0;

};

//------------------------//
// ������� �������� ����� //
//------------------------//
int fastCalcHeights(BiVertex *biVertex){

	if (biVertex->leftChild != NULL){

		if (biVertex->leftChild->leftChild != NULL)
			biVertex->leftChild->leftHeight = max(biVertex->leftChild->leftChild->leftHeight, biVertex->leftChild->leftChild->rightHeight) + 1;
		else biVertex->leftChild->leftHeight = 0;

		if (biVertex->leftChild->rightChild != NULL)
			biVertex->leftChild->rightHeight = max(biVertex->leftChild->rightChild->leftHeight, biVertex->leftChild->rightChild->rightHeight) + 1;
		else biVertex->leftChild->rightHeight = 0;

		biVertex->leftHeight = max(biVertex->leftChild->leftHeight, biVertex->leftChild->rightHeight) + 1;
	
	}
	else biVertex->leftHeight = 0;

	if (biVertex->rightChild != NULL){

		if (biVertex->rightChild->leftChild != NULL)
			biVertex->rightChild->leftHeight = max(biVertex->rightChild->leftChild->leftHeight, biVertex->rightChild->leftChild->rightHeight) + 1;
		else biVertex->rightChild->leftHeight = 0;

		if (biVertex->rightChild->rightChild != NULL)
			biVertex->rightChild->rightHeight = max(biVertex->rightChild->rightChild->leftHeight, biVertex->rightChild->rightChild->rightHeight) + 1;
		else biVertex->rightChild->rightHeight = 0;
		
		biVertex->rightHeight = max(biVertex->rightChild->leftHeight, biVertex->rightChild->rightHeight) + 1;

	}
	else biVertex->rightHeight = 0;

	return 0;

};

//---------------------------------//
// ������� ����� ������ ��-������� //
//---------------------------------//
BiVertex* rotateLeft (BiVertex *biVertex){

	BiVertex *tmp = biVertex->rightChild;
	biVertex->rightChild = tmp->leftChild;
	tmp->leftChild = biVertex;
	return tmp;

};

//----------------------------------//
// ������� ������ ������ ��-������� //
//----------------------------------//
BiVertex* rotateRight (BiVertex *biVertex){

	BiVertex *tmp = biVertex->leftChild;
	biVertex->leftChild = tmp->rightChild;
	tmp->rightChild = biVertex;
	return tmp;

};

//-------------------------//
// ������������ ��-������� //
//-------------------------//
BiVertex* balancingBiVertex(BiVertex *biVertex){

	int balance = biVertex->rightHeight - biVertex->leftHeight;
	while(balance > 1 || balance < -1){

		if(balance > 1){

			if(biVertex->rightChild != NULL && (biVertex->rightChild->leftHeight > biVertex->rightChild->rightHeight)){
				biVertex->rightChild = rotateRight(biVertex->rightChild);
				fastCalcHeights(biVertex->rightChild);
			};

			biVertex = rotateLeft(biVertex);
			fastCalcHeights(biVertex);
		}
		else if (balance < -1){

			if(biVertex->leftChild != NULL && (biVertex->leftChild->leftHeight < biVertex->leftChild->rightHeight)){
				biVertex->leftChild = rotateLeft(biVertex->leftChild);
				fastCalcHeights(biVertex->leftChild);
			};

			biVertex = rotateRight(biVertex);
			fastCalcHeights(biVertex);

		};

		if(biVertex->leftChild != NULL) biVertex->leftChild = balancingBiVertex(biVertex->leftChild);
		if(biVertex->rightChild != NULL) biVertex->rightChild = balancingBiVertex(biVertex->rightChild);
		fastCalcHeights(biVertex);

		balance = biVertex->rightHeight - biVertex->leftHeight;

	};

	return biVertex;

};

//----------------------------//
// ����� ��������� ��-������� //
//----------------------------//
Array traversalBiVertex(BiVertex *biVertex){

	Array arr = createArray();

	if(biVertex->leftChild != NULL){
		arr = traversalBiVertex(biVertex->leftChild);
		pushIntoEnd(&arr, biVertex->value);
		if(biVertex->rightChild != NULL){
			Array arr2 = traversalBiVertex(biVertex->rightChild);
			mergeArray(&arr, &arr2);
		};
	}
	else if(biVertex->rightChild != NULL){
		pushIntoEnd(&arr, biVertex->value);
		Array arr2 = traversalBiVertex(biVertex->rightChild);
		mergeArray(&arr, &arr2);
	}
	else{
		pushIntoEnd(&arr, biVertex->value);
	};

	return arr;

};
