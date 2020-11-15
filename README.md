# DNS Saver
This repository implements a small command line (CLI) utility tool to serialize and deserialize human genome data to a binary format. The human genome can be represented using the character pairs A, C, T and G. The usual text representation takes up 1 byte per genome character and is therefore not really efficient. The CLI tool serializes the genome data in pairs of two bits. Therefore we can fit up to 4 characters in a single byte of data.

## Serializing
Use the parameter -b to store the input file in binary format. The default is human readable output.
```
dns_cli input_default.txt input_default.bin -b
dns_cli input_large.txt input_large.bin -b
```

## Deserializing
```
dns_cli input_default.bin output_default.txt
dns_cli input_large.bin output_large.txt
```

## Building
Use the default CMake configuration to build this project. The project consists of a library object and the CLI interface.
