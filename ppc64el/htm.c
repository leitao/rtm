#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<htmintrin.h>
#include<unistd.h>
#include <inttypes.h>

#define MAX 50000

// This function runs the a transaction as big as n, to see it
// aborting due to CAPACITY issue.
// If I do write to a different memory position, the CAPACITY
// abort it never triggered.
int depth(int n){
	int *ptr = malloc(MAX*sizeof(int));
	memset(ptr, 0, MAX); 

	if (__builtin_tbegin(0)){
		for (int z = 0 ; z <n ; z++)
			ptr[0] = z;
		__builtin_tend(0);
	} else
		return -1;

	free(ptr);

	return 0;
}

void dump_error(int ret){
	char str[1024] = "";

	printf("%s\n", str);
}

int main(int argc, char **argv){
	printf(" Hello to Hardware Transactional Memory example\n");

	for (int i = 0; i < MAX ; i++){
		long ret = depth(i);
		if (!ret)
			printf("%4d : Transaction block executed\n", i);
		else {
			uint64_t z = __builtin_get_texasr();

			printf(" %d : Failure with error: %lx\n", i,  _TEXASR_FAILURE_CODE(z));
			printf("     : Summary error: %lx\n",  _TEXASR_FAILURE_SUMMARY(z));
			printf("     : TFIAR error: %lx\n",  _TEXASR_TFIAR_EXACT(z));
			break;
		}
	}

	return 0;
}
