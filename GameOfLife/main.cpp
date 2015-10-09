//
//  main.cpp
//  GameOfLife
//
//  Created by Marianna Neubauer on 10/4/15.
//  Copyright (c) 2015 Marianna Neubauer. All rights reserved.
//

#include <time.h>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>

#include "Board.h"

#define ITERATIONS 100

using std::cout;
using std::endl;



int main(int argc, const char * argv[]) {

	Board *board = new Board();
	
	if (argc < 2) {
		cout << "Please provide a list of inputs (x,y), one live cell per line, then press crtl-d" << endl;
		board->initializeBoard(std::cin);
	} else {
		std::ifstream input(argv[1]);
		if (input.good()) {
			board->initializeBoard(input);
		} else {
			cout << "Error" << endl;
			exit(0);
		}
	}

	/*for (int i = 0; i < ITERATIONS; i++) {
		board->PrintBoard();
		board->Tick(std::chrono::milliseconds(50));
		board->UpdateBoard();
	}*/
	
	while (true) {
		board->PrintBoard();
		board->Tick(std::chrono::milliseconds(50));
		board->UpdateBoard();
	}

	return 0;
	
}
