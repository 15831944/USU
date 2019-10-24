RM = rm -f
CC = gcc
CDEBUGFLAGS = -O

DTINCLUDE       = -I/usr/dt/include
X11INCLUDE      = 

INCLUDES        = $(DTINCLUDE) $(X11INCLUDE)
CFLAGS          = $(DEFINES) $(CDEBUGFLAGS)

UIL = /usr/bin/X11/uil

DTLIBS          = -L/usr/dt/lib -lMrm -lXm -lXt
X11LIBS         = -lX11

LIBRARIES       = $(DTLIBS) $(X11LIBS) $(SYSLIBS)

.SUFFIXES: .o .uid .c .uil
.c.o:
	$(RM) $@
	${CC} -c $(CFLAGS) $(INCLUDES) $*.c

.uil.uid:
	$(RM) $@
	$(UIL) -o $*.uid $*.uil 

make_mtest1: mtest1 mtest1.uid

mtest1: mtest1.o
	$(RM) $@
	$(CC) -o mtest1 mtest1.o $(LIBRARIES)

clean_mtest1:
	$(RM) mtest1
	$(RM) mtest1.uid
	$(RM) mtest1.o

