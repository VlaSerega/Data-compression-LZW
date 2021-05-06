#include <iostream>
#include <map>
#include "Dictionary.h"

using namespace std;

int main(int argc, char **argv) {
    Dictionary dictionary;

    dictionary.push_word({false});
    dictionary.push_word({true});
    dictionary.push_word({true, true});

    return 0;
}

