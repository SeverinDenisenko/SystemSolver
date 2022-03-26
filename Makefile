all: run

run: build $(wildcard data.dat)
	./build -l

build: $(wildcard *hpp *cpp)
	g++ *.cpp -o build

clean:
	rm -rf build result.dat

