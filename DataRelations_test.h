/*
 * DataRelations_test.h
 *
 *  Created on: Jul 2, 2014
 *      Author: vineet
 */

#ifndef DATARELATIONS_TEST_H_
#define DATARELATIONS_TEST_H_

#include "DataRelations.h"

void test_voxel_vertices(relative_vertex_coordinate_vector v, int* vi);
void test_num_set_adj_voxels(voxel_and_vertex_vector vox_vert_vec, int i);
void test_set_adj_voxels(voxel_and_vertex_vector vox_vert_vec, int i);
void test_children_and_parent_voxels(voxel_and_vertex_vector vox_vert_vec,
    int i);
void test_set_adj_vertices(voxel_and_vertex_vector vox_vert_vec, int i);
void test_incident_voxels(voxel_and_vertex_vector vox_vert_vec, int i);
void test_adj_ver_next_finer_level(voxel_and_vertex_vector vox_vert_vec, int i);
void test_adj_ver_next_coarser_level(voxel_and_vertex_vector vox_vert_vec,
    int i);
#endif /* DATARELATIONS_TEST_H_ */

