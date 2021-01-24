PLIKI=main.o komunikacja.o response.o mapa.o logika.o

all: $(PLIKI)
	gcc $(PLIKI) -lcurl -o logo-worlds ../../cJSON/cjson.o -Wall --pedantic

%.o:%.c
	cc -c $^ -o $@

clean:
	rm -f logo-worlds
	rm -f *.o

reset: all
	./logo-worlds $(filter-out $@,$(MAKECMDGOALS)) reset

info: all
	./logo-worlds $(filter-out $@,$(MAKECMDGOALS))

move: all
	./logo-worlds $(filter-out $@,$(MAKECMDGOALS)) M

explore: all
	./logo-worlds $(filter-out $@,$(MAKECMDGOALS)) E

rright: all
	./logo-worlds $(filter-out $@,$(MAKECMDGOALS)) Rright

rleft: all
	./logo-worlds $(filter-out $@,$(MAKECMDGOALS)) Rleft
