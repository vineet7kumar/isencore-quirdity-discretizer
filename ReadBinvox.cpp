/*
 * ReadBinvox.cpp
 *
 *  Created on: Jun 14, 2014
 *      Author: vineet
 */

#include "ReadBinvox.h"
#include "includes.h"
#include "DataAbstractor.h"
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;

typedef unsigned char byte;

ReadBinvox::ReadBinvox() {
	// TODO Auto-generated constructor stub

}

ReadBinvox::~ReadBinvox() {
	// TODO Auto-generated destructor stub
}

void ReadBinvox::read(std::string filespec) {
	//TODO: Replace the below debug with aglobal one
	bool debug = false;
	binvox_info* bv_info = new binvox_info;
	// = (ReadBinvox::binvox_info*) malloc(sizeof(ReadBinvox::binvox_info));
	ifstream *input = new ifstream(filespec.c_str(), ios::in | ios::binary);

	//
	// read header
	//
	string line;
	*input >> line;  // #binvox
	if (line.compare("#binvox") != 0) {
		cout << "Error: first line reads [" << line << "] instead of [#binvox]"
				<< " ABORTING." << endl;
		delete input;
		exit(1);
	}
	*input >> bv_info->binvox_info::version;
	if (debug) {
		cout << "reading binvox version " << bv_info->binvox_info::version
				<< endl;
	}

	bv_info->binvox_info::depth = -1;
	int done = 0;
	while (input->good() && !done) {
		*input >> line;
		if (line.compare("data") == 0)
			done = 1;
		else if (line.compare("dim") == 0) {
			*input >> bv_info->binvox_info::depth
					>> bv_info->binvox_info::height
					>> bv_info->binvox_info::width;
		} else if (line.compare("translate") == 0) {
			*input >> bv_info->binvox_info::tx >> bv_info->binvox_info::ty
					>> bv_info->binvox_info::tz;
		} else if (line.compare("scale") == 0) {
			*input >> bv_info->binvox_info::scale;
		} else {
			cout << "  unrecognized keyword [" << line << "], skipping" << endl;
			char c;
			do {  // skip until end of line
				c = input->get();
			} while (input->good() && (c != '\n'));

		}
	}
	if (!done) {
		cout << "  error reading header" << endl;
		exit(1);
	}
	if (bv_info->binvox_info::depth == -1) {
		cout << "  missing dimensions in header" << endl;
		exit(1);
	}

	bv_info->binvox_info::size = bv_info->binvox_info::width
			* bv_info->binvox_info::height * bv_info->binvox_info::depth;
	bv_info->binvox_info::voxels = new bool[bv_info->binvox_info::size];
	if (!bv_info->binvox_info::voxels) {
		cout << "  error allocating memory" << endl;
		exit(1);
	}

	//
	// read voxel data
	//
	byte value;
	byte count;
	int index = 0;
	int end_index = 0;
	int nr_voxels = 0;

	input->unsetf(ios::skipws);  // need to read every byte now (!)
	*input >> value;  // read the linefeed char

	while ((end_index < bv_info->binvox_info::size) && input->good()) {
		*input >> value >> count;

		if (input->good()) {
			end_index = index + count;
			if (end_index > bv_info->binvox_info::size)
				exit(1);
			for (int i = index; i < end_index; i++)
				bv_info->binvox_info::voxels[i] = value == 1 ? true : false;

			if (value==1)
				nr_voxels += count;
			index = end_index;
		}  // if file still ok

	}  // while

	input->close();
	bv_info->binvox_info::num_set_voxels = nr_voxels;
	if (debug)
		cout << "  read " << nr_voxels << " voxels" << endl;
	binvox_data = bv_info;
}

const binvox_info* ReadBinvox::getBinvoxData() {
	return binvox_data;
}

void ReadBinvox::setBinvoxData(binvox_info* binvoxData) {
	binvox_data = binvoxData;
}
