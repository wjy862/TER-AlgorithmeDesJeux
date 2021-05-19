CC= gcc
CFLAGS = -Wall -Werror -Wextra -g
MATH = -lm
run: run2


## SIMUL 1
run1: simul1
	./simul1

simul1: simul1.c
	gcc -o simul1 -Wall simul1.c -lm

## SIMUL 2
run2: pdf/mm1_2.pdf
      ##qpdfview mm1_2.pdf
	xdg-open pdf/mm1_2.pdf

pdf/mm1_2.pdf: data/mm1_2.data gnuplot/mm1_2.gplt
	gnuplot gnuplot/mm1_2.gplt

data/mm1_2.data: bin/simul2
	./bin/simul2

bin/simul2: src/main.c .obj/sommet.o .obj/graphe.o .obj/benefice.o .obj/apprentissage.o .obj/jeu.o
	$(CC) $(CFLAGS) -o $@ $^ $(MATH)

##GENERAL

.obj/benefice.o: src/benefice.c inc/benefice.h inc/sommet.h 
	$(CC) -c $(CFLAGS) $< -o $@
.obj/%.o: src/%.c inc/%.h 
	$(CC) -c $(CFLAGS) $< -o $@

## SIMUL 3
run3: mm1_3.pdf
	qpdfview mm1_3.pdf

mm1_3.pdf: mm1_3.data mm1_3.gplt
	gnuplot mm1_3.gplt

mm1_3.data: simul3
	./simul3

simul3: simul3.c
	gcc -o simul3 -Wall simul3.c -lm

## clean
clean:
	rm -f simul1
	rm -f bin/simul2
	rm -f data/mm1_2.data 
	rm -f pdf/mm1_2.pdf
	rm -f simul3
	rm -f mm1_3.data mm1_3.pdf

