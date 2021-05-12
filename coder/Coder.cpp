#include <iostream>
#include "Coder.h"

void Coder::code(const std::string &input_file, const std::string &output_file) {
    buffer_reader in(input_file);
    std::ofstream out_file(output_file, std::ofstream::binary);

    if (!in.is_open())
        return;

    unsigned int length = 0;
    unsigned int latter_length = dictionary.getLatterLength();

    while (!in.is_end()) {
        word_ w = in.get(length + latter_length);

        if (!dictionary.exist_in(w)) {
            dictionary.push_word(w);

            dictionary.get_code({w.first, length});

            in.skip(length);
            length = 0;
        } else {
            if (in.all_get(length + latter_length)) {

                in.skip(length + latter_length);
            }
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
