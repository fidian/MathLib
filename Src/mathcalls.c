/* MathLib: Pilot shared library of IEEE-754 double math functions
 *
 * Jump target stub routines called from the library's dispatch table.
 * These routines serve two important functions:
 *    1.  They encapsulate the GCC math routines, translating the
 *        function call format as required for invocation through
 *        the OS library SYS_TRAP() interface.  This allows us to
 *        leave the GCC source code largely untouched, for easier
 *        inclusion of future GCC updates.
 *    2.  By cleverly controlling the way the library is linked so
 *        that these routines end up being placed somewhere around
 *        the middle of the code segment, they provide a way to
 *        get around the 32KB code segment size limit.  The 32KB code
 *        limit is caused by the limited range of a 68000 pc-relative
 *        'jmp' instruction, which can only jump +/-32KB.  Since
 *        the dispatch table at the start of our library has to do a
 *        jmp anyway, we put these intermediate routines in the middle,
 *        and now from here we can jump 32KB in *either* direction.
 *        This lets us get by with having almost 64KB of code.
 *
 * Copyright (C) 1997 Rick Huebner
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Library General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this program; see file COPYING.LIB.  If not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA
 *
 * Version 1.0, 15 August 1997, Rick Huebner
 */
#include <PalmOS.h>
//#include <SysAll.h>

#include "MathLib.h"
#include "MathLibPrv.h"
#include "math.h"



// Special "jump island" routines, used to provide a bridge when
// a routine near one end of our oversized code segment has to call
// a routine near the other end.  The need for these rest stops has
// been minimized by trying to arrange our code segment for good
// locality of reference.
double jumpto__ieee754_sqrt(double x) {
	return __ieee754_sqrt(x);
}

double jumpto__fabs(double x) {
	return __fabs(x);
}

double jumpto__scalbn(double x, int n) {
	return __scalbn(x, n);
}



// Jump target/GCC encapsulation stub routines
Err mathlib_acos(UInt16 refnum, double x, double *result) {
#pragma unused(refnum)
	*result = __ieee754_acos(x);
	return mlErrNone;
}

Err mathlib_asin(UInt16 refnum, double x, double *result) {
#pragma unused(refnum)
	*result = __ieee754_asin(x);
	return mlErrNone;
}

Err mathlib_atan(UInt16 refnum, double x, double *result) {
#pragma unused(refnum)
	*result = __atan(x);
	return mlErrNone;
}

Err mathlib_atan2(UInt16 refnum, double y, double x, double *result) {
#pragma unused(refnum)
	*result = __ieee754_atan2(y, x);
	return mlErrNone;
}

Err mathlib_cos(UInt16 refnum, double x, double *result) {
#pragma unused(refnum)
	*result = __cos(x);
	return mlErrNone;
}

Err mathlib_sin(UInt16 refnum, double x, double *result) {
#pragma unused(refnum)
	*result = __sin(x);
	return mlErrNone;
}

Err mathlib_tan(UInt16 refnum, double x, double *result) {
#pragma unused(refnum)
	*result = __tan(x);
	return mlErrNone;
}

Err mathlib_sincos(UInt16 refnum, double x, double *sinx, double *cosx) {
#pragma unused(refnum)
	__sincos(x, sinx, cosx);
	return mlErrNone;
}

Err mathlib_cosh(UInt16 refnum, double x, double *result) {
#pragma unused(refnum)
	*result = __ieee754_cosh(x);
	return mlErrNone;
}

Err mathlib_sinh(UInt16 refnum, double x, double *result) {
#pragma unused(refnum)
	*result = __ieee754_sinh(x);
	return mlErrNone;
}

Err mathlib_tanh(UInt16 refnum, double x, double *result) {
#pragma unused(refnum)
	*result = __tanh(x);
	return mlErrNone;
}

Err mathlib_acosh(UInt16 refnum, double x, double *result) {
#pragma unused(refnum)
	*result = __ieee754_acosh(x);
	return mlErrNone;
}

Err mathlib_asinh(UInt16 refnum, double x, double *result) {
#pragma unused(refnum)
	*result = __asinh(x);
	return mlErrNone;
}

Err mathlib_atanh(UInt16 refnum, double x, double *result) {
#pragma unused(refnum)
	*result = __ieee754_atanh(x);
	return mlErrNone;
}

Err mathlib_exp(UInt16 refnum, double x, double *result) {
#pragma unused(refnum)
	*result = __ieee754_exp(x);
	return mlErrNone;
}

Err mathlib_frexp(UInt16 refnum, double x, double *fraction, Int16 *exponent) {
#pragma unused(refnum)
	int exp;
	*fraction = __frexp(x, &exp);
	*exponent = exp;
	return mlErrNone;
}

Err mathlib_ldexp(UInt16 refnum, double x, Int16 exponent, double *result) {
#pragma unused(refnum)
	*result = __ldexp(x, exponent);
	return mlErrNone;
}

Err mathlib_log(UInt16 refnum, double x, double *result) {
#pragma unused(refnum)
	*result = __ieee754_log(x);
	return mlErrNone;
}

