all: xyzp2vox

xyzp2vox: VoxWriter.cpp main.cpp cTools.cpp
	g++ -std=c++11 -o $@ $^

clean:
	rm xyzp2vox
