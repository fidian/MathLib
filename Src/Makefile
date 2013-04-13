#
# Makefile for Linux & GCC for MathLib.
#

APP=MathLib

PALMSDK=/opt/palmdev/sdk-5r3
PRCTOOLS=/usr/share/prc-tools

ARCH=m68k-palmos
ARM-ARCH=arm-palmos

ARM-CC=$(ARM-ARCH)-gcc
ARM-AS=$(ARM-ARCH)-as
ARM-LD=$(ARM-ARCH)-ld

CC=$(ARCH)-gcc
AS=$(ARCH)-as
LD=$(ARCH)-ld
STUBGEN=$(ARCH)-stubgen
BUILDPRC=build-prc

DEFINES=
INCLUDES=-I. -I$(PALMSDK)/include -I$(PRCTOOLS)/include
CFLAGS=-pipe -O2 -Wall $(DEFINES) $(INCLUDES)
LIBRARIES=-L$(PALMSDK)/lib
LDFLAGS=-O -shared -nostartfiles -T /usr/$(ARCH)/lib/text_64k_palmos3

PRC=$(APP).prc

SRC=startup.c $(APP)-dispatch.s \
e_acos.c e_sqrt.c e_asin.c s_fabs.c \
s_atan.c e_atan2.c s_cos.c k_cos.c e_rem_pio2.c k_sin.c \
k_rem_pio2.c s_scalbn.c s_floor.c s_copysign.c s_sin.c \
s_tan.c k_tan.c s_sincos.c e_cosh.c s_expm1.c e_exp.c \
e_sinh.c s_tanh.c e_acosh.c e_log.c s_log1p.c s_asinh.c \
mathcalls.c \
e_atanh.c s_frexp.c s_ldexp.c s_finite.c \
e_log10.c s_modf.c s_logb.c s_log2.c e_pow.c e_hypot.c \
s_cbrt.c s_ceil.c e_fmod.c s_isinf.c e_remainder.c \
s_significand.c e_scalb.c s_ilogb.c s_isnan.c s_rint.c \
s_nextafter.c s_round.c s_trunc.c s_signbit.c

OBJS=$(patsubst %.c,%.o,$(patsubst %.s,%.o,$(SRC)))

OBJS-LIST= startup.o $(APP)-dispatch.o \
e_acos.o e_sqrt.o e_asin.o s_fabs.o \
s_atan.o e_atan2.o s_cos.o k_cos.o e_rem_pio2.o k_sin.o \
k_rem_pio2.o s_scalbn.o s_floor.o s_copysign.o s_sin.o \
s_tan.o k_tan.o s_sincos.o e_cosh.o s_expm1.o e_exp.o \
e_sinh.o s_tanh.o e_acosh.o e_log.o s_log1p.o s_asinh.o \
mathcalls.o /usr/$(ARCH)/lib/libnfm.a \
e_atanh.o s_frexp.o s_ldexp.o s_finite.o \
e_log10.o s_modf.o s_logb.o s_log2.o e_pow.o e_hypot.o \
s_cbrt.o /usr/lib/gcc-lib/$(ARCH)/2.95.3-kgpd/libgcc.a \
s_ceil.o e_fmod.o s_isinf.o e_remainder.o \
s_significand.o e_scalb.o s_ilogb.o s_isnan.o s_rint.o \
s_nextafter.o s_round.o s_trunc.o s_signbit.o


all:	$(APP)-dispatch.s $(PRC)

$(PRC):	$(APP)
	$(BUILDPRC) $(APP).def $(APP)
	ls -l $(APP) $(APP).prc

$(APP)-dispatch.s:	$(APP).def
	$(STUBGEN) $(APP).def

$(APP):	$(OBJS)
	$(LD) $(LDFLAGS) $(LIBRARIES) $(OBJS-LIST) -o $@

%.o:  %.c %.s Makefile $(APP)-dispatch.s $(SRC)
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(APP)-dispatch.s *.o $(APP) *.prc *~

install:  $(PRC)
	pilot-xfer -i MathLib.prc

