#include <iostream>
#include <fstream>  // to use ifstream to read from files
#include <cstring>
#include <string>

extern char MAGIC;

bool isBinary(std::ifstream &file);
int copyFile(std::ifstream &in, std::ofstream &out);
int binToText(std::ifstream &in, std::ofstream &out);
int textToBin(std::ifstream &in, std::ofstream &out);
