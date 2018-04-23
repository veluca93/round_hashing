# round_hashing
Implementation of Round Hashing and benchmark
## Compilation
Compile with
`gcc round_hashing.c -O3 -Wall -o round_hashing -lm -DHARDCODE_DIVISION` 
Some other `#define`s you may want to use are 
- `ASSUME_HASHED`, which makes Round Hashing skip the hash function
- `UNIFORM_DISTRIBUTION`, which generates as an input an uniform sample of the hash space
## Execution
Run with
`./round_hashing num_keys num_server`
