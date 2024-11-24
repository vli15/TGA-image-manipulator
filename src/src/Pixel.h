//
// Created by vli15 on 11/4/2024.
//

#ifndef PIXEL_H
#define PIXEL_H

class Pixel {

public:
    unsigned char red;
    unsigned char blue;
    unsigned char green;
    Pixel(unsigned char& r, unsigned char& b, unsigned char& g);
    Pixel();
    unsigned char getRed();
    unsigned char getBlue();
    unsigned char getGreen();
    void setRed(unsigned char& r);
    void setBlue(unsigned char& b);
    void setGreen(unsigned char& g);

};




#endif //PIXEL_H
