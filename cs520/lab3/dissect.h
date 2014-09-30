#ifndef DISSECT_H
#define DISSECT_H

typedef struct {
    int sign;
    int exponent;
    long mantissa;
} fp_struct;

typedef struct {
    int sign;
    long magnitude;
} long_struct;

fp_struct dissect_double(double d);
long_struct dissect_long(long l);

#endif
