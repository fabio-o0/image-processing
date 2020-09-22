//
//  Image.h
//  
//
//  Created by Fabio Suarez on 11/4/19.
//

#pragma once
#include <string>
#include <vector>
#include "Pixel.h"
#include "Header.h"

using namespace std;

struct Image {
    string name;
    Header header;
    vector<Pixel> imageData;
    
    Image() {}
    
    Image(string name, Header &header, vector<Pixel> &imageData);
    
    bool operator == (const Image &other) const;
    
    Image& operator = (Image &image);
    
    Image operator * (Image &image);
    
    Image operator * (const Image &image);
    
    friend Image operator * (const int &factor, Image &image) {
        Image mult;
        mult.header = image.header;
        for (unsigned int i = 0; i < image.imageData.size(); i++) {
            mult.imageData.push_back(factor * image.imageData[i]);
        }
        return mult;
    }
    
    friend Image operator * (const int &factor, const Image &image) {
        Image mult;
        mult.header = image.header;
        for (unsigned int i = 0; i < image.imageData.size(); i++) {
            mult.imageData.push_back(factor * image.imageData[i]);
        }
        return mult;
    }
    
    Image operator / (Image &image);
    
    Image operator / (const Image &image);
    
    friend Image operator / (const Image &image1, const Image &image2) {
        Image screen;
        screen.header = image1.header;
        for (unsigned int i = 0; i < image1.imageData.size(); i++) {
            screen.imageData.push_back(image1.imageData[i] / image2.imageData[i]);
        }
        return screen;
    }
    
    Image operator - (Image &image);
    
    Image operator - (const Image &image);
    
    Image operator | (Image &image);
    
    Image addRed(const int &num);

    Image addGreen(const int &num);

    Image addBlue(const int &num);

    Image timesRed(const int &factor);

    Image timesGreen(const int &factor);

    Image timesBlue(const int &factor);
    
    Image isolateRed();
    
    Image isolateGreen();
    
    Image isolateBlue();
    
    Image rotate180();
};
