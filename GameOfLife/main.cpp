//
//  main.cpp
//  GameOfLife
//
//  Created by Marianna Neubauer on 10/4/15.
//  Copyright (c) 2015 Marianna Neubauer. All rights reserved.
//

#include <time.h>

#include "Board.h"

#define ITERATIONS 1000

int main(int argc, const char * argv[]) {
	// insert code here...
	std::cout << "Let's Start!\n";
	
	srand(time(NULL));
	
	
	Board *board = new Board();
	
	// start the board
	for ( int64_t y = MIN; y < MAX; y++) {
		for (int64_t x = MIN; x < MAX; x++) {
			int num = rand() % 10;
			if (num > 5) {
				board->CellIsAlive(x, y);
			}
		}
	}
	
	for (int i = 0; i < ITERATIONS; i++) {
		board->PrintBoard();
		board->Tick();
		board->UpdateBoard();
	}
	
	
	
	return 0;
	
}
