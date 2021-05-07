#include "Coder.h"

void Coder::code(const std::string &input_file, const std::string &output_file) {
    std::ifstream in_file(input_file, std::ifstream::binary);
    std::ofstream out_file(output_file, std::ofstream::binary);


}

const Dictionary &Coder::getDictionary() const {
    return dictionary;
}
