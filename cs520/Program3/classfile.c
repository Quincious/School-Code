#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

#include "classfile.h"
#include "utils.h"

cp_info* read_constant(int index, FILE* stream);
unsigned int read8(FILE* stream);
unsigned int read16(FILE* stream);
unsigned int read32(FILE* stream);
field_info* read_field(FILE* stream);
method_info* read_method(classfile* c, FILE* stream);
attribute_info* read_attribute(FILE* stream);


char* UNPRINTABLE = "Unprintable";

bool is_printable(char* s, int length){
    for(int i = 0; i < length; i++){
	if(s[i] >= 32 && s[i] <= 126)
	    continue;
	else
	    return false;
    }
    return true;
}

char* get_constant_name(classfile* cf, int index){
    assert(index - 1< cf->constant_pool_count);
    char* to_return = (char*) cf->constant_pool[index - 1]->info;
    if(is_printable(to_return, cf->constant_pool[index - 1]->cp_length))
	return to_return;
    else
	return UNPRINTABLE;
}

cp_info* read_constant(int index, FILE* stream){
    unsigned char c = read8(stream);
    unsigned int burn_length = 0;
    switch(c){
    case 1:
	burn_length = read16(stream);
	break;
    case 3:
	burn_length = 4;
	break;
    case 4:
	burn_length = 4;
	break;
    case 5:
	burn_length = 8;
	break;
    case 6:
	burn_length = 8;
	break;
    case 7:
	burn_length = 2;
	break;
    case 8:
	burn_length = 2;
	break;
    case 9:
	burn_length = 4;
	break;
    case 10:
	burn_length = 4;
	break;
    case 11:
	burn_length = 4;
	break;
    case 12:
	burn_length = 4;
	break;
    case 15:
	burn_length = 3;
	break;
    case 16:
	burn_length = 2;
	break;
    case 18:
	burn_length = 4;
	break;
    default:
	burn_length = 0;
    }
//    fprintf(stderr, "%d\n", c);
    cp_info* cp = malloc(sizeof(cp_info));
    memcheck(cp);
    cp->tag = c;
    cp->cp_length = burn_length;
    cp->info = malloc(burn_length + 1);
    cp->info[burn_length] = 0;
//    assert(burn_length > 0);
    for(int i = 0; i < burn_length; i++){
	unsigned char next = read8(stream);
	cp->info[i] = next;
    }
    

    return cp;
}


unsigned int read8(FILE* stream){
    unsigned int next = getc(stream);
    return next;
}

unsigned int read16(FILE* stream){
    unsigned int toReturn = 0;
    unsigned char* c = (unsigned char*) &toReturn;
    for(int i = 0; i < 2; i++){
	unsigned int newChar = getc(stream);
	if(newChar == EOF){
	    return EOF;
	}
	c[1-i] = newChar;
    }
    return toReturn;
}

unsigned int read32(FILE* stream){
    unsigned int toReturn;
    unsigned char* c = (unsigned char*) &toReturn;
    for(int i = 0; i < 4; i++){
	unsigned int newChar = getc(stream);
	if(newChar == EOF){
	    return EOF;
	}
	c[3-i] = newChar;
    }
    return toReturn;
    
}

void print_attribute(classfile* cf, attribute_info* a, FILE* out){
    fprintf(out, "\t\tAttribute Name: %d <<%s>>\n", a->name_index, get_constant_name(cf, a->name_index));
    fprintf(out, "\t\tAttribute Length: %d\n", a->attribute_length);
    /* for(int i = 0; i < a->attribute_length; i++){ */
    /* 	fputc(a->info[i], out); */
    /* } */

    fprintf(out, "\t(%d)\t", a->attribute_length);
    for(int i = 0; i < a->attribute_length; i++){
	fprintf(out, "%02x ", a->info[i]);
    }
    fprintf(out, "\n");
}



void print_method(classfile* cf, method_info* m, FILE* out){
    fprintf(out, "\tMethod Flags: %x\n", m->access_flags);
    fprintf(out, "\tMethod Name: %d <<%s>>\n", m->name_index, get_constant_name(cf, m->name_index));
    fprintf(out, "\tMethod Descriptor: %d <<%s>>\n", m->descriptor_index, get_constant_name(cf, m->descriptor_index));
    fprintf(out, "\tMethod Attribute Count: %d\n", m->attributes_count);
    for(int i = 0; i < m->attributes_count; i++){
	print_attribute(cf, m->attributes[i], out);
    }
}


