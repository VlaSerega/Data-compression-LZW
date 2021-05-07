#include "Coder.h"

void Coder::code(const std::string &input_file, const std::string &output_file) {
    buffer_reader in(input_file);
    std::ofstream out_file(output_file, std::ofstream::binary);

    if (!in.is_open())
        return;

    unsigned int length = 0;
    unsigned int latter_length = dictionary.getLatterLength();

    std::vector<bool> w(0);

    while (!in.is_end()) {
        in.read(latter_length);
        w = in.get(length + latter_length);

        if (!dictionary.exist_in(w)) {
            w.erase(w.begin() + length, w.end());
            w.swap(w);

            dictionary.get_code(w);

            in.skip(length);
            length = 0;
        }

        length += latter_length;
    }
}

const Dictionary &Coder::getDictionary() const {
    return dictionary;
}

Coder::Coder(const Dictionary &dictionary) : dictionary(dictionary) {}

Coder::Coder() {
    dictionary.generate_start_words(8);
}
