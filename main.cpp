#include "VoxWriter.h"

// Takes XYZP input file on stdin.
// XYZP format:
// Each line has 4 ASCII decimal numbers; they describe a single voxel.
// The first three are the 0-indexed X, Y, and Z coordinates. The fourth is a 1-255 magicaVoxel
// palette index.
// The output dimension is inferred from the input.

#include <iostream>
#include <string>

int main() {
	int lineNr = 0;
	int minX = INT_MAX;
	int minY = INT_MAX;
	int minZ = INT_MAX;
	std::vector<unsigned int> data;
	for (std::string line; std::getline(std::cin, line); ++lineNr) { // parse input
		int nums[4];
		std::stringstream ss(line);
		int ti;
		int ct = 0;
		while(ss >> ti) {
			if (++ct > 4) {
				printf("invalid line %d \"%s\" has more than 4 numbers in it!\n", lineNr, line.c_str());
				break;
			}
			nums[ct-1] = ti;
			printf("read a %d\n", ti);
		}
		if (ct < 4) {
			printf("invalid line %d \"%s\" has less than 4 numbers in it!\n", lineNr, line.c_str());
			continue;
		}
		if (minX > nums[0]) { minX = nums[0]; }
		if (minY > nums[1]) { minY = nums[1]; }
		if (minZ > nums[2]) { minZ = nums[2]; }
		data.push_back(nums[0]);
		data.push_back(nums[1]);
		data.push_back(nums[2]);
		data.push_back(nums[3]);
	}

	if (minX < 0 || minY < 0 || minZ < 0) {
		printf("Negative positions found. Take note! Minimum bounds are assigned to origin. Positions have been shifted by <%d,%d,%d>\n", -minX, -minY, -minZ);
	} else {
		minX = 0; minY = 0; minZ = 0;
	}
	vox::VoxWriter vox(126,126,126);
	for (int i=0; i<data.size(); i+=4) {
		// printf("position %d %d %d\n", data[i], data[i+1], data[i+2]);
		// printf("adding voxel %d %d %d %d\n", data[i] - minX, data[i+1] - minY, data[i+2] - minZ, data[i+3]);
		vox.AddVoxel(data[i] - minX, data[i+1] - minY, data[i+2] - minZ, data[i+3]);
	}
	vox.SaveToFile("output_voxwriter.vox");
}
