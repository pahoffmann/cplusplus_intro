CC=/usr/bin/gcc
CFLAGS=-Wall -Wstrict-prototypes -ansi -pedantic -lSDL2 -lSDL2main
FILES=sortrectangle.c
BINARY=$(FILES:.c=.o)

#wildcard pattern rule to compile c code

%.o:	%.c 
	$(CC) -c $(CFLAGS) $< -o $@ 

default: $(BINARY)
	$(CC) $(BINARY) -o main $(CFLAGS)

test: default
	./main 10 20 100	

clean: 
	$(RM) $(BINARY)
	$(RM) main	 
