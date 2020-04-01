#include "VoxWriter.h"

int main() {
	vox::VoxWriter vox(120,120,120);
	vox.AddVoxel(0,0,0,2);
	vox.AddVoxel(0,1,0,1);
	vox.AddVoxel(0,0,1,1);
	vox.AddVoxel(1,0,0,1);
	vox.AddVoxel(1,1,1,3);
	vox.SaveToFile("output_voxwriter.vox");
}
