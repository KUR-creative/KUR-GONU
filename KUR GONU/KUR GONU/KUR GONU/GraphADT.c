/**********************************************************
 *그래프 추상 데이터 타입 Graph ADT 
 *
 * adjIdArr와 dataArr는 상수로 선언해야하며 배열을 이용하여 그래프를 한번에 만들때만 사용된다. 
 * 인접행렬을 입력하면 연결리스트 그래프로 만드는 함수는 지원하지 않음.
 * traversal에 관한 함수는 아직 지원하지 않음. 
 *
 *만든놈 : KUR	
 * https://www.facebook.com/KURcreative
 * kur941017@gmail.com
 *
 *********************************************************/

#include "GraphADT.h"

/******************************main의 코드는 사용 예시이다.***************************************** 
int main(){
	

	Graph graph0;
	const Data dataArr0[] = {100, 101, 102, 103, 104, NULL_DATA};
	//정점이 가지는 data를 나열한다. (ID == 인덱스)
	const int IdArr0[VERTEX_NUM_MAX][ADJACENT_NUM_MAX] = 
	//행의 index는 정점의 ID를 의미한다. [ID][]
	//각 행에는 그 ID가 가지는 인접한 정점들의 ID를 나열한다.
	//배열의 끝은 NULL_ID로 표시한다.
	//(edge 가 없는 vertex는 {}를 이용한 초기화로는 생성 불가)
	{
		{1,2,3, NULL_ID},
		{0, NULL_ID},
		{0,4, NULL_ID},
		{0, NULL_ID},
		{2, NULL_ID},
		{NULL_ID},
	};

	graph0 = createGraphByIdArr(IdArr0, dataArr0);
	
	return 0;
}
***********************************************************************************/


//----------------------------------------------------------Graph ADT functions------------------------------------------------------------------------

//adjIdArr와 dataArr에 따라 그래프를 생성한다.
Graph createGraphByIdArr( const int adjIdArr[][ADJACENT_NUM_MAX], const Data dataArr[] )
{
	int id;	 //id는 계수기역할을 하고 adjIdArr,dataArr의 인덱스이면서 동시에 Vertex들의 ID이다.
	Graph graph = { 0, {NULL} };
	int numV = 0;

	id = 0;
	while( adjIdArr[id][0] != NULL_ID ){
		numV++;
		id++;
	}
	graph.numV = numV;

	for(id = 0; id < numV; id++){
		Vertex* phead = NULL;
		
		createLinkedList(id, &phead, adjIdArr[id], dataArr);
		graph.vertices[id] = phead;
	}

	return graph;	
}

//새로운 Vertex를 graph에 추가하고 1을 반환.
//수동삽입 : 기존의 Vertex를 graph에 추가한다. 
//			만일 ID가 기존의 ID와 겹친다면 0을 반환한다.
//자동삽입 : 만일 vertex에 NULL을 대입하면
//		1)새로 Vertex를 만든다.
//		2)graph.vertices에서 NULL포인터를 갖는 인덱스값 중 최소값minNullId을  
//			새로 만들어진 Vertex의 ID로 할당하고
//			graph.vertices[minNullId]는 새로 만든 Vertex를 가리킨다.
//		3)Vertex의 data와 간선은 설정하지 않는다(data = NULL_DATA, link = NULL)
int insertNewVertex(Graph* graph, Vertex* vertex)
{
	int i;
	
	if(vertex){//수동
		int newVertexID = vertex->IDnum;

		for(i = 0; i < graph->numV; i++){
			if(newVertexID == graph->vertices[i]->IDnum){	//새로 만드는 정점의 ID == 기존의 정점 ID 라면
				printf("ERROR:	기존의 ID와 겹치는 정점입니다. 추가되지 않습니다. \n");
				return 0;
			}
		}

		graph->vertices[newVertexID] = vertex;
		(graph->numV)++;
		
		return 1;

	}else{//자동
		int minNullId;//graph.vertices에서 NULL포인터를 갖는 인덱스값 중 최소값
		Vertex* newVertex = NULL;

		minNullId = 0;
		while( graph->vertices[minNullId] != NULL ){
			minNullId++;
		}

		newVertex = allocVertexById(minNullId, NULL_DATA);

		graph->vertices[minNullId] = newVertex;
		(graph->numV)++;

		return 1;
	}
}

