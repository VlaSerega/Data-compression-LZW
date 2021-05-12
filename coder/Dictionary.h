#ifndef DATA_COMPRESSION_LZW_DICTIONARY_H
#define DATA_COMPRESSION_LZW_DICTIONARY_H

#include <map>
#include <vector>

typedef std::pair<std::vector<bool>, unsigned int> word_;

class cmp_word {
public:
    bool operator()(const word_ &a, const word_ &b) const;
};

class Dictionary {
private:
    std::map<word_, size_t, cmp_word> dictionary;
    unsigned int latter_length = 0;
public:
    Dictionary();

    void push_word(const word_ &word);

    bool exist_in(const word_ &word) const;

    word_ get_code(const word_ &word) const;

    void generate_start_words(unsigned short int length);

    static word_ convert_num(unsigned long long int num, unsigned int count_bit);

    std::string to_string() const;

    unsigned int getLatterLength() const;
};

#endif
