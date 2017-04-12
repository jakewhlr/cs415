# PA4 - Matrix Multiplication

## Description
The goal of this program is to perform matrix multiplication on two given matrices,
and compare the execution time, speedup, and efficiency of a parallel implementation
vs. a sequential implementation.

### Compiling
Running `make` from the repository's root directory will compile the source code
found in `src/` into binaries in `bin/`.

### Running
Two sbatch files will be provided in the root directory, `sequential.sh` and `parallel.sh`
, which will run various tests with the sequential implementation and the parallel
implementation, respectively. The output of these scripts will be stored in `output/sequential/`
and `output/parallel/`.
