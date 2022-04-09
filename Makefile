all: run

run: build $(wildcard data.dat)
	./build -g

build: $(wildcard *h *cpp)
	g++ *.cpp -o build

clean:
	rm -rf build result.dat
