#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Image.h"
using namespace std;

template <typename T>
T read(fstream &file) {
    T temp;
    file.read((char*)&temp, sizeof(temp));
    return temp;
}

Image readFile(const string &fileName) {
    Image image;
    string name = fileName.substr(6);
    name.pop_back();
    name.pop_back();
    name.pop_back();
    name.pop_back();
    image.name = name;
    fstream file(fileName, ios_base::in | ios_base::binary);
    if (file.is_open()) {
        image.header.idLength = read<char>(file);
        image.header.colorMapType = read<char>(file);
        image.header.imageType = read<char>(file);
        image.header.colorMapOrigin = read<short>(file);
        image.header.colorMapLength = read<short>(file);
        image.header.colorMapDepth = read<char>(file);
        image.header.xOrigin = read<short>(file);
        image.header.yOrigin = read<short>(file);
        image.header.width = read<short>(file);
        image.header.height = read<short>(file);
        image.header.pixelDepth = read<char>(file);
        image.header.imageDescriptor = read<char>(file);
        for (unsigned int i = 0; i < image.header.width * image.header.height; i++) {
            Pixel newpix;
            newpix.Blue = read<unsigned char>(file);
            newpix.Green = read<unsigned char>(file);
            newpix.Red = read<unsigned char>(file);
            newpix.normalBlue = (float) newpix.Blue / 255;
            newpix.normalGreen = (float) newpix.Green / 255;
            newpix.normalRed = (float) newpix.Red / 255;
            image.imageData.push_back(newpix);
        }
    }
    file.close();
    return image;
}

void writeFile(const Image &image, const string &fileName) {
    ofstream outFile(fileName, ios_base::out | ios_base::binary);
    outFile.write((char*)&image.header.idLength, 1);
    outFile.write((char*)&image.header.colorMapType, 1);
    outFile.write((char*)&image.header.imageType, 1);
    outFile.write((char*)&image.header.colorMapOrigin, 2);
    outFile.write((char*)&image.header.colorMapLength, 2);
    outFile.write((char*)&image.header.colorMapDepth, 1);
    outFile.write((char*)&image.header.xOrigin, 2);
    outFile.write((char*)&image.header.yOrigin, 2);
    outFile.write((char*)&image.header.width, 2);
    outFile.write((char*)&image.header.height, 2);
    outFile.write((char*)&image.header.pixelDepth, 1);
    outFile.write((char*)&image.header.imageDescriptor, 1);
    for (unsigned int i = 0; i < image.imageData.size(); i++) {
        outFile.write((char*)&image.imageData[i].Blue, 1);
        outFile.write((char*)&image.imageData[i].Green, 1);
        outFile.write((char*)&image.imageData[i].Red, 1);
    }
    outFile.close();
}

Image combineChannels(Image &red, Image &green, Image &blue) {
    Image out = red;
    for (unsigned int i = 0; i < out.imageData.size(); i++) {
        out.imageData[i].Green = green.imageData[i].Green;
        out.imageData[i].Blue = blue.imageData[i].Blue;
    }
    return out;
}
    
int testImages(const Image &image1, const Image &image2) {
    string example = image2.name;
    example.erase(0, 3);
    cout << "Testing " << image1.name << " against " << example << "..." << endl;
    if (image1 == image2) {
        cout << "Images match. Test passed." << endl;
        return 1;
    } else {
        cout << "Images do not match. Test failed." << endl;
        return 0;
    }
}

