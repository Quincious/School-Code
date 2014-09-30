#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dissect.h"

void print_fps(FILE* s, fp_struct fps){
    fprintf(s, "sign: %d\n", fps.sign);
    fprintf(s, "exponent: %d\n", fps.exponent);
    fprintf(s, "Mantissa (in binary): ");
    unsigned long mask = 0x10000000000000l;
    int counter = 0;
    while(mask != 0){
	if(mask & fps.mantissa){
	    fprintf(s, "1");
	} else
	    fprintf(s, "0");
	if(counter == 0)
	    fprintf(s, ".");
	if((counter % 4) == 0 && counter != 0)
	    fprintf(s, " ");
	counter ++;
	mask >>= 1;
    }
    fprintf(s, "\n");
}

void print_ls(FILE* s, long_struct ls){
    fprintf(s, "sign: %d\n", ls.sign);
    fprintf(s, "magnitude: %ld\n", ls.magnitude);
}

bool is_float(char* s){
    int index = 0;
    while(s[index] != 0){
	if(s[index] == '.')
	    return true;
	index ++;
    }
    return false;
}

int main(int argc, char** argv){
    //contains decimal point
    if(is_float(argv[1])){
	char* end;
    	errno = 0;
	double d = strtod(argv[1], &end);
	if(errno != 0 || *end != 0){
	    fprintf(stderr, "invalid floating point number %s\n", argv[1]);
	    return -1;
	}
	fp_struct fps = dissect_double(d);
	print_fps(stdout, fps);
    } else {
    //no decimal point, treat as a long
	char* end;
    	errno = 0;
	long l = strtol(argv[1], &end, 10);
	if(errno != 0 || *end != 0){
	    fprintf(stderr, "invalid long integer %s\n", argv[1]);
	    return -1;
	}
	long_struct ls = dissect_long(l);
	print_ls(stdout, ls);
    }
    return 0;
}
