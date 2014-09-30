#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

void memcheck(void* p){
    if (p == NULL){
	fprintf(stderr, "Malloc failed\n");
	exit(1);
    }
}
