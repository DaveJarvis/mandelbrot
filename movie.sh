#!/bin/bash

# Example script to generate a sequence of still images that zooms into a
# particular location in the fractal. These still images can be combined
# to make a movie.

i=250
z=781250

while true; do
  f=$(printf "%07d" $z)
  echo $i $z as $f ...

  ./mandelbrot -t 128 -s 4 -i $i -x -0.761574 -y -0.0847596 -z $z \
    -p "rgb(52,49,72)" -o $f.png

  let z="$z + 500"
  let i="$i+5"
done

