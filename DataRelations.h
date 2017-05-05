/*
 * DataRelations.h
 *
 *  Created on: Jun 25, 2014
 *      Author: vineet
 */

#ifndef DATARELATIONS_H_
#define DATARELATIONS_H_

#include "vertices.h"
#include "voxels.h"
#include "voxel_data.h"
#include "vertex_data.h"
#include "DataAbstractor.h"
#include "ReadBinvox.h"
#include "all_data.h"

/*MACROS*/
#define NUM_ADJACENTS 27

class DataRelations {
public:
  DataRelations();

  DataRelations(const ReadBinvox* reader, const DataAbstractor* data_abstractor,
      int num_levels);

  virtual ~DataRelations();

  void relate_data();

  voxel_and_vertex populate_level_data(const DataAbstractor* data_abstractor,
      int level);

  void fill_voxels(DataAbstractor abstract_data_level, voxel_and_vertex &vv_l);

  void fill_vertices(DataAbstractor abstract_data_level,
      voxel_and_vertex &vv_l);
  const DataAbstractor* getdata_abstractor() const {
    return _data_abstractor;
  }

  /*BEGIN
   * Methods for populating voxel data
   */
  relative_vertex_coordinate_vector set_vertex(
      relative_vertex_coordinate_vector vcv, int width, int height,
      int voxel_index, voxel voxels);
  int* set_voxel_vertices(int width, int height, int voxel_index, voxel voxels);
//  absolute_vertex_coordinate* set_absolute_vertex(
//      relative_vertex_coordinate_vector rv, DataAbstractor abstract_data_level,
//      int width, int height, int depth);
//  int set_num_set_adjacent_voxels(DataAbstractor abstract_data_level, voxel vox,
//      int width, int height);

  int* set_adjacent_voxel_indices(DataAbstractor abstract_data_level,
      int* adj_vox, int num_adj, int width, int height, int depth, voxel &vox);

  int* set_children_voxel_indices(DataAbstractor abstract_data_level, int width,
      int height, voxel vox, int level);

  int set_parent_index(DataAbstractor abstract_data_level, int width,
      int height, voxel vox, int level);
  /*END*/
  /*BEGIN
   * Methods for populating vertex data
   */
  absolute_vertex_coordinate calculateAbsoluteCoordinates(
      relative_vertex_coordinate relative_coordinates,
      DataAbstractor abstract_data_level, int width, int height, int depth);
  int* set_adjacent_vertex_indices(DataAbstractor abstract_data_level,
      int width, int height, int depth, vertex &ver, voxel_and_vertex &vv_l);
  int* set_incident_voxels(DataAbstractor abstract_data_level, int width,
      int height, int depth, vertex &ver);
  int* set_adjacent_vertices_next_finer_level(
      DataAbstractor abstract_data_level, int width, int height, int depth,
      int level, vertex &ver);
  int* set_adjacent_vertices_next_coarser_level(
      DataAbstractor abstract_data_level, int width, int height, int depth,
      int level, vertex &ver);
  const bool is_vertex_in_incident_voxel(int adj_index, vertex& ref_ver,
  /*voxel_and_vertex &vv_l,*/int width, int height,
      DataAbstractor abstract_data_level);
  const bool is_vertex_in_incident_voxel(int adj_index, int* incident_voxels,
  /*voxel_and_vertex &vv_l,*/int width, int height,
      DataAbstractor abstract_data_level);
  /*END*/
  void setdata_abstractor(const DataAbstractor* dataAbstractor) {
    _data_abstractor = dataAbstractor;
  }
  int linear_index(int width, int height, int z, int y, int x);
  int getnum_levels() const {
    return _num_levels;
  }

  const ReadBinvox* getreader() const {
    return _reader;
  }

  void setreader(const ReadBinvox* reader) {
    _reader = reader;
  }

  void setnum_levels(int numLevels) {
    _num_levels = numLevels;
  }

  const voxel_and_vertex* getvoxel_and_vector() const {
    return _voxel_and_vector;
  }

  void setvoxel_and_vector(const voxel_and_vertex* voxelAndVector) {
    _voxel_and_vector = voxelAndVector;
  }

  void test_voxels(voxel_and_vertex_vector vox_vert_vec, int i);

  void test_vertices(voxel_and_vertex_vector vox_vert_vec, int i);

  voxel_and_vertex_vector fix_adjacencies(voxel_and_vertex_vector& vox_vert_vec,
      int num_levels, const DataAbstractor* abstract_data);
  voxel_and_vertex fix_adjacency_next_finer_level(voxel_and_vertex& vv_this,
      voxel_and_vertex& vv_next_finer, DataAbstractor abstract_data_this,
      DataAbstractor abstract_data_nf, int level);
  voxel_and_vertex fix_adjacency_next_coarser_level(voxel_and_vertex& vv_this,
      voxel_and_vertex& vv_next_coarser, DataAbstractor abstract_data_this,
      DataAbstractor abstract_data_nc, int level);
  int get_relative_child_vertex(relative_vertex_coordinate ver_this,
      voxel_and_vertex& vv_nf, DataAbstractor ad_nf, int child_width,
      int child_height);
  vertex get_relative_parent_vertex(relative_vertex_coordinate ver_this,
      voxel_and_vertex& vv_nc, DataAbstractor ad_nc, int parent_width,
      int parent_height);
  int* find_incident_voxels_ncl(relative_vertex_coordinate ver_this,
      voxel_and_vertex& vv_this, voxel_and_vertex& vv_next_coarser,
      DataAbstractor abstract_data_this, DataAbstractor abstract_data_nc,
      int level, int ind);
  int* remove_duplicate_voxels(int* voxels);

private:
  const ReadBinvox* _reader;
  const DataAbstractor* _data_abstractor;
  int _num_levels;
  const voxel_and_vertex* _voxel_and_vector;
  bool debug;
};

#endif /* DATARELATIONS_H_ */
