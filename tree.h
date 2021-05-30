#pragma once
#include "help.h"
#include "array.h"

/////////////////////////////////////////////////////////////////
//                                                             //
//                     Префиксное дерево                       //
//                                                             //
/////////////////////////////////////////////////////////////////

//---------------------------//
// Структура вершины словаря //
//---------------------------//
typedef struct Vertex_Tag{

	_Bool haveEnd;                 //Имеется ли здесь конец слова
	char c;						   //Символ в вершине
	int howManyChildren;		   //Количенство потомков
	struct Vertex_Tag **children;  //Массив указателей на потомков
	
} Vertex;

//----------------------------------------------------------------------------//
// Функция создания новой вершины (возвращает указатель на созданную вершину) //
//----------------------------------------------------------------------------//
Vertex* createVertex(){

	//Создаем указатель на новую вершину. Под саму вершину выделяем под нее память
	Vertex *vertex;
	vertex = (Vertex*)malloc(sizeof(Vertex));

	//Заполним ее нулевыми свойствами (так как вершина пустая и не содержит потомков)
	vertex->c = 0;
	vertex->howManyChildren = 0;
	vertex->children = NULL;
	vertex->haveEnd = 0;

	return vertex;

};

//----------------------//
// Удаление поддеревьев //
//----------------------//
int clearVertex(Vertex *v){

	// Удаляем поддеревья, идущие от потомков данной вершины
	for(int i = 0; i < v->howManyChildren; i++){

		clearVertex(v->children[i]); //Рекурсивно удаляем поддеревья, идущие от i-го потомка
		free(v->children[i]);        //Освобождаем память, выделенную на i-го потомка

	};

	v->howManyChildren = 0;
	free(v->children); //Освобождаем память, выделенную на массив указателей на потомков

	return 0;

};

//------------------//
// Добавление слова //
//------------------//
int addWord(Vertex *vertex, char *str){

	int size = strlen(str);      // Узнаем размер строки

	// Запускаем цикл, имеющий столько итераций, сколько символов в строке и пойдем вглубь дерева
	for(int i = 0; i < size; i++){

		// Сейчас мы на вершине i-й глубины (0-вая глубина - корень)

		// Если в данной вершине есть потомки, проверяем, имеются ли среди них потомок с символом, совпадающий с str[i]
		if(vertex->howManyChildren > 0){

			// Найдем j такое, что str[i] > children[j-1]->c и str[i] <= children[j]->c
			int j = 0;
			for(int k = 0; k < vertex->howManyChildren; k++){
				if(str[i] > vertex->children[j]->c) j++;
				else break;
			};

			// Если нет потомков с символом, совпадающим с str[i], то создаем новую вершину
			if(j == vertex->howManyChildren || str[i] < vertex->children[j]->c){

				// Выделяем память под новый указатель
				vertex->children = (Vertex**)realloc(vertex->children, (vertex->howManyChildren + 1) * sizeof(Vertex*));
				vertex->howManyChildren++;

				// В массиве children сдвигаем все указатели на потомков после j включительно вправо
				for(int k = vertex->howManyChildren - 1; k > j; k--) vertex->children[k] = vertex->children[k - 1];

				vertex->children[j] = createVertex(); // Создаем пустую вершину
				vertex->children[j]->c = str[i];      // Записываем в нее символ str[i]
			};

			// Переходим к потомку с символом str[i]
			vertex = vertex->children[j];

		}

		// Если потомков нет, создаем новую вершину
		else{

			// Выделяем память под новый указатель
			vertex->children = (Vertex**)malloc(sizeof(Vertex*)); 
			vertex->howManyChildren++;

			vertex->children[0] = createVertex(); // Создаем пустую вершину
			vertex->children[0]->c = str[i];      // Записываем в нее символ str[i]
			vertex = vertex->children[0];         // Переходим к этому потомку

		};
	};

	// Пометим конец слова
	vertex->haveEnd = 1;
	
	return 0;

};

