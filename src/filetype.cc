#include <dnssaver/dnssaver.h>

using namespace std;

bool isBinary(ifstream &file)
{
    char magic;
    file.get(magic);    // reads the first byte of the file
    file.seekg(0);      // returns to the first position afterwards
    if (magic == MAGIC) // binary files start with the magic byte
        return true;

    return false;
}