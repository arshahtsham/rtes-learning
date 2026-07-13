INCLUDE_DIRS = 
LIB_DIRS = 
CC=gcc

CDEFS=
CFLAGS= -O3 $(INCLUDE_DIRS) $(CDEFS)
LIBS= 

HFILES= 
# This is for the source file
CFILES= pthread.c 

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

# Main target
all:	pthread

clean:
	-rm -f *.o *.d
	-rm -f perfmon pthread

distclean:
	-rm -f *.o *.d
	-rm -f pthread

# This is the linking rule
pthread: pthread.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $@.o -lpthread

depend:

# Compilation rule
.c.o:
	$(CC) $(CFLAGS) -c $<
