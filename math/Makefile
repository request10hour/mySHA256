SRCS=mysqrt.c mycbrt.c nthprime.c
OBJS=mysqrt.o mycbrt.o nthprime.o

all:	libmath clean

%o:			%c
			gcc -o $@

libmath:	$(OBJS)
			ar rcs libmath $(OBJS)

clean:
		rm -rf $(OBJS)

fclean:	clean
		rm -rf libmath test

test:	libmath clean
		gcc -o test testmain.c libmath
