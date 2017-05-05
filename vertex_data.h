/*
 * vertex_data.h
 *
 *  Created on: Jun 24, 2014
 *      Author: vineet
 */

#ifndef VERTEX_DATA_H_
#define VERTEX_DATA_H_

#include "voxels.h"
#include "vertices.h"

struct vertex {
  int vertex_index;
  relative_vertex_coordinate relative_coordinates;
  absolute_vertex_coordinate absolute_coordinates;
  int num_set_adjacent_vertices;
  int* adjacent_vertices;
  int* incident_voxels;
  double* displacement;/*The elements in this vector are not initialized here.
   Make sure to do so*/
  int* adjacent_vertices_next_finer_level;
  int* adjacent_vertices_next_coarser_level;

  vertex() {
    vertex_index = -1;
    num_set_adjacent_vertices = 0;
    //relative_coordinates = new vertex_coordinate[1];
    adjacent_vertices = 0;
    incident_voxels = 0;
    displacement = 0;
    adjacent_vertices_next_coarser_level = 0;
    adjacent_vertices_next_finer_level = 0;
  }
};

typedef vertex* vertex_vector;

#endif /* VERTEX_DATA_H_ */
