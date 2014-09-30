#ifndef CLASSFILE_H
#define CLASSFILE_H

#include <stdio.h>

typedef struct {
    unsigned char tag;
    short cp_length;
    unsigned char* info;
} cp_info ;

typedef struct {
    short name_index;
    int attribute_length;
    unsigned char* info;
} attribute_info;

typedef struct {
    short attribute_name_index;
    int attribute_length;
    short max_stack;
    short max_locals;
    int code_length;
    unsigned char* code;
} code_attribute;

typedef struct {
    short             access_flags;
    short             name_index;
    short             descriptor_index;
    short             attributes_count;
    attribute_info**  attributes;
} field_info;

typedef struct {
    short             access_flags;
    short             name_index;
    short             descriptor_index;
    short             attributes_count;
    attribute_info**  attributes;
    code_attribute*   code;
} method_info;

typedef struct {
    unsigned int      magic;
    short             minor_version;
    short             major_version;
    short             constant_pool_count;
    cp_info**         constant_pool;
    short             access_flags;
    short             this_class;
    short             super_class;
    short             interfaces_count;
    short*            interfaces;
    short             fields_count;
    field_info**      fields;
    short             methods_count;
    method_info**     methods;
    short             attributes_count;
    attribute_info**  attributes;
} classfile;


classfile* read_classfile(FILE* stream);
void print_classfile(classfile* c, FILE* out);
void cleanup_classfile(classfile* c);
char* get_constant_name(classfile* cf, int index);
void print_attribute(classfile* cf, attribute_info* a, FILE* out);

#endif
