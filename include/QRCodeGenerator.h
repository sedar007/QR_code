#pragma once
#include <string>

class QRCodeGenerator {
public:
    bool generate(const std::string& url, const std::string& filename);
};
