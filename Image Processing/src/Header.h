//
//  Header.h
//  ImageProcessing
//
//  Created by Fabio Suarez on 11/4/19.
//  Copyright © 2019 Fabio Suarez. All rights reserved.
//

#pragma once

struct Header {
    char  idLength;
    char  colorMapType;
    char  imageType;
    short colorMapOrigin;
    short colorMapLength;
    char  colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char  pixelDepth;
    char  imageDescriptor;
};
