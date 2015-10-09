//
//  main.cpp
//  GameOfLife
//
//  Created by Marianna Neubauer on 10/4/15.
//  Copyright (c) 2015 Marianna Neubauer. All rights reserved.
//

#include <time.h>
#include <ctime>
//#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include "Board.h"

#define ITERATIONS 10

using std::cout;
using std::endl;

int main(int argc, const char * argv[]) {
	
	std::ifstream input(argv[1]);
	std::cout << "Let's Start!\n";
	
	srand(time(NULL));
	
	Board *board = new Board();
	
	char line[64];
	while(input) {
		input.getline(line, 64);
		std::string coordinates(line);

		auto pos1 = coordinates.find("(");
		auto pos2 = coordinates.find(",");
		auto pos3 = coordinates.find(")");
		
		if (pos1 == std::string::npos || pos2 == std::string::npos || pos3 == std::string::npos) continue;
		
		/*auto pos_neg = coordinates.find("-");
		bool x_neg = pos_neg != std::string::npos ? true : false;
		
		pos_neg = pos_neg != std::string::npos ? pos_neg : 0;

		pos_neg = coordinates.substr(pos_neg).find("-");
		bool y_neg = pos_neg != std::string::npos ? true : false;*/
		
		auto x_coord = coordinates.substr(pos1+1, pos2-1);
		auto y_coord = coordinates.substr(pos2+1, pos3-1);
		
		unsigned long long x_ull = std::strtoull(x_coord.c_str(), 0, 10);
		unsigned long long y_ull = std::strtoull(y_coord.c_str(), 0, 10);
		
		int64_t x = x_ull;
		int64_t y = y_ull;
		
		board->CellIsAlive(x, y);
		//std::cout << std::to_string(x) << " " << std::to_string(y) << std::endl;
	}
	
	
	
	// start the board
	/*for ( int64_t y = MIN; y < MAX; y++) {
		for (int64_t x = MIN; x < MAX; x++) {
			int num = rand() % 10;
			if (num > 5) {
				board->CellIsAlive(x, y);
			}
		}
	}*/
	
	//std::clock_t start;
	//double duration;
	
	for (int i = 0; i < ITERATIONS; i++) {
		board->PrintBoard();
		board->Tick(std::chrono::milliseconds(50));
		
		//start = std::clock();
		
		board->UpdateBoard();
		
		//duration = ( std::clock() - start );
		//std::cout<< duration <<'\n';
	}
	
	
	
	return 0;
	
}
