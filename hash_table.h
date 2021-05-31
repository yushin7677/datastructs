#pragma once
#include <stdio.h>

/////////////////////////////////////////////////////////////////
//                                                             //
//                       Хэш-таблицы                           //
//                                                             //
/////////////////////////////////////////////////////////////////

//--------------------------------------//
// Структура односвязного узла с словом //
//--------------------------------------//
typedef struct WordNode_tag{

	char *word;
	struct WordNode_tag *next;
	
} WordNode;

//-----------------------//
// Структура хэш-таблицы //
//-----------------------//
typedef struct HashTable_tag{

	WordNode *wordNode[26]; // Количество латинских букв в алфавите
	
} HashTable;

//----------------------//
// Создание хэш-таблицы //
//----------------------//
HashTable createHashTable(void){

	HashTable hTable;
	for(int i = 0; i < 26; i++) hTable.wordNode[i] = NULL;
	return hTable;
	
};

//---------------------//
// Поиск в хэш-таблице //
//---------------------//
int checkWordInHashTable(HashTable *hTable, char *word){

	if(strlen(word) > 0){

		_Bool haveWord = 0;
		int num = word[0] - 'a';
		WordNode *node = hTable->wordNode[num];
		while(node != NULL && !haveWord){

			haveWord = 1;

			if(strlen(word) != strlen(node->word)) haveWord = 0;
			else{
				for(unsigned long long int i = 0; i < strlen(word) && i < strlen(node->word) && haveWord; i++)
					if(word[i] != node->word[i]) haveWord = 0;
			};

			node = node->next;

		};

		return haveWord;	

	}
	else return 0;
	
};

//-----------------------//
// Вставка в хэш-таблицу //
//-----------------------//
int addWordToHashTable(HashTable *hTable, char *word){

	if(strlen(word) > 0 && !checkWordInHashTable(hTable, word)){

		int num = word[0] - 'a';
		WordNode *node = malloc(sizeof(WordNode));
		node->word = word;
		node->next = hTable->wordNode[num];
		hTable->wordNode[num] = node;
		return 1;

	}
	else return 0;
	
};

//-------------------------//
// Удаление из хэш-таблицы //
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
			else{
				for(unsigned long long int i = 0; i < strlen(word) && i < strlen(node->word) && haveWord; i++)
					if(word[i] != node->word[i]) haveWord = 0;
			};

			if(!haveWord){
				parent = node;
				node = node->next;
			}
			else if(node == hTable->wordNode[num]){
				hTable->wordNode[num] = hTable->wordNode[num]->next;
				free(node);
			}
			else{
				parent->next = node->next;
				free(node);
			};

		};

		return haveWord;

	}
	else return 0;
	
};
