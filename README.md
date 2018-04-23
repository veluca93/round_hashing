# round_hashing
Implementation of Round Hashing and benchmark
## Compilation
Compile with
`gcc load_balance.c -O3 -Wall -o load_balance -lm -DHARDCODE_DIVISION` 
Some other `#define`s you may want to use are 
- `ASSUME_HASHED`, which makes Round Hashing skip the hash function
- `UNIFORM_DISTRIBUTION`, which generates as an input an uniform sample of the hash space
## Execution
Run with
`./load_balance num_keys num_server`
