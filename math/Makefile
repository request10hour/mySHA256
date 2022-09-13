SRCS=sqrt.c nthprime.c
OBJS=sqrt.o nthprime.o

all:	libmath

%o:			%c
			gcc -o $@

libmath:	$(OBJS)
			ar rcs libmath $(OBJS)

clean:
		rm -rf $(OBJS)
