//
// Created by vli15 on 11/4/2024.
//

#include "Pixel.h"
Pixel::Pixel(unsigned char& r, unsigned char& b, unsigned char& g){
    red = r;
    green = g;
    blue = b;
}

Pixel::Pixel() {
    red = 0;
    green = 0;
    blue = 0;
}

void Pixel::setBlue(unsigned char& b) {
    blue = b;
}
void Pixel::setGreen(unsigned char& g) {
    green = g;
}
void Pixel::setRed(unsigned char& r) {
    red = r;
}
unsigned char Pixel::getBlue() {
    return blue;
}
unsigned char Pixel::getGreen() {
    return green;
}
unsigned char Pixel::getRed() {
    return red;
}