# Simple Mandelbrot

Renders an image from the Mandelbrot Set.

# Software Requirements

Building the project requires:

* [Clang](http://clang.llvm.org/) - C compiler
* [GNU Make](https://www.gnu.org/software/make/) - Build scripting
* [git](https://git-scm.com/) - Version control system

## Libraries

Third-party libraries required to build the binary include:

* [glibc](https://www.gnu.org/software/libc/) - Math & Threading
* [libgd](https://libgd.github.io/) - Graphics
* [libpng](http://www.libpng.org/pub/png/libpng.html) - PNG format
* [libjpeg](http://libjpeg.sourceforge.net/) - JPEG format
* [zlib](https://www.zlib.net/) - Image compressor

# Build

Build the project from scratch as follows:

```
mkdir -p $HOME/dev/c
cd $HOME/dev/c
git clone https://github.com/DaveJarvis/mandelbrot
cd mandelbrot
make
```

The project is built.

# Run

Use `./mandelbrot` to run.

# Help

Use `./mandelbrot --help` to view the command line options.

# Result

View `out.png` to see the output.

