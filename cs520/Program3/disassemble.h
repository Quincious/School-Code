#ifndef DISASSEMBLE_H
#define DISASSEMBLE_H

#include "classfile.h"

typedef struct{
	char * name;
	int arg;
}opCode_info;

static opCode_info *Dictionary;

void disassemble(classfile* cp);

void LoadOpCode(char* name, int index, int arg);
void LoadDictionary();




#endif
