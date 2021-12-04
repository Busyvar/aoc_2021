#!/bin/tcc -run
#include <stdio.h>
#define BIT_WIDTH 12
#define ENTRIES 1000

int main(){
	FILE *fp = fopen("input","r");
	int diag[BIT_WIDTH] = {0,};
	int gamma=0;
	int epsilonn=0;
	int vals[ENTRIES];
	if(NULL == fp)
		return -1;
	char binVal[BIT_WIDTH+1];
	int entryIndex = 0;
	while(EOF != fscanf(fp, "%s", binVal)){
		for(int i=0;i<BIT_WIDTH;i++){
			diag[i] += binVal[i]-48;
			vals[entryIndex] += (binVal[i]-48) << (BIT_WIDTH-1-i);
		}
		entryIndex++;
	};
	for(int i=0; i<ENTRIES;i++){
		printf("entry %d : %d\n",i, vals[i]);
		
	}
	for(int i=BIT_WIDTH-1;i>=0;i--){
		printf("%d/%d\n",diag[i], ENTRIES);
		gamma 	 |= (diag[BIT_WIDTH-1-i] > (ENTRIES>>1)) << i;
		epsilonn |= (diag[BIT_WIDTH-1-i] < (ENTRIES>>1)) << i;
	}
	fclose(fp);
	printf("1rst gamma %d *  epsilonn %d = %d\n", gamma, epsilonn, gamma*epsilonn);
	return 0;
}
