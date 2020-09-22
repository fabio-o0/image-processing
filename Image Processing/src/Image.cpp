//
//  Image.cpp
//  
//
//  Created by Fabio Suarez on 11/4/19.
//

#include "Image.h"

Image::Image(string name, Header &header, vector<Pixel> &imageData) {
    this->name = name;
    this->header = header;
    this->imageData = imageData;
}

bool Image::operator == (const Image &other) const {
    for (unsigned int i = 0; i < this->imageData.size(); i++) {
        if (this->imageData[i] == other.imageData[i]) {
            return true;
        }
    }
    return false;
}

Image& Image::operator = (Image &image) {
    this->header = image.header;
    this->imageData = image.imageData;
    return *this;
}

Image Image::operator * (Image &image) {
    Image mult;
    mult.header = this->header;
    for (unsigned int i = 0; i < this->imageData.size(); i++) {
        mult.imageData.push_back(this->imageData[i] * image.imageData[i]);
    }
    return mult;
}

Image Image::operator * (const Image &image) {
    Image mult;
    mult.header = this->header;
    for (unsigned int i = 0; i < this->imageData.size(); i++) {
        mult.imageData.push_back(this->imageData[i] * image.imageData[i]);
    }
    return mult;
}

Image Image::operator / (Image &image) {
    Image screen;
    screen.header = this->header;
    for (unsigned int i = 0; i < this->imageData.size(); i++) {
        screen.imageData.push_back(this->imageData[i] / image.imageData[i]);
    }
    return screen;
}

Image Image::operator / (const Image &image) {
    Image screen;
    screen.header = this->header;
    for (unsigned int i = 0; i < this->imageData.size(); i++) {
        screen.imageData.push_back(this->imageData[i] / image.imageData[i]);
    }
    return screen;
}

Image Image::operator - (Image &image) {
    Image minus;
    minus.header = this->header;
    for (unsigned int i = 0; i < this->imageData.size(); i++) {
        minus.imageData.push_back(this->imageData[i] - image.imageData[i]);
    }
    return minus;
}

Image Image::operator - (const Image &image) {
    Image minus;
    minus.header = this->header;
    for (unsigned int i = 0; i < this->imageData.size(); i++) {
        minus.imageData.push_back(this->imageData[i] - image.imageData[i]);
    }
    return minus;
}

Image Image::operator | (Image &image) {
    Image out = *this;
    float screenValue;
    for (unsigned int i = 0; i < image.imageData.size(); i++) {
        if (image.imageData[i].normalRed <= 0.5) {
            out.imageData[i].Red = (2 * out.imageData[i].normalRed * image.imageData[i].normalRed) * 255 + 0.5f < 255 ? (2 * out.imageData[i].normalRed * image.imageData[i].normalRed) * 255 + 0.5f : 255;
        } else {
            screenValue = 1 - 2 * (1 - out.imageData[i].normalRed) * (1 - image.imageData[i].normalRed);
            out.imageData[i].Red = screenValue >= 0 ? screenValue * 255 + 0.5f : 0;
        }
        if (image.imageData[i].normalBlue <= 0.5) {
            out.imageData[i].Blue = (2 * out.imageData[i].normalBlue * image.imageData[i].normalBlue) * 255 + 0.5f < 255 ? (2 * out.imageData[i].normalBlue * image.imageData[i].normalBlue) * 255 + 0.5f : 255;
        } else {
            screenValue = 1 - 2 * (1 - out.imageData[i].normalBlue) * (1 - image.imageData[i].normalBlue);
            out.imageData[i].Blue = screenValue >= 0 ? screenValue * 255 + 0.5f : 0;
        }
        if (image.imageData[i].normalGreen <= 0.5) {
            out.imageData[i].Green = (2 * out.imageData[i].normalGreen * image.imageData[i].normalGreen) * 255 + 0.5f < 255 ? (2 * out.imageData[i].normalGreen * image.imageData[i].normalGreen) * 255 + 0.5f : 255;
        } else {
            screenValue = 1 - 2 * (1 - out.imageData[i].normalGreen) * (1 - image.imageData[i].normalGreen);
            out.imageData[i].Green = screenValue >= 0 ? screenValue * 255 + 0.5f : 0;
        }
    }
    return out;
}

