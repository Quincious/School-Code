#include "convert.h"
#include <stdio.h>

int main(int argc, char** argv){
    for(double d = 0.5; d < 100; d*= 2){
	long l1 = double_to_long(d);
	long l2 = (long) d;
	if(l1 != l2){
	    fprintf(stderr, "Input: %lf, Should be %ld, got %ld\n", d, l2, l1);
	    return 1;
	}
    }
    for(double d = -0.5; d > -100; d*= 2){
	long l1 = double_to_long(d);
	long l2 = (long) d;
	if(l1 != l2){
	    fprintf(stderr, "Input: %lf, Should be %ld, got %ld\n", d, l2, l1);
	    return 1;
	}
    }
    return 0;
}
