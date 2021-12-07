#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <sys/param.h>

#define DEBUG 0
#define MAP_SIZE (DEBUG ? 10: 1000)
typedef struct{
	int x;
	int y;
}coord2_t;
static int map[MAP_SIZE][MAP_SIZE];

int getDangerousZoneAmount(){
	int res = 0;
	for(int i=0;i<MAP_SIZE;i++){
		for(int j=0;j<MAP_SIZE;j++){
			if(map[i][j]>1)
				res++;
		}
	}
	return res;
}

void showMap(){
	for(int i=0;i<MAP_SIZE;i++){
		for(int j=0;j<MAP_SIZE;j++){
			printf("%c", map[i][j] > 0 ? map[i][j]+48:'.');
		}
		printf("\n");
	}
}
void computeOrthogonalPath(coord2_t src, coord2_t dst){
	if(src.x == dst.x){
		for(int i=MIN(dst.y, src.y);i <= MAX(dst.y, src.y);i++){
			map[i][src.x] += 1;
		}
	}
	else if(src.y == dst.y){
		for(int i=MIN(dst.x, src.x);i <= MAX(dst.x, src.x);i++){
			map[src.y][i] += 1;
		}
	}
}
void computeDiagonalPath(coord2_t src, coord2_t dst){
	if (!(abs(src.x-dst.x)-abs(src.y-dst.y)==0)){ //operate only for 45° diagonals
		return;
	}
		const signed xSide = (src.x < dst.x)? 1: -1;
		const signed ySide = (src.y < dst.y)? 1: -1;
		for(int i=0;i <= abs(src.y-dst.y);i++){
			map[src.y+(i*ySide)][src.x+(i*xSide)] += 1;
		}
}
int main(){
	memset(map, 0, sizeof(int) * MAP_SIZE * MAP_SIZE);
	FILE* fp = fopen( DEBUG ? "miniset" : "input","r");
	if(NULL == fp)
		return -1;
	coord2_t src;
	coord2_t dst;
	while(EOF != fscanf(fp, "%d,%d%*s%d,%d", &src.x, &src.y, &dst.x, &dst.y)){
		//printf("%d,%d -> %d,%d\n", src.x, src.y, dst.x, dst.y);
		computeOrthogonalPath(src, dst);
		computeDiagonalPath(src, dst);
	}
#if DEBUG
	showMap(); //do not use with large set!
#endif
	printf("#1: dangerous zone amount: %d\n",getDangerousZoneAmount());
	fclose(fp);
	return 0;
}
