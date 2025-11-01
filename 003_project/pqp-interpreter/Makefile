TARGET = build/pqp-interpreter

FLAGS = -Wall -O3 -g -Iinclude

OBJECTS = main.o cpu.o mem.o

all: $(OBJECTS)
	gcc $(OBJECTS) -o $(TARGET)

main.o: src/main.c
	gcc $(FLAGS) -c src/main.c -o main.o

cpu.o: src/cpu.c
	gcc $(FLAGS) -c src/cpu.c -o cpu.o

mem.o: src/mem.c
	gcc $(FLAGS) -c src/mem.c -o mem.o

clean:
	rm -f $(TARGET) $(OBJECTS)