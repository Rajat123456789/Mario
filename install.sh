#! /bin/bash
#
# install.sh
# Copyright (C) 2013 sagar <sagar@sagar-liquid>
#


# echo "Installing freeglut..."
# sudo apt-get install freeglut3-dev

# echo "Installing SDL..."
# sudo apt-get install libsdl1.2-dev libsdl-image1.2-dev

echo "Installing freeglut..."
sudo pacman -S freeglut 

echo "Installing SDL..."
sudo pacman -S sdl sdl_image