//for undirected graph: create (a , b) ---> automatically create (b , a)
void insertNewEdge(Graph* graph, int ID1, int ID2, const Data dataArr[])
{
	Vertex* vertex1 = graph->vertices[ID1];
	Vertex* vertex2 = graph->vertices[ID2];

	if( vertex1  &&  vertex2 ){//ID1, ID2의 정점이 둘 다 NULL이 아니면
		Vertex* prev = NULL;
		Vertex* traveler = NULL;
		
		//ID1->ID2
		traveler = vertex1;
		while( traveler->IDnum != vertex2->IDnum  &&  traveler->link != NULL ){
			//연결리스트 안에 D2정점이 있다면 검색 그만.
			//검색하는놈의 ID와 목표하는 놈 ID가 다름 && 연결리스트가 끝나지 않으면: 계속검색
			prev = traveler;								
			traveler = traveler->link;
		}
		if( (traveler->IDnum == vertex2->IDnum) ){
			//연결리스트 안에 D2정점이 이미 있음.
																		//printf("ERROR:	edge (%d, %d)는 이미 존재합니다. \n", ID1, ID2);	
			return;
		}else{
			//정말로 두 정점 사이의 간선이 없는 상태
			Vertex* newNode = allocVertexById( ID2, dataArr[ID2] );
			
			prev = traveler;
			insertListNode( &(prev->link) , newNode);
		}

		//ID2->ID1
		traveler = vertex2;
		while( traveler->link != NULL ){
			if(traveler->IDnum == vertex1->IDnum){
				break;
			}
			prev = traveler;
			traveler = traveler->link;
		}

		{
		Vertex* newNode = allocVertexById( ID1, dataArr[ID1] );

		prev = traveler;
		insertListNode( &(prev->link), newNode );
		}

	}else{
																		printf("ERROR:	vertex ID:%d or ID:%d has not existed in this graph.\n", ID1, ID2);
		return;
	}
}

//for undirected graph. delete ALL adjacent edges and then delete vertex.
void deleteVertex(Graph* graph, int ID)
{
	Vertex* thisVertex = graph->vertices[ID];
	Vertex* adjVertex;

	//delete edge
	adjVertex = thisVertex->link;//ID정점에 연결되있는 첫번째 간선을 가리킴.
	while(adjVertex != NULL){
		deleteEdge(graph, ID, adjVertex->IDnum);						
		adjVertex = thisVertex->link;
	}																	

	//delete vertex
	deleteListNode(  &( thisVertex ), graph->vertices[ID]  );

	graph->vertices[ID] = NULL;
	(graph->numV)--;
}

//for undirected graph: delete (a , b) ---> automatically delete (b , a)
void deleteEdge(Graph* graph, int ID1, int ID2)
{
	Vertex* vertex1 = graph->vertices[ID1];
	Vertex* vertex2 = graph->vertices[ID2];

	if( vertex1  &&  vertex2 ){//ID1, ID2의 정점이 둘 다 존재한다면:
		Vertex* prev = NULL;
		Vertex* traveler = NULL;
		
		//ID1->ID2
		traveler = vertex1;
		while( traveler->IDnum != vertex2->IDnum  &&  traveler->link != NULL ){
			//연결리스트 안에 D2정점이 있다면 검색 그만.
			//현재 검사하는 ID와 목표하는 놈의 ID가 다름 && 연결리스트가 끝나지 않으면: 계속검색

			prev = traveler;								
			traveler = traveler->link;
		}
		
		if(	traveler->link == NULL  &&  traveler->IDnum != vertex2->IDnum){
			//연결리스트 안에 D2정점이 없음:
			//연결리스트가 끝남 && 현재 검사하는 ID와 목표하는 놈의 ID가 다름 : 
				printf("ERROR:	edge (%d, %d)는 존재하지 않습니다. \n", ID1, ID2);	
				return;
			}
		
		deleteListNode( &(prev->link) ,traveler );
		
		//ID2->ID1
		traveler = vertex2;
		while( traveler->link != NULL ){
			if(traveler->IDnum == vertex1->IDnum){
				break;
			}
			prev = traveler;
			traveler = traveler->link;
		}

		deleteListNode(&(prev->link) ,traveler);

	}else{
		printf("ERROR:	vertex ID:%d or ID:%d has not existed in this graph.\n", ID1, ID2);
		return;
	}
}

