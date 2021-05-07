#ifndef DATA_COMPRESSION_LZW_DICTIONARY_H
#define DATA_COMPRESSION_LZW_DICTIONARY_H

#include <map>
#include <vector>

class cmp_word {
public:
    bool operator()(const std::vector<bool> &a, const std::vector<bool> &b) const;
};

class Dictionary {
private:
    std::map<std::vector<bool>, size_t, cmp_word> dictionary;
    unsigned int latter_length;
public:
    Dictionary();

    void push_word(const std::vector<bool> &word);

    bool exist_in(const std::vector<bool> &word) const;

    std::vector<bool> get_code(const std::vector<bool> &word) const;

    void generate_start_words(unsigned short int length);

    static std::vector<bool> convert_num(unsigned long long int num, int length);

    std::string to_string() const;

    unsigned int getLatterLength() const;
};

#endif
