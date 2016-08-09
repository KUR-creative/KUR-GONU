#ifndef _GRAPH_ADT_H_
#define _GRAPH_ADT_H_

#ifndef _INC_STDIO
# include <stdio.h>
#endif

#ifndef _INC_STDLIB
# include <stdlib.h>
#endif

#define VERTEX_NUM_MAX		80
#define ADJACENT_NUM_MAX	20	
#define NULL_ID				-1
//그래프 생성createGraphByIdArr시 필요한 
//인접정점의ID배열adjIdRow[]에서 배열의 끝을 나타낸다.
#define NULL_DATA			-1
// 그래프 생성createGraphByIdArr시 필요한 데이터배열 끝을 나타낸다.
//새 정점을 heap영역에 할당할 때 자동으로 들어가는 초기 data값이다.
#define VERTEX_SIZE			sizeof(Vertex)

typedef int Data;//주소를 쓸 경우 형변환을 해도 아무 변화도 없어 ㅋㅋ 주소값 걍 집어넣으면 된다.

//int가 아닌 다른 데이터를 써도 된다.

typedef struct Vertex{// 정점 하나를 의미하며 연결리스트를 이루는 구성원이다.
	int IDnum;	//정점을 식별하는 숫자이자 graph.vertices배열에서의 인덱스이다.
	Data data;
	struct Vertex* link;
} Vertex;

void createLinkedList(int vertexId, Vertex** phead, const int adjIdRow[], const Data dataArr[]);
Vertex* allocVertexById(int IDnum, Data data);
void insertListNode(Vertex** prevPtr, Vertex* newNode);
void deleteListNode(Vertex** prevPtr, Vertex* removed);
void printListNodeAll(Vertex* phead);

int hasNodeById(Vertex* phead, int ID);


typedef struct Graph{
	int numV;
	struct Vertex* vertices[VERTEX_NUM_MAX];// list of head pointers to each vertices.
} Graph;

Graph createGraphByIdArr( const int adjIdArr[][ADJACENT_NUM_MAX], const Data dataArr[] );
//adjIdArr에 따라 방향그래프도, 유향그래프도 만들 수 있다.
int insertNewVertex(Graph* graph, Vertex* vertex);
void insertNewEdge(Graph* graph, int ID1, int ID2, const Data dataArr[]);
void deleteVertex(Graph* graph, int ID);
void deleteEdge(Graph* graph, int ID1, int ID2);
void clearGraphFromZero(Graph* graph);					

void insertNewArc(Graph* graph, int ID1, int ID2, const Data dataArr[]);
//void deleteVertexDi(Graph* graph, int ID);
//void deleteArc(Graph* graph, int ID1, int ID2);
//void clearDigraphFromZero(Graph* graph);

Vertex* getVertex(Graph* graph, int ID);

#endif