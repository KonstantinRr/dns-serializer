#include <dnssaver/dnssaver.h>

using namespace std;

int main(int argc, char **argv)
{
    char const *inputPath = nullptr;
    char const *outputPath = nullptr;
    bool writeBinary = false;

    for (char **ptr = argv + 1; *ptr; ++ptr)
    {
        if (strcmp(*ptr, "-b") == 0 && !writeBinary) // optional argument -b
            writeBinary = true;
        else if (!inputPath)    // first argument is stored in inputPath
            inputPath = *ptr;
        else if (!outputPath)   // second argument is stored in outputPath
            outputPath = *ptr;
        else                    // more than 2 unnamed arguments
        {
            cerr << "too many arguments in program call\n";
            return -1;          // error code -1: invalid argument(s)
        }
    }
    if (!inputPath || !outputPath)
    {
        cerr << "input path or output were not set\n";
        return -1;              // error code -1: invalid argument(s)
    }

                // open output file for writing
    ofstream outfile(outputPath, ios::binary);
    if (!outfile.is_open())
    {
        cerr << "unable to open output file " << outputPath << '\n';
        return -2;          // error code -2: file could not be opened
    }
                // open input file, for reading
    ifstream infile(inputPath, ios::binary);
    if (!infile.is_open())
    {
        outfile.close();    // outfile was already opened
        cerr << "unable to open input file " << inputPath << '\n';
        return -2;          // error code -2: file could not be opened
    }

    bool readBinary = isBinary(infile);
    if (readBinary == writeBinary)
        return copyFile(infile, outfile);   // copy process
    else if (!readBinary && writeBinary)
        return textToBin(infile, outfile);  // text to bin conversion
    else if (readBinary && !writeBinary)
        return binToText(infile, outfile);  // bin to text conversion

    infile.close();
    outfile.close();
}
