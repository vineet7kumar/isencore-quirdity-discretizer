/*
 * DataAbstractor.cpp
 *
 *  Created on: Jun 19, 2014
 *      Author: vineet
 */

#include "DataAbstractor.h"
#include "voxels.h"
#include "voxel_data.h"

DataAbstractor::DataAbstractor() {
  // TODO Auto-generated constructor stub

}

DataAbstractor::~DataAbstractor() {
  // TODO Auto-generated destructor stub
}

/**
 * Makes a (x,y,z) co-ordinate view of all the voxels in the bounding box.
 * This view can be used to query a voxel at index i to get its x,y,z
 * co-ordinates and whether it is set or not, i.e, inside the geometry.
 */
vox_coordinate* DataAbstractor::create_xyz_voxel_data(
    const binvox_info raw_data) {
  vox_coordinate* voxels = new vox_coordinate[raw_data.size];
  int x, y, z, i = 0, ofst = 0;
  for (x = 0; x < raw_data.width; x++) {
    for (z = 0; z < raw_data.depth; z++) {
      for (y = 0; y < raw_data.height; y++) {
        ofst = offset(z, y, x, raw_data.width, raw_data.height);
        voxels[ofst].is_set = raw_data.voxels[i];
        voxels[ofst].x = x;
        voxels[ofst].y = y;
        voxels[ofst].z = z;
        i++;
      }
    }
  }
  if (i != raw_data.size) {
    std::cout
        << "number of voxels unequal to recorded number of voxels, somehow!";
    exit(1);
  }
  return voxels;
}

/**
 * Returns a boolean vector of voxels indexed in an ordering such that z is the
 * most significant axis and x the least (z is the outermost loop and x, the
 * innermost). A value of true for voxel at index i represents that it is contained
 * inside the geometry.
 */
bool* DataAbstractor::create_zyx_voxel_vector(
    const vox_coordinate* voxCoordinatesArray, const binvox_info rawData) {
  int size = rawData.size;
  int w = rawData.width, h = rawData.height, d = rawData.depth;
  bool* zyx_voxel_vector = new bool[rawData.size];
  int index_to_set = 0;
  int x, y, z;
  int i;
  for (i = 0; i < size; i++) {
    x = voxCoordinatesArray[i].x;
    y = voxCoordinatesArray[i].y;
    z = voxCoordinatesArray[i].z;
    index_to_set = z * w * h + y * w + x;
    zyx_voxel_vector[index_to_set] = voxCoordinatesArray[i].is_set;
  }
  if (i != size) {
    std::cout
        << "number of voxels unequal to recorded number of voxels, somehow!";
    exit(1);
  }
  return zyx_voxel_vector;

}

/**
 * Creates an array of indices of voxels that are contained in the geometry.
 * These indices are sorted in the order z-y-x
 */
int* DataAbstractor::create_set_voxels_vector(const bool* zyxVoxels,
    const binvox_info rawData) {
  int* set_voxels_vector = new int[rawData.num_set_voxels];
  int ctr = 0;
  for (int i = 0; i < rawData.size; i++) {
    if (zyxVoxels[i]) {
      set_voxels_vector[ctr] = i;
      ctr++;
    }
  }
  if (ctr != rawData.num_set_voxels) {
    std::cout << "number of set voxels mismatch number of set voxels counted.";
    exit(1);
  }
  return set_voxels_vector;
}

int DataAbstractor::offset(int z, int y, int x, int width, int height) {
  return (z * width * height + y * width + x);
}

/**
 * create a vector of all the vertices in the bounding box, ordered in z-y-x.
 * Can also be used to query x,y,z co-ordinates and and whether the vertex is
 * set or not.
 */
relative_vertex_coordinate* DataAbstractor::create_xyz_vertex_data(
    const binvox_info raw_data) {
  int num_x_verts = raw_data.width + 1;
  int num_y_verts = raw_data.height + 1;
  int num_z_verts = raw_data.depth + 1;
  int num_total_verts = num_x_verts * num_y_verts * num_z_verts;

  relative_vertex_coordinate* vertices =
      new relative_vertex_coordinate[num_total_verts];
  const vox_coordinate* vox_array = getvox_coordinate_array();
  bool* is_vertex_written = new bool[num_total_verts];

  for (int i = 0; i < num_total_verts; i++) {
    is_vertex_written[i] = false;
  }
  /*
   * Number of voxels in the bounding box is equal to
   * raw_data.size
   */
  int x = 0, y = 0, z = 0, ctr = 0;
  for (int i = 0; i < raw_data.size; i++) {

    x = vox_array[i].x;
    y = vox_array[i].y;
    z = vox_array[i].z;

    for (int u = 0; u <= 1; u++)
      for (int v = 0; v <= 1; v++)
        for (int w = 0; w <= 1; w++) {
          z += u;
          y += v;
          x += w;

          //std::cout << z << "," << y << "," << x << std::endl;

          ctr = offset(z, y, x, num_x_verts, num_y_verts);
          //if (!is_vertex_written[ctr]) {
          vertices[ctr].x = x;
          vertices[ctr].y = y;
          vertices[ctr].z = z;
          vertices[ctr].i = ctr;
          vertices[ctr].is_set =
              vertices[ctr].is_set ? vertices[ctr].is_set : vox_array[i].is_set;
          is_vertex_written[ctr] = true;
          //}
          z -= u;
          y -= v;
          x -= w;
        }
  }

  if (ctr - num_total_verts != -1) {
    std::cout
        << "Something is wrong. number of set vertices is not what it should be";
    exit(1);
  }
  //std::cout << "~~ctr=" << ctr << " ~~total verts=" << num_total_verts << std::endl;

  return vertices;
}
/**
 * Returns a boolean array of vertices indicating whether a vertex is
 * inside the geometry or not.
 */
