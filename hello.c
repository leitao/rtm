#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "immintrin.h"

#define MAX 5000

int depth(int n){
	unsigned int stat; 

	stat = _xbegin();
	int i = 1;

	if (stat == _XBEGIN_STARTED){
		for (int z = 0 ; z <n ; z++)
			i++;
		_xend();
	} else {
		return stat;
	} 
	return 0;
}


void dump_error(int ret){
	char str[] = "";
	char *string;
	
	if (ret & _XABORT_EXPLICIT)
		string = strcat(str, "EXPLICT | ");	
	if (ret & _XABORT_RETRY)
		string = strcat(str, "RETRY | ");	
	if (ret & _XABORT_CONFLICT)
		string = strcat(str, "CONFLICT | ");	
	if (ret & _XABORT_CAPACITY)
		string = strcat(str, "CAPACITY | ");	
	if (ret & _XABORT_DEBUG)
		string = strcat(str, "DEBUG | ");	
	if (ret & _XABORT_NESTED)
		string = strcat(str, "NESTED | ");	

	printf("%s\n", string);
}

int main(int argc, char **argv){
	printf(" Hello to Hardware Transactional Memory example\n");

	for (int i = 0; i < MAX ; i++){
		int ret = depth(i);
		if (!ret)
			printf("%4d : Transaction executed\n", i);
		else {
			printf("%4d : Transaction failed with code: ", i);
			dump_error(ret);
			break;
		}
	}

	return 0;
}
