//
//  Image.cpp
//  ImageProcessing
//
//  Created by Fabio Suarez on 11/4/19.
//  Copyright © 2019 Fabio Suarez. All rights reserved.
//

#include <stdio.h>
#include "Pixel.h"

Pixel::Pixel(unsigned char Red, unsigned char Green, unsigned char Blue) {
    this->Red = Red;
    this->Green = Green;
    this->Blue = Blue;
    this->normalRed = (float) Red / 255;
    this->normalGreen = (float) Green / 255;
    this->normalBlue = (float) Blue / 255;
}

bool Pixel::operator == (const Pixel &other) const {
    if(
       this->Red == other.Red &&
       this->Green == other.Green &&
       this->Blue == other.Blue
       )
    {
        return true;
    }
    return false;
}

Pixel Pixel::operator * (Pixel &pix) {
    return Pixel((this->normalRed * pix.normalRed) * 255 + 0.5f, (this->normalGreen * pix.normalGreen) * 255 + 0.5f, (this->normalBlue * pix.normalBlue) * 255 + 0.5f);
}

Pixel Pixel::operator * (const Pixel &pix) {
    return Pixel((this->normalRed * pix.normalRed) * 255 + 0.5f, (this->normalGreen * pix.normalGreen) * 255 + 0.5f, (this->normalBlue * pix.normalBlue) * 255 + 0.5f);
}

Pixel Pixel::operator / (Pixel &pix) {
    return Pixel((1 - (1 - this->normalRed) * (1 - pix.normalRed)) * 255 + 0.5f, (1 - (1 - this->normalGreen) * (1 - pix.normalGreen)) * 255 + 0.5f, (1 - (1 - this->normalBlue) * (1 - pix.normalBlue)) * 255 + 0.5f);
}

Pixel Pixel::operator / (const Pixel &pix) {
    return Pixel((1 - (1 - this->normalRed) * (1 - pix.normalRed)) * 255 + 0.5f, (1 - (1 - this->normalGreen) * (1 - pix.normalGreen)) * 255 + 0.5f, (1 - (1 - this->normalBlue) * (1 - pix.normalBlue)) * 255 + 0.5f);
}

Pixel Pixel::operator - (Pixel &pix) {
    return Pixel((int) this->Red - (int) pix.Red > 0 ? (unsigned char) ((int)this->Red - (int)pix.Red) : 0, (int) this->Green - (int) pix.Green > 0 ? (unsigned char) ((int) this->Green - (int) pix.Green) : 0, (int) this->Blue - (int) pix.Blue > 0 ? (unsigned char) ((int) this->Blue - (int) pix.Blue) : 0);
}

Pixel Pixel::operator - (const Pixel &pix) {
    return Pixel((int) this->Red - (int) pix.Red > 0 ? (unsigned char) ((int) this->Red - (int)pix.Red) : 0, (int) this->Green - (int) pix.Green > 0 ? (unsigned char) ((int) this->Green - (int) pix.Green) : 0, (int) this->Blue - (int) pix.Blue > 0 ? (unsigned char) ((int) this->Blue - (int) pix.Blue) : 0);
}
