/*
 * DataAbstractor.h
 *
 *  Created on: Jun 19, 2014
 *      Author: vineet
 */

#ifndef DATAABSTRACTOR_H_
#define DATAABSTRACTOR_H_

#include "ReadBinvox.h"
#include "includes.h"
#include "BinvoxInfo.h"
#include "voxels.h"
#include "vertices.h"

class DataAbstractor {
public:
  DataAbstractor();

  virtual ~DataAbstractor();
  void abstract_data(const binvox_info raw_data, int level);
  vox_coordinate* create_xyz_voxel_data(const binvox_info raw_data);
  bool* create_zyx_voxel_vector(const vox_coordinate* voxCoordinatesArray,
      const binvox_info rawData);
  int* create_set_voxels_vector(const bool* zyxVoxels,
      const binvox_info rawData);
  int offset(int z, int y, int x, int width, int height);
  relative_vertex_coordinate* create_xyz_vertex_data(
      const binvox_info raw_data);
  absolute_vertex_coordinate* create_xyz_absolute_vertex_data(
      const relative_vertex_coordinate* relative_vertex_coordinates,
      const binvox_info raw_data, int num_total_vertices);
  bool* create_zyx_vertex_vector(
      const relative_vertex_coordinate* vertex_coordinate_array,
      const binvox_info raw_data, int num_total_vertices);
  int* create_set_vertex_vector(const bool* zyx_vertices,
      const relative_vertex_coordinate* vertex_coordinate_array,
      int num_total_vertices);

  /**
   * Returns a 1*rawData.size array vox_coordinates with (x,y,z) and corresponding
   * boolean value of set or not set.
   */
  const vox_coordinate* getvox_coordinate_array() const {
    return vox_coordinate_array;
  }
  /**
   * Sets the 1*rawData.size array of vox_coordinates
   */
  void setvox_coordinate_array(const vox_coordinate* voxCoordinateArray) {
    vox_coordinate_array = voxCoordinateArray;
  }
  /**
   * Returns the boolean vector of 1*rawData.size representing whether a voxel is
   * set or not. Voxels are ordered in z-y-x.
   */
  const bool* getvox_zyx_vector() const {
    return vox_zyx_vector;
  }
  /**
   * Sets the Boolean vector of voxels with set/unset data in the order z-y-x
   */
  void setvox_zyx_vector(const bool* voxZyxVector) {
    vox_zyx_vector = voxZyxVector;
  }
  /**
   * Returns a vector of indices of only those voxels that are set, sorted in the
   * order z-y-x
   */
  const int* getset_voxels_vector() const {
    return set_voxels_vector;
  }
  /*
   * Sets the array of indices of set voxels.
   */
  void setset_voxels_vector(const int* setVoxelsVector) {
    set_voxels_vector = setVoxelsVector;
  }

  const relative_vertex_coordinate* getvertex_coordinate_array() const {
    return relative_vertex_coordinate_array;
  }

  void setvertex_coordinate_array(
      const relative_vertex_coordinate* vertexCoordinateArray) {
    relative_vertex_coordinate_array = vertexCoordinateArray;
  }

  const bool* getvertex_zyx_vector() const {
    return vertex_zyx_vector;
  }

  void setvertex_zyx_vector(const bool* vertexZyxVector) {
    vertex_zyx_vector = vertexZyxVector;
  }

  const int* getset_vertex_vector() const {
    return set_vertex_vector;
  }

  void setset_vertex_vector(const int* setVertexVector) {
    set_vertex_vector = setVertexVector;
  }

  int getnum_set_vertices() const {
    return num_set_vertices;
  }

  void setnum_set_vertices(int numSetVertices) {
    num_set_vertices = numSetVertices;
  }

  int getnum_set_voxels() const {
    return num_set_voxels;
  }

  void setnum_set_voxels(int numSetVoxels) {
    num_set_voxels = numSetVoxels;
  }

  int getnum_total_vertices() const {
    return num_total_vertices;
  }

  void setnum_total_vertices(int numTotalVertices) {
    num_total_vertices = numTotalVertices;
  }

  int getnum_total_voxels() const {
    return num_total_voxels;
  }

  void setnum_total_voxels(int numTotalVoxels) {
    num_total_voxels = numTotalVoxels;
  }
  const absolute_vertex_coordinate* getabsolute_vertex_coordiante_array() const {
    return absolute_vertex_coordiante_array;
  }

  void setabsolute_vertex_coordiante_array(
      const absolute_vertex_coordinate* _absoluteVertexCoordianteArray) {
    absolute_vertex_coordiante_array = _absoluteVertexCoordianteArray;
  }

  struct translate_offset {
    float tx;
    float ty;
    float tz;

    translate_offset() {
      tx = 0.0;
      ty = 0.0;
      tz = 0.0;
    }

  };

  float getscale() const {
    return scale;
  }

  void setscale(float _scale) {
    this->scale = _scale;
  }

  struct translate_offset gettranslate() const {
    return translate;
  }

  void settranslate(struct translate_offset _translate) {
    this->translate = _translate;
  }

private:
  const vox_coordinate* vox_coordinate_array;
  const bool* vox_zyx_vector;
  const int* set_voxels_vector;
  struct translate_offset translate;
  float scale;
  const relative_vertex_coordinate* relative_vertex_coordinate_array;
  const absolute_vertex_coordinate* absolute_vertex_coordiante_array;
  const bool* vertex_zyx_vector;
  const int* set_vertex_vector;
  int num_total_voxels;
  int num_set_voxels;
  int num_total_vertices;
  int num_set_vertices;
};

#endif /* DATAABSTRACTOR_H_ */
