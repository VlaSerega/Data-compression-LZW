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

bool Dictionary::exist_in(const std::vector<bool> &word) {
    if (dictionary.find(word) != dictionary.end())
        return true;
    return false;
}

std::vector<bool> Dictionary::get_code(const std::vector<bool> &word) {
    std::vector<bool> code;
    size_t code_num;
    short int count;

    if (dictionary.find(word) == dictionary.end())
        throw std::out_of_range("There isn't such word!");

    code_num = dictionary.find(word)->second.first;
    count = dictionary.find(word)->second.second;

    code = std::vector<bool>(count);

    for (int i = count - 1; i >= 0; --i) {
        code[i] = code_num % 2;
        code_num /= 2;
    }

    return code;
}

void Dictionary::push_word(const std::vector<bool> &word) {
    size_t code_num = 0;
    short int count = 1;

    if (!dictionary.empty()) {
        code_num = dictionary.rbegin()->second.first + 1;
        count = dictionary.rbegin()->second.second;
        if (1 << count == code_num)
            count++;
    }

    dictionary.insert({word, {code_num, count}});
}

void Dictionary::generate_start_words(unsigned short int length) {
    long long int count = (1 << (length - 1)) - 1;

    if (length > 12)
        throw std::out_of_range("Too large length of start words!");

    for (; count >= 0; --count) {
        dictionary.insert({Dictionary::convert_num(count, length),{count, length}});
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

std::string Dictionary::to_string() {

    return std::__cxx11::string();
}
