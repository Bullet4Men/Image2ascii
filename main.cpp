#include <iostream>
#include <fstream>
#include <cmath>
#include <ImageMagick-7/Magick++.h>
#include <ImageMagick-7/Magick++/Color.h>
#include "argument-parser.h"

double intensity(const Magick::Image& image, const ssize_t & x, const ssize_t & y) {
    Magick::ColorRGB pixel = image.pixelColor(x, y);
    double red = pixel.red() * 255;
    double green = pixel.green() * 255;
    double blue = pixel.blue() * 255;

    return (red + green + blue) / 3;
}

size_t convertToIndex(double number, size_t count_of_symbols, size_t size) {
    return number * count_of_symbols / size;
}

int main(int argc, char **argv)
{
    ArgumentParser& parser = ArgumentParser::getInstance();
    parser.parseArguments(argc, argv);
    std::string filePath;
    std::string outputFilePath;
    std::ofstream file;
    size_t width = 50;
    size_t height = 40;

    if (parser.hasAnyArgument("-h", "--help")) {
        std::cout << "Image to ASCII is the process of converting an image into text character art.\n"
                     "-h  --help\tshow help message\n"
                     "-p  --path\tspecifies the path to the image file that will be converted to ASCII art. [required]\n"
                     "-H  --height\tit determines the height of the output image and also takes an integer value. [default value 100]\n"
                     "-W  --width\tit specifies the width of the output image and also takes an integer value. [default value 100]\n"
                     "-o  --output\tdefines the path to the file where the result will be saved\n";
        return 0;
    }

    if (parser.hasAnyArgument("-p", "--path"))
        filePath = parser.returnValue("-p", "--path");
    else
        throw std::runtime_error("Missing required argument --path or -p");

    if (parser.hasAnyArgument("-o", "--output"))
        outputFilePath = parser.returnValue("-o", "--output");

    bool show = parser.hasAnyArgument("-s", "--show");

    if (parser.hasAnyArgument("-W", "--width"))
        width = std::stoi(parser.returnValue("-W", "--width"));
    if (parser.hasAnyArgument("-H", "--height"))
        height = std::stoi(parser.returnValue("-H", "--height"));

    Magick::InitializeMagick("");

    std::string symbols = R"(_.,:-=+;cba?!0123456789$W#@N)";

    Magick::Image image;
    try {
        image.read(filePath);

        if (!outputFilePath.empty())
            file.open(outputFilePath);

        std::string result = std::to_string(width);
        result += "x";
        result += std::to_string(height);
        result += "!";

        image.resize(result);

        for(ssize_t y = 0; y < height; y++) {
            for(ssize_t x = 0; x < width; x++) {
                double brightness = intensity(image, x, y);
                size_t index = convertToIndex(brightness, symbols.size(), 255);

                if (!outputFilePath.empty())
                    file << symbols[index];
                if (show)
                    std::cout << symbols[index];
            }
            if (!outputFilePath.empty())
                file << '\n';
            if (show)
                std::cout << '\n';
        }

        file.close();
    }
    catch( std::exception &error_ )
    {
        std::cerr << "Caught exception: " << error_.what() << '\n';
        return 1;
    }
    return 0;
}
