/* MathLib: Pilot shared library of IEEE-754 double math functions
 *
 * Main library entry point and control routines; see file shlib.htm
 * (many thanks to Ian Goldberg) for details on how shared libraries
 * are structured and controlled.  This module is written for the
 * MetroWerks CodeWarrior C compiler, and will require significant
 * changes to compile cleanly with anything else.
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
 * Version 1.1.01, 6 February 2003, Rick Huebner
 *    Tweaked main entry point to use Entry Point setting in 68K Target control panel instead
 *    of hijacking default entry point name as required by older CodeWarrior compilers.
 *    No executable code changes.
 */
#include <PalmOS.h>
//#include <SysAll.h>

#include "MathLib.h"
#include "MathLibPrv.h"

// Convenient macros for defining the dispatch table (below)
#define NFUNCS				51	// Number of entry points in library
#define SIZEOF_OFFSET		sizeof(UInt16)
#define SIZEOF_OFFSET_TABLE	((1+NFUNCS) * SIZEOF_OFFSET)	// for name, plus one per function
#define SIZEOF_JMP			4	// Memory model/platform dependent

#define LIBENTRY_OFFSET(x)	(SIZEOF_OFFSET_TABLE + x * SIZEOF_JMP)
#define LIBNAME_OFFSET		(SIZEOF_OFFSET_TABLE + NFUNCS * SIZEOF_JMP)

Err LibMain(UInt16 refnum, SysLibTblEntryPtr entryP);



/* Main entry point of the library, automatically invoked by the
 * OS when the library is loaded.  Fills in the SysLibTblEntry
 * structure passed by the OS to publish the address of
 * our dispatch table.
 */
Err LibMain(UInt16 refnum, SysLibTblEntryPtr entryP) {
#pragma unused(refnum)
	// Install pointer to our dispatch table
	entryP->dispatchTblP = DispatchTable();
	
	// Initialize globals handle to zero until mathlib_open called
	entryP->globalsP = 0;
	
	return mlErrNone;
}



/* Library dispatch table.  Offset of library name, followed
 * by offset of each function's jmp instruction, followed by
 * a jmp for each function, followed by the library name used
 * for SysLibFind() calls.
 */
asm MemPtr *DispatchTable(void) {
	lea		table, a0
	rts

table:
	dc.w	LIBNAME_OFFSET
	dc.w	LIBENTRY_OFFSET(0)	// Must start from 0
	dc.w	LIBENTRY_OFFSET(1)
	dc.w	LIBENTRY_OFFSET(2)
	dc.w	LIBENTRY_OFFSET(3)
	dc.w	LIBENTRY_OFFSET(4)
	dc.w	LIBENTRY_OFFSET(5)
	dc.w	LIBENTRY_OFFSET(6)
	dc.w	LIBENTRY_OFFSET(7)
	dc.w	LIBENTRY_OFFSET(8)
	dc.w	LIBENTRY_OFFSET(9)
	dc.w	LIBENTRY_OFFSET(10)
	dc.w	LIBENTRY_OFFSET(11)
	dc.w	LIBENTRY_OFFSET(12)
	dc.w	LIBENTRY_OFFSET(13)
	dc.w	LIBENTRY_OFFSET(14)
	dc.w	LIBENTRY_OFFSET(15)
	dc.w	LIBENTRY_OFFSET(16)
	dc.w	LIBENTRY_OFFSET(17)
	dc.w	LIBENTRY_OFFSET(18)
	dc.w	LIBENTRY_OFFSET(19)
	dc.w	LIBENTRY_OFFSET(20)
	dc.w	LIBENTRY_OFFSET(21)
	dc.w	LIBENTRY_OFFSET(22)
	dc.w	LIBENTRY_OFFSET(23)
	dc.w	LIBENTRY_OFFSET(24)
	dc.w	LIBENTRY_OFFSET(25)
	dc.w	LIBENTRY_OFFSET(26)
	dc.w	LIBENTRY_OFFSET(27)
	dc.w	LIBENTRY_OFFSET(28)
	dc.w	LIBENTRY_OFFSET(29)
	dc.w	LIBENTRY_OFFSET(30)
	dc.w	LIBENTRY_OFFSET(31)
	dc.w	LIBENTRY_OFFSET(32)
	dc.w	LIBENTRY_OFFSET(33)
	dc.w	LIBENTRY_OFFSET(34)
	dc.w	LIBENTRY_OFFSET(35)
	dc.w	LIBENTRY_OFFSET(36)
	dc.w	LIBENTRY_OFFSET(37)
	dc.w	LIBENTRY_OFFSET(38)
	dc.w	LIBENTRY_OFFSET(39)
	dc.w	LIBENTRY_OFFSET(40)
	dc.w	LIBENTRY_OFFSET(41)
	dc.w	LIBENTRY_OFFSET(42)
	dc.w	LIBENTRY_OFFSET(43)
	dc.w	LIBENTRY_OFFSET(44)
	dc.w	LIBENTRY_OFFSET(45)
	dc.w	LIBENTRY_OFFSET(46)
	dc.w	LIBENTRY_OFFSET(47)
	dc.w	LIBENTRY_OFFSET(48)
	dc.w	LIBENTRY_OFFSET(49)
	dc.w	LIBENTRY_OFFSET(50)	// NFUNCS must equal this index + 1
	jmp		mathlib_open	// These must match the sequence in MathLib.h
	jmp		mathlib_close
	jmp		mathlib_sleep
	jmp		mathlib_wake
	jmp		mathlib_acos
	jmp		mathlib_asin
	jmp		mathlib_atan
	jmp		mathlib_atan2
	jmp		mathlib_cos
	jmp		mathlib_sin
	jmp		mathlib_tan
	jmp		mathlib_sincos
	jmp		mathlib_cosh
	jmp		mathlib_sinh
	jmp		mathlib_tanh
	jmp		mathlib_acosh
	jmp		mathlib_asinh
	jmp		mathlib_atanh
	jmp		mathlib_exp
	jmp		mathlib_frexp
	jmp		mathlib_ldexp
	jmp		mathlib_log
	jmp		mathlib_log10
	jmp		mathlib_modf
	jmp		mathlib_expm1
	jmp		mathlib_log1p
	jmp		mathlib_logb
	jmp		mathlib_log2
	jmp		mathlib_pow
	jmp		mathlib_sqrt
	jmp		mathlib_hypot
	jmp		mathlib_cbrt
	jmp		mathlib_ceil
	jmp		mathlib_fabs
	jmp		mathlib_floor
	jmp		mathlib_fmod
	jmp		mathlib_isinf
	jmp		mathlib_finite
	jmp		mathlib_scalbn
	jmp		mathlib_drem
	jmp		mathlib_significand
	jmp		mathlib_copysign
	jmp		mathlib_isnan
	jmp		mathlib_ilogb
	jmp		mathlib_rint
	jmp		mathlib_nextafter
	jmp		mathlib_remainder
	jmp		mathlib_scalb
	jmp		mathlib_round
	jmp		mathlib_trunc
	jmp		mathlib_signbit
	dc.b	MathLibName
}



