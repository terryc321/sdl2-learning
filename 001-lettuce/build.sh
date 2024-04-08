#!/bin/bash

# weird
# sdl2 library is lowercase sdl2
# sdl2-image library is uppercase SDL2_image 
gcc -Wall \
    -fPIC \
    -o hello hello.c \
    `pkg-config --cflags --libs guile-3.0`\
    `pkg-config --cflags --libs sdl2`\
    `pkg-config --cflags --libs SDL2_image`\
    

