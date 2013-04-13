MathLib
=======

This is a git mirror of MathLib, the shared Palm OS math library.  Since it was difficult to find, Tyler (fidian) has pulled together what he could find and placed it into a GitHub repository.

None of the code is from Tyler.

Original Information
====================

Last updated March 24th, 2005. Email questions and comments to me at rhuebner@radiks.net.

Description
-----------

MathLib is a PalmOS shared library which makes a complete set of IEEE-754 double-precision math functions available to other PalmPilot applications. These functions include all the standard routines normally accessed by including "`math.h`" on other systems, including trigonometry (with inverse and hyperbolic), logarithms, exponentiation, and miscellaneous helper functions. The only standard routines I left out were the Bessel and Gamma functions, which had the poor taste to be both very large and very rarely used. These routines have been ported from the GCC 2.7.2.2 source code for `libm.a` (which was itself based on free code originally developed by Sun Microsystems, Inc.), so this library is free software covered by the GNU Library General Public License.

There are two main advantages to using this library. Firstly, writing floating-point math functions that are reasonably fast, accurate, and robust is so incredibly difficult that few programmers will manage it on their own; hopefully, this library will spark the availability of many new programs for the Pilot that were impossible before. And secondly, as you can see from the size of this thing, floating-point code on the Pilot takes up a lot of space. It's much better to have a single copy shared between all the programs that need it than to have each application include their own. How many copies of the trig functions (at 20 or 30 KB each) do you really want on your Pilot?

Many thanks to Ian Goldberg of Berkeley's ISAAC Group for the excellent treatise on Pilot shared libraries that made this project possible. You should read and understand that document completely before you even think about making any changes to this library, but it's not really necessary if you just want to call the library from your program.

Note: Due to a fundamental constraint of the `NewFloatMgr.lib` floating point emulation library, MathLib requires version 2.0 or greater of the OS. The problem is that the floating point emulation library (which must be used in order to do IEEE 754 math under OS 1.x) requires the global variable `__SoftFPSCR__`, and SysLib-style shared libraries can't have any global variables. GLib-style libraries are supposed to support globals, but can only be built or used with GCC, and I needed this library to be usable by applications written with the CodeWarrior compiler (namely MathPad and Parens). If anyone comes up with a way to build and call shared libraries using CodeWarrior on my Win98 system that will let me use the `NewFloatMgr` routines under OS 1.x, please let me know.

Need more info? Check out the user's manual.

Maintenance Notes
-----------------

**24 March 2005**: Added MathLib.gcc.zip for Linux and/or GCC users.

**6 February 2003**: Corrected licensing of `MathLib.c` file, and changed `startup.c` to use Entry Point setting in 68K Target control panel. No executable code changes.

**1 August 2001**: Updated web page address.

**2 May 2001**: Updated to use Palm OS 4.0 SDK.

**Version 1.1, 13 April 1999**: Updated the code for `s_cbrt.c` and `s_modf.c` to match what's being used in GNU libc 2.0. This fixes a problem with the cube root function that caused it to give invalid results for values from 0.5 to 1.0. The library has also shrunk by about 5KB, due to improved optimization in the latest version of the CodeWarrior compiler.

**Version 1.02, 13 July 1998**: Corrected the documentation and some source code comments to more correctly identify the use of the GNU *Library* General Public License instead of the plain old regular General Public License. No code changes.

**Version 1.01, 24 August 1997**: Changed the convenience wrapper functions from inline declarations to standard functions in their own source file, due to CodeWarrior problems with the inline routines. Rewrote the startup code to make it easier to understand. Changed the global data to use movable dynamic memory instead of fixed.

**Version 1.0, 19 August 1997**: Original release.

