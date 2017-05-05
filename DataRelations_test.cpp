/*
 * DataRelations_test.cpp
 *
 *  Created on: Jun 25, 2014
 *      Author: vineet
 */

#include "DataRelations.h"
#include "DataRelations_test.h"

void test_voxel_vertices(relative_vertex_coordinate_vector v, int* vi) {
  for (int i = 0; i < 8; i++) {
    std::cout << v[i].i << "|" << vi[i] << " ";
  }
  std::cout << std::endl;
}

void test_num_set_adj_voxels(voxel_and_vertex_vector vox_vert_vec, int i) {
  for (int j = 0; j < vox_vert_vec[i].num_set_voxels; j++) {
    std::cout << vox_vert_vec[i].voxels[j].voxel_index << " has "
        << vox_vert_vec[i].voxels[j].num_set_adjacent_voxels
        << "set adjacent voxels " << std::endl;
  }
}
void test_set_adj_voxels(voxel_and_vertex_vector vox_vert_vec, int i) {
  for (int j = 0; j < vox_vert_vec[i].num_set_voxels; j++) {
    std::cout << vox_vert_vec[i].voxels[j].voxel_index << " has "
        << vox_vert_vec[i].voxels[j].num_set_adjacent_voxels
        << " set adjacent voxels : ";
    for (int k = 0;
        k < NUM_ADJACENTS /*vox_vert_vec[i].voxels[j].num_set_adjacent_voxels*/;
        k++) {
      std::cout << vox_vert_vec[i].voxels[j].adjacent_voxels[k] << " ";
    }
    std::cout << std::endl;
  }
}
void test_children_and_parent_voxels(voxel_and_vertex_vector vox_vert_vec,
    int i) {
  for (int j = 0; j < vox_vert_vec[i].num_set_voxels; j++) {
    if (vox_vert_vec[i].voxels[j].children_voxels != 0) {
      std::cout << vox_vert_vec[i].voxels[j].voxel_index << " : ";
      for (int k = 0; k < 8; k++) {
        std::cout << vox_vert_vec[i].voxels[j].children_voxels[k] << " ";
      }
      std::cout << "| " << vox_vert_vec[i].voxels[j].parent;
      std::cout << std::endl;
    } else {
      std::cout << "Level 0 ";
      std::cout << "| " << vox_vert_vec[i].voxels[j].parent;
      std::cout << std::endl;

    }
  }

}

void test_set_adj_vertices(voxel_and_vertex_vector vox_vert_vec, int i) {
  for (int j = 0; j < vox_vert_vec[i].num_set_vertices; j++) {
    std::cout << vox_vert_vec[i].vertices[j].vertex_index << " has "
        << vox_vert_vec[i].vertices[j].num_set_adjacent_vertices
        << " set adjacent vertices : ";
    for (int k = 0;
        k < NUM_ADJACENTS /*vox_vert_vec[i].voxels[j].num_set_adjacent_voxels*/;
        k++) {
      std::cout << vox_vert_vec[i].vertices[j].adjacent_vertices[k] << " ";
    }
    std::cout << std::endl;
  }
}

void test_incident_voxels(voxel_and_vertex_vector vox_vert_vec, int i) {
  for (int j = 0; j < vox_vert_vec[i].num_set_vertices; j++) {
    std::cout << vox_vert_vec[i].vertices[j].vertex_index << " has ";
    for (int k = 0; k < 8; k++) {
      std::cout << vox_vert_vec[i].vertices[j].incident_voxels[k] << " ";
    }
    std::cout << "incident voxels" << std::endl;
  }
}

void test_adj_ver_next_finer_level(voxel_and_vertex_vector vox_vert_vec,
    int i) {
  for (int j = 0; j < vox_vert_vec[i].num_set_vertices; j++) {
    if (vox_vert_vec[i].vertices[j].adjacent_vertices_next_finer_level != 0) {
      std::cout << vox_vert_vec[i].vertices[j].vertex_index << " has ";
      for (int k = 0;
          k < NUM_ADJACENTS /*vox_vert_vec[i].voxels[j].num_set_adjacent_voxels*/;
          k++) {
        std::cout
            << vox_vert_vec[i].vertices[j].adjacent_vertices_next_finer_level[k]
            << " ";
      }
      std::cout << "adjacent vertices at the NFL" << std::endl;
    } else {
      std::cout << "level 0" << std::endl;
    }
  }

}

void test_adj_ver_next_coarser_level(voxel_and_vertex_vector vox_vert_vec,
    int i) {
  for (int j = 0; j < vox_vert_vec[i].num_set_vertices; j++) {
    std::cout << vox_vert_vec[i].vertices[j].vertex_index << " has ";
    for (int k = 0; k < 8; k++) {
      std::cout
          << vox_vert_vec[i].vertices[j].adjacent_vertices_next_coarser_level[k]
          << " ";
    }
    std::cout << "adjacent vertices at the NCL" << std::endl;
  }
}
