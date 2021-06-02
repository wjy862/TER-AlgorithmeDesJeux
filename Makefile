CC= gcc
CFLAGS = -Wall -Werror -Wextra -g
MATH = -lm

run: pdf/results.pdf
      ##qpdfview mm1_2.pdf
	xdg-open pdf/results.pdf

pdf/results.pdf: ter gnuplot/plot.gplt
	gnuplot gnuplot/plot.gplt

ter: bin/ter
	./bin/ter

bin/ter: main.c .obj/sommet.o .obj/benefice.o .obj/apprentissage.o .obj/graphe.o .obj/jeu.o .obj/prints.o
	$(CC) -o $@ $(CFLAGS) $^ -lm

.obj/benefice.o: src/benefice.c inc/benefice.h inc/sommet.h inc/parametre.h
	$(CC) -c $(CFLAGS) $< -o $@
.obj/%.o: src/%.c inc/%.h inc/parametre.h
	$(CC) -c $(CFLAGS) $< -o $@


## clean
clean:
	rm -rf .obj/*
	rm -rf bin/*
	rm -rf pdf/*
	rm -rf data/*

