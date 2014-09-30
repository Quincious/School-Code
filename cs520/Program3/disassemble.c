/*
Jonathan Hart
Program3
10/06/2013
*/

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "classfile.h"
#include "disassemble.h"

void disassemble(classfile* c)
{		
	Dictionary = malloc(sizeof(opCode_info) * 256);
	LoadDictionary();
	method_info* currentMethod;
	code_attribute* currentCode;

	for(int i = 0; i < c->methods_count; i++)
	{
		currentMethod = c->methods[i];		
		
		currentCode = currentMethod->code;
		unsigned char* method_name = c->constant_pool[currentMethod->name_index - 1]->info;
		
		fprintf(stdout,"Method Name: %s\n", method_name);	

		for(int j = 0; j < currentCode->code_length; j++)
		{
			if(Dictionary[(int)currentCode->code[j]].arg == 0)
			{
				fprintf(stdout,"\t%d %s \n", j, Dictionary[(int)currentCode->code[j]].name);
			}
			else if(Dictionary[(int)currentCode->code[j]].arg == 1)
			{				
				fprintf(stdout,"\t%d %s", j, Dictionary[(int)currentCode->code[j]].name);
				j++;
				int arg = (int)currentCode->code[j];
				fprintf(stdout, " (%d)\n", arg);				
			}
			else if(Dictionary[(int)currentCode->code[j]].arg == 21)
			{				
				fprintf(stdout,"\t%d %s", j, Dictionary[(int)currentCode->code[j]].name);
				j++;
				int arg = (int)currentCode->code[j];
				arg = arg << 8;
				j++;
				arg += (int)currentCode->code[j];
				fprintf(stdout, " (%d)\n", arg);				
			}
			else if(Dictionary[(int)currentCode->code[j]].arg == 22)
			{		
				int index = j;
				fprintf(stdout,"\t%d %s", j, Dictionary[(int)currentCode->code[j]].name);
				j++;
				short arg = (unsigned short)currentCode->code[j];
				arg = arg << 8;
				j++;
				arg += (unsigned short)currentCode->code[j];
				arg += index;
				fprintf(stdout, " (%d)\n", arg);				
			}
			else if(Dictionary[(int)currentCode->code[j]].arg == 23)
			{					
				fprintf(stdout,"\t%d %s", j, Dictionary[(int)currentCode->code[j]].name);
				j++;
				int arg1 = (int)currentCode->code[j];				
				j++;
				int arg2 = (int)currentCode->code[j];
				fprintf(stdout, " (%d, %d)\n", arg1, arg2);				
			}
			else if(Dictionary[(int)currentCode->code[j]].arg == 3)
			{		
				fprintf(stdout,"\t%d %s", j, Dictionary[(int)currentCode->code[j]].name);
				j++;
				int arg1 = (int)currentCode->code[j];
				arg1 = arg1 << 8;
				j++;
				arg1 += (int)currentCode->code[j];
				j++;
				int arg2 = (int)currentCode->code[j];	
				fprintf(stdout, " (%d, %d)\n", arg1, arg2);				
			}
			else if(Dictionary[(int)currentCode->code[j]].arg == 41)
			{		
				fprintf(stdout,"\t%d %s", j, Dictionary[(int)currentCode->code[j]].name);
				j++;
				int arg1 = (int)currentCode->code[j];
				arg1 = arg1 << 8;
				j++;
				arg1 += (int)currentCode->code[j];
				j++;
				int arg2 = (int)currentCode->code[j];
				j++;
				int arg3 = (int)currentCode->code[j];
				fprintf(stdout, " (%d, %d, %d)\n", arg1, arg2, arg3);				
			}
			else if(Dictionary[(int)currentCode->code[j]].arg == 42)
			{		
				fprintf(stdout,"\t%d %s", j, Dictionary[(int)currentCode->code[j]].name);
				j++;
				int arg1 = (int)currentCode->code[j];
				arg1 = arg1 << 8;
				j++;
				arg1 += (int)currentCode->code[j];
				j++;
				int arg2 = (int)currentCode->code[j];
				j++;
				int arg3 = (int)currentCode->code[j];
				fprintf(stdout, " (%d, %d, %d)\n", arg1, arg2, arg3);				
			}
			else if(Dictionary[(int)currentCode->code[j]].arg == 43)
			{		
				fprintf(stdout,"\t%d %s", j, Dictionary[(int)currentCode->code[j]].name);
				j++;
				int arg1 = (int)currentCode->code[j];
				arg1 = arg1 << 24;
				j++;
				arg1 += (int)currentCode->code[j] << 16;
				j++;
				arg1 += (int)currentCode->code[j] << 8;
				j++;
				arg1 += (int)currentCode->code[j];
				fprintf(stdout, " (%d)\n", arg1);				
			}
			else if(Dictionary[(int)currentCode->code[j]].arg == 44)
			{		
				fprintf(stdout,"\t%d %s:\n", j, Dictionary[(int)currentCode->code[j]].name);				
				int index = j;
				j++;
				while((j % 4) != 0)
					j++;
								
				int defaultValue = (int)currentCode->code[j];
				defaultValue = defaultValue << 24;
				j++;
				defaultValue += (int)currentCode->code[j] << 16;
				j++;
				defaultValue += (int)currentCode->code[j] << 8;
				j++;
				defaultValue += (int)currentCode->code[j];
				defaultValue += index;
				fprintf(stdout, "Default: %d\n", defaultValue);	
				
				j++;
				int lowValue = (int)currentCode->code[j];
				lowValue = lowValue << 24;
				j++;
				lowValue += (int)currentCode->code[j] << 16;
				j++;
				lowValue += (int)currentCode->code[j] << 8;
				j++;
				lowValue += (int)currentCode->code[j];
				fprintf(stdout, "Low: %d\n", lowValue);
				
				j++;
				int highValue = (int)currentCode->code[j];
				highValue = highValue << 24;
				j++;
				highValue += (int)currentCode->code[j] << 16;
				j++;
				highValue += (int)currentCode->code[j] << 8;
				j++;
				highValue += (int)currentCode->code[j];
				fprintf(stdout, "High: %d\n", highValue);
				
				for(int i = lowValue; i < highValue; i++)
				{
					j++;
					int currentVal = (int)currentCode->code[j];
					currentVal = currentVal << 24;
					j++;
					currentVal += (int)currentCode->code[j] << 16;
					j++;
					currentVal += (int)currentCode->code[j] << 8;
					j++;
					currentVal += (int)currentCode->code[j];
					fprintf(stdout, "%d: %d\n", i, currentVal);
				}
			}
		}
		fprintf(stdout, "\n");
	}

}

