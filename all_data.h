/*
 * all_data.h
 *
 *  Created on: Jun 25, 2014
 *      Author: vineet
 */

#ifndef ALL_DATA_H_
#define ALL_DATA_H_

#include "vertices.h"
#include "voxels.h"
#include "voxel_data.h"
#include "vertex_data.h"
#include "DataAbstractor.h"
#include "ReadBinvox.h"

struct voxel_and_vertex{
	voxel_vector voxels;
	vertex_vector vertices;
	int num_set_vertices;
	int num_set_voxels;
	int num_total_voxels;
	int num_total_vertices;
	int level_num;
};
/*
 * Define a vector to represent each level.
 */
typedef voxel_and_vertex* voxel_and_vertex_vector;


#endif /* ALL_DATA_H_ */
