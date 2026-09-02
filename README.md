# File-integrity

A small command-line tool written in C++ that verifies whether two files are
identical by comparing their cryptographic hashes. It's useful for checking
that a file hasn't been corrupted or tampered with — for example, confirming a
downloaded file matches its original.

The program hashes a **reference file** and a **file to check**, prints both
hashes, and tells you whether the integrity is intact.

## Supported hash functions

- **MD5**
- **SHA-256**
- **Keccak** - 224, 256, 384 and 512 bits

## Build

Requires `g++` and `make`.

```bash
git clone https://github.com/Mordekay15/File-integrity.git
cd File-integrity
make
```

This produces an executable named `file_integrity`.

## Usage

```bash
./file_integrity -i [reference file] [file to check] [hash option]
```

Where the hash option is one of:

```
-md5 | -sha_256 | -keccak_224 | -keccak_256 | -keccak_384 | -keccak_512
```

### Example

```bash
./file_integrity -i original.txt downloaded.txt -sha_256
```

Output:

```
Reference hash       : <hash of original.txt>
Hash of file to check: <hash of downloaded.txt>
Integrity is correct
```

If the hashes differ, the program prints `Integrity is BROKEN !`.

## How it works

1. Both files are read into memory.
2. The selected hash function is applied to each file's contents.
3. The two resulting hashes are compared:
   - Equal → `Integrity is correct`
   - Different → `Integrity is BROKEN !`

## Project structure

| File          | Description                              |
| ------------- | ---------------------------------------- |
| `main.cpp`    | Entry point and argument parsing         |
| `md5.*`       | MD5 implementation                       |
| `sha-256.*`   | SHA-256 implementation                   |
| `keccak.*`    | Keccak (224/256/384/512) implementation  |
| `Makefile`    | Build configuration                      |

## License

MIT
