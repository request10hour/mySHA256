SRCS=preprocess.c
OBJS=preprocess.o

all:	libprep clean

%o:			%c
			gcc -o $@

libprep:	$(OBJS)
			ar rcs libprep $(OBJS)

clean:
		rm -rf $(OBJS)

fclean:	clean
		rm -rf libprep test

test:	libprep clean
		gcc -o test testmain.c libprep
