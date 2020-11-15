#include <dnssaver/dnssaver.h>

using namespace std;

state copyFile(ifstream &in, ofstream &out)
{
    int const size = 8192;  // we choose a large buffer size
    char buffer[size];      // we create the buffer
    while (!in.eof())
    {
        in.read(buffer, size); // read in the buffer 
        if (!in.eof() && in.fail())  // error during input reading
            return s_err_read_input; // err -3: error reading input file
        
        out.write(buffer, in.gcount()); // write from the buffer
        if (out.fail()) // error during output writing
            return s_err_write_output;  // err -4: error writing output file
    }
    return s_success;
}