SRCS=mymemmove.c
OBJS=mymemmove.o

all:	libutil clean

%o:			%c
			gcc -o $@

libutil:	$(OBJS)
			ar rcs libutil $(OBJS)

clean:
		rm -rf $(OBJS)

fclean:	clean
		rm -rf libutil
