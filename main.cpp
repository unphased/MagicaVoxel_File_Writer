#include "VoxWriter.h"

// Takes XYZP input file on stdin.
// XYZP format:
// Each line has 4 ASCII decimal numbers; they describe a single voxel.
// The first three are the 0-indexed X, Y, and Z coordinates. The fourth is a 1-255 magicaVoxel
// palette index.
// The output dimension is inferred from the input.

#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include <memory>

int main(int argc, char* argv[]) {
	auto parse = [=](std::istream& in){
		int lineNr = 0;
		int minX = INT_MAX;
		int minY = INT_MAX;
		int minZ = INT_MAX;
		int maxX = INT_MIN;
		int maxY = INT_MIN;
		int maxZ = INT_MIN;
		std::vector<unsigned int> data;
		for (std::string line; std::getline(in, line); ++lineNr) { // parse input
			int nums[4];
			std::stringstream ss(line);
			int ti;
			int ct = 0;
			while(ss >> ti) {
				if (++ct > 4) {
					printf("invalid line %d \"%s\" has more than 4 numbers in it!\n", lineNr, line.c_str());
					continue;
				}
				nums[ct-1] = ti;
			}
			if (ct < 3) {
				printf("invalid line %d \"%s\" has less than 3 numbers in it!\n", lineNr, line.c_str());
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
			if (ct == 3) {
				data.push_back(255);
			} else if (ct == 4) {
				data.push_back(nums[3]);
			} else {
				printf("Should not be here\n");
			}
		}

		if (minX < 0 || minY < 0 || minZ < 0) {
			printf("Negative positions found. Take note! Minimum bounds are assigned to origin. Positions have been shifted by <%d,%d,%d>\n", -minX, -minY, -minZ);
		} else {
			minX = 0; minY = 0; minZ = 0;
		}
		vox::VoxWriter vox(maxX,maxY,maxZ);
		for (int i=0; i<data.size(); i+=4) {
			// printf("position %d %d %d\n", data[i], data[i+1], data[i+2]);
			// printf("adding voxel %d %d %d %d\n", data[i] - minX, data[i+1] - minY, data[i+2] - minZ, data[i+3]);
			vox.AddVoxel(data[i] - minX, data[i+1] - minY, data[i+2] - minZ, data[i+3]);
		}
		if (argc == 2) {
			vox.SaveToFile(std::string(argv[1]) + ".vox");
		} else {
			vox.SaveToFile("output_voxwriter.vox");
		}
	};

	if (argc == 2) {
		std::ifstream file(argv[1]);
		if (file) {
			parse(file);
		} else {
			std::cerr << "Could not open " << argv[1] << std::endl;
		}
	} else {
		parse(std::cin);
	}
}
