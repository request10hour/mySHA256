SRCS=mysqrt.c mycbrt.c nthprime.c
OBJS=mysqrt.o mycbrt.o nthprime.o

all:	libmath.a clean

%o:			%c
			gcc -o $@

libmath.a:	$(OBJS)
			ar rcs libmath.a $(OBJS)

clean:
		rm -rf $(OBJS)

fclean:	clean
		rm -rf libmath.a test

test:	libmath.a clean
		gcc -o test testmain.c libmath.a
