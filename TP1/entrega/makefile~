CC=g++
CFLAGS=-std=c++11

objects = Ejercicio1 Ejercicio2 Ejercicio3
all: $(objects)
clean: rm -f $(objects)

$(objects): %: %.cpp
	$(CC) $(CFLAGS) -o $@ $<
