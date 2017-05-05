/*
 * voxel_data.h
 *
 *  Created on: Jun 24, 2014
 *      Author: vineet
 */

#ifndef VOXEL_DATA_H_
#define VOXEL_DATA_H_

#include "voxels.h"
#include "vertices.h"

typedef unsigned char byte;
struct voxel{
	byte geometric_pos;
	/* 1=in geometry,
	 * 0=outside geometry, but inside bounding box,
	 * -1=outside binding box
	 * Other values should not be read if this is -1;
	 * They will just be garbage !
	 */
	int voxel_index;
	vox_coordinate coordinates;
	relative_vertex_coordinate_vector relative_voxel_vertices;/*8 vertices of voxels*/
	int* vertex_indices;
	absolute_vertex_coordinate* absolute_voxel_vertices;
	int num_set_adjacent_voxels;
	int* adjacent_voxels;/*array of indices in the bounding box*/
	int* children_voxels;/*array of indices in the bounding box of child level*/
	int parent;/*index of the parent in the parent level bounding box*/

	voxel(){
		geometric_pos=-1;
		voxel_index=-1;
		//coordinates = 0;
		num_set_adjacent_voxels = 0;
		relative_voxel_vertices=0;
		vertex_indices = 0;
		adjacent_voxels = 0;
		children_voxels=0;
		parent=0;

	}
};

typedef voxel* voxel_vector;



#endif /* VOXEL_DATA_H_ */
