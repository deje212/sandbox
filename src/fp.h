#ifndef __FP_INCLUDED__
#define __FP_INCLUDED__

#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <values.h>

/* Em comparações de igualdade entre valores "grandes" (maiores que 1.0)
   a comparação "absoluta" é útil. */
#define IS_SFP_EQUAL_ABS(x,y) (fabs((x) - (y)) < FLT_EPSILON)
#define IS_DFP_EQUAL_ABS(x,y) (fabs((x) - (y)) < DBL_EPSILON)

/* Em comparações de igualdade entre valores "pequenos" (entre 0.0 e 1.0)
   a caomparação "relativa" é mais eficaz. */
#define IS_SFP_EQUAL_REL(x,y) ((fabs((x) - (y)) < max(fabs((x)), fabs((y))) * FLT_EPSILON)
#define IS_DFP_EQUAL_REL(x,y) ((fabs((x) - (y)) < max(fabs((x)), fabs((y))) * DBL_EPSILON)

/* typedef para união que permite "desmantelar" o tipo "float". */
typedef union {
	float f;
	int32_t i32;
	struct {
		unsigned int mantissa:23;
		unsigned int expoent:8;
		unsigned int sign:1;
	} s;
} sfp_t;

/* typedef para união que permite "desmantelar" o tipo "double". */
typedef union {
	double d;
	int64_t i64;
	struct {
		unsigned long long mantissa:53;
		unsigned int expoent:10;
		unsigned int sign:1;
	} s;
} dfp_t;

/* Comparações via UPLs */
int sfp_compare_upls(float x, float y);
int dfp_compare_upls(double x, double y);

#endif
