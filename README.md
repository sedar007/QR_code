# QR_code

A simple C++ library for generating QR codes, with an example application.

## Features

- Generate QR codes from text
- Save QR codes as PNG images
- Example usage provided

## Requirements

- CMake >= 3.15
- C++ compiler (supports C++11 or newer)
- [libqrencode](https://fukuchi.org/works/qrencode/)
- [libpng](http://www.libpng.org/pub/png/libpng.html)

## Build Instructions

1. Install dependencies (on macOS):
   ```sh
   brew install qrencode libpng# QR_code
    ```
2. Clone the repository:
    ```sh
    git clone https://github.com/sedar007/QR_code.git
    cd QR_code
    ```
3. Build the project:
   ```sh
   cmake -S . -B build
   cmake --build build
   ```
4. Run the example application:
   ```sh
   ./build/QRCodeExample https://github.com/sedar007/
   ```
## Usage
Include the library in your project and use the `QRCodeGenerator` class to generate QR codes.
