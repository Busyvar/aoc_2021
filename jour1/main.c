#!/bin/tcc -run
#include <stdio.h>
#define LINE_BUFF 8
#define MAX_LEN 5000

int main(){
	FILE *fp = fopen("input","r");
	if(NULL == fp)
		return -1;
	char* raw_value;
	size_t* ln;
	int vals[MAX_LEN];
	int resP1 = 0;
	int resP2 = 0;
	for(int i=0; -1 != getline(&raw_value, &ln, fp); i++){
		vals[i] = atoi(raw_value);
		if(i > 0 && vals[i] > vals[i-1]){
			resP1++;
		}
		if(i >= 3 && 
				(vals[i-3]+vals[i-2] + vals[i-1]) <
				(vals[i-2] + vals[i-1] + vals[i])
		){
			resP2++;
		}
	};
	fclose(fp);
	printf("number of increase part one = %d\n", resP1);
	printf("number of increase part two = %d\n", resP2);
	return 0;
}
