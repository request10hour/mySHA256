SRCS=sqrt.c nthprime.c
OBJS=sqrt.o nthprime.o

all:	libmath clean

%o:			%c
			gcc -o $@

libmath:	$(OBJS)
			ar rcs libmath $(OBJS)

clean:
		rm -rf $(OBJS)

fclean:	clean
		rm -rf libmath

test:	libmath clean
		gcc -o test testmain.c libmath
