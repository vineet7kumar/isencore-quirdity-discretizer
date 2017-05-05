/*
 * voxels.h
 *
 *  Created on: Jun 20, 2014
 *      Author: vineet
 */

#ifndef VOXELS_H_
#define VOXELS_H_


/**
 * x,y,z coordinates of the voxels
 */
struct vox_coordinate{
	int x;
	int y;
	int z;
	bool is_set;//is the voxel inside the geometry?

	vox_coordinate(){
	  x=0;
	  y=0;
	  z=0;
	  is_set=true;
	}
};

typedef struct vox_coordinate* vox_coordinate_vector;

#endif /* VOXELS_H_ */
