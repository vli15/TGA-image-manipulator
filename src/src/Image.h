//
// Created by vli15 on 11/7/2024.
//

#ifndef IMAGE_H
#define IMAGE_H
#include <vector>
#include "Pixel.h"


class Image {
public:
    int width;
    int height;
    Image(int h, int w);
    std::vector<Pixel> data;

void multiply(std::vector<Pixel>& a, std::vector<Pixel>& b);
    void subtract(std::vector<Pixel>& a, std::vector<Pixel>& b);
    void overlay(std::vector<Pixel>& a, std::vector<Pixel>& b);
    void screen(std::vector<Pixel>& a, std::vector<Pixel>& b);
};



#endif //IMAGE_H
