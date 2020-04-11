#include "VoxWriter.h"

int main() {
	vox::VoxWriter vox(126,126,126);
	for (int i=0; i<500; ++i) {
		for (int j=0; j<500; ++j) {
			vox.AddVoxel(i,j, floor(sin((float)(i * i + j * j) / 30000) * 100) + 100,(i+j)%255 + 1);
		}
	}
	vox.SaveToFile("sinTest.vox");
}
