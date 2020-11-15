#include <iostream>
#include <fstream>  // to use ifstream to read from files
#include <cstring>
#include <string>

extern const char MAGIC;
extern const char *err_descr;

enum state
{
    s_success = 0,
    s_err_args = -1,
    s_err_paths = -2,
    s_err_open_input = -3,
    s_err_open_output = -4,
    s_err_read_input = -5,
    s_err_write_output = -6,
    s_err_unknown_char = -7
};

bool isBinary(std::ifstream &file);
state copyFile(std::ifstream &in, std::ofstream &out);
state binToText(std::ifstream &in, std::ofstream &out);
state textToBin(std::ifstream &in, std::ofstream &out);
