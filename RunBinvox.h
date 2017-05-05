/*
 * RunBinvox.h
 *
 *  Created on: Jun 16, 2014
 *      Author: vineet
 */

#ifndef RUNBINVOX_H_
#define RUNBINVOX_H_

class RunBinvox {
public:
	RunBinvox();
	static int run(char* dim, char* num_down, char* infile_path);
	virtual ~RunBinvox();
};

#endif /* RUNBINVOX_H_ */
