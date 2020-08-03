#!/bin/sh

sudo apt-get update

# GLEW
    git clone https://github.com/nigels-com/glew
    cd glew
    cd auto
    make
    cd ..
    make
    make install
    cd ..
    rm -rf GLEW

# GLFW
    git clone https://github.com/glfw/glfw
    cd glfw
    cmake .
    make
    make install
    cd ..
    rm -rf cglm

# CGLM
    git clone https://github.com/recp/cglm
    cd cglm
    cmake .
    make
    make install
    cd ..
    rm -rf cglm

echo Done!
