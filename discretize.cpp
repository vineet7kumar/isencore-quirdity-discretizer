/*
 * Main.cpp
 *
 *  Created on: Jun 16, 2014
 *      Author: vineet
 */

#include "RunBinvox.h"
#include "ReadBinvox.h"
#include "BinvoxInfo.h"
#include "DataAbstractor.h"
#include "DataRelations.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include "includes.h"

using namespace std;
/*
 * std_patch is defined as a workaround to the bug in g++
 * that does not identify to_string method in scpe std.
 * see:
 *  http://stackoverflow.com/questions/12975341/to-string-is-not-a-member-of-std-says-so-g
 */
namespace std_patch {
template<typename T> std::string to_string(const T& n) {
  std::ostringstream stm;
  stm << n;
  return (stm.str());
}
}

std::string* get_binvox_file_names(char* argv[]) {
  std::string input_file = string(argv[3]);
  unsigned dot_posn = input_file.find_last_of(".");
  std::string file_name = input_file.substr(0, dot_posn);
  int num_downs = atoi(argv[2]);
  std::string* binvox_files = new std::string[num_downs + 1];
  binvox_files[0] = file_name + ".binvox";
  for (int i = 1; i <= num_downs; i++) {
    binvox_files[i] = file_name + "_" + std_patch::to_string(i) + ".binvox";
  }
  return (binvox_files);
}

void test_data_abstractor_output(int i, DataAbstractor* data_abstractor) {
  cout << "number of set vertices " << data_abstractor[i].getnum_set_vertices()
      << endl;
  for (int j = 0; j < data_abstractor[i].getnum_set_vertices(); j++) {
    int t = data_abstractor[i].getset_vertex_vector()[j];
    cout << data_abstractor[i].getset_vertex_vector()[j] << "--"
        << data_abstractor[i].getvertex_coordinate_array()[t].x << ","
        << data_abstractor[i].getvertex_coordinate_array()[t].y << ","
        << data_abstractor[i].getvertex_coordinate_array()[t].z << endl;
  }
  cout << "number of set voxels " << data_abstractor[i].getnum_set_voxels()
      << endl;
  for (int j = 0; j < data_abstractor[i].getnum_set_voxels(); j++) {
    int t = data_abstractor[i].getset_voxels_vector()[j];
    cout << data_abstractor[i].getset_voxels_vector()[j] << "--"
        << data_abstractor[i].getvox_coordinate_array()[t].x << ","
        << data_abstractor[i].getvox_coordinate_array()[t].y << ","
        << data_abstractor[i].getvox_coordinate_array()[t].z << endl;
  }
}

DataRelations do_discretization(int argc, char* argv[]) {
  bool debug = false;
  RunBinvox runner;
  int run_result;
  int num_levels = atoi(argv[2]) + 1;
  if (argc < 4) {
    std::cout << "Number of arguments is less than 3. ABORTING";
    exit(1);
  }
  if (argc > 4) {
    std::cout << "Number of arguments is more than 3. Ignoring extra arguments";
  }
  /*
   * argv[1] = dims
   * argv[2] = max number of -downs passed to binvox
   * argv[3] = path to the input image file
   */
  run_result = runner.run(argv[1], argv[2], argv[3]);
  if (run_result != 0) {
    std::cout << "Binvox did not run properly. Aborting.\n";
  }
  ReadBinvox* reader = new ReadBinvox[num_levels];
  std::string* binvox_file_names;
  binvox_file_names = get_binvox_file_names(argv);
  DataAbstractor* data_abstractor = new DataAbstractor[num_levels];
  /*
   * Read all the files at different levels in
   * a loop.
   */
  for (int i = 0; i < num_levels; i++) {
    reader[i].read(binvox_file_names[i]);
    const binvox_info* raw_data;
    raw_data = reader[i].getBinvoxData();
    if (debug)
      cout << raw_data->num_set_voxels << endl;
    data_abstractor[i].abstract_data(*raw_data, i);
    if (debug) {
      test_data_abstractor_output(i, data_abstractor);
    }
  }

  /*
   * No need for the generated binvox files now. Removing them.
   */
  for (int i = 0; i < num_levels; i++) {
    remove(binvox_file_names[i].c_str());
  }
  //system("rm *.binvox");

  const ReadBinvox* reader_ = reader;
  const DataAbstractor* data_abstractor_ = data_abstractor;
  DataRelations data_relations(reader_, data_abstractor_, num_levels);
  data_relations.relate_data();
  return data_relations;
}

//int main(int argc, char* argv[]) {
//	DataRelations dr;
//	dr = do_discretization(argc, argv);
//	return 0;
//}

absolute_vertex_coordinate get_absolute_vertex_coordinates(
    DataAbstractor abstract_data, int index) {

  return (abstract_data.getabsolute_vertex_coordiante_array()[index]);
}

//	std::cout << "Starting discretization...";
//	//vnv = voxelRelations.getvoxel_and_vector();
//
////	std::cout << "Geometry info:\n" << "\tNumber of vertices: "
////			<< vnv->num_set_vertices << "\n" << "\tNumber of voxels: "
////			<< vnv->num_set_voxels << "\n\n";
////
////	std::cout << "Bounding box info:\n" << "\tNumber of vertices: "

absolute_vertex_coordinate av;

