/***************************************************
 *고누 게임 맵 생성용 파일 입력 함수들.
 *
 * 1.오직 KUR GONU만을 위한 파일형 .gonu를 지원하는파일 로드함수
 * 2.char형 수를 int로 바꿔주는 함수( 유용함! )
 * 3.파일에 적힌 char형 숫자를 int로 바꾸면서 파일 포인터를 옮기는 함수( 유용함2! )
 *
 *만든놈 : KUR 
 * https://www.facebook.com/KURcreative
 * kur941017@gmail.com
 *
 *********************************************/

#include "GameData.h"
#include "MenuAndUI.h"

// 파일을 읽어 게임을 로드하는 함수
short loadDataFile( char fileName[] )
	// 실패하면 0반환
{
	FILE* dataFile;
	int count = 0;
	int i;
	char vertexDataStruct, _mode; //정점 데이터의 저장법 체크: L / M , 게임모드: N / F
	char temp;

	int castleCountP1 = 0, castleCountP2 = 0;

	dataFile = fopen(fileName, "rt");// 이름, 즉 문자열을 넣는 방법.
	if(dataFile == NULL){
		puts("파일 열기 에러!");
		return 0;
	}

	// Vertex : mapGraph의 정점에 값 채워넣기.
	fscanf(dataFile, "%d", &count);	// 원소 수(최대값)
	for(i = 0; i < count; i++){
		Vertex* vertex = NULL;
		Crossing* crossing = (Crossing*)malloc( sizeof(Crossing) );
		
		if(crossing == NULL){
			puts("memory leak 에러 : 교차점 메모리 할당 실패!");
			fclose(dataFile);
			exit(1);
		}

		//파일의 값들을 변수들에 넣는다.
		crossing->IDnum = i;
		fscanf(dataFile, "%d %d %c %d %d %d %d %p", &crossing->point.x , &crossing->point.y, &crossing->crossingType, &crossing->enterable.p1, &crossing->enterable.p2, &crossing->txtColor.txt, &crossing->txtColor.back, &crossing->occupier);
		vertex = allocVertexById( i, (Data)crossing );// 즉 주소값을 int 로 변환(?아무것도 안하는거임 ㅋ)시켜 넣는다.

		if(		crossing->point.x > LOG_SCREEN_X - 1  
			||  crossing->point.y > CONSOLE_HEIGHT_NUM - 1
			||	crossing->point.x < 0  
			||	crossing->point.y < 0){
				puts("올바른 .gonu형식 파일이 아닙니다. 교차점의 좌표가 범위를 벗어납니다.");
				fclose(dataFile);
				return 0;
		}

		//각 플레이어들의 성을 등록시킨다.
		if( crossing->enterable.p1 == 0  &&  crossing->enterable.p2 == 1 ){
			//crossing은 1p의 성
			castlesP1[ castleCountP1 ] = crossing;
			castleCountP1++;
		}
		else if( crossing->enterable.p1 == 1  &&  crossing->enterable.p2 == 0 ){
			//crossing은 2p의 성
			castlesP2[ castleCountP2 ] = crossing;
			castleCountP2++;
		}

		insertNewVertex( &mapGraph, vertex );
	}

	// Edge : 간선 정보를 저장 형식에 따라 처리한다.
	fgetc(dataFile);			// '\n' 받고
	vertexDataStruct = fgetc(dataFile);	// 저장형식 체크 L:adjacency index list
	if(vertexDataStruct == 'L'){
		int id;				// 현재 읽고 있는 정점의 ID
		
		//mapGraph의 dataArr초기화. 
		for(id = 0; id < count; id++){
			mapCrossingArr[id] = (Crossing*)mapGraph.vertices[id]->data;
		}
		
		fgetc(dataFile);// '\n'을 가리키고 있는 dataFile->_ptr을 한 칸 옮겨 다음 값을 가리키게 한다.

		//mapGraph의 edge들 추가.
		id = 0;
		while( id < count ){
			int adjEdgeId = readNumAndMoveFilePtr(&dataFile->_ptr);
			insertNewEdge(&mapGraph, id, adjEdgeId, (const Data*)mapCrossingArr);
			
			if( *(dataFile->_ptr) == '\t' ){
				(dataFile->_ptr)++;//파일에서는 아직 같은 행이다.
			}
			else if( *(dataFile->_ptr) == '\n' ){
				(dataFile->_ptr)++;
				id++;//다음 행으로 넘어간다.
			}
			else{
				puts("올바른 .gonu형식 파일이 아닙니다. 인접 인덱스 리스트를 양수, 탭\'\\t\', 줄바꿈\'\\n\'만 쓰도록 수정하시오.");
				fclose(dataFile);
				return 0;
			}
		}
	}else if(vertexDataStruct == 'M'){
		puts("인접행렬은 아직 지원하지 않습니다");
		_getch();
		fclose(dataFile);
		return 0;
	}else{
		puts("올바른 .gonu형식 파일이 아닙니다. 파일 형식에서 문제가 될 수 있는 것은 다음과 같습니다. \
			 \n 1. 간선정보 저장형식 설정문자(L)가 L이 아닙니다. \
			 \n 2. 파일의 첫번째 숫자는 맵의 정점수를 결정합니다. 이 수가 맵의 실제 정점 수와 다를 수 있습니다.");
		_getch();
		fclose(dataFile);
		return 0;
	}	

	//말piece 초기값 관련
	_mode = fgetc(dataFile);
	if( _mode == 'N' ){
		int pieceNumP1, pieceNumP2;
		int tempPieceId;

		//1p 초기값 적재, 1p 관련 변수 초기화
		fscanf(dataFile, "%d", &pieceNumP1);
		for(tempPieceId = 0; tempPieceId < pieceNumP1; tempPieceId++){
			int initOccupyingId;	//
			Piece* piece = (Piece*)malloc( sizeof(Piece) );

			//1p 말 관련 변수 초기화
			piece->pieceId = tempPieceId;
			fscanf(dataFile, "%d %d %d %d %d", &initOccupyingId, &piece->txtColor.txt, &piece->txtColor.back, &piece->range, &piece->stackable);
			piece->player = 1;
			piece->occupying = mapGraph.vertices[ initOccupyingId ];
			
			if( initOccupyingId > count ){
				puts("올바른 .gonu형식 파일이 아닙니다. 맵에 존재하지 않는 정점에 말이 있을 수 없습니다. \
					\n말 정보 중 pieceId를 저장하는 숫자를 수정하십시오");
				_getch();
				fclose(dataFile);
				return 0;
			}

		//기타 1p 관련 변수 초기화
		piecesP1[ tempPieceId ] = piece;
		}
		restP1 = pieceNumOriginP1 = pieceNumP1;				

		//2p 초기값 적재, 2p 관련 변수 초기화
		fscanf(dataFile, "%d", &pieceNumP2);
		for(tempPieceId = 0; tempPieceId < pieceNumP2; tempPieceId++){
			int initOccupyingId;
			Piece* piece = (Piece*)malloc( sizeof(Piece) );

			piece->pieceId = tempPieceId;
			fscanf(dataFile, "%d %d %d %d %d", &initOccupyingId, &piece->txtColor.txt, &piece->txtColor.back, &piece->range, &piece->stackable);
			piece->player = 2;
			piece->occupying = mapGraph.vertices[ initOccupyingId ];

			if( initOccupyingId > count ){
				puts("올바른 .gonu형식 파일이 아닙니다. 맵에 존재하지 않는 정점에 말이 있을 수 없습니다. \
					\n말 정보 중 pieceId를 저장하는 숫자를 수정하십시오");
				_getch();
				fclose(dataFile);
				return 0;
			}
			
		piecesP2[ tempPieceId ] = piece;
		}
		restP2 = pieceNumOriginP2 = pieceNumP2;
		

	}else if( _mode == 'F' ){
		int i;
		int indexP1, indexP2;

		
		fscanf( dataFile, "%d %d %d %d %d", &range1PieceNumMax, &range2PieceNumMax, &range3PieceNumMax, &range4PieceNumMax, &range5PieceNumMax );
		if( range1PieceNumMax +
			range2PieceNumMax +
			range3PieceNumMax +
			range4PieceNumMax +
			range5PieceNumMax  > 10){
						puts("올바른 .gonu형식 파일이 아닙니다. free deploy에 쓰일 말들이 너무 많습니다. F 다음 행의 숫자들의 합은 10 이하여야합니다.");
						_getch();
						fclose(dataFile);
						return 0;
		}
		

		mode = _MODE_F;
		
		i = 0;
		indexP1 = 0, indexP2 = 0;
		while( mapGraph.vertices[i] != NULL ){
			Crossing* crossing = (Crossing*)mapGraph.vertices[i]->data;

			if( crossing->crossingType == '*' ){//1p
				tempSetSpotsP1[indexP1] = mapGraph.vertices[i];
				indexP1++;
			}
			else if( crossing->crossingType == '+'){//2p
				tempSetSpotsP2[indexP2] = mapGraph.vertices[i];
				indexP2++;
			}

			i++;
		}

	}else{
		puts("올바른 .gonu형식 파일이 아닙니다. 파일 형식에서 문제가 될 수 있는 것은 다음과 같습니다. \
			\n 1. 모드 설정 문자(N/F)가 잘못되었습니다. \
			\n 2. 간선 정보를 저장하는 행의 수가 맵의 실제 정점 수(파일의 첫번째 수)보다 큽니다.");
		_getch();
		fclose(dataFile);
		return 0;
	}

	// 간선을 그릴 때 쓰는 char는 무엇인가?
	fgetc(dataFile);
	if(  ( temp = fgetc(dataFile) ) == 'e'  ){
		lineElement = '.';
		fclose(dataFile);
		return 1;
	}else{
		lineElement = temp;
		fclose(dataFile);
		return 1;
	}
}


