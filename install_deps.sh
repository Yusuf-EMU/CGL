#!/bin/sh

sudo apt-get update

# GLEW & GLFW
    sudo apt-get -y install libglew-dev libglfw-dev

# CGLM
    git clone https://github.com/recp/cglm
    cd cglm
    cmake .
    make
    make install
    cd ..
    rm -rf cglm

echo Done!
