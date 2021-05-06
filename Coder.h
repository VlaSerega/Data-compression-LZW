#ifndef DATA_COMPRESSION_LZW_CODER_H
#define DATA_COMPRESSION_LZW_CODER_H

#include "Dictionary.h"
#include <string>
#include <fstream>

class Coder {
private:
    Dictionary dictionary;
public:
    void code(const std::string &input_file, const std::string &output_file = "out.code");
};


#endif //DATA_COMPRESSION_LZW_CODER_H
