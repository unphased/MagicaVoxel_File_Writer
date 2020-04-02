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
	int minX = INFINITY;
	int minY = INFINITY;
	int minZ = INFINITY;
	int maxX = -INFINITY;
	int maxY = -INFINITY;
	int maxZ = -INFINITY;
	std::vector<unsigned int> data;
	for (std::string line; std::getline(std::cin, line); ++lineNr) { // parse input
		std::cout << line << std::endl;
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
		}
		if (ct < 4) {
			printf("invalid line %d \"%s\" has less than 4 numbers in it!\n", lineNr, line.c_str());
			continue;
		}
		if (minX > nums[0]) { minX = nums[0]; }
		if (minY > nums[1]) { minY = nums[1]; }
		if (minZ > nums[2]) { minZ = nums[2]; }
		if (maxX < nums[0]) { maxX = nums[0]; }
		if (maxY < nums[1]) { maxY = nums[1]; }
		if (maxZ < nums[2]) { maxZ = nums[2]; }
		data.push_back(nums[0]);
		data.push_back(nums[1]);
		data.push_back(nums[2]);
		data.push_back(nums[3]);
	}

	if (minX < 0 || minY < 0 || minZ < 0) {
		printf("Negative positions found\n");
	}
	vox::VoxWriter vox(126,126,126);
	vox.AddVoxel(i,j, floor(sin((float)(i * i + j * j) / 10000) * 50) + 50,(i+j)%255 + 1);
	vox.SaveToFile("output_voxwriter.vox");
}