Image Image::addRed(const int &num) {
    Image out = *this;
    for (unsigned int i = 0; i < out.imageData.size(); i++) {
        out.imageData[i].Red = (int) out.imageData[i].Red + num < 255 ? (int) out.imageData[i].Red + num : 255;
    }
    return out;
}

Image Image::addGreen(const int &num) {
    Image out = *this;
    for (unsigned int i = 0; i < out.imageData.size(); i++) {
        out.imageData[i].Green = (int) out.imageData[i].Green + num < 255 ? (int) out.imageData[i].Green + num : 255;
    }
    return out;
}

Image Image::addBlue(const int &num) {
    Image out = *this;
    for (unsigned int i = 0; i < out.imageData.size(); i++) {
        out.imageData[i].Blue = (int) out.imageData[i].Blue + num < 255 ? (int) out.imageData[i].Blue + num : 255;
    }
    return out;
}

Image Image::timesRed(const int &factor) {
    Image out = *this;
    for (unsigned int i = 0; i < out.imageData.size(); i++) {
        out.imageData[i].Red = (out.imageData[i].normalRed * factor) * 255 + 0.5f < 255 ? (out.imageData[i].normalRed * factor) * 255 + 0.5f : 255;
    }
    return out;
}

Image Image::timesGreen(const int &factor) {
    Image out = *this;
    for (unsigned int i = 0; i < out.imageData.size(); i++) {
        out.imageData[i].Green = (out.imageData[i].normalGreen * factor) * 255 + 0.5f < 255 ? (out.imageData[i].normalGreen * factor) * 255 + 0.5f : 255;
    }
    return out;
}

Image Image::timesBlue(const int &factor) {
    Image out = *this;
    for (unsigned int i = 0; i < out.imageData.size(); i++) {
        out.imageData[i].Blue = (out.imageData[i].normalBlue * factor) * 255 + 0.5f < 255 ? (out.imageData[i].normalBlue * factor) * 255 + 0.5f : 255;
    }
    return out;
}

Image Image::isolateRed() {
    Image out = *this;
    for (unsigned int i = 0; i < out.imageData.size(); i++) {
        out.imageData[i].Green = out.imageData[i].Red;
        out.imageData[i].Blue = out.imageData[i].Red;
    }
    return out;
}

Image Image::isolateGreen() {
    Image out = *this;
    for (unsigned int i = 0; i < out.imageData.size(); i++) {
        out.imageData[i].Red = out.imageData[i].Green;
        out.imageData[i].Blue = out.imageData[i].Green;
    }
    return out;
}


Image Image::isolateBlue() {
    Image out = *this;
    for (unsigned int i = 0; i < out.imageData.size(); i++) {
        out.imageData[i].Red = out.imageData[i].Blue;
        out.imageData[i].Green = out.imageData[i].Blue;
    }
    return out;
}

Image Image::rotate180() {
    Image out = *this;
    vector< vector<Pixel> > xyPixels(out.header.width);
    for (int i = 0; i < out.header.width; i++) {
        xyPixels[i].resize(out.header.height);
    }
    
    int counter = 0;
    for (unsigned int i = 0; i < out.header.width; i++) {
        for (unsigned int j = 0; j < out.header.height; j++) {
            xyPixels[i][j] = out.imageData[counter];
            counter++;
        }
    }
    
    counter = 0;
    for (unsigned int i = 0; i < out.header.width; i++) {
        for (unsigned int j = 0; j < out.header.height; j++) {
            out.imageData[counter] = xyPixels[out.header.width - 1 - i][out.header.height - 1 - j];
            counter++;
        }
    }
    
    return out;
}
