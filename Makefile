CC=gcc
CFLAGS=-Wall -Wextra -Werror -pedantic

build: src/*.c
	$(CC) $(CFLAGS) -o main $< $(shell sdl2-config --cflags --libs) -lSDL2_mixer

run: main
	./main

clean: main
	rm main