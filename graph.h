#pragma once
#include <stdio.h>

/////////////////////////////////////////////////////////////////
//                                                             //
//                            ����                             //
//                                                             //
/////////////////////////////////////////////////////////////////

//-------------------------//
// ��������� ������� ����� //
//-------------------------//
typedef struct GraphVertex_tag{
	
	struct GraphVertex_tag **connect;
	int degree;
	int internal;

} GraphVertex;

//-----------------//
// ��������� ����� //
//-----------------//
typedef struct Graph_tag{
	
	GraphVertex **gVertexes;
	int size;

} Graph;

//------------------------//
// ������� �������� ����� //
//------------------------//
Graph createGraph(){
	
	Graph graph;
	graph.gVertexes = NULL;
	graph.size = 0;
	return graph;

};

//--------------------------------//
// ������� �������� ������� ����� //
//--------------------------------//
GraphVertex* createGraphVertex(){

	//������� ��������� �� ����� ������� �����, ������� ��� ��� ������ 
	GraphVertex *gVertex = malloc(sizeof(GraphVertex));

	//�������� �� �������� ���������� (��� ��� ������� ����� �� ����������� �� � ������ �������)
	gVertex->degree = 0;
	gVertex->internal = 0;
	gVertex->connect = NULL;

	return gVertex;

};

//----------------------------//
// ������� ���������� ������� //
//----------------------------//
int addGraphVertex(Graph *graph){
	
	if(graph->gVertexes == NULL) graph->gVertexes = malloc(sizeof(GraphVertex*));
	else graph->gVertexes = realloc(graph->gVertexes, (graph->size + 1) * sizeof(GraphVertex*));

	graph->gVertexes[graph->size] = createGraphVertex();
	graph->size++;
	return 0;

};

//--------------------------//
// ������� ���������� ����� //
//--------------------------//
int addEdge(GraphVertex *gVertex1, GraphVertex *gVertex2){
	
	gVertex1->connect = realloc(gVertex1->connect, (gVertex1->degree + 1) * sizeof(GraphVertex*));
	gVertex1->connect[gVertex1->degree] = gVertex2;
	gVertex1->degree++;
	return 0;

};

//--------------------------------------------------------------------------//
// �������� ������� ������� � ������ ����� (� ������ ������� ���������� -1) //
//--------------------------------------------------------------------------//
int checkGraphVertex(Graph *graph, GraphVertex *gVertex){
	
	int i = 0;
	while(i < graph->size && graph->gVertexes[i] != gVertex) i++;

	if(i == graph->size) return -1; // ���� � ������� graph->gVertexes ��� gVertex, ������ ����� ������� ���
	else return i; 				    // � ��������� ������ ������ ����� ����������

};

//---------------------------------------------------------//
// �������� ������� ����� (� ������ ������� ���������� -1) //
//---------------------------------------------------------//
int checkEdge(GraphVertex *gVertex1, GraphVertex *gVertex2){
	
	int i = 0;
	while(i < gVertex1->degree && gVertex1->connect[i] != gVertex2) i++;

	if(i == gVertex1->degree) return -1; // ���� �� ���� ���������� gVertex1->connect �� ��������� �� gVertex2, ������ ������ ����� ���
	else return i; 					     // � ��������� ������ ������ ����� ���������� � gVertex1

};

//--------------------------------------------------------------------------------//
// ������� �������� ����� (���������� 1 - � ������ ������ � 0 - � ������ �������) //
//--------------------------------------------------------------------------------//
int deleteEdge(GraphVertex *gVertex1, GraphVertex *gVertex2){
	
	int num = checkEdge(gVertex1, gVertex2);

	// ���� ����� ����� ����, �� ������ ��� � ������� ������ ���������� �����
	if(num >=0 ){
		for(int i = num; i < gVertex1->degree - 1; i++) gVertex1->connect[i] = gVertex1->connect[i + 1];
		gVertex1->connect = realloc(gVertex1->connect, (gVertex1->degree - 1) * sizeof(GraphVertex*));
		gVertex1->degree--;
	}

	// ����� ������ 0
	else return 0;

};

//--------------------------//
// ������� �������� ������� //
//--------------------------//
int deleteGraphVertex(Graph *graph, GraphVertex *gVertex){
	
	int num = checkGraphVertex(graph, gVertex);

	// ���� ����� ������� ����, ��...
	if(num >= 0){

		// ������ ��� ����� � ���
		for(int i = 0; i < graph->size; i++) deleteEdge(graph->gVertexes[i], gVertex);

		// � ����� ������ ��� � ������� ������ ���������� �����
		for(int i = num; i < graph->size - 1; i++) graph->gVertexes[i] = graph->gVertexes[i + 1];
		graph->gVertexes = realloc(graph->gVertexes, (graph->size - 1) * sizeof(GraphVertex*));
		graph->size--;
	}

	// ����� ������ 0
	else return 0;

};

//-------------------------------------------------//
// ����� ����������� ���� ����� ��������� � ������ //
//-------------------------------------------------//
int broadSearch(Graph *graph, GraphVertex *gVertex1, GraphVertex *gVertex2){
	
	int s = 0;
	GraphVertex **gVertexes, **newGVertexes = NULL;
	gVertexes = malloc(sizeof(GraphVertex*));
	newGVertexes = malloc(sizeof(GraphVertex*));
	gVertexes[0] = gVertex1;
	int size = 1;
	int newSize = 0;
	int haveRoute = 2; // ��������� �����

	while(haveRoute == 2){

		haveRoute = 0;
		newSize = 0;

		for (int i = 0; i < size && haveRoute != 1; i++){

			haveRoute = 2;

			for (int j = 0; j < gVertexes[i]->degree; j++){

				if(gVertexes[i]->connect[j] == gVertex2) haveRoute = 1; 
				else if(gVertexes[i]->connect[j]->internal == 0){

					newGVertexes = realloc(newGVertexes, (newSize + 1) * sizeof(GraphVertex*));

					newGVertexes[newSize] = gVertexes[i]->connect[j];
					newGVertexes[newSize]->internal = 1;
					newSize++;

				};
			};
		};

		gVertexes = newGVertexes;
		size = newSize;
		s++;
 
	};

	for (int i = 0; i < graph->size; i++) graph->gVertexes[i]->internal = 0;

	if(haveRoute) return s;
	else return -1;

};

//------------------------------------------//
// ����������� ������� ��� ������ � ������� //
//------------------------------------------//
int depthSearchForVertex(GraphVertex *gVertex1, GraphVertex *gVertex2){

	int s = -1, newS; //5
	gVertex1->internal = 1;

	for (int i = 0; i < gVertex1->degree; i++){

		if(gVertex1->connect[i] == gVertex2) s = 0;
		else if(gVertex1->connect[i]->internal == 0){

			newS = depthSearchForVertex(gVertex1->connect[i], gVertex2);
			if((newS < s || s == -1) && newS != -1) s = newS;

		};

	};

	gVertex1->internal = 0;

	if(s == -1) return -1;
	else return s + 1;
};

//--------------------------------------------------//
// ����� ����������� ���� ����� ��������� � ������� //
//--------------------------------------------------//
int depthSearch(Graph *graph, GraphVertex *gVertex1, GraphVertex *gVertex2){
	
	int s = depthSearchForVertex(gVertex1, gVertex2);
	return s;

};
