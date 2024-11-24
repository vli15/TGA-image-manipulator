#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include "Header.h"
#include "Pixel.h"
#include "Image.h"

// struct __attribute__((__packed__)) header{
//
// };

void readFile(string name, Header& headerObject, Image& image) {
    ifstream myFile(name, ios::binary);
    // cout<<"Opening file..."<<name<<endl;
    if (myFile.is_open()) {
        // cout<<"Opening file...done"<<endl;
        myFile.read(&headerObject.idLength, sizeof(headerObject.idLength));
        myFile.read(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
        myFile.read(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
        myFile.read(reinterpret_cast<char *>(&headerObject.colorMapOrigin), sizeof(headerObject.colorMapOrigin));
        myFile.read(reinterpret_cast<char*>(&headerObject.colorMapLength), sizeof(headerObject.colorMapLength));
        myFile.read(&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
        myFile.read(reinterpret_cast<char*>(&headerObject.xOrigin), sizeof(headerObject.xOrigin));
        myFile.read(reinterpret_cast<char*>(&headerObject.yOrigin), sizeof(headerObject.yOrigin));
        myFile.read(reinterpret_cast<char*>(&headerObject.width), sizeof(headerObject.width));
        myFile.read(reinterpret_cast<char*>(&headerObject.height), sizeof(headerObject.height));
        myFile.read(&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
        myFile.read(&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));
        int imageSize = headerObject.width * headerObject.height; //amount of pixels contained in the file
        vector<Pixel>& imagePixels = image.data;
        for(int i = 0; i < imageSize; i++) {
            Pixel pixel;
            myFile.read(reinterpret_cast<char*>(&pixel.blue), sizeof(char));
            myFile.read(reinterpret_cast<char*>(&pixel.green), sizeof(char));
            myFile.read(reinterpret_cast<char*>(&pixel.red), sizeof(char));
            imagePixels.push_back(pixel);
        }
    }
}

void writeFile(string name, Header& headerObject, Image& image) {
    // cout<<"writing file..."<<name<<endl;
    int imageSize = headerObject.width * headerObject.height;
    vector<Pixel>& imagePixels = image.data;
    ofstream outStream(name, std::ios::binary);
        outStream.write(&headerObject.idLength, sizeof(headerObject.idLength));
        outStream.write(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
        outStream.write(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
        outStream.write(reinterpret_cast<char *>(&headerObject.colorMapOrigin), sizeof(headerObject.colorMapOrigin));
        outStream.write(reinterpret_cast<char*>(&headerObject.colorMapLength), sizeof(headerObject.colorMapLength));
        outStream.write(&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
        outStream.write(reinterpret_cast<char*>(&headerObject.xOrigin), sizeof(headerObject.xOrigin));
        outStream.write(reinterpret_cast<char*>(&headerObject.yOrigin), sizeof(headerObject.yOrigin));
        outStream.write(reinterpret_cast<char*>(&headerObject.width), sizeof(headerObject.width));
        outStream.write(reinterpret_cast<char*>(&headerObject.height), sizeof(headerObject.height));
        outStream.write(&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
        outStream.write(&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));

        for(int i = 0; i < imageSize; i++) {
            // Pixel& pixel = imagePixels[i];
            outStream.write(reinterpret_cast<char*>(&imagePixels[i].blue), sizeof(char));
            outStream.write(reinterpret_cast<char*>(&imagePixels[i].green), sizeof(char));
            outStream.write(reinterpret_cast<char*>(&imagePixels[i].red), sizeof(char));
            // imagePixels.push_back(imagePixels[i]);
        }
    // cout<<"done"<<endl;
        outStream.close();
    }

// void test(vector<Pixel>& a, vector<Pixel>& b) {
//     int size = a.size();
//     bool same = true;
//     for(int i=0; i<size; i++) {
//         if(a[i].red == b[i].red && a[i].green == b[i].green && a[i].blue == b[i].blue) {
//             same = true;
//         }
//         else {
//             same = false;
//             break;
//         }
//     }
//     if(same) {
//         cout<<"Success!"<<endl;
//     }
//     else {
//         cout<<"Failed!"<<endl;
//     }
// }

int main() {
    Header head;
    string testing;
    //part1
    Image layer1(head.width, head.height);
    string in = "input/layer1.tga";
    readFile(in, head, layer1); //vector gets filled up with the pixels
    Image pattern1(head.width, head.height);
    string patIn = "input/pattern1.tga";
    readFile(patIn, head, pattern1);
    Image part1(head.width, head.height);
    part1.multiply(layer1.data, pattern1.data);
    string p1 = "output/part1.tga";
    writeFile(p1, head, part1);

    // testing = "examples/EXAMPLE_part1.tga";
    // Image testImage(head.width, head.height);
    // readFile(testing, head, testImage);
    // cout<<"part1: ";
    // test(part1.data, testImage.data);

    // //part2
    Image layer2(head.width, head.height);
    string l2 = "input/layer2.tga";
    readFile(l2, head, layer2);
    Image car(head.width, head.height);
    string carString = "input/car.tga";
    readFile(carString, head, car);
    Image part2(head.width, head.height);
    part2.subtract(car.data, layer2.data);
    string p2 = "output/part2.tga";
    writeFile(p2, head, part2);

    // testing = "examples/EXAMPLE_part2.tga";
    // Image testImage2(head.width, head.height);
    // readFile(testing, head, testImage2);
    // cout<<"part2: ";
    // test(part2.data, testImage2.data);

    //part 3
    Image layer1p3(head.width, head.height);
    Image pattern1p3(head.width, head.height);
    readFile(in, head, layer1p3); //vector gets filled up with the pixels
    string pattern2p3 = "input/pattern2.tga";
    readFile(pattern2p3, head, pattern1p3);
    Image tempResult(head.width, head.height);
    tempResult.multiply(layer1p3.data, pattern1p3.data);
    string tempFile = "output/temp.tga";
    string t = "input/text.tga";
    Image text(head.width, head.height);
    readFile(t, head, text);
    Image part3(head.width, head.height);
    part3.screen(text.data, tempResult.data);
    string p3 = "output/part3.tga";
    writeFile(p3, head, part3);

    // testing = "examples/EXAMPLE_part3.tga";
    // Image testImage3(head.width, head.height);
    // readFile(testing, head, testImage3);
    // cout<<"part3: ";
    // test(part3.data, testImage3.data);

    //part 4
    Image circles(head.width, head.height);
    Image layer2p4(head.width, head.height);
    Image pattern1p4(head.width, head.height);
    string fileName1 = "input/layer2.tga";
    string fileName2 = "input/circles.tga";
    string fileName3 = "input/pattern2.tga";
    readFile(fileName1,head,layer2p4);
    readFile(fileName2, head, circles);
    readFile(fileName3, head, pattern1p4);
    Image tempResult1(head.width, head.height);
    tempResult1.multiply(layer2p4.data, circles.data);
    Image part4(head.width, head.height);
    part4.subtract(tempResult1.data, pattern1p4.data);
    string p4 = "output/part4.tga";
    writeFile(p4, head, part4);

    // testing = "examples/EXAMPLE_part4.tga";
    // Image testImage4(head.width, head.height);
    // readFile(testing, head, testImage4);
    // cout<<"part4: ";
    // test(part4.data, testImage4.data);

    //part 5
    readFile(in, head, layer1);
    readFile(patIn, head, pattern1);
    Image part5(head.width, head.height);
    string output = "output/part5.tga";
    part5.overlay(layer1.data, pattern1.data);
    writeFile(output, head, part5);

    // testing = "examples/EXAMPLE_part5.tga";
    // Image testImage5(head.width, head.height);
    // readFile(testing, head, testImage5);
    // cout<<"part5: ";
    // test(part5.data, testImage5.data);

    //part 6
    string carName = "input/car.tga";
    Image car6(head.width, head.height);
    readFile(carName, head, car6);
    vector<Pixel> &pixelData = car6.data;
    int size = head.width*head.height;
    for(int i=0; i<size; i++) {
        Pixel &pixel = pixelData[i];
        unsigned char g = (unsigned char)min(255,pixel.green + 200);
        // if((int)g>255){g=(unsigned char)255;}
        pixel.green = g;
    }
    string p6 = "output/part6.tga";
    writeFile(p6, head, car6);

    // testing = "examples/EXAMPLE_part6.tga";
    // Image testImage6(head.width, head.height);
    // readFile(testing, head, testImage6);
    // cout<<"part6: ";
    // test(car6.data, testImage6.data);

    //part 7
    Image car7(head.width, head.height);
    readFile(carName, head, car7);
    vector<Pixel> &pixelDatacar = car7.data;
    for(int i=0; i<size; i++) {
        Pixel &pixel = pixelDatacar[i];
        unsigned char r = (unsigned char)min(255,pixel.red*4);
        pixel.red = r;
        unsigned char b = (unsigned char)((int)pixel.blue * 0);
        pixel.blue = b;
    }
    string p7 = "output/part7.tga";
    writeFile(p7, head, car7);

    // testing = "examples/EXAMPLE_part7.tga";
    // Image testImage7(head.width, head.height);
    // readFile(testing, head, testImage7);
    // cout<<"part7: ";
    // test(car7.data, testImage7.data);

    //part 8_g
    Image car8g(head.width, head.height);
    string rFile = "output/part8_r.tga";
    string gFile = "output/part8_g.tga";
    string bFile = "output/part8_b.tga";
    readFile(carName, head, car8g);
    for(int i=0; i<size; i++) { //changing everything to equal to green's value
        Pixel &pixel = car8g.data[i];
        int g= (int)pixel.green;
        pixel.red = (unsigned char)g;
        pixel.blue = (unsigned char)g;
    }
    writeFile(gFile, head, car8g);
    // testing = "examples/EXAMPLE_part8_g.tga";
    // Image testImage8g(head.width, head.height);
    // readFile(testing, head, testImage8g);
    // cout<<"part8g: ";
    // test(car8g.data, testImage8g.data);

    //part 8_b
    Image car8b(head.width, head.height);
    readFile(carName, head, car8b);
    for(int i=0; i<size; i++) { //changing everything to equal to green's value
        Pixel &pixel = car8b.data[i];
        int g= (int)pixel.blue;
        pixel.red = (unsigned char)g;
        pixel.green = (unsigned char)g;
    }
    writeFile(bFile, head, car8b);

    // testing = "examples/EXAMPLE_part8_b.tga";
    // Image testImage8b(head.width, head.height);
    // readFile(testing, head, testImage8b);
    // cout<<"part8b: ";
    // test(car8b.data, testImage8b.data);

    //part 8_r
    Image car8r(head.width, head.height);
    readFile(carName, head, car8r);
    for(int i=0; i<size; i++) { //changing everything to equal to green's value
        Pixel &pixel = car8r.data[i];
        int g= (int)pixel.red;
        pixel.green = (unsigned char)g;
        pixel.blue = (unsigned char)g;
    }
    writeFile(rFile, head, car8r);
    // testing = "examples/EXAMPLE_part8_r.tga";
    // Image testImage8r(head.width, head.height);
    // readFile(testing, head, testImage8r);
    // cout<<"part8r: ";
    // test(car8r.data, testImage8r.data);

    //part 9
    string r = "input/layer_red.tga";
    string g = "input/layer_green.tga";
    string b = "input/layer_blue.tga";
    Image part9(head.width, head.height);
    Image red(head.width, head.height);
    readFile(r, head, red);
    Image green(head.width, head.height);
    readFile(g, head, green);
    Image blue(head.width, head.height);
    readFile(b, head, blue);
    for(int i=0; i < size; i++) {
        Pixel pixel;
        pixel.red = red.data[i].red;
        pixel.green = green.data[i].green;
        pixel.blue = blue.data[i].blue;
        part9.data.push_back(pixel);
    }
    string p9 = "output/part9.tga";
    writeFile(p9, head, part9);

    // testing = "examples/EXAMPLE_part9.tga";
    // Image testImage9(head.width, head.height);
    // readFile(testing, head, testImage9);
    // cout<<"part9: ";
    // test(part9.data, testImage9.data);

    //part 10
    string name = "input/text2.tga";
    Image textImage(head.width, head.height);
    Image part10(head.width, head.height);
    string p10 = "output/part10.tga";
    readFile(name, head, textImage);
    int size10 = head.width*head.height;
    for(int i =size10-1; i >= 0; i--) {
        Pixel pixel = textImage.data[i];
        part10.data.push_back(pixel);
    }
    writeFile(p10, head, part10);
    // testing = "examples/EXAMPLE_part10.tga";
    // Image testImage10(head.width, head.height);
    // readFile(testing, head, testImage10);
    // cout<<"part10: ";
    // test(part10.data, testImage10.data);

    //extra credit
    // string ec = "output/extracredit.tga";
    // Image extracredit(head.width*2, head.height*2);
    // string first = "input/car.tga";
    // string second = "input/circles.tga";
    // string third = "input/pattern1.tga";
    // string fourth = "input/text.tga";
    // Image uno(head.width, head.height);
    // Image dos(head.width, head.height);
    // Image tres(head.width, head.height);
    // Image cuatro(head.width, head.height);
    // readFile(first, head, uno);
    // readFile(second, head, dos);
    // readFile(third, head, tres);
    // readFile(fourth, head, cuatro);
    // for(int i=0; i<head.width*2; i++) {
    //     for(int j=0; j<head.height*2; j++) {
    //         Pixel pixel;
    //         if(i<=head.width && j<=head.height) {
    //             pixel = uno.data[i];
    //         }
    //         else if(i>head.width && j<=head.height) {
    //             pixel = dos.data[i];
    //         }
    //         else if(i>head.width && j>head.height) {
    //             pixel = tres.data[i];
    //         }
    //         else {
    //             pixel = cuatro.data[i];
    //         }
    //         extracredit.data.push_back(pixel);
    //     }
    // }
    // writeFile(ec, head, extracredit);
    return 0;
}



// vector<Pixel> imageData;
//
// for(int i = 0; i < imageSize; i++) {
//     unsigned char red, green, blue;
//
//     myFile.read(reinterpret_cast<char*>(&red), sizeof(red));
//     myFile.read(reinterpret_cast<char*>(&green), sizeof(blue));
//     myFile.read(reinterpret_cast<char*>(&blue), sizeof(green));
//
//     imageData.emplace_back(red, green, blue);
// }
