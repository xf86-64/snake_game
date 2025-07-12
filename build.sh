#!/bin/bash

echo "Compiling program..."

# checking if this directiory exists
if [ ! -d "bin" ]; then
  mkdir bin
else
  rm -rf bin
  mkdir bin
fi

# compiling 
gcc src/*.c -lncurses -o bin/snake 2>/dev/null # redirecting output to nowhere

# check last executed command for errors (in this case compliling string (22))
if [ $? -ne 0 ]; then  
  echo "Compiling error"
  rm -rf bin
else
  echo "Done"
fi