void print_field(classfile* cf, field_info* f, FILE* out){
    fprintf(out, "\tField Flags: %x\n", f->access_flags);
    fprintf(out, "\tField Name: %d <<%s>>\n", f->name_index, get_constant_name(cf, f->name_index));
    fprintf(out, "\tField Descriptor: %d\n", f->descriptor_index);
    fprintf(out, "\tAttribute Count: %d\n", f->attributes_count);
    for(int i = 0; i < f->attributes_count; i++){
	print_attribute(cf, f->attributes[i], out);
    }
}

void print_constant(cp_info* cp, FILE* out){
    if(is_printable((char*) cp->info, cp->cp_length)){
    	for(int i = 0; i < cp->cp_length; i++){
    	    fputc(cp->info[i], out);
    	}
    } else {
	fprintf(out, "(%d) ", cp->cp_length);
	for(int i = 0; i < cp->cp_length; i++){
	    fprintf(out, "%02x ", cp->info[i]);
	}
    }
}

void print_classfile(classfile* c, FILE* out){
    fprintf(out, "Magic: %x\n", c->magic);
    fprintf(out, "Minor: %x\n", c->minor_version);
    fprintf(out, "Major: %x\n", c->major_version);
    fprintf(out, "Constant Pool Count: %d\n", c->constant_pool_count);
    for(int i = 0; i < c->constant_pool_count-1; i++){
	fprintf(out, "\t%d\t", i + 1);
	print_constant(c->constant_pool[i], out);
	fprintf(out, "\n");
    }

    fprintf(out, "Access Flags: %x\n", c->access_flags);
    fprintf(out, "This class index: %x\n", c->this_class);
    fprintf(out, "Super class index: %x\n", c->super_class);
    fprintf(out, "Interface count: %x\n", c->interfaces_count);
    fprintf(out, "Fields count: %x\n", c->fields_count);
    for(int i = 0; i < c->fields_count; i++){
	print_field(c, c->fields[i], out);
    }


    fprintf(out, "Methods count: %x\n", c->methods_count);
    for(int i = 0; i < c->methods_count; i++){
	print_method(c, c->methods[i], out);
    }

    fprintf(out, "Attributes count: %x\n", c->attributes_count);
    for(int i = 0; i < c->attributes_count; i++){
	print_attribute(c, c->attributes[i], out);
    }
}

void cleanup_attribute(attribute_info* a){
    free(a->info);
    free(a);
}

void cleanup_constant(cp_info* cp){
    free(cp->info);
    free(cp);
}
void cleanup_field(field_info* f){
    for(int i = 0; i < f->attributes_count; i++){
	cleanup_attribute(f->attributes[i]);
    }
    free(f->attributes);
    free(f);
}


void cleanup_method(method_info* m){
    for(int i = 0; i < m->attributes_count; i++){
	cleanup_attribute(m->attributes[i]);
    }
    free(m->attributes);
    free(m->code->code);
    free(m->code);
    free(m);
}


void cleanup_classfile(classfile* c){
    for(int i = 0; i < c->constant_pool_count-1; i++){
	cleanup_constant(c->constant_pool[i]);
    }
    for(int i = 0; i < c->fields_count; i++){
	cleanup_field(c->fields[i]);
    }
    for(int i = 0; i < c->attributes_count; i++){
	cleanup_attribute(c->attributes[i]);
    }
    for(int i = 0; i < c->methods_count; i++){
	cleanup_method(c->methods[i]);
    }
    free(c->constant_pool);
    free(c->fields);
    free(c->methods);
    free(c->attributes);
    free(c);
    return;
}



