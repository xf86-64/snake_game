#!/bin/bash

echo "Compiling program..."

# error signal function 
function catch_error() {  
  echo "Catch error"
  exit 1
}
# catching any error
trap catch_error ERR

# checking if this directiory exists
if [ -d "bin" ]; then
  rm -rf bin
  mkdir bin
else
  mkdir bin
fi

# compiling 
gcc src/*.c -lncurses -o bin/snake


