#include <iostream>
#include <map>
#include "Dictionary.h"
#include "Coder.h"

using namespace std;

int main(int argc, char **argv) {
    Dictionary dictionary;

    Coder coder;

    coder.code("../CMakeLists.txt");
    return 0;
}

