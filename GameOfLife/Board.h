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
#include <array>
#include <thread>
#include <set>
#include <vector>

#include "SINT64.h"
#include "Cell.h"

/*#ifdef _WIN32
#include <windows.h>

void sleep(unsigned milliseconds)
{
	Sleep(milliseconds);
}
#else
#include <unistd.h>

void sleep(unsigned milliseconds)
{
	usleep(milliseconds * 1000); // takes microseconds
}
#endif*/

//#define HEIGHT 50
//#define WIDTH 50

#define MIN 0 //if (draw_board) 0 else std::numeric_limits<int64_t>::min()
#define MAX 50 //if (draw_board) 50 else std::numeric_limits<int64_t>::max()
//bool draw_board = true;

class Board {
public:
	
	Board() : totalAlive_(0) { }
	~Board() { }
	
	
	void CellIsAlive(int64_t x, int64_t y) {
		//cells_[y + HEIGHT/2][x + WIDTH/2].statusIs("alive");
		aliveCells_.insert({x,y});
		totalAlive_++;
	}
	
	void UpdateBoard();
	
	void PrintBoard();
	
	void Tick() {
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	
private:
	
	void CheckDeadCellsNeighbors(int64_t deadCellX, int64_t deadCellY);
	
	//std::array<std::array<Cell, WIDTH>, HEIGHT> cells_;
	//std::array<std::array<Cell, WIDTH>, HEIGHT> previousCells_;
	std::set<std::pair<int64_t, int64_t>> aliveCells_;
	std::set<std::pair<int64_t, int64_t>> previousAliveCells_;
	std::set<std::pair<int64_t, int64_t>> checkedDeadCells_;
	uint64_t totalAlive_;
};

#endif /* defined(__GameOfLife__Board__) */
