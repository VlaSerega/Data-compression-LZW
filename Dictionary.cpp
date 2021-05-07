#include <iostream>
#include "Dictionary.h"


bool cmp_word::operator()(const std::vector<bool> &a, const std::vector<bool> &b) const {
    size_t min = a.size() < b.size() ? a.size() : b.size();

    for (int i = 0; i < min; ++i)
        if (a[i] != b[i])
            return !a[i];

    return a.size() < b.size();
}

Dictionary::Dictionary() {
}

bool Dictionary::exist_in(const std::vector<bool> &word) const {
//    for(bool i : word){
//        std::cout << std::to_string(i);
//    }
//    std::cout << std::endl;
//    fflush(stdout);
    if (dictionary.find(word) != dictionary.end())
        return true;
    return false;
}

std::vector<bool> Dictionary::get_code(const std::vector<bool> &word) const{
    std::vector<bool> code;
    size_t code_num;

    if (dictionary.find(word) == dictionary.end()) {
        throw std::out_of_range("There isn't such word!");
    }

    code_num = dictionary.find(word)->second;

    code = std::vector<bool>(1);

    while (code_num != 0) {
        code.push_back(code_num % 2);
        code_num /= 2;
    }

    return code;
}

void Dictionary::push_word(const std::vector<bool> &word) {
    size_t code_num = 0;

    if (!dictionary.empty()) {
        code_num = dictionary.rbegin()->second + 1;
    } else {
        latter_length = 1;
    }

    dictionary.insert({word, code_num});
}

void Dictionary::generate_start_words(unsigned short int length) {
    long long int count = (1 << length) - 1;
    latter_length = length;

    if (length > 12)
        throw std::out_of_range("Too large length of start words!");

    for (; count >= 0; --count) {
        dictionary.insert({Dictionary::convert_num(count, length),count});
    }
}

std::vector<bool> Dictionary::convert_num(unsigned long long int num, int length) {
    std::vector<bool> code(length);

    for (int i = length - 1; i >= 0; --i) {
        code[i] = num % 2;
        num /= 2;
    }
    return code;
}

std::string Dictionary::to_string() const {
    std::string out;

    for (std::pair<std::vector<bool>, size_t> t : dictionary){
        for(bool e : t.first){
            out += std::to_string(e);
        }

        out += " " + std::to_string(t.second) + "\n";
    }

    return out;
}

unsigned int Dictionary::getLatterLength() const {
    return latter_length;
}
