//
//  Board.cpp
//  GameOfLife
//
//  Created by Marianna Neubauer on 10/4/15.
//  Copyright (c) 2015 Marianna Neubauer. All rights reserved.
//

#include "Board.h"

void Board::initializeBoard(std::istream& input) {
	
	char line[64];
	while(input) {
		input.getline(line, 64);
		std::string coordinates(line);
		
		auto pos1 = coordinates.find("(");
		auto pos2 = coordinates.find(",");
		auto pos3 = coordinates.find(")");
		
		if (pos1 == std::string::npos || pos2 == std::string::npos || pos3 == std::string::npos) continue;
		
		auto x_coord = coordinates.substr(pos1+1, pos2-1);
		auto y_coord = coordinates.substr(pos2+1, pos3-1);
		
		// Not sure why but strtoll does not return a signed 64 bit int,
		// so I get the unsigned 64 bit int can cast it to signed.
		// This assumes long long is represented by 64 bits on the machine
		unsigned long long x_ull = std::strtoull(x_coord.c_str(), 0, 10);
		unsigned long long y_ull = std::strtoull(y_coord.c_str(), 0, 10);
		
		int64_t x = x_ull;
		int64_t y = y_ull;
		
		CellIsAlive(x, y);
	}
	
	// if no input, random generation of live cells
	if (aliveCells_.size() == 0) {
		for ( int64_t y = 0; y < HEIGHT; y++) {
			for (int64_t x = 0; x < WIDTH; x++) {
				int num = rand() % 10;
				if (num > 5) {
		 			CellIsAlive(x, y);
				}
		 	}
		}
	}
}


void Board::UpdateBoard() {
	
	previousAliveCells_ = aliveCells_;
	checkedDeadCells_.clear();
	
	for (auto cell: previousAliveCells_) {
		uint8_t numNeighborsAlive = 0;
		
		int64_t start_x = (cell.first == MIN ? cell.first : cell.first-1);
		int64_t end_x = (cell.first == MAX ? cell.first : cell.first+1);
		int64_t start_y = (cell.second == MIN ? cell.second : cell.second-1);
		int64_t end_y = (cell.second == MAX-1 ? cell.second : cell.second+1);
		
		for (int64_t x = start_x; x <= end_x; x++){
			for (int64_t y = start_y; y <= end_y; y++) {
				if (x == cell.first && y == cell.second) {
					continue;
				}
				
				if (previousAliveCells_.find({x, y}) == previousAliveCells_.end()) {
					CheckDeadCellsNeighbors(x,y);
				} else {
					numNeighborsAlive++;
				}
			}
		}
		
		if (numNeighborsAlive < 2 || numNeighborsAlive > 3) {
			aliveCells_.erase(cell);
		}
	}
	
	if (aliveCells_.size() == 0) {
		std::cout << "Colony died :(" << std::endl;
		exit(0);
	}
}


void Board::PrintBoard() {
	
	for (int64_t y = 0; y < HEIGHT; y++) {
		for (int64_t x = 0; x < WIDTH; x++) {
			if (aliveCells_.find({x, y}) != aliveCells_.end()) {
				std::cout << "\u25A0";
			} else {
				std::cout << " ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << std::endl;
}


void Board::CellIsAlive(int64_t x, int64_t y) {
	
	aliveCells_.insert({x,y});
}


void Board::CheckDeadCellsNeighbors(int64_t deadCellX, int64_t deadCellY) {
	
	if (checkedDeadCells_.find({deadCellX, deadCellY}) != checkedDeadCells_.end()) {
		return;
	}
	
	uint8_t numNeighborsAlive = 0;
	
	int64_t start_x = (deadCellX == MIN ? deadCellX : deadCellX-1);
	int64_t end_x = (deadCellX == MAX ? deadCellX : deadCellX+1);
	int64_t start_y = (deadCellY == MIN ? deadCellY : deadCellY-1);
	int64_t end_y = (deadCellY == MAX-1 ? deadCellY : deadCellY+1);
	
	for (int64_t x = start_x; x <= end_x; x++){
		for (int64_t y = start_y; y <= end_y; y++) {
			if (x == deadCellX && y == deadCellY) {
				continue;
			}
			
			if (previousAliveCells_.find({x, y}) != previousAliveCells_.end()) {
				numNeighborsAlive++;
			}
		}
	}
	
	if (numNeighborsAlive == 3) {
		aliveCells_.insert({deadCellX, deadCellY});
	}
	checkedDeadCells_.insert({deadCellX, deadCellY});
}