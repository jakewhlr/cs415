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

#### Command Line arguments  
The program accepts the following arguments:
* `-s <int>`, specifies the square size of the matrices to multiply. Defaults to 5
* `-e <int>`, specifies a seed for the random generation of matrices. Defaults to current time.
* `-c`, specifies whether this run is used for collecting data, changes output accordingly. Defaults to false.
* `-v`, specifies level of verbosity, between 0 and 4 `v`'s. Defaults to 0.
* `-f <string> <string>`, specifies files for matrix A and matrix B, in the format shown below. Overrides `-s` and `-e`.  

  *Example*: `bin/sequential -vv -s 10 -e 45` , two levels of verbosity with size 10 and seed 45.
###### `-f` File format
   A.txt, matrix of size 3.
   ```shell
   3  #size
   1 2 3
   4 5 6
   7 8 9
   ```
