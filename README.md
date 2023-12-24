# File-integrity
The programm checks the integrity of two files. Verification occurs using a hash comparison. The programm supports hash functions: MD5, SHA256 and Keccak (224, 256,384,512)

## Build the project
- `git clone <link>`
- `make`

## Usege 

`./file_integrity -i [reference file] [file to check] [-md5 | -sha_256 | -keccak_224 | -keccak_256 | -keccak_384 | -keccak_512]`
