/*
 * BinvoxInfo.h
 *
 *  Created on: Jun 19, 2014
 *      Author: vineet
 */

#ifndef BINVOXINFO_H_
#define BINVOXINFO_H_
/**
 * binvox_info holds the data read from .binvox file in its original format.
 */
struct binvox_info {
	int version; //binvox version number
	int depth, height, width; //total number of voxels per side of the bounding box
	int size; //total no. of voxels in the bounding box
	bool *voxels; //vector of voxels in the order x-z-y
	//(y is the innermost loop). true voxels represent voxels inside the geometry.
	float tx, ty, tz; //offset of the geometry from 0,0,0
	float scale; //scaing factor to fit the geometry in the unit-sized bounding box
	unsigned num_set_voxels; //number of voxels inside the geometry.
};

#endif /* BINVOXINFO_H_ */
