#!/bin/bash

MODE=Debug

if [ ! -z "$1" ]; then
  MODE="$1" 
fi

if [ ! -d "build" ]; then
  mkdir build
fi

cd build

cmake -DCMAKE_BUILD_TYPE="$MODE" ..

if [ -f "../compile_commands.json" ]; then
  rm ../compile_commands.json
fi

if [ -f "compile_commands.json" ]; then
  cp compile_commands.json ../compile_commands.json 
fi
