default: sequential parallel

sequential: src/sequential.cpp
	mpic++ -lpmi -o bin/sequential src/sequential.cpp

parallel: src/parallel.cpp
	mpic++ -lpmi -o bin/parallel src/parallel.cpp

clean:
	-rm bin/sequential bin/parallel
