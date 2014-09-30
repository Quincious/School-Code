/*
Jonathan Hart
9/18/2013
Lab4
*/

#include "convert.h" 
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <assert.h>
#include <stdbool.h>

int RoundUp(unsigned long mantissa, long shiftAmount)
{
	long *bits = malloc(sizeof(long) * (shiftAmount+1));
	int LSBKeptChecked = 0;
	int LSBKept;
	int MSBDroppedChecked = 0;
	int MSBDropped;

	bits[0] = (mantissa >> shiftAmount) & 1;

	for(int k = 1; k < shiftAmount; k++)
	{
		int mask =  1 << k;
		int masked_mant = mantissa & mask;
		int thebit = masked_mant >> k;
		bits[k] = thebit;
	}

	for(int i = (shiftAmount); i >= 0; i--)
	{
		if(LSBKeptChecked == 0)
			LSBKept = bits[i];
		else if(MSBDroppedChecked == 0)
		{
			MSBDropped = bits[i];
			if(MSBDropped == 0)
			{
				free(bits);
				return 0;
			}
			else if(MSBDropped == 1 && LSBKept == 1)
			{
				free(bits);
				return 1;
			}
		}
		else
		{
			if(bits[i] == 1)
			{
				free(bits);
				return 1;
			}
		}
	}

	free(bits);
	return 0;
}
double long_to_double(signed long l)
{	
	unsigned long sign;
	unsigned long exponent;
	unsigned long mantissa;
	unsigned long magnitude;
	
	if(l == 0 )
	{
		return 0.0d;
	}	
	else if(l > DBL_MAX || l < DBL_MIN)
	{
		return  0x8000000000000000;
	}
	else if(l < 0)
	{
		long l2 = l;
		l2 = ~l2;
		l2 += 1;
		
		sign = 1;
		sign = sign << 63;
		magnitude = l2 & 0x7FFFFFFFFFFFFFFF;		
	}
	else
	{
		sign = 0;
		magnitude = l;
	}
	
	long longForExponent = magnitude;
	
	int count;
	
	for(count = 0; count <= 64; count++)
	{
		if(longForExponent >= 0)
			longForExponent = longForExponent << 1;
		else
			break;
	}

	long HBS; //highest bit set
	HBS = 64 - (count + 1);
	exponent = HBS + 1023;
	exponent = exponent << 52;		

	if(HBS <= 52)
	{
		mantissa = magnitude << (52 - HBS);
		mantissa = mantissa & 0xFFFFFFFFFFFFF;
	}
	else
	{
		int rounding = RoundUp(magnitude, (HBS - 52));
				
		mantissa = magnitude >> (HBS - 52);

		if(rounding == 1)
		{
			mantissa++;

			if((mantissa >> 52) == 1)
			{
				exponent++;	
				mantissa = mantissa >> 1;
			}
		}
			
		mantissa = mantissa & 0xFFFFFFFFFFFFF;		
	}		
	
	unsigned long result = sign | exponent | mantissa;

	return *((double*)&result);
}
signed long double_to_long(double d)
{	
	if(d == 0)
	{
		return 0l;
	}
	else if(isinf(d) || isnan(d))
	{
		assert(false);
	}
	else if((d > 0 && d < 1) || (d < 0 && d > -1))
	{
		return 0l;
	}
	else
	{
		unsigned long sign;
		unsigned long exponent;
		unsigned long mantissa;
		
		unsigned long longForSign = *((unsigned long*) &d);
		unsigned long longForExp = *((unsigned long*) &d);
		unsigned long longForMant = *((unsigned long*) &d);	
		
		sign = longForSign >> 63;
		
		longForExp = longForExp >> 52;
		longForExp = longForExp & 0x7FF;
			
		exponent = (long)longForExp - 1023;		
				
		longForMant = longForMant & 0x000FFFFFFFFFFFFF;		
		
		mantissa = longForMant | 0x0010000000000000;	
		
		long returnAmount = 0;

		if(exponent >= 52)
		{
			long shiftAmount = exponent - 52;
			if(shiftAmount < 11)
				returnAmount = mantissa << shiftAmount;
			else
				return 0x8000000000000000l;
		}
		else
		{
			returnAmount = mantissa >> (52 - exponent);
		}
		
		if(sign == 1)
			returnAmount *= -1;
		
		return returnAmount;
	}
}
