TARGET = build/pqp-interpreter

FLAGS = -Wall -O3 -g -Iinclude

OBJECTS = main.o cpu.o mem.o fetch.o decode.o

all: $(OBJECTS)
	gcc $(OBJECTS)
	mkdir -p $(TARGET)
	mv $(OBJECTS) $(TARGET)

main.o: src/main.c
	gcc $(FLAGS) -c src/main.c -o main.o

cpu.o: src/cpu.c
	gcc $(FLAGS) -c src/cpu.c -o cpu.o

mem.o: src/mem.c
	gcc $(FLAGS) -c src/mem.c -o mem.o

fetch.o: src/fetch.c
	gcc $(FLAGS) -c src/fetch.c -o fetch.o

decode.o: src/decode.c
	gcc $(FLAGS) -c src/decode.c -o decode.o

clean:
	rm a.out
	rm -rf $(TARGET)
