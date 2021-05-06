#ifndef DATA_COMPRESSION_LZW_DICTIONARY_H
#define DATA_COMPRESSION_LZW_DICTIONARY_H

#include <map>
#include <vector>

class cmp_word{
    bool operator()(const std::vector<bool>& a, const std::vector<bool>& b) const;
};

class Dictionary {
private:
    std::map<std::vector<bool>, int, cmp_word> dictionary;
public:
    Dictionary();
    void push_word(const std::vector<bool> &word);
    bool exist_in(const std::vector<bool> &word);
    std::vector<bool> get_code(const std::vector<bool> &word);
};


#endif //DATA_COMPRESSION_LZW_DICTIONARY_H
