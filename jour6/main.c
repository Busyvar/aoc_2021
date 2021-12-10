#!/bin/tcc -run
#include <stdio.h>
#define DEBUG 0
#define DAYS 256

int main(){
	FILE* fp = fopen(DEBUG? "miniset" : "input", "r");
	if(!fp)
		return -1;
	unsigned long long fishes[9] = {0,0,0,0,0,0,0,0,0};
	int f=0;
	while(EOF != fscanf(fp,"%d,", &f)){
		fishes[f]++;
	}
	fclose(fp);
#if DEBUG
	for(int i=0;i<9;i++)
		printf("%llu%c ",fishes[i], i<8?',':'\n');
#endif
	for(int i=0;i<DAYS;i++){
		const unsigned long long dDay = fishes[0];
		for(int j=1;j<9;j++){
			fishes[j-1] = fishes[j];
		}
		fishes[6] += dDay;
		fishes[8] = dDay;
#if DEBUG
		printf("day %d:   \t",i+1);
		for(int k=0;k<9;k++)
			printf("%llu%c ",fishes[k], k<8?',':'\n');
#endif
	}
	unsigned long long count=0;
	for(int i=0;i<9;i++){
		count += fishes[i];
	}
	printf("amount of fishes after %d days : %llu \n",DAYS, count);
	return 0;
}
