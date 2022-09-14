SRCS=initialize.c
OBJS=initialize.o
LIBS=./math/libmath ./preprocess/libprep ./utils/libutil

all:	libmake run.out clean

%o:			%c
			gcc -o $@

libmake:
			make -C ./math
			make -C ./preprocess
			make -C ./utils

run.out:	$(OBJS)
			gcc -o run.out $(OBJS) $(LIBS)

clean:
		rm -rf $(OBJS)

fclean:	clean
		rm -rf run.out
		make fclean -C ./math
		make fclean -C ./preprocess
		make fclean -C ./utils
