#!/bin/bash

# Example script to generate a sequence of still images that zooms into a
# particular location in the fractal. These still images can be combined
# to make a movie.

# iterations
i=250

# zoom and steps
z=781250
z_step=1500

# x, y coordinate
x=-0.761574
y=-0.0847596

# samples
s=4

while true; do
  f=$(printf "%07d" $z)
  echo "Generating ($x, $y) @ $z:$i ..."

  ./mandelbrot -t 128 -s $s -i $i -x $x -y $y -z $z \
    -p "rgb(52,49,72)" -o $f.png

  let z="$z+$z_step"
  let i="$i+1"
done

