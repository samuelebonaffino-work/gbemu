#!/bin/bash

# Set the compiler
CC=gcc

# Set compiler flags
CFLAGS="-std=c11 -Wall"

# Set the source folder
SRC_FOLDER=src

# Set the output folder
OUTPUT_FOLDER=build

# Set the SDL2 and SDL2_ttf flags and libraries
SDL2_CFLAGS=$(sdl2-config --cflags)
SDL2_TTF_CFLAGS=$(pkg-config --cflags SDL2_ttf)
SDL2_LIBS=$(sdl2-config --libs)
SDL2_TTF_LIBS=$(pkg-config --libs SDL2_ttf)

# Create the output folder if it doesn't exist
mkdir -p $OUTPUT_FOLDER
rm -f $OUTPUT_FOLDER/*

# Compile the project using make
$CC $CFLAGS $SDL2_CFLAGS $SDL2_TTF_CFLAGS -I$SRC_FOLDER $SRC_FOLDER/*.c -o $OUTPUT_FOLDER/gbemu $SDL2_LIBS $SDL2_TTF_LIBS -lm

clear
echo
echo "****************************************"
echo "** Build task completed (build/gbemu) **"
echo "****************************************"
echo
