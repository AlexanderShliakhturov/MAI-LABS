.PHONY: build run point-tests rectangle-tests square-tests triangle-tests vector-tests clean

build:
	make clean
	mkdir -p build
	cd ./build; cmake ..; make all

run:
	./build/*_exe

point-tests:
	./build/*_point_tests

rectangle-tests:
	./build/*_rectangle_tests

square-tests:
	./build/*_square_tests

triangle-tests:
	./build/*_triangle_tests

vector-tests:
	./build/*_vector_tests

all-tests: point-tests rectangle-tests square-tests triangle-tests vector-tests

clean:
	rm -rf ./build/