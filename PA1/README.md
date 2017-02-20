# PA1 - Ping Pong  
This program determines the time it takes to pass integers between processes on the same box, and other boxes across the network. The MPI_Send() and MPI_Recv() functions are used to send/recieve messages between the boxes, and MPI_Wtime() is used for timing.

#### main.c  
The main function of this program takes in two command line arguments, the first being the number of samples to get, and the second being the count of integers to be sent. Increasing the sample size increases the accuracy of the data that will be interpreted, while increasing the count of integers lets us see the pattern of timing more clearly.  
For example: when run with `srun -n2 -N1 ./PA1 100 150`, the program would start at 1 int, send it 100 times, and determine the average time. It would then send 2 ints 100 times, and time. It would continue to do this until 150 ints were sent and timed.

#### One_box.sh  
This bash script is used to run the binary `PA1` with the proper command line arguments for the one box test. `srun -n2 PA1 1000 1`, with `-n2 -N1`, specifying the program to run two tasks, on one node and `1000 1` specifying 1000 samples to average, and 1 int to send. This ensures that the processes are communicating within one box.

#### Two_box.sh  
Similar to One_box.sh, this bash scirpt runs `PA1` with the proper arguments for the two box test. It runs `srun -n2 -N2 --ntasks-per-node=1 PA1 1000 1`, specifying 2 tasks to run, on two nodes, with a maximum of 1 task per node. This ensures that the processes are communicating via the network.

#### Timing.sh  
Timing.sh is very similar to Two_box.sh. It runs practically the same command, `srun -n2 -N2 --ntasks-per-node=1 PA1 1000 1000`, but with the count at 1000 rather than 1. This runs the two box test for various arrays of integers, ranging from 1 to 1000. By seeing and graphing the output of this we can see where the significant jumps in timing are when adding more and more integers to be sent./
