default: sequential dynamic

sequential: src/sequential.c
	mpicc -lpmi -o bin/sequential src/sequential.c

dynamic: src/dynamic.c
	mpicc -lpmi -o bin/dynamic src/dynamic.c

clean:
	-rm bin/sequential bin/dynamic
