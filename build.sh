#!/bin/bash

# waiting after command execution
function waiting() {
  sleep 0.1
}
function compile() {
  # compiling(debug)
  if [ "$1" == "debug" ]; then
    echo "Compiling...(debug mode)"
    gcc src/*.c -g -lncurses -o bin/snake 2>/dev/null
  # compiling(normal)
  elif [ "$1" == "normal" ]; then
    echo "Compiling...(normal mode)"
    gcc src/*.c -lncurses -o bin/snake 2>/dev/null
  else
    echo "unknown operation"
    exit 1
  fi
}
waiting
echo "Create the necessary directories..."
# checking if this directiory exists
if [ ! -d "bin" ]; then
  mkdir bin
else
  rm -rf bin
  mkdir bin
fi
waiting
# process arguments(keys) when running a script. In this case processed key -d for debug compiling
if [ $# -ne 0 ]; then
  while [ -n "$1" ] 
  do 
    case "$1" in 
      -d) compile "debug"; break;;
      *) echo "argument $1 not found"; waiting; echo "deleting directories..."; rm -rf bin; exit 1; break;;   
    esac
  done
else  
  compile "normal" 
fi

waiting
# check last executed command for errors (in this case compliling string (22))
if [ $? -ne 0 ]; then  
  echo "Compiling error"
  rm -rf bin
else
  echo "Done"
fi



