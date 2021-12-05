#!/bin/tcc -run
#include <stdio.h>
#define BIT_WIDTH 12
#define MAX_ENTRIES 1000

typedef struct{
	int a[MAX_ENTRIES];
	size_t size;
}arrWrap_t;
arrWrap_t arrayFilter(const int entryToKeep, const int bitIndex, const arrWrap_t arrayToFilter){
	printf("%s called with: %d, %d, %d, %d\n", __FUNCTION__, entryToKeep, bitIndex, arrayToFilter.a[0], (int) arrayToFilter.size);
	arrWrap_t result = {.a= {0,}, .size=0};
	if(arrayToFilter.size == 1)
		return arrayToFilter;
	for(int i=0; i<arrayToFilter.size; i++){
		if(entryToKeep == ((arrayToFilter.a[i] & (1 << bitIndex))?1:0)){
			result.a[result.size] = arrayToFilter.a[i];
			result.size++;
		}
	};
	return result;
}
int main(){
	FILE *fp = fopen("input","r");
	int diag[BIT_WIDTH] = {0,};
	int gamma=0;
	int epsilonn=0;
	arrWrap_t values = {.a= {0,}, .size=0};
	if(NULL == fp)
		return -1;
	char binVal[BIT_WIDTH+1];
	while(EOF != fscanf(fp, "%s", binVal)){
		for(int i=0;i<BIT_WIDTH;i++){
			diag[i] += binVal[i]-48;
			values.a[values.size] += (binVal[i]-48) << (BIT_WIDTH-1-i);
		}
		values.size++;
	};
	arrWrap_t O2 = values;
	arrWrap_t CO2 = values;
	for(int i=BIT_WIDTH-1;i>=0;i--){
		int more = 0;
		int less = 0;
		printf("%d/%d\n",diag[i], (int) values.size);
		gamma 	 |= (diag[BIT_WIDTH-1-i] >= (values.size>>1)) << i;
		for(int j=0; j < O2.size;j++)
			more += (O2.a[j] & (1 << i)) ? 1 : 0;
		more = more >= ((float) O2.size/2);
		for(int j=0; j < CO2.size;j++)
			less += (CO2.a[j] & (1 << i)) ? 1 : 0;
		less = less == (float) CO2.size/2 ? 0 : (less < ((float) CO2.size/2));
		O2 = arrayFilter(more,i,O2);
		CO2 = arrayFilter(less,i,CO2);
	}
	epsilonn = ~gamma & 4095;
	printf("values:%d O2:%d CO2:%d\n", (int)values.size, (int)O2.size, (int)CO2.size);
	fclose(fp);
	printf("1rst gamma %d *  epsilonn %d = %d\n", gamma, epsilonn, gamma*epsilonn);
	printf("2nd oxygen generator %d *  Co2 scrubber %d = %d\n", O2.a[0], CO2.a[0],  O2.a[0] * CO2.a[0]);
	return 0;
}
