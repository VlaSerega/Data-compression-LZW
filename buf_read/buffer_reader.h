#ifndef DATA_COMPRESSION_LZW_BUFFER_READER_H
#define DATA_COMPRESSION_LZW_BUFFER_READER_H

#include <fstream>
#include <vector>
#include "../coder/Dictionary.h"

class buffer_reader {
private:
    std::ifstream in_stream;
    std::vector<bool> buffer;
    unsigned int start;
    unsigned int end;
public:
    ~buffer_reader();

    explicit buffer_reader(const std::string &path, size_t buf_size = 2048);

    void skip(unsigned int count);

    word_ get(unsigned int count);

    void set_capacity(unsigned int count);

    bool all_get(unsigned int count);

    bool is_end();

    unsigned int size();

    void read(size_t count);

    bool is_open() const;
};


#endif //DATA_COMPRESSION_LZW_BUFFER_READER_H
