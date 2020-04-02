#include "VoxWriter.h"

int main() {
	vox::VoxWriter vox(500,500,101);
	vox.AddVoxel(0,0,0,2);
	vox.AddVoxel(0,1,0,1);
	vox.AddVoxel(0,0,1,1);
	vox.AddVoxel(1,0,0,1);
	vox.AddVoxel(1,1,1,3);
	
	for (int i=0; i<500; ++i) {
		for (int j=0; j<500; ++j) {
			vox.AddVoxel(i,j, floor(sin((float)(i * i + j * j) / 10000) * 50) + 50,(i+j)%255 + 1);
		}
	}
	vox.SaveToFile("output_voxwriter.vox");
}
