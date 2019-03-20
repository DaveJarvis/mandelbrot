CC = clang
CFLAGS = -O3
LIBS = -lgd -lpng -lz -ljpeg -lfreetype -lm -lpthread

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

