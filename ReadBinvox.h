/*
 * ReadBinvox.h
 *
 *  Created on: Jun 14, 2014
 *      Author: vineet
 */

#ifndef READBINVOX_H_
#define READBINVOX_H_

#include "includes.h"
#include "string"
#include "BinvoxInfo.h"
#include "DataAbstractor.h"

//struct binvox_info;
class ReadBinvox {
public:

//typedef binvox_info* binvox_p;
	ReadBinvox();
	void read(std::string filespec);
	virtual ~ReadBinvox();
	const binvox_info* getBinvoxData() ;
	void setBinvoxData(binvox_info* binvoxData);

private:
	binvox_info* binvox_data;

};

#endif /* READBINVOX_H_ */
