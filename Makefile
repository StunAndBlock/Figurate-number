CFLAGS=$(math) $(xlib) $(debug) $(build)
math=-lm
debug=-g
xlib=-lX11
build=-o $(bdir)/$(name)
bdir=./build
name=Figurate-number
##-------------- object files
objects=FN-main.o FN-window.o
##-------------- make
all: FN-main

FN-main: $(objects)
	gcc $(objects) $(CFLAGS)

FN-main.o: FN-main.c FN-window.h
	gcc -c FN-main.c
FN-window.o: FN-window.c FN-window.h
	gcc -c FN-window.c

clean:
	rm -rf $(objects) $(bdir)$(name)
rebuild: clean all 