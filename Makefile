CC = clang
CFLAGS = -O3 -Wall
LIBS = -lgd -lpng -lz -ljpeg -lm -lpthread

HEADERS = $(wildcard *.h)
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

BINARY = mandelbrot

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJECTS)
	$(CC) -o $(BINARY) $^ $(CFLAGS) $(LIBS)
	strip $(BINARY)

.PHONY: clean

clean:
	rm -f *.o $(BINARY)

