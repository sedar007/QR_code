#include "../include/QRCodeGenerator.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <URL>" << std::endl;
        return EXIT_FAILURE;
    }
    QRCodeGenerator generator;
    if (generator.generate(argv[1], "qrcode.png"))
        std::cout << "QR code generated and saved to qrcode.png" << std::endl;
    else
        std::cout << "Failed to generate QR code" << std::endl;
    return EXIT_SUCCESS;
}
