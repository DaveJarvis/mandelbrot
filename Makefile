CC = clang
CFLAGS = -I. -O3
DEPS = mandelbrot.h image.h
OBJ = mandelbrot.o image.o
LIBS = -lgd -lpng -lz -ljpeg -lfreetype -lm

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

mandelbrot: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	strip mandelbrot

.PHONY: clean

clean:
	rm -f *.o mandelbrot

