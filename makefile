all: xyzp2vox sinTest

xyzp2vox: VoxWriter.cpp main.cpp cTools.cpp
	g++ -O2 -std=c++11 -o $@ $^

sinTest: sinTest.cpp VoxWriter.cpp cTools.cpp
	g++ -O3 -std=c++11 -o $@ $^

clean:
	rm xyzp2vox sinTest
