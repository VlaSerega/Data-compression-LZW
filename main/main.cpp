#include <iostream>
#include <map>
#include "../coder/Dictionary.h"
#include "../coder/Coder.h"

using namespace std;

int main(int argc, char **argv) {
    Dictionary dictionary;

    Coder coder;

    coder.code("../CMakeLists.txt");
    return 0;
}

