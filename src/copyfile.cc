#include <dnssaver/dnssaver.h>

using namespace std;

int copyFile(ifstream &in, ofstream &out)
{
    int const size = 8192;  // we choose a large buffer size
    char buffer[size];      // we initialize the buffer
    while (!in.eof())
    {
        in.read(buffer, size); // read in the buffer 
        if (!in.eof() && in.fail())      // error during input reading
            return -3;      // err -3: error reading input file
        
        out.write(buffer, in.gcount()); // write from the buffer
        if (out.fail())     // error during output writing
            return -4;      // err -4: error writing output file
    }
    return 0;
}