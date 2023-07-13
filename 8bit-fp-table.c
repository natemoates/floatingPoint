/* Nathaniel Oates
 * CPSC 2311 : Section 001
 * Lab 11 : Floating Point
 * 06/22/23
*/

#include <stdio.h>	

int main()	
{	
    int sign, exp, fraction, significand;	
    int i;	
    float f;	
    float prev = 0;	
    for (i = 0; i < 256; i++)	
    {	
        /* begin your code */	
        sign = (i >> 7) & 1;                          // extract sign bit	
        exp = (i >> 3) & 0x0F;                        // extract exponent bits	
        fraction = i & 0x07;                          // extract fraction bits		
        if (exp == 0 && fraction == 0)                // handle special cases (zero and subnormals)	
        {	
            f = sign ? -0.0f : 0.0f;	
        }	
	else if (exp == 0 && fraction != 0)	
        {    
	    significand = fraction;	
            f = sign ? -1.0f : 1.0f;
            int bias = 8;                             // exponent bias for 4-bit floating point
            exp = 1 - bias;                           // convert exponent from bias notation to signed
            while (exp < 0)
            {
                f /= 2.0f;
                exp++;
            }
            f *= significand / 8.0f;
        }	
        else                                          // normal numbers
        {   
	    significand = (1 << 3) | fraction;        // set the leading 1 in significand
            f = sign ? -1.0f : 1.0f;	
            int bias = 8;                             // exponent bias for 4-bit floating point
            exp = exp - bias;                         // convert exponent from bias notation to signed
            while (exp > 0)	
            {	
                f *= 2.0f;	
                exp--;	
            }	
            while (exp < 0)	
            {	
                f /= 2.0f;	
                exp++;	
            }	
            f *= significand / 8.0f;	
        }	
        /* end your code */	
        printf("%02x => %08x = %+11.6f (spacing = %+11.6f)\n",	
               i, *(int*) &f, f, prev - f);	
        prev = f;	
    }	
    return 0;
}
