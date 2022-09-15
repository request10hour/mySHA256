SRCS=preprocess.c
OBJS=preprocess.o

all:	libprep.a clean

%o:			%c
			gcc -o $@

libprep.a:	$(OBJS)
			ar rcs libprep.a $(OBJS)

clean:
		rm -rf $(OBJS)

fclean:	clean
		rm -rf libprep.a test

test:	libprep.a clean
		gcc -o test testmain.c libprep.a
