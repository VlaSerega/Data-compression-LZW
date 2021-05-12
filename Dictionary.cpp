#include <iostream>
#include "Dictionary.h"

static int signed_bit(unsigned int num){
    int count = 0;

    for(int i = 0; i < sizeof(unsigned int) * 8; ++i){
        if ((num >> (sizeof(unsigned int) * 8 - i) & 0x1) == 1)
            break;
        count ++;
    }

    return count;
}

bool
cmp_word::operator()(const word_ &a, const word_ &b) const {
    size_t min = a.second < b.second ? a.second : b.second;

    for (int i = 0; i < min; ++i)
        if (a.first[i] != b.first[i])
            return !a.first[i];

    return a.second < b.second;
}

Dictionary::Dictionary() = default;

bool Dictionary::exist_in(const word_ &word) const {
    if (dictionary.find(word) != dictionary.end())
        return true;
    return false;
}

word_ Dictionary::get_code(const word_ &word) const{
    size_t code_num;

    if (dictionary.find(word) == dictionary.end()) {
        throw std::out_of_range("There isn't such word!");
    }

    code_num = dictionary.find(word)->second;

    return Dictionary::convert_num(code_num, signed_bit(code_num));
}

void Dictionary::push_word(const word_ &word) {
    size_t code_num = 0;

    if (!dictionary.empty()) {
        code_num = dictionary.rbegin()->second + 1;
    } else {
        latter_length = 1;
    }

    dictionary.insert({word, code_num});
    std::cout << "Push: ";

    for (int i = 0; i < word.second; ++i)
        std::cout << word.first[i];

    std::cout << std::endl;
    fflush(stdout);
}

void Dictionary::generate_start_words(unsigned short int length) {
    long long int count = 1 << length;
    latter_length = length;

    if (length > 12)
        throw std::out_of_range("Too large length of start words!");

    for (int i = 0; i < count; ++i) {
        dictionary.insert({Dictionary::convert_num(i, length), i});
    }
}

word_ Dictionary::convert_num(unsigned long long int num, unsigned int count_bit) {
    std::vector<bool> code(count_bit);
    code.reserve(count_bit);

    for (int i = 0; i < count_bit; ++i){
        code[count_bit - 1 - i] = num % 2;
        num /= 2;
    }

    return {code, count_bit};
}

std::string Dictionary::to_string() const {
    std::string out;

    for (std::pair<word_, size_t> t : dictionary){
        for(unsigned int i = 0; i < t.first.second;++i){
            out += std::to_string(t.first.first[i]);
        }

        out += " " + std::to_string(t.second) + "\n";
    }

    return out;
}

unsigned int Dictionary::getLatterLength() const {
    return latter_length;
}
