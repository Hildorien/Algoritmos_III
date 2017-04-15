CC=g++
CFLAGS=-std=c++11

objects = Ejercicio1 Ejercicio2 Ejercicio3

.PHONY: clean

all: $(objects) 

clean: 
	rm Ejercicio1
	rm Ejercicio2
	rm Ejercicio3

$(objects): %: %.cpp
	$(CC) $(CFLAGS) -o $@ $<
