#ifndef DATA_COMPRESSION_LZW_CODER_H
#define DATA_COMPRESSION_LZW_CODER_H

#include "Dictionary.h"
#include <string>
#include <fstream>
#include "../buf_read/buffer_reader.h"
#include "Dictionary.h"

class Coder {
private:
    Dictionary dictionary;
public:
    void code(const std::string &input_file, const std::string &output_file = "out.code");

    const Dictionary &getDictionary() const;

    explicit Coder(const Dictionary &dictionary);

    Coder();
};


#endif
