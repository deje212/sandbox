#include "fp.h"

int sfp_compare_upls(float x, float y)
{
	sfp_t xfp, yfp;

	xfp.f = x;
	yfp.f = y;

	if (xfp.s.sign != yfp.s.sign)
		return 0;

	return abs(xfp.i32 - yfp.i32) < 2;
}

int dfp_compare_upls(double x, double y)
{
	dfp_t xfp, yfp;

	xfp.d = x;
	yfp.d = y;

	if (xfp.s.sign != yfp.s.sign)
		return 0;

	return llabs(xfp.i64 - yfp.i64) < 2;
}

