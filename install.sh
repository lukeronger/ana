#!/bin/bash

# make ana executable
chmod +x ana

# make in selector
cd src/selector
make

# set up hipo2root
cd ../data/hipo2root/
git submodule update --recursive --remote
./make_hipo2root.py -a
make
