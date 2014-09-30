/*
	Jonathan Hart
	Lab3
	9/11/13	
*/

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

fp_struct dissect_double(double d)
{
	fp_struct fps;
	unsigned long longForSign = *((unsigned long*) &d);
	unsigned long longForExp = *((unsigned long*) &d);
	unsigned long longForMant = *((unsigned long*) &d);	
	
	fps.sign = longForSign >> 63;
	
	longForExp = longForExp >> 52;
	longForExp = longForExp & 0x7FF;
		
	fps.exponent = (int)longForExp - 1023;		
		
	longForMant = longForMant & 0x000FFFFFFFFFFFFF;
	
	if(longForMant != 0)
		fps.mantissa = longForMant | 0x0010000000000000;	
	else
		fps.mantissa = 0;
		
	return fps;
}
long_struct dissect_long(long l)
{
	long_struct ls;
	
	if((l >> 63) != 0)
	{
		long l2 = l;
		l2 = ~l2;
		l2 += 1;
		
		ls.sign = 1;
		ls.magnitude = l2 & 0x7FFFFFFFFFFFFFFF;
	}
	else
	{
		ls.sign = 0;
		ls.magnitude = l;
	}
	
	return ls;
}

#endif