all: run

run: build $(wildcard data.dat)
	time ./build -g
	time ./build -j
	time ./build -l

build: $(wildcard *h *cpp)
	g++ *.cpp -o build

clean:
	rm -rf build result.dat
