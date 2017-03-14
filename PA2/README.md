# PA2 - Mandelbrot Set  

### Compiling
Running `make` from the repository's root directory will compile the source code
found in `src/` into the binaries `sequential` and `dynamic` in `bin/`.

### Running
Two sbatch files are located in the repo's root directory, `sequential.sh` and
`dynamic.sh` to run various tests for the sequential code and dynamic code, respectively.
These can be run with `sbatch dynamic.sh` and `sbatch sequential.sh`.

### Output
The programs will output to various files, being stored in `output/sequential` or `output/dynamic`
depending on which testcase is run. Within each output folder will be `sequential.log`,
which contains the output of stdout when sbatch is run, `sequential.csv`, which
contains the timings of various tests, and various `.ppm` files, which are the
image outputted by the compiled binaries. When the sbatch files are run, `.ppm`
files are created for the cases of 500x500, 1000x1000, 5000x5000, 10000x10000, and
25000x25000. These files will show an image of the Mandelbrot set, and can be opened
with various image viewers/editors, such as Gimp.
