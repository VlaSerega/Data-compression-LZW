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
    return false;
}

std::vector<bool> Dictionary::get_code(const std::vector<bool> &word) {
    return std::vector<bool>();
}

void Dictionary::push_word(const std::vector<bool> &word) {

}