bool* DataAbstractor::create_zyx_vertex_vector(
    const relative_vertex_coordinate* vertex_coordinate_array,
    const binvox_info raw_data, int num_total_vertices) {
  bool* vertex_vector = new bool[num_total_vertices];
  for (int i = 0; i < num_total_vertices; i++) {
    if (vertex_coordinate_array[i].i != i) {
      std::cout << "Vertices are not ordered properly." << std::endl;
      exit(1);
    }
    vertex_vector[i] = vertex_coordinate_array[i].is_set ? true : false;
  }
  return (vertex_vector);
}

absolute_vertex_coordinate* DataAbstractor::create_xyz_absolute_vertex_data(
    const relative_vertex_coordinate* relative_vertex_coordinates,
    const binvox_info raw_data, int num_total_vertices) {
  absolute_vertex_coordinate* abs_ver =
      new absolute_vertex_coordinate[num_total_vertices];
  float scale = getscale();
    translate_offset t_off = gettranslate();
  for (int v = 0; v < num_total_vertices; v++) {
    double vox_width = (double) (scale / raw_data.width);
    double vox_height = (double) (scale / raw_data.height);
    double vox_depth = (double) (scale / raw_data.depth);

    abs_ver[v].x = (double) (vox_width * relative_vertex_coordinates[v].x)
        + (double) t_off.tx;
    abs_ver[v].y = (double) (vox_height * relative_vertex_coordinates[v].y)
        + (double) t_off.ty;
    abs_ver[v].z = (double) (vox_depth * relative_vertex_coordinates[v].z)
        + (double) t_off.tz;
    abs_ver[v].i = relative_vertex_coordinates[v].i;
    abs_ver[v].is_set = relative_vertex_coordinates[v].is_set;
  }
  return (abs_ver);
}

int* DataAbstractor::create_set_vertex_vector(const bool* zyx_vertices,
    const relative_vertex_coordinate* vertex_coordinate_array,
    int num_total_vertices) {
  int num_set_verts = 0;
  for (int i = 0; i < num_total_vertices; i++) {
    if (zyx_vertices[i]) {
      num_set_verts++;
    }
  }
  setnum_set_vertices(num_set_verts);
  int* set_vertex_vector = new int[num_set_verts];
  int ctr = 0;
  for (int i = 0; i < num_total_vertices; i++) {
    if (zyx_vertices[i]) {
      set_vertex_vector[ctr] = i;
      ctr++;
    }
  }
  if (ctr != num_set_verts) {
    std::cout << "something went wrong." << std::endl;
    exit(1);
  }
  return (set_vertex_vector);
}

/**
 * Entry method that calls all the create methods and set the appropriate
 * fields in the DataAbstractor object.
 * Note that all these fields are const and cannot be modified.
 */
void DataAbstractor::abstract_data(const binvox_info raw_data, int level) {

  /*
   * fill offset and scaling info
   */
  translate_offset off;
  off.tx = raw_data.tx;
  off.ty = raw_data.ty;
  off.tz = raw_data.tz;
  settranslate(off);
  setscale(raw_data.scale);

  /**
   * Voxel information
   */
  const vox_coordinate* vc = create_xyz_voxel_data(raw_data);
  setvox_coordinate_array(vc);
  const bool* b = create_zyx_voxel_vector(getvox_coordinate_array(), raw_data);
  setvox_zyx_vector(b);
  const int* i = create_set_voxels_vector(getvox_zyx_vector(), raw_data);
  setset_voxels_vector(i);
  setnum_total_voxels(raw_data.size);
  setnum_set_voxels(raw_data.num_set_voxels);

  /**
   * vertex information
   */
  const relative_vertex_coordinate* vec = create_xyz_vertex_data(raw_data);
  setvertex_coordinate_array(vec);
  int num_total_verts = (raw_data.depth + 1) * (raw_data.height + 1)
      * (raw_data.width + 1);
  const absolute_vertex_coordinate* abs_vec = create_xyz_absolute_vertex_data(
      getvertex_coordinate_array(), raw_data, num_total_verts);
  setabsolute_vertex_coordiante_array(abs_vec);
  const bool* be = create_zyx_vertex_vector(getvertex_coordinate_array(),
      raw_data, num_total_verts);
  setvertex_zyx_vector(be);
  const int* ie = create_set_vertex_vector(be, vec, num_total_verts);
  setset_vertex_vector(ie);
  setnum_total_vertices(num_total_verts);
  //num_set_vertices is set inside cretae_set_vertex_vector
}

