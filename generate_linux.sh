#!/bin/bash

# vendor/premake/premake5 gmake2 --os=linux
# make CC="$HOME/.config/nvim/autoload/plugged/clang_complete/bin/cc_args.py gcc" CXX="$HOME/.config/nvim/autoload/plugged/clang_complete/bin/cc_args.py g++" -B

# find . -name ".clang_complete" -type f | xargs cat | sort | uniq > .clang_complete

mkdir build
cd build

cmake ..

cp compile_commands.json ../compile_commands.json 

make
