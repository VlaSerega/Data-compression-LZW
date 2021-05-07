#include "buffer_reader.h"

buffer_reader::~buffer_reader() {
    in_stream.close();
}

buffer_reader::buffer_reader(const std::string &path, size_t buf_size = 2048) {
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

    if (buffer.size() < count) {
        read(count - size() < buffer.capacity() - size() ? buffer.capacity() - size() : count - size());
    }

    if (end < start) {
        if (buffer.capacity() - start < count) {
            std::copy(buffer.begin() + start, buffer.begin() + start + count, data.begin());
        } else {
            int part = buffer.capacity() - start;
            std::copy(buffer.begin() + start, buffer.end(), data.begin());
            std::copy(buffer.begin(), buffer.begin() + count - part, data.begin() + part);
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
    unsigned int size = 0;

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
    char tmp[count];
    in_stream.read(tmp, count);

    if(buffer.capacity() - end < count) {
        unsigned int part = buffer.capacity() - end;
        std::copy(tmp, tmp + part, buffer.begin() + end);
        std::copy(tmp + part, tmp + count, buffer.begin());
    } else {
        std::copy(tmp, tmp + count, buffer.begin() + end);
    }
}
