#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "immintrin.h"
#include<unistd.h>

#define MAX 50000

// This function runs the a transaction as big as n, to see it
// aborting due to CAPACITY issue.
// If I do write to a different memory position, the CAPACITY
// abort it never triggered.
int depth(int n){
	unsigned int stat; 
	int *ptr = malloc(MAX*sizeof(int));
	memset(ptr, 0, MAX); 

	stat = _xbegin();

	if (stat == _XBEGIN_STARTED){
		for (int z = 0 ; z <n ; z++)
			ptr[z] = z;
		_xend();
	} else {
		return stat;
	} 

	free(ptr);

	return 0;
}


void dump_error(int ret){
	char str[1024] = "";
	
	if (ret & _XABORT_EXPLICIT)
		strcat(str, "EXPLICT | ");	
	if (ret & _XABORT_RETRY)
		strcat(str, "RETRY | ");	
	if (ret & _XABORT_CONFLICT)
		strcat(str, "CONFLICT | ");	
	if (ret & _XABORT_CAPACITY)
		strcat(str, "CAPACITY | ");	
	if (ret & _XABORT_DEBUG)
		strcat(str, "DEBUG | ");	
	if (ret & _XABORT_NESTED)
		strcat(str, "NESTED | ");	

	printf("%s\n", str);
}

int main(int argc, char **argv){
	printf(" Hello to Hardware Transactional Memory example\n");

	for (int i = 0; i < MAX ; i++){
		int ret = depth(i);
		if (!ret)
			printf("%4d : Transaction executed\n", i);
		else {
			if (_xtest())
				printf("Transaction is still active\n");

			printf("%4d : Transaction failed with code: ", i);
			dump_error(ret);
			break;
		}
		usleep(400);
	}

	return 0;
}
