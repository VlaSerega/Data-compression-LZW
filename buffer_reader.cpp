#include <iostream>
#include "buffer_reader.h"

buffer_reader::~buffer_reader() {
    in_stream.close();
}

buffer_reader::buffer_reader(const std::string &path, size_t buf_size) {
    in_stream = std::ifstream(path, std::ifstream::binary);
    buffer = std::vector<bool>(buf_size);
    start = 0;
    end = 0;
}

void buffer_reader::skip(unsigned int count) {
    start = start + count;

    if (start >= buffer.capacity())
        start -= buffer.capacity();

    if (start > end)
        start = end = 0;
}

word_ buffer_reader::get(unsigned int count) {
    std::vector<bool> data(count);

    if (this->size() < count) {
        read(count - this->size() < buffer.capacity() - this->size() ?
             buffer.capacity() - this->size() : count - this->size());
    }

    if (end < start) {
        if (buffer.capacity() - start < count) {
            unsigned int part = buffer.capacity() - start;
            std::copy(buffer.begin() + start, buffer.end(), data.begin());
            std::copy(buffer.begin(), buffer.begin() + (count - part), data.begin() + part);
        } else {
            std::copy(buffer.begin() + start, buffer.begin() + start + count, data.begin());
        }
    } else {
        std::copy(buffer.begin() + start, buffer.begin() + start + count, data.begin());
    }

    return {data, count < size() ? count : size()};
}

bool buffer_reader::is_end() {
    return in_stream.eof() && end == start;
}

bool buffer_reader::all_get(unsigned int count) {
    return in_stream.eof() && count >= size();
}

unsigned int buffer_reader::size() {
    unsigned int size;

    if (end < start)
        size = buffer.capacity() - start + end;
    else
        size = end - start;

    return size;
}

void buffer_reader::read(size_t count) {

    if (buffer.capacity() - this->size() < count) {
        set_capacity(count + this->size());
    }

    unsigned long count_byte = count / 8 + 1;
    char tmp[count_byte];
    in_stream.read(tmp, count_byte);
    count_byte = in_stream.gcount();

    if (buffer.capacity() - end < count_byte * 8) {
        unsigned int part = buffer.capacity() - end;
        for (int i = 0; i < part * 8; ++i){
            buffer[i + end] = (tmp[i / 8] >> (7 - (i % 8))) & 0x1;
        }

        for (int i = part * 8; i < count_byte * 8; ++i){
            buffer[i - part] = (tmp[i / 8] << (7 - (i % 8))) & 0x1;
        }
    } else {
        for (int i = 0; i < count_byte * 8; ++i){
            buffer[i + end] = (tmp[i / 8] >> (7 - (i % 8))) & 0x1;
        }
    }

    end = end + count_byte * 8;

    if (end >= buffer.capacity())
        end -= buffer.capacity();
}

bool buffer_reader::is_open() const {
    return in_stream.is_open();
}

void buffer_reader::set_capacity(unsigned int count) {
    if (buffer.capacity() < count) {
        int old_cap = buffer.capacity();
        buffer.reserve(count);

        if(end < start){
            std::copy(buffer.rbegin() + buffer.capacity() - old_cap, buffer.rbegin() + buffer.capacity() - start, buffer.rbegin());
            start = start + buffer.capacity() - old_cap;
        }
    }
}
