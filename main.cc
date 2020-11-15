#include <dnssaver/dnssaver.h>

using namespace std;

state cli(ofstream &outfile, ifstream &infile, int argc, char **argv)
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
            return s_err_args;  // error code -1: invalid argument(s)
    }
    if (!inputPath || !outputPath)
        return s_err_paths; // error code -1: invalid argument(s)

    // open output file for writing
    outfile.open(outputPath, ios::binary);
    if (!outfile.is_open()) {
        err_descr = outputPath;
        return s_err_open_input; // error code -3: file could not be opened
    }
    // open input file, for reading
    infile.open(inputPath, ios::binary);
    if (!infile.is_open()) {
        err_descr = inputPath;
        return s_err_open_output; // error code -4: file could not be opened
    }

    state status;
    bool readBinary = isBinary(infile);
    if (readBinary == writeBinary)
        status = copyFile(infile, outfile);   // copy process
    else if (!readBinary && writeBinary)
        status = textToBin(infile, outfile);  // text to bin conversion
    else if (readBinary && !writeBinary)
        status = binToText(infile, outfile);  // bin to text conversion
    return status;
}


int main(int argc, char **argv)
{
    ofstream outfile;
    ifstream infile;
    state status = cli(outfile, infile, argc, argv);
    switch (status)
    {
        case s_err_args:
            cerr << "error: too many arguments in program call" << endl;
            break;
        case s_err_paths:
            cerr << "error: input path or output were not set" << endl;
            break;
        case s_err_open_output:
            cerr << "error: unable to open output file" << endl;
            break;
        case s_err_open_input:
            cerr << "error: unable to open input file" << endl;
            break;
        case s_err_read_input:
            cerr << "error: reading input file " << endl;
            break;
        case s_err_write_output:
            cerr << "error: writing output file" << endl;
            break;
        case s_err_unknown_char:
            cerr << "error: unknown char" << endl;
            break;
        default:
            break; // do nothing on success
    }

    if (outfile.is_open())
        outfile.close();
    if (infile.is_open())
        infile.close();

    return (int)status;
}
