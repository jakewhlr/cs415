#include<vector>
#include<climits>

// Returns a vector containing 'size' number of random integers
//
//	Input Arguments:
// 	int seed - seed used for random number generation
// 	int size - size of vector to create
// Output Arguments:
// 	int* min - minimum integer found in randomly generated vector
//		int* max - maximum integer found in randomly generated vector
//
std::vector<int> generator(int seed, int size, int* min, int* max){
	srand(seed); // initialize RNG
	std::vector<int> output; // output vector
	*min = INT_MAX, *max = INT_MIN; // set defaults for min, max to be high, low
	for(int index = 0; index < size; index++){
		output.push_back(random() % 1000); // push random number (0-99) onto output
		if(output[index] < *min) // check for new min
			*min = output[index]; // set new min
		else if(output[index] > *max) // check for new max
			*max = output[index]; // set new max
	}
	return output;
}