//----------------------------------------------------------------------------//
// Проверка наличия слова в словаре (возвращает 0 - если нет и 1 - если есть) //
//----------------------------------------------------------------------------//
int chekWord(Vertex *vertex, char *str){

	int size = strlen(str);      // Узнаем размер строки
	int haveWord = 1;            // Предпологаем, что слово str есть в дереве

	// Проходимся вглубь дерева и останавливаемся, если:
	// 1) поймем, что такого слова нет
	// 2) строка закончится
	for(int i = 0; i < size && haveWord; i++){

		// Сейчас мы на вершине i-й глубины (0-вая глубина - корень)

		// Если у вершины есть потомки, проверяем, есть ли среди них такие, у которых символ совпадает с str[i]
		if(vertex->howManyChildren > 0){

			// Найдем j такое, что str[i] > children[j-1]->c и str[i] <= children[j]->c
			int j = 0;
			for(int k = 0; k < vertex->howManyChildren; k++){
				if(str[i] > vertex->children[j]->c) j++;
				else break;
			};

			// Если нет потомков с символом, совпадающим с str[i], значит слова нет и цикл останавливается
			if(j == vertex->howManyChildren || str[i] < vertex->children[j]->c) haveWord = 0;

			// Иначе переходим к потомку с символом str[i]
			else vertex = vertex->children[j];

		}

		// Если нет, то слова в дереве нет
		else haveWord = 0;
	};

	// Если вершина, на которой мы остановились, имеет конец и мы не убедились, что слова нет, значит слово есть
	if(vertex->haveEnd == 1 && haveWord) return 1;

	// Иначе слова нет
	else return 0;

};

//---------------------------------------------------------------------------------//
// Удаление слова (возвращает 0 - если слова нет и 1 - если слово успешно удалено) //
//---------------------------------------------------------------------------------//
int deleteWord(Vertex *vertex, char *str){

	Vertex *parent = vertex;  // Создадим указатель на родителя

	int size = strlen(str);       // Узнаем размер строки
	int numb = 0;     			  // Номер удаляемого потомка в массиве children данной вершины
	int haveWord = 1; 			  // Предпологаем, что слово str есть в дереве

	// Проходимся вглубь дерева и останавливаемся, если:
	// 1) поймем, что такого слова нет
	// 2) строка закончится
	for(int i = 0; i < size && haveWord; i++){

		// Сейчас мы на вершине i-й глубины (0-вая глубина - корень)

		// Если у вершины есть потомки, проверяем, есть ли среди них такие, у которых символ совпадает с str[i]
		if(vertex->howManyChildren > 0){

			// Найдем j такое, что str[i] > children[j-1]->c и str[i] <= children[j]->c
			int j = 0;
			for(int k = 0; k < vertex->howManyChildren; k++){
				if(str[i] > vertex->children[j]->c) j++;
				else break;
			};

			// Если нет потомков с символом, совпадающим с str[i], значит слова нет и цикл останавливается
			if(j == vertex->howManyChildren || str[i] < vertex->children[j]->c) haveWord = 0;

			// Иначе делаем следующие действия
			else{

				// Если у данной вершины более одного потомка или есть конец слова,
				// то, возможно, у данной вершины стоит удалить поддерево j-го потомка.
				// Тогда необходимо переуказать указатели parent и deleted
				if(vertex->howManyChildren > 1 || vertex->haveEnd){
					parent = vertex;
					numb = j; // Запомним номер удаляемого потомка
				};
				vertex = vertex->children[j]; // Переходим к потомку с символом str[i]
			};

		}

		// Если нет, то слова в дереве нет
		else haveWord = 0;
	};

	// Если вершина, на которой мы остановились, имеет конец и мы не убедились, что слова нет,
	// значит слово есть и его нужно удалить
	if(vertex->haveEnd == 1 && haveWord){

		// Чтобы удалить слово, нужно удалить ветку, ведущую в конец ТОЛЬКО этого слова.
		// Поэтому мы заранее указали родителя и номер потомка
		clearVertex(parent->children[numb]);  // Удалим поддерево
		free(parent->children[numb]);         // Освобождаем память 

		// В массиве children сдвигаем все указатели на потомков после numb включительно влево
		for(int i = numb; i < parent->howManyChildren - 1; i++) parent->children[i] = parent->children[i + 1];

		// Освобождаем память, так как потомков стало меньше, а значит и указателей стало меньше
		parent->children = realloc(parent->children, (parent->howManyChildren - 1)*sizeof(Vertex*));
		parent->howManyChildren--;

		return 1;
	}

	// Иначе слова нет
	else return 0;

};

