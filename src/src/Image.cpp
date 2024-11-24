//
// Created by vli15 on 11/7/2024.
//

#include "Image.h"

#include <iostream>
#include <ostream>

#include "Pixel.h"
#include <vector>
Image::Image(int h, int w) {
    height = h;
    width = w;

}

void Image::multiply(std::vector<Pixel>& a, std::vector<Pixel>& b) { //multiplying a by b into this
    int size = this->width * this->height;
    for(int i=0; i<size; i++) {
        Pixel pixel;
        unsigned char r = ((float)a[i].red/255*(float)b[i].red)+.5f;
        pixel.red = r;
        unsigned char bb = (float)a[i].blue/255*(float)b[i].blue+.5f;
        pixel.blue = bb;
        unsigned char g = (float)a[i].green/255*(float)b[i].green+.5f;
        pixel.green = g;
        this->data.push_back(pixel);
    }
}

void Image::subtract(std::vector<Pixel>& a, std::vector<Pixel>& b) {
    int size = this->width * this->height;
    for(int i=0; i<size; i++) {
        Pixel pixel;
        int r = (int)a[i].red-(int)b[i].red;
        // if(r>255) {r=255;}
        if(r<0) {r=0;}
        pixel.red = (unsigned char)r;
        int bb = (int)a[i].blue-(int)b[i].blue;
        // if(b>255) {b=255;}
        if(bb<0) {bb=0;}
        pixel.blue = (unsigned char)bb;
        int g = (int)a[i].green-(int)b[i].green;
        // if(g>255) {g=255;}
        if(g<0) {g=0;}
        pixel.green = (unsigned char)g;
        this->data.push_back(pixel);
    }
}

void Image::screen(std::vector<Pixel>& a, std::vector<Pixel>& b) {
    int size = this->width * this->height;
    for(int i=0; i<size; i++) {
        Pixel pixel;
        unsigned char r = (1-(1-(int)a[i].red/255.0f)*(1-(int)b[i].red/255.0f))*255+.5f;
        pixel.red = (unsigned char)r;
        unsigned char bb = (1-(1-(int)a[i].blue/255.0f)*(1-(int)b[i].blue/255.0f))*255+.5f;
        pixel.blue = (unsigned char)bb;
        unsigned char g = (1-(1-(int)a[i].green/255.0f)*(1-(int)b[i].green/255.0f))*255+.5f;
        pixel.green = (unsigned char)g;
        this->data.push_back(pixel);
    }
}

void Image::overlay(std::vector<Pixel>& a, std::vector<Pixel>& b) {
    int size = this->width * this->height;
    for(int i=0; i<size; i++) {
        Pixel pixel;
        if((float)b[i].blue/255 <= 0.5) {
            pixel.blue = (unsigned char)((2*(float)b[i].blue/255*(float)a[i].blue) + .5f);
        }
        else {
            pixel.blue = (unsigned char)((1-(1-(float)a[i].blue/255) * (1-(float)b[i].blue/255)*2)*255+.5);
        }
        if((float)b[i].green/255 <= 0.5) {
            pixel.green = (unsigned char)((2*(float)b[i].green/255*(float)a[i].green) + .5f);
        }
        else {
            pixel.green = (unsigned char)((1-(1-(float)a[i].green/255) * (1-(float)b[i].green/255) * 2)*255+.5f);

        }
        if((float)b[i].red/255 <= 0.5) {
            pixel.red = (unsigned char)((2*(float)b[i].red/255*(float)a[i].red) + .5f);
        }
        else {
            pixel.red = (unsigned char)((1-(1-(float)a[i].red/255) * (1-(float)b[i].red/255) * 2)*255+.5);
        }
        this->data.push_back(pixel);
    }

}
