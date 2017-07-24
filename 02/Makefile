CC=gcc
CFLAGS=-Wall -lm -std=c99
SOURCES=$(wildcard src/*.c)
OBJECTS=$(SOURCES:src/%.c=%.o)
DEPS=$(wildcard *.h)

main: $(OBJECTS)
	mkdir -p bin
	$(CC) $(CFLAGS) -o bin/$@ $(patsubst %.o,bin/%.o,$^)

%.o:src/%.c $(DEPS)
	mkdir -p bin
	$(CC) $(CFLAGS) -o bin/$@ -c $<

clean:
	rm -rf bin
	rm -rf dbg

debug: $(SOURCES)
	rm -rf dbg/
	mkdir -p dbg
	$(CC) -o dbg/main -g3 -ggdb $(SOURCES) $(CFLAGS)