void LoadOpCode(char* name, int index, int arg)
{
	Dictionary[index].name = name;
	Dictionary[index].arg = arg;
}

void LoadDictionary()
{
	LoadOpCode("nop",0x0,0);
	LoadOpCode("aconst_null",0x1,0);
	LoadOpCode("iconst_m1",0x2,0);
	LoadOpCode("iconst_0",0x3,0);
	LoadOpCode("iconst_1",0x4,0);
	LoadOpCode("iconst_2",0x5,0);
	LoadOpCode("iconst_3",0x6,0);
	LoadOpCode("iconst_4",0x7,0);
	LoadOpCode("iconst_5",0x8,0);
	LoadOpCode("lconst_0",0x9,0);
	LoadOpCode("lconst_1",0x0a,0);
	LoadOpCode("fconst_0",0x0b,0);
	LoadOpCode("fconst_1",0x0c,0);
	LoadOpCode("fconst_2",0x0d,0);
	LoadOpCode("dconst_0",0x0e,0);
	LoadOpCode("dconst_1",0x0f,0);
	LoadOpCode("bipush",0x10,1);
	LoadOpCode("sipush",0x11,21);
	LoadOpCode("ldc",0x12,1);
	LoadOpCode("ldc_w",0x13,21);
	LoadOpCode("ldc2_w",0x14,21);
	LoadOpCode("iload",0x15,1);
	LoadOpCode("lload",0x16,1);
	LoadOpCode("fload",0x17,1);
	LoadOpCode("dload",0x18,1);
	LoadOpCode("aload",0x19,1);
	LoadOpCode("iload_0",0x1a,0);
	LoadOpCode("iload_1",0x1b,0);
	LoadOpCode("iload_2",0x1c,0);
	LoadOpCode("iload_3",0x1d,0);
	LoadOpCode("lload_0",0x1e,0);
	LoadOpCode("lload_1",0x1f,0);
	LoadOpCode("lload_2",0x20,0);
	LoadOpCode("lload_3",0x21,0);
	LoadOpCode("fload_0",0x22,0);
	LoadOpCode("fload_1",0x23,0);
	LoadOpCode("fload_2",0x24,0);
	LoadOpCode("fload_3",0x25,0);
	LoadOpCode("dload_0",0x26,0);
	LoadOpCode("dload_1",0x27,0);
	LoadOpCode("dload_2",0x28,0);
	LoadOpCode("dload_3",0x29,0);
	LoadOpCode("aload_0",0x2a,0);
	LoadOpCode("aload_1",0x2b,0);
	LoadOpCode("aload_2",0x2c,0);
	LoadOpCode("aload_3",0x2d,0);
	LoadOpCode("iaload",0x2e,0);
	LoadOpCode("laload",0x2f,0);
	LoadOpCode("faload",0x30,0);
	LoadOpCode("daload",0x31,0);
	LoadOpCode("aaload",0x32,0);
	LoadOpCode("baload",0x33,0);
	LoadOpCode("caload",0x34,0);
	LoadOpCode("saload",0x35,0);
	LoadOpCode("istore",0x36,1);
	LoadOpCode("lstore",0x37,1);
	LoadOpCode("fstore",0x38,1);
	LoadOpCode("dstore",0x39,1);
	LoadOpCode("astore",0x3a,1);
	LoadOpCode("istore_0",0x3b,0);
	LoadOpCode("istore_1",0x3c,0);
	LoadOpCode("istore_2",0x3d,0);
	LoadOpCode("istore_3",0x3e,0);
	LoadOpCode("lstore_0",0x3f,0);
	LoadOpCode("lstore_1",0x40,0);
	LoadOpCode("lstore_2",0x41,0);
	LoadOpCode("lstore_3",0x42,0);
	LoadOpCode("fstore_0",0x43,0);
	LoadOpCode("fstore_1",0x44,0);
	LoadOpCode("fstore_2",0x45,0);
	LoadOpCode("fstore_3",0x46,0);
	LoadOpCode("dstore_0",0x47,0);
	LoadOpCode("dstore_1",0x48,0);
	LoadOpCode("dstore_2",0x49,0);
	LoadOpCode("dstore_3",0x4a,0);
	LoadOpCode("astore_0",0x4b,0);
	LoadOpCode("astore_1",0x4c,0);
	LoadOpCode("astore_2",0x4d,0);
	LoadOpCode("astore_3",0x4e,0);
	LoadOpCode("iastore",0x4f,0);
	LoadOpCode("lastore",0x50,0);
	LoadOpCode("fastore",0x51,0);
	LoadOpCode("dastore",0x52,0);
	LoadOpCode("aastore",0x53,0);
	LoadOpCode("bastore",0x54,0);
	LoadOpCode("castore",0x55,0);
	LoadOpCode("sastore",0x56,0);
	LoadOpCode("pop",0x57,0);
	LoadOpCode("pop2",0x58,0);
	LoadOpCode("dup",0x59,0);
	LoadOpCode("dup_x1",0x5a,0);
	LoadOpCode("dup_x2",0x5b,0);
	LoadOpCode("dup2",0x5c,0);
	LoadOpCode("dup2_x1",0x5d,0);
	LoadOpCode("dup2_x2",0x5e,0);
	LoadOpCode("swap",0x5f,0);
	LoadOpCode("iadd",0x60,0);
	LoadOpCode("ladd",0x61,0);
	LoadOpCode("fadd",0x62,0);
	LoadOpCode("dadd",0x63,0);
	LoadOpCode("isub",0x64,0);
	LoadOpCode("lsub",0x65,0);
	LoadOpCode("fsub",0x66,0);
	LoadOpCode("dsub",0x67,0);
	LoadOpCode("imul",0x68,0);
	LoadOpCode("lmul",0x69,0);
	LoadOpCode("fmul",0x6a,0);
	LoadOpCode("dmul",0x6b,0);
	LoadOpCode("idiv",0x6c,0);
	LoadOpCode("ldiv",0x6d,0);
	LoadOpCode("fdiv",0x6e,0);
	LoadOpCode("ddiv",0x6f,0);
	LoadOpCode("irem",0x70,0);
	LoadOpCode("lrem",0x71,0);
	LoadOpCode("frem",0x72,0);
	LoadOpCode("drem",0x73,0);
	LoadOpCode("ineg",0x74,0);
	LoadOpCode("lneg",0x75,0);
	LoadOpCode("fneg",0x76,0);
	LoadOpCode("dneg",0x77,0);
	LoadOpCode("ishl",0x78,0);
	LoadOpCode("lshl",0x79,0);
	LoadOpCode("ishr",0x7a,0);
	LoadOpCode("lshr",0x7b,0);
	LoadOpCode("iushr",0x7c,0);
	LoadOpCode("lushr",0x7d,0);
	LoadOpCode("iand",0x7e,0);
	LoadOpCode("land",0x7f,0);
	LoadOpCode("ior",0x80,0);
	LoadOpCode("lor",0x81,0);
	LoadOpCode("ixor",0x82,0);
	LoadOpCode("lxor",0x83,0);
	LoadOpCode("iinc",0x84,23);
	LoadOpCode("i2l",0x85,0);
	LoadOpCode("i2f",0x86,0);
	LoadOpCode("i2d",0x87,0);
	LoadOpCode("l2i",0x88,0);
	LoadOpCode("l2f",0x89,0);
	LoadOpCode("l2d",0x8a,0);
	LoadOpCode("f2i",0x8b,0);
	LoadOpCode("f2l",0x8c,0);
	LoadOpCode("f2d",0x8d,0);
	LoadOpCode("d2i",0x8e,0);
	LoadOpCode("d2l",0x8f,0);
	LoadOpCode("d2f",0x90,0);
	LoadOpCode("i2b",0x91,0);
	LoadOpCode("i2c",0x92,0);
	LoadOpCode("i2s",0x93,0);
	LoadOpCode("lcmp",0x94,0);
	LoadOpCode("fcmpl",0x95,0);
	LoadOpCode("fcmpg",0x96,0);
	LoadOpCode("dcmpl",0x97,0);
	LoadOpCode("dcmpg",0x98,0);
	LoadOpCode("ifeq",0x99,22);
	LoadOpCode("ifne",0x9a,22);
	LoadOpCode("iflt",0x9b,22);
	LoadOpCode("ifge",0x9c,22);
	LoadOpCode("ifgt",0x9d,22);
	LoadOpCode("ifle",0x9e,22);
	LoadOpCode("if_icmpeq",0x9f,22);
	LoadOpCode("if_icmpne",0xa0,22);
	LoadOpCode("if_icmplt",0xa1,22);
	LoadOpCode("if_icmpge",0xa2,22);
	LoadOpCode("if_icmpgt",0xa3,22);
	LoadOpCode("if_icmple",0xa4,22);
	LoadOpCode("if_acmpeq",0xa5,22);
	LoadOpCode("if_acmpne",0xa6,22);
	LoadOpCode("goto",0xa7,22);
	LoadOpCode("jsr",0xa8,22);
	LoadOpCode("ret",0xa9,1);
	LoadOpCode("tableswitch",0xaa,44);
	LoadOpCode("lookupswitch",0xab,44);
	LoadOpCode("ireturn",0xac,0);
	LoadOpCode("lreturn",0xad,0);
	LoadOpCode("freturn",0xae,0);
	LoadOpCode("dreturn",0xaf,0);
	LoadOpCode("areturn",0xb0,0);
	LoadOpCode("return",0xb1,0);
	LoadOpCode("getstatic",0xb2,21);
	LoadOpCode("putstatic",0xb3,21);
	LoadOpCode("getfield",0xb4,21);
	LoadOpCode("putfield",0xb5,21);
	LoadOpCode("invokevirtual",0xb6,21);
	LoadOpCode("invokespecial",0xb7,21);
	LoadOpCode("invokestatic",0xb8,21);
	LoadOpCode("invokeinterface",0xb9,42);
	LoadOpCode("invokedynamic",0xba,41);
	LoadOpCode("new",0xbb,21);
	LoadOpCode("newarray",0xbc,1);
	LoadOpCode("anewarray",0xbd,21);
	LoadOpCode("arraylength",0xbe,0);
	LoadOpCode("athrow",0xbf,0);
	LoadOpCode("checkcast",0xc0,21);
	LoadOpCode("instanceof",0xc1,21);
	LoadOpCode("monitorenter",0xc2,0);
	LoadOpCode("monitorexit",0xc3,0);
	LoadOpCode("wide",0xc4,35);
	LoadOpCode("multianewarray",0xc5,3);
	LoadOpCode("ifnull",0xc6,22);
	LoadOpCode("ifnonnull",0xc7,22);
	LoadOpCode("goto_w",0xc8,43);
	LoadOpCode("jsr_w",0xc9,43);
	LoadOpCode("breakpoint",0xca,0);
	LoadOpCode("impdep1",0xfe,0);
	LoadOpCode("impdep2",0xff,0);

}

