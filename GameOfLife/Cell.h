//
//  Cell.h
//  GameOfLife
//
//  Created by Marianna Neubauer on 10/4/15.
//  Copyright (c) 2015 Marianna Neubauer. All rights reserved.
//

#ifndef __GameOfLife__Cell__
#define __GameOfLife__Cell__

#include <cstdlib>
#include <iostream>
#include <string>

class Cell
{
public:
	
	Cell() : status_(0) { }

	~Cell() { }
	
	uint8_t status() {
		return status_;
	}
	
	void statusIs(std::string status) {
		if (status == "alive") {
			status_ = 1;
		} else if (status == "dead") {
			status_ = 0;
		} if (status != "alive" && status != "dead") {
			std::cerr << "Cell cannot be " << status <<
			". Cell must be alive or dead" << std::endl;
		}
	}
	
private:
	uint8_t status_;
	
};

#endif /* defined(__GameOfLife__Cell__) */
