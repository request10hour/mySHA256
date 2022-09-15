SRCS=initialize.c compression.c mysha256.c
OBJS=initialize.o compression.o mysha256.o
LIBS=./math/libmath.a ./preprocess/libprep.a ./utils/libutil.a

all:	libmake mysha256 clean

%o:			%c
			gcc -o $@

libmake:
			make -C ./math
			make -C ./preprocess
			make -C ./utils

mysha256:	$(OBJS)
			gcc -o mysha256 $(OBJS) $(LIBS)

clean:
		rm -rf $(OBJS)

fclean:	clean
		rm -rf mysha256
		make fclean -C ./math
		make fclean -C ./preprocess
		make fclean -C ./utils
