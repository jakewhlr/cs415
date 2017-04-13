default: sequential

sequential: src/sequential.cpp
	mpic++ -lmpi -o bin/sequential src/sequential.cpp

clean:
	-rm bin/sequential bin/parallel
