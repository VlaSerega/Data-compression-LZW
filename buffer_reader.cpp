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

std::vector<bool> buffer_reader::get(unsigned int count) {
    std::vector<bool> data(count);

    if (this->size() < count) {
        read(count - this->size() < buffer.capacity() - this->size() ?
             buffer.capacity() - this->size() : count - this->size());
    }

    if (end < start) {
        if (buffer.capacity() - start < count) {
            int part = buffer.capacity() - start;
            std::copy(buffer.begin() + start, buffer.end(), data.begin());
            std::copy(buffer.begin(), buffer.begin() + (count - part), data.begin() + part);
        } else {
            std::copy(buffer.begin() + start, buffer.begin() + start + count, data.begin());
        }
    } else {
        std::copy(buffer.begin() + start, buffer.begin() + start + count, data.begin());
    }

    return data;
}

bool buffer_reader::is_end() {
    return in_stream.eof();
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
    size_t old_capacity;

    if (buffer.capacity() - size() < count) {
        old_capacity = buffer.capacity();
        buffer.reserve((count < buffer.capacity() ? buffer.capacity() : count) * 2);

        std::copy(buffer.rbegin() - buffer.capacity() + start, buffer.rbegin() - buffer.capacity() + old_capacity,
                  buffer.rbegin());

        start = start + (buffer.capacity() - old_capacity);
    }

    long count_byte = count / 8 + 1;
    bool tmp_bit[count_byte * 8];
    in_stream.read((char*) tmp_bit, count_byte);
    count_byte = in_stream.gcount();

    if (buffer.capacity() - end < count_byte * 8) {
        unsigned int part = buffer.capacity() - end;
        std::copy(tmp_bit, tmp_bit + part, buffer.begin() + end);
        std::copy(tmp_bit + part, tmp_bit + count_byte * 8, buffer.begin());
    } else {
        std::copy(tmp_bit, tmp_bit + count_byte * 8, buffer.begin() + end);
    }

    end = end + count_byte * 8;

    if (end >= buffer.capacity())
        end -= buffer.capacity();
}

bool buffer_reader::is_open() const {
    return in_stream.is_open();
}
