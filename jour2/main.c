#!/bin/tcc -run
#include <stdio.h>

int main(){
	FILE *fp = fopen("input","r");
	if(NULL == fp)
		return -1;
	int position = 0;
	int depth1 = 0;
	int depth2 = 0;
	int aim=0;
	char *instruction;
	int val;
	while(EOF != fscanf(fp, "%s %d", instruction, &val)){
		//printf("instruction:%s\n",instruction);
		//printf("val:%d\n",val);
		switch(instruction[0]){
			case 'f': {
									position += val;
									depth2 += aim*val;
									break;
								}
			case 'd': {
									depth1 += val;
									aim += val;
									break;
								}
			case 'u': {
									depth1 -= val;
									aim -= val;
									break;
								}
		}
	};
	fclose(fp);
	printf("1rst position %d *  depth %d = %d\n", position, depth1, position*depth1);
	printf("2nd position %d *  depth %d = %d\n", position, depth2, position*depth2);
	return 0;
}
