/*
 * discretize.h
 *
 *  Created on: Jul 2, 2014
 *      Author: vineet
 */

#ifndef DISCRETIZE_H_
#define DISCRETIZE_H_

#include "BinvoxInfo.h"
#include "DataAbstractor.h"
#include "DataRelations.h"
#include "DataRelations_test.h"
#include "ReadBinvox.h"
#include "RunBinvox.h"
#include "all_data.h"
#include "vertex_data.h"
#include "vertices.h"
#include "voxel_data.h"
#include "voxels.h"

std::string* get_binvox_file_names(char* argv[]);
void test_data_abstractor_output(int i, DataAbstractor* data_abstractor);
DataRelations do_discretization(int argc, char* argv[]);
absolute_vertex_coordinate get_absolute_vertex_coordinates(
    DataAbstractor abstract_data, int index);

#endif /* DISCRETIZE_H_ */
