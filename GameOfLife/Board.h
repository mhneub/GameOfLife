//
//  Board.h
//  GameOfLife
//
//  Created by Marianna Neubauer on 10/4/15.
//  Copyright (c) 2015 Marianna Neubauer. All rights reserved.
//

#ifndef __GameOfLife__Board__
#define __GameOfLife__Board__

#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>
#include <set>
#include <array>

#define WIDTH 200
#define HEIGHT 50

#define MIN std::numeric_limits<int64_t>::min()
#define MAX std::numeric_limits<int64_t>::max()

class Board {
public:
	
	Board() { }
	~Board() { }
	
	void initializeBoard(std::istream& input);
	
	void UpdateBoard();
	
	void PrintBoard();
	
	void Tick(std::chrono::milliseconds ms) {
		std::this_thread::sleep_for(ms);
	}
	
private:
	
	void CheckDeadCellsNeighbors(int64_t deadCellX, int64_t deadCellY);
	void CellIsAlive(int64_t x, int64_t y);

	// These sets are the bulk of the optimization.
	// We only need to store the cells that are alive and the dead neighbors
	// of the live cells during each update.
	std::set<std::pair<int64_t, int64_t>> aliveCells_;
	std::set<std::pair<int64_t, int64_t>> previousAliveCells_;
	std::set<std::pair<int64_t, int64_t>> checkedDeadCells_;
};

#endif /* defined(__GameOfLife__Board__) */
