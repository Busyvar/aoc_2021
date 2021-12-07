//#!/bin/tcc -run
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ENTRIES 1000

typedef struct{
	int rank;
	int id;
	int values[5][5];
	int crossed[5][5];
	int sequence[5];
}grid_t;
typedef struct{ 
	grid_t* winner[100];
}winResult_t;
static int m_currentRank=1;

winResult_t winnerFound(grid_t* boards, int cnt){
	winResult_t res;
	memset(res.winner, 0,  sizeof(grid_t*)*100 );
	int wIndex = 0;
	for(int i=0;i<cnt; i++){
		for(int j=0;j<5; j++){
			const int winCnt[5]= {1,1,1,1,1};
			//check rows
			if(boards[i].rank==0 && (0 == memcmp(winCnt,  boards[i].crossed[j], sizeof(int)*5))){
				res.winner[wIndex]= &boards[i];
				res.winner[wIndex]->rank = m_currentRank;
				m_currentRank++;
				memcpy(res.winner[wIndex]->sequence, boards[i].values[j], sizeof(int)*5);
				wIndex++;
				break;
			}
			//check cols
			if(boards[i].rank==0 &&
					boards[i].crossed[0][j] &&
					boards[i].crossed[1][j] &&
					boards[i].crossed[2][j] &&
					boards[i].crossed[3][j] &&
					boards[i].crossed[4][j]) {
				res.winner[wIndex]= &boards[i];
				res.winner[wIndex]->rank = m_currentRank;
				m_currentRank++;
				for(int r=0;r<5;r++)
					res.winner[wIndex]->sequence[r] = boards[i].values[r][j];
				wIndex++;
				break;
			}
		}
	}
	return res;
}
void showGrid(grid_t board){
	for(int i=0; i<5; i++){
		for(int j=0; j< 5; j++){
			printf("|%s%d%s\t%s", board.crossed[i][j]?"\033[7;31m":"", board.values[i][j],board.crossed[i][j]?"\033[0m":"", j==4? "|\n" : " ");
		}
	}
	printf("\t\t\t\t\t\n");
}
void update(grid_t* boards, int cnt, int tirage){
	for(int i=0;i<cnt; i++){
		for(int j=0;j<5; j++){
			for(int k=0;k<5; k++){
				if(boards[i].values[j][k] == tirage){
					boards[i].crossed[j][k] = 1;
				}
			}
		}
		//showGrid(boards[i]);
	}
}
const int getUnmarkedSum(grid_t* board){
	int sum= 0;
	for(int i=0;i<5; i++){
		for(int j=0;j<5; j++){
				if(board->crossed[i][j] == 0){
					sum += board->values[i][j];
				}
		}
	}
	return sum;
}
int main(){
	FILE *fp = fopen("input","r");
	if(NULL == fp)
		return -1;
	int tirage[MAX_ENTRIES];
	memset(tirage, -1, sizeof(int)*MAX_ENTRIES);
	{
		char line[MAX_ENTRIES];
		fgets(line, MAX_ENTRIES, fp);
		char *strToken = strtok(line,",");
		for(int i =0; strToken !=NULL; i++){
			tirage[i] = atoi(strToken);
			strToken = strtok(NULL,",");
		}
	}
	int bIndex = 0;
	grid_t *boards = malloc(sizeof(grid_t)*(bIndex+1));
	boards[0].id = 1;
	{
		int j=0;
		int id=2;
		int num=0;
		for(int i =0;EOF != fscanf(fp, "%d,", &num ); i++){
			if(i>4){
				i=0;
				j++;
			}
			if(j>4){
				j=0;
				bIndex++;
				boards = realloc(boards, sizeof(grid_t)* (bIndex+1));
				boards[bIndex].id=id;
				id++;
			}
			boards[bIndex].values[j][i]=num;
		};
	}
	for(int i = 0; tirage[i]!=-1; i++){
		update(boards, bIndex+1, tirage[i]);
		winResult_t wRes = winnerFound(boards, bIndex+1);
		if(wRes.winner[0] != 0){
			printf("bingo!\n");
			for(int w=0;wRes.winner[w]!=0;w++){
				const int lastNumber = tirage[i];
				const int unmarkedSum = getUnmarkedSum(wRes.winner[w]);
				char sSeq[100];
				sprintf(sSeq, "%d, %d, %d, %d, %d", 
						wRes.winner[w]->sequence[0],wRes.winner[w]->sequence[1],wRes.winner[w]->sequence[2],wRes.winner[w]->sequence[3], wRes.winner[w]->sequence[4]);
				printf("#%d : player %.2d \t-> score :%d x %d = %d \t-> sequence: %s\n", 
						wRes.winner[w]->rank, wRes.winner[w]->id,lastNumber, unmarkedSum, lastNumber*unmarkedSum, sSeq);

			}
		}
	}
	printf("end of game\n");
	free(boards);
	fclose(fp);
	return 0;
}
