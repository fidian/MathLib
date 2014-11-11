MathLib User's Manual
=====================

Last updated February 6th, 2003. See the [GitHub project](http://github.com/fidian/MathLib) for the latest version, source code, bug reports, or other information.


Description
-----------

MathLib is a PalmOS shared library which makes a complete set of IEEE-754 double-precision math functions available to other PalmPilot applications. These functions include all the standard routines normally accessed by including "math.h" on other systems, including trigonometry (with inverse and hyperbolic), logarithms, exponentiation, and miscellaneous helper functions. The only standard routines I left out were the Bessel and Gamma functions, which had the poor taste to be both very large and very rarely used. These routines have been ported from the GCC 2.7.2.2 source code for libm.a (which was itself based on free code originally developed by Sun Microsystems, Inc.), so this library is free software covered by the [GNU Library General Public License](LICENSE.txt).

There are two main advantages to using this library. Firstly, writing floating-point math functions that are reasonably fast, accurate, and robust is so incredibly difficult that few programmers will manage it on their own; hopefully, this library will spark the availability of many new programs for the Pilot that were impossible before. And secondly, as you can see from the size of this thing, floating-point code on the Pilot takes up a lot of space. It's much better to have a single copy shared between all the programs that need it than to have each application include their own. How many copies of the trig functions (at 20 or 30 KB each) do you really want on your Pilot?

Many thanks to [Ian Goldberg](iang@cs.berkeley.edu) of [Berkeley's ISAAC Group](http://www.isaac.cs.berkeley.edu/pilot/) for the excellent treatise on [Pilot shared libraries](http://www.isaac.cs.berkeley.edu/pilot/shlib.html) that made this project possible. You should read and understand that document completely before you even think about making any changes to this library, but it's not really necessary if you just want to call the library from your program.

**Note:** Due to a fundamental constraint of the NewFloatMgr.lib floating point emulation library, MathLib requires **version 2.0 or greater** of the OS. The problem is that the floating point emulation library (which must be used in order to do IEEE 754 math under OS 1.x) requires the global variable __SoftFPSCR__, and SysLib-style shared libraries can't have any global variables. GLib-style libraries are supposed to support globals, but can only be built or used with GCC, and I needed this library to be usable by applications written with the CodeWarrior compiler (namely [MathPad](http://www.radiks.net/~rhuebner/mathpad.html) and [Parens](http://www.radiks.net/~rhuebner/parens.html)).  If anyone comes up with a way to build and call shared libraries using CodeWarrior on my Win95 system that will let me use the NewFloatMgr routines under OS 1.x, please let me know.


Installation
------------

MathLib is packaged as a standard .PRC Pilot resource database, and can be installed on your Pilot just like any regular application program. Just use your install tool or equivalent to load it into your Pilot before using any programs that call it. To remove MathLib from your Pilot, just use the standard Memory application built into the Pilot ROM to delete it. Ian mentions in his writeup that he has to delete an older version of a library before installing a new one, but I haven't had any problems with that. It might depend on what software you use to synchronize, but the standard Win95 HotSync program has always worked OK for me.

Each program which uses a shared library is responsible for gracefully failing if the library's not available when it runs.  If they try and run anyway, they'll simply cause a system reset as soon as they try to call a library routine, but this shouldn't hurt anything.


Using MathLib
-------------

Include "MathLib.h" in any source file that needs to do anything with the library. Add MathLib.c to your project file or makefile. Prepare the library for use in your StartApplication( ) routine or equivalent, like this:

```c
Err error;

error = SysLibFind(MathLibName, &MathLibRef);
if (error)
    error = SysLibLoad(LibType, MathLibCreator, &MathLibRef);
ErrFatalDisplayIf(error, "Can't find MathLib"); // Just an example; handle it gracefully
error = MathLibOpen(MathLibRef, MathLibVersion);
ErrFatalDisplayIf(error, "Can't open MathLib");
```

Call whatever functions you need:

```c
FlpCompDouble x;  // For compatibility with the Flp routines. Bleah.

x.d = sqrt(867.5309) * tan(42);
FlpFToA(x.fd, buffer);
```

And release the library in your StopApplication( ) routine or
equivalent, like so:

```c
UInt usecount;

error = MathLibClose(MathLibRef, &usecount);
ErrFatalDisplayIf(error, "Can't close MathLib");
if (usecount == 0)
    SysLibRemove(MathLibRef);
```

That's it. As for the math routines themselves, please remember that all angles are measured in radians, not degrees.  There's no exception signaling or error reporting, but the standard IEEE-754 special "non-number" values of NaN (not a number), +INF (positive infinity) and -INF (negative infinity) will be returned appropriately if you do something silly like divide by 0. If you have any specific questions about a particular math function or its algorithm, look at the source code for that routine; most of them have quite complete documentation describing how they work. Please don't bother asking me; I didn't write these routines, and generally don't know any more about how they work than you do. I'm just repackaging them.


Rebuilding MathLib
------------------

If you fix any bugs or add new functions to this library that would be generally useful to others, I'd appreciate being kept informed so that I can keep it up to date. It'll be a real mess if we have 10 flavors of MathLib out on the net with subtle differences between each. And the space savings of sharing the code would be pretty much wasted if we ended up needing several different math libraries loaded into our Pilots to get all of our apps to work. However, this is free software, and you're entitled to modify it. If you do so, here's what you'll need to know in order to rebuild it.

The first consideration is that it was developed with CodeWarrior. If you need to rebuild this under GCC, you'll have to do some major surgery on the startup code in MathLib.c, to change the inline assembler code to GCC format. See Ian Goldberg's [shared library treatise](http://www.isaac.cs.berkeley.edu/pilot/shlib.html) for a good example of how to do this. The rest of the code should be pretty much OK, except for some pragmas. To get CodeWarrior to create a shared library instead of a regular program, set the 68K Target "Project Type" to "PalmOS Code Resource", with a ResType of "libr" and a ResID of 0. You must also specify a PilotRez "Output Options" Type of "libr" and Creator of "MthL" (use a different creator code if you're not replacing MathLib). Under 68K Processor, be sure to check "4-Byte Ints" so that the math routines (which were written under UNIX) will be happy, and "8-Byte Doubles" for IEEE-754 double precision format. Finally, check "Link Single Segment" in the 68K Linker section.

The second thing to bear in mind is the size of the library.  Some trickiness was used to allow this library to hold more than the usual 32KB of code. The key to making this work is the arrangement of the routines within the code segment. All of the library entry points jump to mathcalls.c, which contains a set of encapsulation stubs which translate the Palm OS mandated library routine calling conventions into the standard arguments expected by the GCC math functions. By putting these translation stubs in the middle of the code segment instead of at the beginning, we can stretch the 32KB limit. The reason 32KB is usually considered to be the maximum size of a code segment is that the 68000 chip's pc-relative jmp and jsr instructions can only jump +/-32KB from the calling routine. From the launch point of the translation stubs in the middle of the code segment, we can jump 32KB in *either* direction, allowing us to have up to 64KB of code. The only problem this leaves is the possibility that a routine near one end of the code segment might try to call something near the other other end, exceeding the jmp distance limit. This is avoided by carefully arranging the order in which the functions are appended to the code segment to cluster the routines that call each other together and maximize locality of reference. The few unavoidable cases that remain are handled by using "jump islands" in mathcalls.c to act as jump repeaters and extend the range. See the file MathLib.map for a detailed listing of the current subroutine order being used.

I've included the CodeWarrior project file MathLib.mcp in this archive; hopefully this will give you the correct compiler settings and code segment link order. GCC users should see Ian's library treatise (again) for detailed instructions on generating shared libraries with GCC. Read the MathLib.map file to get the correct order for the math function object files on the gcc command line when linking.


Legal Stuff
-----------

MathLib.prc is a derivative work of the libm.a math library that comes with GCC 2.7.2.2. It's distributed in accordance with the [GNU Library General Public License](LICENSE.txt), which explicitly gives you the right to make use of the library from within your own programs, without any effect on anybody's rights regarding your software. If you write a program using GCC, calling a function from libm.a does *not* automatically make your program fall under the Public License. In exactly the same way, calling a function from MathLib.prc does *not* make your program come under the Public License, either. The GNU Library General Public License applies only to MathLib itself, and not to those programs which make use of MathLib. Your software is *not* considered a derivative work of MathLib.prc.

Let's see if I can stress this a bit more strongly for all those barracks lawyers out there. To quote the holy LGPL:

> A program that contains no derivative of any portion of the
> Library, but is designed to work with the Library by being compiled or
> linked with it, is called a "work that uses the Library". Such a
> work, in isolation, is not a derivative work of the Library, and
> therefore falls outside the scope of this License.

And regarding distribution:

> In addition, mere aggregation of another work not based on the Library
> with the Library (or with a work based on the Library) on a volume of
> a storage or distribution medium does not bring the other work under
> the scope of this License.

And finally, a quote from an email from the great Richard Stallman himself (prompted by some idiot who was trying to force a MathLib user to publish his source code):

> If MathLib was released under the Library GPL, then it is permitted to
> link it into proprietary (non-free) programs, following the rules of
> the Library GPL of course.

OK, people? I don't want to get off on a rant, but... *(cue spotlight)* I'm sick and tired of catching grief from schmucks who assume that anything which in any way comes into contact with free OSF code must automatically be free also. Quit trying to use MathLib as an excuse for extortion of other people's hard work. The time and effort that I and other programmers have to spend responding to you idiots' accusations discourages the very use of OSF code that the GPL is supposed to promote, and would have been much better spent on improving our programs. "Oooh! He uses MathLib so now he has to give me his source code!" **WRONG.** Yeesh! Get a life and go create something constructive instead of spending your time trashing other people's efforts. *(cue stage lights)*

Whew. I feel better now.

You may distribute a copy of MathLib.prc with your application, so long as you clearly indicate in your documentation that MathLib is not part of your program, but is independently available free software which you are simply providing as a convenience; and that you inform the user where and how they may obtain the latest version and full source code.  A paragraph similar to the following is acceptable (spell out the URL if not using HTML):

* MathLib is a free shared library that can be used by any OS 2.0+ Pilot program that needs IEEE 754 double precision math functions. It's distributed under the terms of the GNU Library General Public License, and is freely available with full source code and documentation at the [MathLib Project Page](http://github.com/fidian/MathLib). It's not a part of the MathPad program, and you're not paying anything for its use; a copy is simply included in this archive for your convenience.

Or, you may simply state that your program requires MathLib in order to work, and inform them where they may obtain it for themselves.

This program is free software; you can redistribute it and/or modify it under the terms of the GNU Library General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public License for more details.

You should have received a copy of the GNU Library General Public License along with this program; see file [LICENSE.txt](LICENSE.txt). If not, write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA


Maintenance Notes
-----------------

6 February 2003: Corrected licensing of MathLib.c file, and changed startup.c to use Entry Point setting in 68K Target control panel.  No executable code changes.

1 August 2001: Updated web page address.

2 May 2001: Updated to use Palm OS 4.0 SDK.

Version 1.1, 13 April 1999: Updated the code for s_cbrt.c and s_modf.c to match what's being used in GNU libc 2.0. This fixes a problem with the cube root function that caused it to give invalid results for values from 0.5 to 1.0. The library has also shrunk by about 5KB, due to improved optimization in the latest version of the CodeWarrior compiler.

Version 1.02, 13 July 1998: Corrected the documentation and some source code comments to more correctly identify the use of the GNU *Library* General Public License instead of the plain old regular General Public License. No code changes.

Version 1.01, 24 August 1997: Changed the convenience wrapper functions from inline declarations to standard functions in their own source file, due to CodeWarrior problems with the inline routines. Rewrote the startup code to make it easier to understand. Changed the global data to use movable dynamic memory instead of fixed.

Version 1.0, 19 August 1997: Original release.

All software and pages are Copyright © 1997-2003 Rick Huebner; All Rights Reserved.
