CFLAGS=`pkg-config --cflags sdl2`
LIBS=`pkg-config --libs sdl2`

hello: hello.c
	gcc $(CFLAGS) $(LIBS) -o $@ $^
