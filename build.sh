#!/bin/bash

clear
cd build
cmake ..
make -j$(nproc) $@