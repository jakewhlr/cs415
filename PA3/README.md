# PA3 - Bucket Sort

### Compiling
Running `make` from the repository's root directory will compile the source code
found in `src/` into binaries in `bin/`.

### Running
The sbatch files found in the root directory `sequential.sh` and `parallel.sh` will run various tests
with the each respective implemented program, and record their times in
`output/sequential/sequential.csv` or `output/parallel/parallel.csv`. The program can be run with `bin/<executable> <command line arguments>`, the accepted arguments can be found below.

##### Command Line Arguments
* `-s <int>` Size, number of integers to sort
* `-b <int>` Number of buckets
* `-e <int>` Seed for random number generation
* `-v` Verbose, up to four levels of verbosity
* `-c` Collecting data, used for running tests and storing timing in .csv format

### Output
The program will output the time in seconds it took for each test into `output/*/*.csv`.
