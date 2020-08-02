#!/bin/sh

sudo apt-get update

# GLEW Install
    sudo apt-get -y install libglew-dev

# Compiling and installing GLFW to avoid weirdness on some distros
    sudo apt-get -y install libx11-dev
    sudo apt-get -y install libxi-dev
    sudo apt-get -y install libxrandr-dev
    sudo apt-get -y install libxinerama-dev
    sudo apt-get -y install libxcursor-dev
    git clone https://github.com/glfw/glfw
    cd glfw
    cmake .
    make
    sudo make install
    cd ..
    rm -rf glfw

# CGLM
    git clone https://github.com/recp/cglm
    cd cglm
    cmake .
    make
    make install
    cd ..
    rm -rf cglm

echo Done!