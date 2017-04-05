# PA3 - Bucket Sort

### Compiling
Running `make` from the repository's root directory will compile the source code
found in `src/sequential.cpp` into the binary `bin/sequential`.

### Running
The sbatch file found in the root directory `sequential.sh` will run various tests
with the sequential implemented program, and record their times in
`output/sequential/sequential.csv`. The program can be run with `bin/sequential <command line arguments>`, the accepted arguments can be found below.

##### Command Line Arguments
* `-s <int>` Size, number of integers to sort
* `-b <int>` Number of buckets
* `-e <int>` Seed for random number generation
* `-v` Verbose, up to four levels of verbosity
* `-c` Collecting data, used for running tests and storing timing in .csv format

### Output
The program will output the original unsorted list as well as the final sorted
list for each test in `sequential.sh` to stdout, which will end up in
 `output/sequential/sequential.log` if run with sbatch.
