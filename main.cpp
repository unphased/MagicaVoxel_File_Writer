#include "VoxWriter.h"

int main() {
	vox::VoxWriter vox(127,127,100);
	vox.AddVoxel(0,0,0,2);
	vox.AddVoxel(0,1,0,1);
	vox.AddVoxel(0,0,1,1);
	vox.AddVoxel(1,0,0,1);
	vox.AddVoxel(1,1,1,3);
	
	for (int i=0; i<127; ++i) {
		for (int j=0; j<127; ++j) {
			vox.AddVoxel(i,j, floor(sin((float)(i * i + j * j) / 1000) * 50) + 50,(i+j)%255 + 1);
		}
	}
	vox.SaveToFile("output_voxwriter.vox");
}
