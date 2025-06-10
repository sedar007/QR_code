#include "../include/QRCodeGenerator.h"
#include <qrencode.h>
#include <png.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

bool QRCodeGenerator::generate(const std::string& url, const std::string& filename) {
    QRcode* qrcode = QRcode_encodeString(url.c_str(), 0, QR_ECLEVEL_L, QR_MODE_8, 1);
    if (!qrcode) {
        std::cerr << "Error: Failed to encode QR code" << std::endl;
        return false;
    }

    int width = qrcode->width;
    int size = width * 10;
    unsigned char* image = (unsigned char*)malloc(size * size);
    if (!image) {
        std::cerr << "Error: Failed to allocate memory for image" << std::endl;
        QRcode_free(qrcode);
        return false;
    }
    memset(image, 255, size * size);

    for (int y = 0; y < width; y++)
        for (int x = 0; x < width; x++)
            if (qrcode->data[y * width + x] & 1)
                for (int dy = 0; dy < 10; dy++)
                    for (int dx = 0; dx < 10; dx++)
                        image[(y * 10 + dy) * size + (x * 10 + dx)] = 0;

    FILE* fp = fopen(filename.c_str(), "wb");
    if (!fp) {
        std::cerr << "Error: Failed to open output file" << std::endl;
        free(image);
        QRcode_free(qrcode);
        return false;
    }

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png) {
        std::cerr << "Error: Failed to create PNG write struct" << std::endl;
        fclose(fp);
        free(image);
        QRcode_free(qrcode);
        return false;
    }

    png_infop info = png_create_info_struct(png);
    if (!info) {
        std::cerr << "Error: Failed to create PNG info struct" << std::endl;
        png_destroy_write_struct(&png, nullptr);
        fclose(fp);
        free(image);
        QRcode_free(qrcode);
        return false;
    }

    if (setjmp(png_jmpbuf(png))) {
        std::cerr << "Error: Failed to set PNG jump buffer" << std::endl;
        png_destroy_write_struct(&png, &info);
        fclose(fp);
        free(image);
        QRcode_free(qrcode);
        return false;
    }

    png_init_io(png, fp);
    png_set_IHDR(png, info, size, size, 8, PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png, info);

    for (int y = 0; y < size; y++)
        png_write_row(png, &image[y * size]);

    png_write_end(png, nullptr);
    png_destroy_write_struct(&png, &info);
    fclose(fp);
    free(image);
    QRcode_free(qrcode);

    return true;
}
