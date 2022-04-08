all: run

run: build $(wildcard data.dat)
	./build -g

build: $(wildcard *hpp *cpp)
	g++ -arch arm64 *.cpp -o build

clean:
	rm -rf build result.dat
