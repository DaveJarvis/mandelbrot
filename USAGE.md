# Usage

This document provides example usages.

# Rendering

Once you've explored the fractal and found coordinates and a zoom level that
you like, use the application to generate a high-quality image. Try these:

    ./mandelbrot -o default.png
    ./mandelbrot -x -0.235125 -y 0.827215 -z 1000000 -i 10000 -o trees.png
    ./mandelbrot -x -0.761825 -y -0.084875 -z 323500 -i 2000 -o spiral.png

# Quality

There are a few ways to increase the render quality, including:

* Use `-s` to increase the subsample size, which controls anti-aliasing.
Increasing this number will dramatically increase the amount of time to
render the image. Usually a setting of 4 will suffice.
  * 1 - The default (no anti-aliasing).
  * 2 - Can leave visible artefact streaks.
  * 4 - Overall smooth appearance.
  * 9 - High-quality smoothing.
  * 16 - Supreme smoothing.
  * 32 - Extraordinarily smooth.
* Use `-w` and `-h` to change the width and height.
* Use `-i` to increase the number of iterations.

# Interesting Regions

[Paul Bourke](http://paulbourke.net/fractals/mandelbrot/) and
[Alan Dewar](http://www.cuug.ab.ca/dewara/mandelbrot/Mandelbrowser.html) have
written about some interesting regions. Regions are given by complex
plane coordinates and a zoom level, including:

| x  | y  | zoom |
|---:|---:|-----:|
| -0.170337 | -1.0650600 | 78125
|  0.428840 | -0.2313450 | 78125
| -1.629170 | -0.0203968 | 78125
| -0.761574 | -0.0847596 | 78125
| -0.746300 |  0.1102000 | 0.005
| -0.745300 |  0.1127000 | 0.00065
| -0.745290 |  0.1130750 | 0.00015
| -0.745428 |  0.1130090 | 0.00003
| -0.925000 |  0.2660000 | 0.032
| -1.250660 |  0.0201200 | 0.00017

Other settings to try:

| x  | y  | zoom | iterations |
|---:|---:|-----:|-----------:|
| -0.761574 | -y -0.0847596 | 781250 | 250

You will have to change their zoom levels and increase the number of
iterations to see these areas using this application.