/* Called by the application to validate the library's version number
 * and prepare it for use.
 */
Err mathlib_open(UInt16 refnum, UInt16 version) {
	SysLibTblEntryPtr entryP;
	MemHandle mlh;
	MathLibData *mld = NULL;

	// Fail if the calling program is expecting a higher version
	// of the library than it's really opening; this protects the
	// program from accidentally using a version of MathLib which
	// doesn't include all the functions it needs.  Version numbers
	// less than ours are OK, since presumably we still have all the
	// old functions from that version available.
	if (version > MathLibVersion)
		return mlErrOldVersion;

	// Get our global data handle from the OS			
	entryP = SysLibTblEntry(refnum);
	mlh = (MemHandle)entryP->globalsP;
	
	// If we've already set up our globals, just increment the use count
	if (mlh) {
		mld = MemHandleLock(mlh);
		++mld->usecount;
	// Otherwise, allocate space for the globals and initialize them
	} else {
		mlh = MemHandleNew(sizeof(MathLibData));
		if (!mlh)
			return mlErrNoMemory;
		entryP->globalsP = (void *)mlh;
		mld = MemHandleLock(mlh);
		// By default, all allocated memory belongs to the app that was
		// running when it was allocated, and is freed automatically
		// when that app closes.  By changing the owner of this memory
		// hunk to 0 (the OS), it won't be freed until we say so.
		MemPtrSetOwner(mld, 0);
		mld->usecount = 1;
	}
	MemHandleUnlock(mlh);
	
	return mlErrNone;
}



/* Called by the application to release any resources used, and to
 * get the current use count to determine if SysLibRemove() should
 * be called.
 */
Err mathlib_close(UInt16 refnum, UInt16* usecountP) {
	SysLibTblEntryPtr entryP;
	MemHandle mlh;
	MathLibData *mld;
	
	// Get our global data pointer from the OS			
	entryP = SysLibTblEntry(refnum);
	mlh = (MemHandle)entryP->globalsP;
	
	// If globals aren't set up, we've haven't been opened yet
	if (!mlh)
		return mlErrNotOpen;

	// Decrement use count; if this makes it zero, free our globals		
	mld = MemHandleLock(mlh);
	*usecountP = --mld->usecount;
	MemHandleUnlock(mlh);
	
	if (!*usecountP) {
		MemHandleFree(mlh);
		entryP->globalsP = 0;
	}
	
	return mlErrNone;
}



/* Called by OS when Pilot sleeps.  We don't care.
 */
Err mathlib_sleep(UInt16 refnum) {
#pragma unused(refnum)
	return mlErrNone;
}



/* Called by OS when Pilot wakes.  We don't care.
 */
Err mathlib_wake(UInt16 refnum) {
#pragma unused(refnum)
	return mlErrNone;
}