//-----------------------------------------------------------------------------//
// Поиск окончания слов в данной вершине и в ее потомках. Вывод слов в консоль //
//-----------------------------------------------------------------------------//
int printVertex(Vertex *vertex, char *str, int size){

	str = realloc(str, (size + 2)*sizeof(char));          // Выделим память под нужный размер существующий строки + на новый символ + на символ окончания
	str[size + 1] = 0;                                    // Обозначим в конце строки символ окончания строки

	for(int i = 0; i < vertex->howManyChildren; i++){
		str[size] = vertex->children[i]->c;                      // Вставляем новый символ в конец строки
		if(vertex->children[i]->haveEnd == 1) printf("%s\n",str);// Если найдено окончание слова, выведем слово, которое записалось в динамической строке
		printVertex(vertex->children[i], str, size + 1);         // Ищем окончания слов на более глубоких уровнях дерева
	};
	return 0;

};

//---------------//
// Вывод словаря //
//---------------//
int printTrie(Vertex *vertex){

	// Создаем динамическую строку, в которую будем записывать слова для вывода
	// Для экономии памяти мы не будем создавать никаких новых строк
	char *str = malloc(sizeof(char)); // Создаем пустую строку: выделяем память только под символ окончания
	str[0] = 0;                       // и запишем этот символ
	printVertex(vetrex, str, 0);	  // Опускаемся к потомкам и ищем окончания слов. Передаем в функцию указатель на нашу строку и его явный размер
	free(str);                        // Строка нам больше не нужна, поэтому освобождаем память, выделенную под нее
	return 0;

};

/////////////////////////////////////////////////////////////////
//                                                             //
//                      Бинарное дерево                        //
//                                                             //
/////////////////////////////////////////////////////////////////

//----------------------//
// Структура би-вершины //
//----------------------//
typedef struct BiVertex_Tag{

	int value;					     //Значение в вершине
	int leftHeight;                  //Высота левого поддерева
	int rightHeight;                 //Высота правого поддерева
	struct BiVertex_Tag *leftChild;  //Указатель на левого потомка
	struct BiVertex_Tag *rightChild; //Указатель на правого потомка
	
} BiVertex;

//----------------------------------------------------------------------------------//
// Функция создания новой би-вершины (возвращает указатель на созданную би-вершину) //
//----------------------------------------------------------------------------------//
BiVertex* createBiVertex(){

	//Создаем указатель на новую би-вершину. Под саму би-вершину выделяем память
	BiVertex *biVertex;
	biVertex = (BiVertex*)malloc(sizeof(BiVertex));

	//Заполним ее нулевыми свойствами (так как би-вершина пустая и не содержит потомков)
	biVertex->value = 0;
	biVertex->leftHeight = 0;
	biVertex->rightHeight = 0;
	biVertex->leftChild = NULL;
	biVertex->rightChild = NULL;

	return biVertex;

};

//------------------//
// Добавление числа //
//------------------//
int addValue(BiVertex *biVertex, int value){

	BiVertex *root = biVertex; // Запомним корневую вершину
	_Bool haveEnd = 0;         // Переменная, говорящая, закончили ли мы искать место для нового значения

	// Пока не закончим искать место для value, выполняем действия:
	while(!haveEnd){

		// Если число меньше значения данной би-вершины, то смотрим левого потомка
		if (value < biVertex->value){

			// Если левого потомка нет, то...
			if(biVertex->leftChild == NULL){

				biVertex->leftChild = createBiVertex(); // ...создаем левого потомка
				biVertex->leftChild->value = value;     // присваиваем его значению value
				haveEnd = 1;                            // и говорим, что мы закончили добавление числа

			}

			// Иначе перейдем к левому потомку
			else biVertex = biVertex->leftChild;

		}

		// Если число больше значения данной би-вершины, то смотрим правого потомка
		else if (value > biVertex->value){

			// Если правого потомка нет, то...
			if(biVertex->rightChild == NULL){

				biVertex->rightChild = createBiVertex(); // ...создаем правого потомка
				biVertex->rightChild->value = value;     // присваиваем его значению value
				haveEnd = 1;                             // и говорим, что мы закончили добавление числа

			}
			else biVertex = biVertex->rightChild;
		}

		// Если число равно значению в узле, то и вставлять его не нужно
		else haveEnd = 1;

	};

	calcHeights(root); // пересчитаем высоты
	
	return 0;

};

