CLI='../build/dns_cli'

$CLI input_default.txt input_default.bin -b
$CLI input_large.txt input_large.bin -b

$CLI input_default.bin output_default.txt
$CLI input_large.bin output_large.txt