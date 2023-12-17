install:
	clang -g src/BMP.c  -lm -I ./include -c -o./lib/BMP.o
	clang -g src/draw.c -I ./include ./lib/BMP.o `pkg-config --cflags --libs x11` -o draw

clean:
	rm ./lib/*
	rm draw