classfile* read_classfile(FILE* f){
    classfile* c = malloc(sizeof(classfile));
    memcheck(c);
    c->magic = read32(f);
    c->minor_version = read16(f);
    c->major_version = read16(f);
    c->constant_pool_count = read16(f);
    c->constant_pool = malloc(sizeof(void*) * (c->constant_pool_count - 1));
    for(int i = 0; i < (c->constant_pool_count - 1); i++){
	c->constant_pool[i] = read_constant(i, f);
//	print_constant(c->constant_pool[i], stderr);
    }
    c->access_flags = read16(f);
    c->this_class = read16(f);
    c->super_class = read16(f);
    c->interfaces_count = read16(f);
    if(c->interfaces_count > 0){
	c->interfaces = malloc(sizeof(short) * c->interfaces_count);
	memcheck(c->interfaces);
	for(int i = 0; i < (c->interfaces_count); i++){
	    c->interfaces[i] = read16(f);
	}
    }
    c->fields_count = read16(f);
    if(c->fields_count > 0){
	c->fields = malloc(sizeof(void*) * c->fields_count);
	memcheck(c->fields);
	//have to read in the fields
	for(int i = 0; i < (c->fields_count); i++){
	    c->fields[i] = read_field(f);
	}
    } else
	c->fields = NULL;
    c->methods_count = read16(f);
    if(c->methods_count > 0){
	c->methods = malloc(sizeof(void*) * c->methods_count);
	memcheck(c->methods);
	for(int i = 0; i < (c->methods_count); i++){
	    c->methods[i] = read_method(c, f);
	}
    } else 
	c->methods = NULL;
    c->attributes_count = read16(f);
    if(c->attributes_count > 0){
	c->attributes = malloc(sizeof(void*) * c->attributes_count);
	memcheck(c->attributes);
	for(int i = 0; i < c->attributes_count; i++){
	    c->attributes[i] = read_attribute(f);
	}
    } else 
	c->attributes = NULL;

    int last = getc(f);
    assert(last == EOF);
    return c;
}

field_info* read_field(FILE* stream){
    field_info* f = malloc(sizeof(field_info));
    memcheck(f);
    f->access_flags = read16(stream);
    f->name_index = read16(stream);
    f->descriptor_index = read16(stream);
    f->attributes_count = read16(stream);
    if(f->attributes_count > 0){
	f->attributes = malloc(sizeof(void*) * f->attributes_count);
	memcheck(f->attributes);
	for(int i = 0; i < f->attributes_count; i++){
	    f->attributes[i] = read_attribute(stream);
	}
    } else 
	f->attributes = NULL;
    return f;
}

method_info* read_method(classfile* c, FILE* stream){
    method_info* m = malloc(sizeof(method_info));
    memcheck(m);
    m->access_flags = read16(stream);
    m->name_index = read16(stream);
    m->descriptor_index = read16(stream);
    m->attributes_count = read16(stream);
    m->code = NULL;
    //assert(m->attributes_count == 1);
    if(m->attributes_count > 0){
	m->attributes = malloc(sizeof(void*) * m->attributes_count);
	memcheck(m->attributes);
	for(int i = 0; i < m->attributes_count; i++){
	    m->attributes[i] = read_attribute(stream);
	    // look for the code attribute, and once it is found, build 
	    // a code object too.
	    char* name = get_constant_name(c, m->attributes[i]->name_index);
	    if(strcmp(name, "Code") == 0){
		//found the code attribute.
		m->code = malloc(sizeof(code_attribute));
		m->code->attribute_name_index = m->attributes[i]->name_index;
		m->code->attribute_length = m->attributes[i]->attribute_length;
		unsigned short s = 0;
		unsigned char* c = (unsigned char*) &s;
		c[1] = m->attributes[i]->info[0];
		c[0] = m->attributes[i]->info[1];
		m->code->max_stack = s;
		c[1] = m->attributes[i]->info[2];
		c[0] = m->attributes[i]->info[3];
		m->code->max_locals = s;
		unsigned int l = 0;
		c = (unsigned char*) &l;
		c[3] = m->attributes[i]->info[4];
		c[2] = m->attributes[i]->info[5];
		c[1] = m->attributes[i]->info[6];
		c[0] = m->attributes[i]->info[7];
		m->code->code_length = l;
		m->code->code = malloc(l);
		memcheck(m->code->code);
		memcpy((char*) m->code->code, (char*) m->attributes[i]->info + 8, l);
	    }
	}
    }
    return m;
}


attribute_info* read_attribute(FILE* stream){
    attribute_info* a = malloc(sizeof(attribute_info));
    memcheck(a);
    a->name_index = read16(stream);
    a->attribute_length = read32(stream);
    assert(a->attribute_length > 0);
    a->info = malloc(a->attribute_length + 1);
    memcheck(a->info);
    a->info[a->attribute_length] = 0;
    for(int i = 0; i < a->attribute_length; i++){
	a->info[i] = read8(stream);
    }
    return a;
}
