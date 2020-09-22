//
//  Image.h
//  ImageProcessing
//
//  Created by Fabio Suarez on 11/4/19.
//  Copyright © 2019 Fabio Suarez. All rights reserved.
//

#pragma once

struct Pixel {
    unsigned char Red;
    unsigned char Green;
    unsigned char Blue;
    float normalRed;
    float normalGreen;
    float normalBlue;
    
    Pixel() {}
    
    Pixel(unsigned char Red, unsigned char Green, unsigned char Blue);
    
    bool operator == (const Pixel &other) const;
    
    Pixel operator * (Pixel &pix);
    
    Pixel operator * (const Pixel &pix);
    
    friend Pixel operator * (const int &factor, Pixel &pix) {
        return Pixel((factor * pix.normalRed) * 255 + 0.5f, (factor * pix.normalGreen) * 255 + 0.5f, (factor * pix.normalBlue) * 255 + 0.5f);
    }
    
    friend Pixel operator * (const int &factor, const Pixel &pix) {
        return Pixel((factor * pix.normalRed) * 255 + 0.5f, (factor * pix.normalGreen) * 255 + 0.5f, (factor * pix.normalBlue) * 255 + 0.5f);
    }
    
    Pixel operator / (Pixel &pix);
    
    Pixel operator / (const Pixel &pix);
    
    friend Pixel operator / (const Pixel &pix1, const Pixel &pix2) {
        return Pixel((1 - (1 - pix1.normalRed) * (1 - pix2.normalRed)) * 255 + 0.5f, (1 - (1 - pix1.normalGreen) * (1 - pix2.normalGreen)) * 255 + 0.5f, (1 - (1 - pix1.normalBlue) * (1 - pix2.normalBlue)) * 255 + 0.5f);
    }
    
    Pixel operator - (Pixel &pix);
    
    Pixel operator - (const Pixel &pix);
};
