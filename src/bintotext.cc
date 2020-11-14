#include <dnssaver/dnssaver.h>

using namespace std;

int binToText(ifstream &in, ofstream &out)
{       
    // static conversion table
    const char convTable[] = { 'A', 'C', 'T', 'G' };
    
    in.get(); // The file must be binary so we discard the magic bytes

    size_t size; // reads the amount of characters stored in binary format
    in.read(reinterpret_cast<char *>(&size), sizeof(size_t));

    char data;              // the current byte that is processed
    size_t shift = 0;       // the shift giving the offset inside the byte
    for (size_t idx = 0; idx != size; ++idx)
    {
        if (shift == 0)     // we are at the beginning of the next byte
        {
            in.get(data);   // reads the next byte
            if (!in)        // fast error checking
                return -3;  // err -3: error reading input file
        }
                            // read two bits from the bytes
        out.put(convTable[(data >> shift) & 0b11]);
        if (out.fail())     // fast error checking
            return -4;      // err -4: error writing output file
            
        shift += 2;     // characters are two bits wide
                        // returns the shift to zero if shift == 8
        shift = shift == 8 ? 0 : shift;
    }
    return 0;
}