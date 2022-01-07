#!/bin/tcc -run
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#define DEBUG 0
#define MAX_CRABS 1000

int compare(const void* a,const void* b){ 
	  int int_a = * ( (int*) a );
    int int_b = * ( (int*) b );
    if ( int_a == int_b ) return 0;
    else if ( int_a < int_b ) return -1;
    else return 1;
}
//get sum of sequence 1+...+n
const int triangularNumber(const int v,const int acc){
	if(!v)
		return acc;
	return triangularNumber(v-1, acc+v);
}
const int triangularSum(const int v){return triangularNumber(v,0);}
const int mean(const int* arr, const int cnt){
	int sum=0;
	for(int i=0;i<cnt;i++){
		sum += arr[i];
	}
	return round((double)sum/cnt);
};
const int variance(const int* sortedArr, const int cnt){
	const int pMean = mean(sortedArr, cnt);
	int sum = 0;
	for(int i=0;i<cnt;i++){
		sum += pow(abs(sortedArr[i]-pMean),2);
	}
	return round((double)sum/cnt);//variance= mean of squared mean diffs
};
int main(){
	FILE* fp = fopen(DEBUG? "miniset" : "input", "r");
	if(!fp)
		return -1;
	int crabsPosition[MAX_CRABS];
	memset(crabsPosition, -1, sizeof(char));
	int buffer=0;
	int cIndex = 0;
	while(EOF != fscanf(fp,"%d,", &buffer)){
		crabsPosition[cIndex]= buffer;
		cIndex++;
	}
	fclose(fp);
	qsort(crabsPosition, cIndex, sizeof(crabsPosition[0]),compare);
#if DEBUG
	printf("Initial positions(sorted) :");
	for(int i=0;i<cIndex;i++)
		printf("%d%c ",crabsPosition[i], i<cIndex-1?',':'\n');
#endif
	const int pMedian = crabsPosition[cIndex/2];
	//symbol kept to find better definition of position in case #2
	//const int pMean = mean(crabsPosition,cIndex);
	//const int pVariance = variance(crabsPosition,cIndex);
	//const int ecartTypeArrondi = round(sqrt((double)pVariance));
	//printf("variance: %d\necart type arrondi:%d\n",pVariance, ecartTypeArrondi);
	int amountOfFuel = 0;
	for(int i=0; i<cIndex;i++){
		amountOfFuel += abs(crabsPosition[i] - pMedian);
	}
	//since no algebraic rule has been found to determine better position we get it by bruteforce
	int amountOfFuel2 = 0x7fffffff;
	for(int j=0;j<cIndex;j++){ 		int testedFuelAmount=0;
		for(int i=0; i<cIndex;i++){
			testedFuelAmount += triangularSum(abs(crabsPosition[i]-j));
		}
		if(testedFuelAmount<amountOfFuel2){
			amountOfFuel2 = testedFuelAmount;
			printf("found better consuming: %d at pos %d\n",amountOfFuel2, j);
		}
	}
	printf("#1 : median position :%d, amount of fuel required to align:%d\n",pMedian, amountOfFuel);
	printf("#2 : Amount of fuel required to align:%d\n",amountOfFuel2);
	return 0;
}
