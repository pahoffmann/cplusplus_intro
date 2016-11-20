prog: PNMrender.o jmprImageFake.o
	gcc PNMrender.o jmprImageFake.o -o -lSDL2 prog

PNMRenderer.o: PNMrender.c
	gcc -c -lSDL2 PNMrender.c 

jmprImageFake.o: jmprImageFake.c
	gcc -c -lSDL2 jmprImageFake.c
