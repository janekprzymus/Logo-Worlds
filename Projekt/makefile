all:
	gcc main.c -lcurl ../cJSON/cjson.o

clean:
	rm -f a.out
	rm -f plansza.txt

//Przy uruchamianiu programu za pomocą makefile należy po komendzie wpisać kod świata!!
//Np. make reset qwerty_27

reset: all
	./a.out $(filter-out $@,$(MAKECMDGOALS)) reset

info: all
	./a.out $(filter-out $@,$(MAKECMDGOALS))

move: all
	./a.out $(filter-out $@,$(MAKECMDGOALS)) M

explore: all
	./a.out $(filter-out $@,$(MAKECMDGOALS)) E

rright: all
	./a.out $(filter-out $@,$(MAKECMDGOALS)) Rright

rleft: all
	./a.out $(filter-out $@,$(MAKECMDGOALS)) Rleft
