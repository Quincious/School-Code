#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "classfile.h"
#include "utils.h"
#include "disassemble.h"


int main(int argc, char** argv){
    if(argc != 2){
	fprintf(stderr, "Needs exactly 1 command line argument, file to disassemble\n");
	return 1;
    }
    FILE* f = fopen(argv[1], "rb");
    if(f == NULL){
	fprintf(stderr, "Failed to open file %s\n", argv[1]);
	return 1;
    }
    
    classfile* cf = read_classfile(f);
    
    fclose(f);

    //print_classfile(cf, stdout);
    disassemble(cf);
    
    cleanup_classfile(cf);
    return 0;
}
