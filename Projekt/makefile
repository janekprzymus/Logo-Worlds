PLIKI=main.o komunikacja.o response.o mapa.o logika.o ppng.o

all: $(PLIKI)
	gcc $(PLIKI) -lcurl -lpng -o logo-worlds ../../cJSON/cjson.o -Wall --pedantic

%.o:%.c
	cc -c $^ -o $@

clean:
	rm -f logo-worlds
	rm -f *.o

test: all
	./logo-worlds $(filter-out $@,$(MAKECMDGOALS))

reset: all
	./logo-worlds $(filter-out $@,$(MAKECMDGOALS)) reset

play: all
	./logo-worlds $(filter-out $@,$(MAKECMDGOALS)) play

bot: all
	./logo-worlds $(filter-out $@,$(MAKECMDGOALS)) bot