//-------------//
// Поиск числа //
//-------------//
int checkValue(BiVertex *biVertex, int value){

	_Bool haveValue	= 1;			   // Предположим, что данное число в дереве есть
	_Bool haveEnd = 0;                 // Переменная, говорящая, закончили ли мы искать место для нового значения

	// Пока не закончим искать место для value, выполняем действия:
	while(!haveEnd){

		// Если число меньше значения данной би-вершины, то смотрим левого потомка
		if (value < biVertex->value){

			// Если левого потомка нет, то...
			if(biVertex->leftChild == NULL){

				haveValue = 0; // числа в дереве нет
				haveEnd = 1;   // и говорим, что мы закончили проверку числа

			}

			// Иначе перейдем к левому потомку
			else biVertex = biVertex->leftChild;

		}

		// Если число больше значения данной би-вершины, то смотрим правого потомка
		else if (value > biVertex->value){

			// Если правого потомка нет, то...
			if(biVertex->rightChild == NULL){

				haveValue = 0; // числа в дереве нет
				haveEnd = 1;   // и говорим, что мы закончили проверку числа

			}
			else biVertex = biVertex->rightChild;
		}

		// Если число равно этому значению, значит мы его нашли
		else haveEnd = 1;

	};
	
	return haveValue;

};

//----------------//
// Удаление числа //
//----------------//
int deleteValue(BiVertex *biVertex, int value){

	BiVertex *root = biVertex;     // Запомним корневую вершину
	BiVertex *parent = biVertex;   // Создаем указатель на родителя, потомка которого удалим
	_Bool haveValue	= 1;		   // Предположим, что данное число в дереве есть
	_Bool haveEnd = 0;             // Переменная, говорящая, закончили ли мы искать место для нового значения

	// Пока не закончим искать место для value, выполняем действия:
	while(!haveEnd){

		// Если число меньше значения данной би-вершины, то смотрим левого потомка
		if (value < biVertex->value){

			// Если левого потомка нет, то...
			if(biVertex->leftChild == NULL){

				haveValue = 0; // числа в дереве нет
				haveEnd = 1;   // и говорим, что мы закончили проверку числа

			}

			// Иначе перейдем к левому потомку, запомнив его родителя
			else{
				parent = biVertex;
				biVertex = biVertex->leftChild;
			};

		}

		// Если число больше значения данной би-вершины, то смотрим правого потомка
		else if (value > biVertex->value){

			// Если правого потомка нет, то...
			if(biVertex->rightChild == NULL){

				haveValue = 0; // числа в дереве нет
				haveEnd = 1;   // и говорим, что мы закончили проверку числа

			}

			// Иначе перейдем к левому потомку, запомнив его родителя
			else{
				parent = biVertex;
				biVertex = biVertex->rightChild;
			};
		}

		// Если число равно этому значению, значит мы его нашли
		else haveEnd = 1;

	};

	// Если число есть, то выполним следующие действия:
	if(haveValue){

		_Bool canDelete = 0; // Пока удалять не можем

		while(!canDelete){

			canDelete = 1; // Предположим, что удалить мы можем

			if(biVertex->leftChild != NULL && biVertex->rightChild != NULL){

				canDelete = 0; // Все-таки удалить мы не можем, так как у нашей вершины есть 2 потомка
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
// Полный пересчет высот //
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
// Быстрый пересчет высот //
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
// Поворот влево вокруг би-вершины //
//---------------------------------//
BiVertex* rotateLeft (BiVertex *biVertex){

	BiVertex *tmp = biVertex->rightChild;
	biVertex->rightChild = tmp->leftChild;
	tmp->leftChild = biVertex;
	return tmp;

};

//----------------------------------//
// Поворот вправо вокруг би-вершины //
//----------------------------------//
BiVertex* rotateRight (BiVertex *biVertex){

	BiVertex *tmp = biVertex->leftChild;
	biVertex->leftChild = tmp->rightChild;
	tmp->rightChild = biVertex;
	return tmp;

};

//-------------------------//
// Балансировка би-вершины //
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
// Обход поддерева би-вершины //
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
