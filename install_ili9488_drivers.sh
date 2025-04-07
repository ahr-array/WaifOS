#!/bin/bash

echo "Updating package lists..."
sudo apt update

echo "Installing necessary libraries..."
sudo apt install git cmake ninja-build python3-pip -y

echo "Setting up ESP-IDF..."
git clone --recursive https://github.com/espressif/esp-idf.git ~/esp/esp-idf
cd ~/esp/esp-idf
./install.sh

echo "Installing TFT_eSPI library..."
git clone https://github.com/Bodmer/TFT_eSPI.git ~/TFT_eSPI
cd ~/TFT_eSPI
echo "Library installed. Now configure it in the setup files."

echo "Installation complete!"

