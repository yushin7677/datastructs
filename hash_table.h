#pragma once

/////////////////////////////////////////////////////////////////
//                                                             //
//                       ���-�������                           //
//                                                             //
/////////////////////////////////////////////////////////////////

//--------------------------------------//
// ��������� ������������ ���� � ������ //
//--------------------------------------//
typedef struct WordNode_tag{

	char *word;
	struct WordNode_tag *next;
	
} WordNode;

//-----------------------//
// ��������� ���-������� //
//-----------------------//
typedef struct HashTable_tag{

	WordNode *wordNode[26]; // ���������� ��������� ���� � ��������
	
} HashTable;

//----------------------//
// �������� ���-������� //
//----------------------//
HashTable createHashTable(){

	HashTable hTable;
	for(int i = 0; i < 26; i++) hTable.wordNode[i] = NULL;
	return hTable;
	
};

//-----------------------//
// ������� � ���-������� //
//-----------------------//
int addWordToHashTable(HashTable *hTable, char *word){

	if(strlen(word) > 0){

		int num = word[0] - 'a';
		WordNode *node = malloc(sizeof(WordNode));
		node->word = word;
		node->next = hTable->wordNode[num];
		hTable->wordNode[num] = node;
		return 1;

	}
	else return 0;
	
};

//---------------------//
// ����� � ���-������� //
//---------------------//
int checkWordInHashTable(HashTable *hTable, char *word){

	if(strlen(word) > 0){

		_Bool haveWord = 0;
		int num = word[0] - 'a';
		WordNode *node = hTable->wordNode[num];
		while(node != NULL && !haveWord){

			haveWord = 1;

			if(strlen(word) != strlen(node->word)) haveWord = 0;
			else for(int i = 0; i < strlen(word) && i < strlen(node->word) && haveWord; i++) if(word[i] != node->word[i]) haveWord = 0;

			node = node->next;

		};

		return haveWord;	

	}
	else return 0;
	
};

//-------------------------//
// �������� �� ���-������� //
//-------------------------//
int deleteWordFromHashTable(HashTable *hTable, char *word){

	if(strlen(word) > 0){

		_Bool haveWord = 0;
		int num = word[0] - 'a';
		WordNode *node = hTable->wordNode[num];
		WordNode *parent = hTable->wordNode[num];

		while(node != NULL && !haveWord){

			haveWord = 1;

			if(strlen(word) != strlen(node->word)) haveWord = 0;
			else for(int i = 0; i < strlen(word) && i < strlen(node->word) && haveWord; i++) if(word[i] != node->word[i]) haveWord = 0;

			if(!haveWord){
				parent = node;
				node = node->next;
				return 0;
			}
			else if(node == hTable->wordNode[num]){
				free(node);
				hTable->wordNode[num] = NULL;
				return 1;
			}
			else{
				parent->next = node->next;
				free(node);
				return 1;
			};

		};	

	}
	else return 0;
	
};
