CC = clang
CFLAGS = -I. -O3
DEPS = mandelbrot.h image.h options.h threads.h
OBJ = mandelbrot.o image.o options.o threads.o
LIBS = -lgd -lpng -lz -ljpeg -lfreetype -lm -lpthread

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

mandelbrot: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	strip mandelbrot

.PHONY: clean

clean:
	rm -f *.o mandelbrot

