CC=gcc
CFLAGS=-Wall -Wextra -pedantic

build: src/*.c src/*.h
	$(CC) $(CFLAGS) -o main $^ $(shell sdl2-config --cflags --libs) -lSDL2_mixer

debug: src/*.c src/*.h
	$(CC) $(CFLAGS) -g -o $@ $^ $(shell sdl2-config --cflags --libs) -lSDL2_mixer && gdb $@

run: build
	./main

clean: main
	rm main