int	charToInt(char ch)
{
	if(ch >= 48 && ch <= 57){
		return ch - 48;
	}else{
		printf("숫자로는 %d, 문자로는 %c ", ch, ch);
		puts("숫자 아스키 코드가 아닙니다. 숫자가 들어가야하는 곳에 다른 문자가 들어갔습니다.");
		puts("문자로 표현했을 때 공백이 나오면 인접 인덱스 리스트에서 tab이나 enter한번을 잘못 쳐 넣은 경우일 수 있습니다.");
		_getch();
		return -1;
	}
}

//char포인터 fptr를 연속된 수의 자릿수만큼 옮기면서 수를 int형으로 반환
//fptr에 파일 포인터를 넣어 사용.
// 1234\t  에서 fptr = &'1'으로 함수를 쓰면 fptr는 함수 반환 후엔 '\t'를 가리키게 된다.
int readNumAndMoveFilePtr(char** fptr)// 양수만 가능.
{
	int digit, result = 0;
	int i, count = 0, returnValue = 0;

	digit = 1;
	do{
		result += digit * charToInt(**fptr);
		digit *= 10;
		*fptr += 1;
		count++;
	}while( **fptr != '\t' && **fptr != '\n' );
	
	digit /= 10;	// digit의 자릿수는 result의 자릿수*10이다.
	for(i = 1; i <= count; i++){
		returnValue += (result % 10) * digit;
		result /= 10;
		digit /= 10;
	}
	return returnValue;
}