int main(int argc, const char * argv[]) {
    
    //Get all images
    Image layer1 = readFile("./input/layer1.tga");
    Image layer2 = readFile("./input/layer2.tga");
    Image pattern1 = readFile("./input/pattern1.tga");
    Image pattern2 = readFile("./input/pattern2.tga");
    Image text = readFile("./input/text.tga");
    Image text2 = readFile("./input/text2.tga");
    Image car = readFile("./input/car.tga");
    Image circles = readFile("./input/circles.tga");
    Image layer_blue = readFile("./input/layer_blue.tga");
    Image layer_green = readFile("./input/layer_green.tga");
    Image layer_red = readFile("./input/layer_red.tga");
    
    Image EXAMPLE_part1 = readFile("./examples/EXAMPLE_part1.tga");
    Image EXAMPLE_part2 = readFile("./examples/EXAMPLE_part2.tga");
    Image EXAMPLE_part3 = readFile("./examples/EXAMPLE_part3.tga");
    Image EXAMPLE_part4 = readFile("./examples/EXAMPLE_part4.tga");
    Image EXAMPLE_part5 = readFile("./examples/EXAMPLE_part5.tga");
    Image EXAMPLE_part6 = readFile("./examples/EXAMPLE_part6.tga");
    Image EXAMPLE_part7 = readFile("./examples/EXAMPLE_part7.tga");
    Image EXAMPLE_part8_r = readFile("./examples/EXAMPLE_part8_r.tga");
    Image EXAMPLE_part8_g = readFile("./examples/EXAMPLE_part8_g.tga");
    Image EXAMPLE_part8_b = readFile("./examples/EXAMPLE_part8_b.tga");
    Image EXAMPLE_part9 = readFile("./examples/EXAMPLE_part9.tga");
    Image EXAMPLE_part10 = readFile("./examples/EXAMPLE_part10.tga");
    
    int testsPassed = 0;
    double totalTests = 12;
    
    //Part 1
    cout << "Multiplying layer1 and pattern1..." << endl;
    Image part1 = layer1 * pattern1;
    writeFile(part1, "./output/part1.tga");
    testsPassed += testImages(part1, EXAMPLE_part1);
    cout << endl;
    
    //Part 2
    cout << "Subtracting layer2 from car..." << endl;
    Image part2 = car - layer2;
    writeFile(part2, "./output/part2.tga");
    testsPassed += testImages(part2, EXAMPLE_part2);
    cout << endl;
    
    //Part 3
    cout << "Multiplying layer1 and pattern2, then Screening it with text..." << endl;
    Image part3 = text / (layer1 * pattern2);
    writeFile(part3, "./output/part3.tga");
    testsPassed += testImages(part3, EXAMPLE_part3);
    cout << endl;
    
    //Part 4
    cout << "Multiplying layer2 and circles, then Subtracting pattern2 from it..." << endl;
    Image part4 = (layer2 * circles) - pattern2;
    writeFile(part4, "./output/part4.tga");
    testsPassed += testImages(part4, EXAMPLE_part4);
    cout << endl;
    
    //Part 5
    cout << "Overlaying layer1 and pattern1..." << endl;
    Image part5 = layer1 | pattern1;
    writeFile(part5, "./output/part5.tga");
    testsPassed += testImages(part5, EXAMPLE_part5);
    cout << endl;
    
    //Part 6
    cout << "Adding 200 to car's green channel..." << endl;
    Image part6 = car.addGreen(200);
    writeFile(part6, "./output/part6.tga");
    testsPassed += testImages(part6, EXAMPLE_part6);
    cout << endl;
    
    //Part 7
    cout << "Multiplying car's red channel by 4 and car's blue channel by 0..." << endl;
    Image part7 = car.timesRed(4).timesBlue(0);
    writeFile(part7, "./output/part7.tga");
    testsPassed += testImages(part7, EXAMPLE_part7);
    cout << endl;
    
    //Part 8
    cout << "Isolating car's red channel..." << endl;
    Image part8_r = car.isolateRed();
    cout << "Isolating car's green channel..." << endl;
    Image part8_g = car.isolateGreen();
    cout << "Isolating car's blue channel..." << endl;
    Image part8_b = car.isolateBlue();
    writeFile(part8_r, "./output/part8_r.tga");
    writeFile(part8_g, "./output/part8_g.tga");
    writeFile(part8_b, "./output/part8_b.tga");
    testsPassed += testImages(part8_r, EXAMPLE_part8_r);
    testsPassed += testImages(part8_g, EXAMPLE_part8_g);
    testsPassed += testImages(part8_b, EXAMPLE_part8_b);
    cout << endl;
    
    //Part 9
    cout << "Combining the RGB channels of layer_red (R), layer_green (G), and layer_blue (B)..." << endl;
    Image part9 = combineChannels(layer_red, layer_green, layer_blue);
    writeFile(part9, "./output/part9.tga");
    testsPassed += testImages(part9, EXAMPLE_part9);
    cout << endl;
    
    //Part 10
    cout << "Rotating text2 by 180 degrees..." << endl;
    Image part10 = text2.rotate180();
    writeFile(part10, "./output/part10.tga");
    testsPassed += testImages(part10, EXAMPLE_part10);
    cout << endl;
    
    cout << "Total tests passed: " << testsPassed << "/" << totalTests << ": " << ( testsPassed / totalTests) * 100 << setprecision(2) << "%" << endl;
    
    return 0;
}
