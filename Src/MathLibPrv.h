/* MathLib: Pilot shared library of IEEE-754 double math functions
 *
 * Private declarations for use only within MathLib source code.
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
 * Version 1.01, 23 August 1997, Rick Huebner
 */
#ifndef __MATHLIBPRV_H__
#define __MATHLIBPRV_H__

// Our global data structure
typedef struct MathLibData {
	UInt16 usecount;
} MathLibData;

// Control function prototypes
Err __Startup__(UInt16 refnum, SysLibTblEntryPtr entryP);
MemPtr *DispatchTable(void);

Err mathlib_open(UInt16 refnum, UInt16 version);
Err mathlib_close(UInt16 refnum, UInt16* numappsP);
Err mathlib_sleep(UInt16 refnum);
Err mathlib_wake(UInt16 refnum);

// Dispatch table jmp target/GCC encapsulation prototypes
Err mathlib_acos(UInt16 refnum, double x, double *result);
Err mathlib_asin(UInt16 refnum, double x, double *result);
Err mathlib_atan(UInt16 refnum, double x, double *result);
Err mathlib_atan2(UInt16 refnum, double y, double x, double *result);
Err mathlib_cos(UInt16 refnum, double x, double *result);
Err mathlib_sin(UInt16 refnum, double x, double *result);
Err mathlib_tan(UInt16 refnum, double x, double *result);
Err mathlib_sincos(UInt16 refnum, double x, double *sinx, double *cosx);
Err mathlib_cosh(UInt16 refnum, double x, double *result);
Err mathlib_sinh(UInt16 refnum, double x, double *result);
Err mathlib_tanh(UInt16 refnum, double x, double *result);
Err mathlib_acosh(UInt16 refnum, double x, double *result);
Err mathlib_asinh(UInt16 refnum, double x, double *result);
Err mathlib_atanh(UInt16 refnum, double x, double *result);
Err mathlib_exp(UInt16 refnum, double x, double *result);
Err mathlib_frexp(UInt16 refnum, double x, double *fraction, Int16 *exponent);
Err mathlib_ldexp(UInt16 refnum, double x, Int16 exponent, double *result);
Err mathlib_log(UInt16 refnum, double x, double *result);
Err mathlib_log10(UInt16 refnum, double x, double *result);
Err mathlib_modf(UInt16 refnum, double x, double *intpart, double *fracpart);
Err mathlib_expm1(UInt16 refnum, double x, double *result);
Err mathlib_log1p(UInt16 refnum, double x, double *result);
Err mathlib_logb(UInt16 refnum, double x, double *result);
Err mathlib_log2(UInt16 refnum, double x, double *result);
Err mathlib_pow(UInt16 refnum, double x, double y, double *result);
Err mathlib_sqrt(UInt16 refnum, double x, double *result);
Err mathlib_hypot(UInt16 refnum, double x, double y, double *result);
Err mathlib_cbrt(UInt16 refnum, double x, double *result);
Err mathlib_ceil(UInt16 refnum, double x, double *result);
Err mathlib_fabs(UInt16 refnum, double x, double *result);
Err mathlib_floor(UInt16 refnum, double x, double *result);
Err mathlib_fmod(UInt16 refnum, double x, double y, double *result);
Err mathlib_isinf(UInt16 refnum, double x, Int16 *result);
Err mathlib_finite(UInt16 refnum, double x, Int16 *result);
Err mathlib_scalbn(UInt16 refnum, double x, Int16 exponent, double *result);
Err mathlib_drem(UInt16 refnum, double x, double y, double *result);
Err mathlib_significand(UInt16 refnum, double x, double *result);
Err mathlib_copysign(UInt16 refnum, double x, double y, double *result);
Err mathlib_isnan(UInt16 refnum, double x, Int16 *result);
Err mathlib_ilogb(UInt16 refnum, double x, Int16 *result);
Err mathlib_rint(UInt16 refnum, double x, double *result);
Err mathlib_nextafter(UInt16 refnum, double x, double y, double *result);
Err mathlib_remainder(UInt16 refnum, double x, double y, double *result);
Err mathlib_scalb(UInt16 refnum, double x, double exponent, double *result);
Err mathlib_round(UInt16 refnum, double x, double *result);
Err mathlib_trunc(UInt16 refnum, double x, double *result);
Err mathlib_signbit(UInt16 refnum, double x, UInt32 *result);

#endif // __MATHLIBPRV_H__
