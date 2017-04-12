default: sequential

sequential: src/sequential.cpp
	mpic++ -lmpi -o bin/sequential src/sequential.cpp

parallel: src/parallel.cpp
	mpic++ -lmpi -g -o bin/parallel src/parallel.cpp

clean:
	-rm bin/sequential bin/parallel
