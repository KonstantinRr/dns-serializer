# DNS Saver
This repository implements a small command line (CLI) utility tool to serialize and deserialize human genome data to a binary format. The human genome can be represented using the character pairs A, C, T and G. The usual text representation takes up 1 byte per genome character and is therefore not really efficient. The CLI tool serializes the genome data in pairs of two bits. Therefore we can fit up to 4 characters in a single byte of data.