//search UNDELETED vertex from [0] and delete ALL of it in graph!
//for UNDIRECTED graph
//from max는 안만들어 귀찮아. 변태냐 뒤에서부터 채우게?
void clearGraphFromZero(Graph* graph)
{
	int i, count = 0;
	int numV = graph->numV;
	
	for(i = 0; i < VERTEX_NUM_MAX; i++){
		
		if(numV == count)	break;

		if( graph->vertices[i] != 0){
			deleteVertex(graph, i);
			graph->vertices[i] = NULL;
			count++;
		}else{
			continue;
		}
	}
}

//유향그래프의 arc간선(ID1, ID2)를 추가한다. 
void insertNewArc(Graph* graph, int ID1, int ID2, const Data dataArr[])
{
	Vertex* vertex1 = graph->vertices[ID1];
	Vertex* vertex2 = graph->vertices[ID2];

	if( vertex1  &&  vertex2 ){//ID1, ID2의 정점이 둘 다 NULL이 아니면
		Vertex* prev = NULL;
		Vertex* traveler = NULL;
		
		traveler = vertex1;
		while( traveler->IDnum != vertex2->IDnum  &&  traveler->link != NULL ){
			//연결리스트 안에 D2정점이 있다면 검색 그만.
			//검색하는놈의 ID와 목표하는 놈 ID가 다름 && 연결리스트가 끝나지 않으면: 계속검색
			prev = traveler;								
			traveler = traveler->link;
		}

		if( (traveler->IDnum == vertex2->IDnum) ){
			//연결리스트 안에 D2정점이 이미 있음.
			printf("ERROR:	edge (%d, %d)는 이미 존재합니다. \n", ID1, ID2);	
			return;
		}else{
			//정말로 두 정점 사이의 간선이 없는 상태
			Vertex* newNode = allocVertexById( ID2, dataArr[ID2] );
			
			prev = traveler;
			insertListNode( &(prev->link) , newNode);
		}

	}else{
		printf("ERROR:	vertex ID:%d or ID:%d has not existed in this digraph.\n", ID1, ID2);
		return;
	}
}

/*미안하지만, 귀찮아서 안 만들란다. 애초에 menuFSM은 런타임에 삭제할 가능성이 없는 방향그래프니까. 

//search UNDELETED vertex from [0] and delete ALL of it in graph!
//for Digraph
//from max는 안만들어 귀찮아. 변태냐 뒤에서부터 채우게?
void clearDigraphFromZero(Graph* graph)
{
	int i, count = 0;
	int numV = graph->numV;
	
	for(i = 0; i < VERTEX_NUM_MAX; i++){//--------------------------------------------------------------------------
		
		if(numV == count)	break;

		if( graph->vertices[i] != 0){
			deleteVertex(graph, i);
			count++;
		}else{
			continue;
		}
	}
}

//유향 그래프를 위한 아크 삭제함수
void deleteArc(Graph* graph, int ID1, int ID2)
{
	Vertex* vertex1 = graph->vertices[ID1];
	Vertex* vertex2 = graph->vertices[ID2];

	if( vertex1  &&  vertex2 ){//ID1, ID2의 정점이 둘 다 존재한다면:
		Vertex* prev = NULL;
		Vertex* traveler = NULL;
		
		//ID1->ID2
		traveler = vertex1;
		while( traveler->IDnum != vertex2->IDnum  &&  traveler->link != NULL ){//--------------------------------------------------------------------------
			//연결리스트 안에 D2정점이 있다면 검색 그만.
			//현재 검사하는 ID와 목표하는 놈의 ID가 다름 && 연결리스트가 끝나지 않으면: 계속검색

			prev = traveler;								
			traveler = traveler->link;
		}
		
		if(	traveler->link == NULL  &&  traveler->IDnum != vertex2->IDnum){
			//연결리스트 안에 D2정점이 없음:
			//연결리스트가 끝남 && 현재 검사하는 ID와 목표하는 놈의 ID가 다름 : 
				printf("ERROR:	edge (%d, %d)는 존재하지 않습니다. \n", ID1, ID2);	
				return;
			}
		
		deleteListNode( &(prev->link) ,traveler );
		
		//ID2->ID1
		traveler = vertex2;
		while( traveler->link != NULL ){
			if(traveler->IDnum == vertex1->IDnum){
				break;
			}
			prev = traveler;
			traveler = traveler->link;
		}

		deleteListNode(&(prev->link) ,traveler);

	}else{
		printf("ERROR:	vertex ID:%d or ID:%d has not existed in this graph.\n", ID1, ID2);
		return;
	}
}
*/

