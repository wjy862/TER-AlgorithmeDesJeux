CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
MATH = -lm
run:bin/sommet
	./bin/sommet

bin/sommet:.obj/sommet.o
	$(CC)  $(CFLAGS) $^ -o $@ 
.obj/sommet.o: inc/sommet.h src/sommet.c
	$(CC) -c $(CFLAGS) -I inc/ -o $@ src/sommet.c

clean:
	rm -rf sommet.o
	rm -rf sommet