Err mathlib_log10(UInt16 refnum, double x, double *result) {
#pragma unused(refnum)
	*result = __ieee754_log10(x);
	return mlErrNone;
}

Err mathlib_modf(UInt16 refnum, double x, double *intpart, double *fracpart) {
#pragma unused(refnum)
	*fracpart = __modf(x, intpart);
	return mlErrNone;
}

Err mathlib_expm1(UInt16 refnum, double x, double *result) {
#pragma unused(refnum)
	*result = __expm1(x);
	return mlErrNone;
}

Err mathlib_log1p(UInt16 refnum, double x, double *result) {
#pragma unused(refnum)
	*result = __log1p(x);
	return mlErrNone;
}

Err mathlib_logb(UInt16 refnum, double x, double *result) {
#pragma unused(refnum)
	*result = __logb(x);
	return mlErrNone;
}

Err mathlib_log2(UInt16 refnum, double x, double *result) {
#pragma unused(refnum)
	*result = __log2(x);
	return mlErrNone;
}

Err mathlib_pow(UInt16 refnum, double x, double y, double *result) {
#pragma unused(refnum)
	*result = __ieee754_pow(x, y);
	return mlErrNone;
}

Err mathlib_sqrt(UInt16 refnum, double x, double *result) {
#pragma unused(refnum)
	*result = __ieee754_sqrt(x);
	return mlErrNone;
}

Err mathlib_hypot(UInt16 refnum, double x, double y, double *result) {
#pragma unused(refnum)
	*result = __ieee754_hypot(x, y);
	return mlErrNone;
}

Err mathlib_cbrt(UInt16 refnum, double x, double *result) {
#pragma unused(refnum)
	*result = __cbrt(x);
	return mlErrNone;
}

Err mathlib_ceil(UInt16 refnum, double x, double *result) {
#pragma unused(refnum)
	*result = __ceil(x);
	return mlErrNone;
}

Err mathlib_fabs(UInt16 refnum, double x, double *result) {
#pragma unused(refnum)
	*result = __fabs(x);
	return mlErrNone;
}

Err mathlib_floor(UInt16 refnum, double x, double *result) {
#pragma unused(refnum)
	*result = __floor(x);
	return mlErrNone;
}

Err mathlib_fmod(UInt16 refnum, double x, double y, double *result) {
#pragma unused(refnum)
	*result = __ieee754_fmod(x, y);
	return mlErrNone;
}

Err mathlib_isinf(UInt16 refnum, double x, Int16 *result) {
#pragma unused(refnum)
	*result = __isinf(x);
	return mlErrNone;
}

Err mathlib_finite(UInt16 refnum, double x, Int16 *result) {
#pragma unused(refnum)
	*result = __finite(x);
	return mlErrNone;
}

Err mathlib_scalbn(UInt16 refnum, double x, Int16 exponent, double *result) {
#pragma unused(refnum)
	*result = __scalbn(x, exponent);
	return mlErrNone;
}

Err mathlib_drem(UInt16 refnum, double x, double y, double *result) {
#pragma unused(refnum)
	*result = __ieee754_remainder(x, y);
	return mlErrNone;
}

Err mathlib_significand(UInt16 refnum, double x, double *result) {
#pragma unused(refnum)
	*result = __significand(x);
	return mlErrNone;
}

Err mathlib_copysign(UInt16 refnum, double x, double y, double *result) {
#pragma unused(refnum)
	*result = __copysign(x, y);
	return mlErrNone;
}

Err mathlib_isnan(UInt16 refnum, double x, Int16 *result) {
#pragma unused(refnum)
	*result = __isnan(x);
	return mlErrNone;
}

Err mathlib_ilogb(UInt16 refnum, double x, Int16 *result) {
#pragma unused(refnum)
	*result = __ilogb(x);
	return mlErrNone;
}

Err mathlib_rint(UInt16 refnum, double x, double *result) {
#pragma unused(refnum)
	*result = __rint(x);
	return mlErrNone;
}

Err mathlib_nextafter(UInt16 refnum, double x, double y, double *result) {
#pragma unused(refnum)
	*result = __nextafter(x, y);
	return mlErrNone;
}

Err mathlib_remainder(UInt16 refnum, double x, double y, double *result) {
#pragma unused(refnum)
	*result = __ieee754_remainder(x, y);
	return mlErrNone;
}

Err mathlib_scalb(UInt16 refnum, double x, double exponent, double *result) {
#pragma unused(refnum)
	*result = __ieee754_scalb(x, exponent);
	return mlErrNone;
}

Err mathlib_round(UInt16 refnum, double x, double *result) {
#pragma unused(refnum)
	*result = __round(x);
	return mlErrNone;
}

Err mathlib_trunc(UInt16 refnum, double x, double *result) {
#pragma unused(refnum)
	*result = __trunc(x);
	return mlErrNone;
}

Err mathlib_signbit(UInt16 refnum, double x, UInt32 *result) {
#pragma unused(refnum)
	*result = __signbit(x);
	return mlErrNone;
}