//유틸리티 함수
Vertex* getVertex(Graph* graph, int ID)
{
	return graph->vertices[ID] ;
}


//------------------------------------------Vertex functions(Vertex as LinkedList node)----------------------------------

//그래프는 vertex로 이뤄진 연결리스트의 헤드포인터들이 나열된 배열vertices을 가진다.
//phead는 새로 만든 연결리스트의 헤드포인터. 헤드포인터들이 나열된 배열 vertices에 들어간다.
//vertexId와 dataArr를 이용하여 데이터를 저장한다.
void createLinkedList(int vertexId, Vertex** phead, const int adjIdRow[], const Data dataArr[])
{
	int i;
	Vertex* prevNode = NULL;
	Vertex* thisNode = allocVertexById( vertexId, dataArr[vertexId] );	//시작정점.
	
	insertListNode( phead, thisNode );
	prevNode = thisNode;
	
	i = 0;
	while( adjIdRow[i] != NULL_ID){
		Vertex* nowNode = allocVertexById( adjIdRow[i], dataArr[ adjIdRow[i] ] );//시작정점에서 연결된 정점들. 

		insertListNode( &(prevNode->link), nowNode );
		prevNode = nowNode;

		i++;
	}			
}

//입력한 ID를 갖고 간선이 없는 vertex 하나를 생성하고 힙영역에 할당한다.
Vertex* allocVertexById(int IDnum, Data data)
{
	Vertex* vertex = (Vertex*)malloc(VERTEX_SIZE);
	if( vertex == NULL ){
		printf("ERROR:	memory leak error!");
		exit(1);
	}

	vertex->IDnum = IDnum;
	vertex->link = NULL;
	vertex->data = data;

	return vertex;
}

//link a new Vertex to prev 
void insertListNode(Vertex** prev, Vertex* newNode)	//prev는 &(헤드포인터) 혹은 &(새로운 Vertex를 붙일 Vertx->link)
{
	newNode->link = *prev;
	*prev = newNode;
}

//prev와 removed의 연결을 끊고 removed의 메모리를 해제한다.
void deleteListNode(Vertex** prevPtr, Vertex* removed)//prev는 &(헤드포인터) 혹은 &(기존의 Vertex를 삭제할 Vertx->link)
{
	*prevPtr = removed->link;
	free(removed);
}


//유틸리티 함수 : 연결리스트에서 노드의 데이터가 NULL이 나올 때까지 순차검색하며 출력
void printListNodeAll(Vertex* phead)
{
	Vertex* traveler = phead;
	while(traveler != NULL){
		printf("%d \t", traveler->IDnum);
		traveler = traveler->link;
	}
	printf("\n");
}

//연결리스트 안에 ID를 가진 node가 있으면 1을 반환
//없으면 0을 반환
int hasNodeById(Vertex* phead, int ID)
{

	Vertex* traveler = phead;
	while(traveler != NULL){
		if(traveler->IDnum == ID){
			return 1;
		}

		traveler = traveler->link;
	}

	return 0;
}

