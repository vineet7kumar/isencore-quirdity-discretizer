/*
 * RunBinvox.cpp
 *
 *  Created on: Jun 16, 2014
 *      Author: vineet
 */

#include "RunBinvox.h"
#include <string>
#include<stdlib.h>
#include<iostream>
#include "includes.h"

RunBinvox::RunBinvox() {
	// TODO Auto-generated constructor stub

}

RunBinvox::~RunBinvox() {
	// TODO Auto-generated destructor stub
}


int RunBinvox::run(char* dim, char* num_down, char* infile_path) {
	bool debug = false;
	std::string _dim(dim), _num_down(num_down), _infile_path(infile_path);
	std::string command = "python run_binvox.py ";
	command = command.append(_dim).append(" ");
	command = command.append(_num_down).append(" ");
	command = command.append(_infile_path).append(" ");
	if (debug) {
		if (command.length() > 0)
			std::cout << command;
	}

	return (system(command.c_str()));

}

