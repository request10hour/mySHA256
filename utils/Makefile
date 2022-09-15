SRCS=mymemmove.c
OBJS=mymemmove.o

all:	libutil.a clean

%o:			%c
			gcc -o $@

libutil.a:	$(OBJS)
			ar rcs libutil.a $(OBJS)

clean:
		rm -rf $(OBJS)

fclean:	clean
		rm -rf libutil.a
