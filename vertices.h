/*
 * vertices.h
 *
 *  Created on: Jun 24, 2014
 *      Author: vineet
 */

#ifndef VERTICES_H_
#define VERTICES_H_

struct relative_vertex_coordinate {
  int x;
  int y;
  int z;
  int i;
  bool is_set;

  relative_vertex_coordinate() {
    x = 0;
    y = 0;
    z = 0;
    i = 0;
    is_set = false;
  }

};

typedef struct relative_vertex_coordinate* relative_vertex_coordinate_vector;

struct absolute_vertex_coordinate {
  double x;
  double y;
  double z;
  int i;
  bool is_set;

  absolute_vertex_coordinate() {
    x = 0.0;
    y = 0.0;
    z = 0.0;
    i = 0;
    is_set = false;
  }

};
typedef struct absolute_vertex_coordinate* absolute_vertex_coordinate_vector;
#endif /* VERTICES_H_ */
