//
//  Board.cpp
//  GameOfLife
//
//  Created by Marianna Neubauer on 10/4/15.
//  Copyright (c) 2015 Marianna Neubauer. All rights reserved.
//

#include "Board.h"



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
				//numNeighborsAlive += (previousAliveCells_.find({x, y}) == previousAliveCells_.end()) ? 0 : 1;
			}
		}
		
		if (numNeighborsAlive < 2 || numNeighborsAlive > 3) {
			aliveCells_.erase(cell);
		}
	}
	
	if( aliveCells_.size() == 0){
		PrintBoard();
		std::cout << "Colony died :(" << std::endl;
		exit(0);
	}
	
	/*previousCells_ = cells_;
	for (int64_t y = 0; y < HEIGHT; y++) {
		for (int64_t x = 0; x < WIDTH; x++) {
			uint8_t numNeighborsAlive = 0;
			
			int64_t start_x = (x == 0 ? x : x-1);
			int64_t end_x = (x == WIDTH-1 ? x : x+1);
			int64_t start_y = (y == 0 ? y : y-1);
			int64_t end_y = (y == HEIGHT-1 ? y : y+1);
			
			for (int64_t i = start_y; i <= end_y; i++){
				for (int64_t j = start_x; j <= end_x; j++) {
					if (i == y && j == x) {
						continue;
					}
					numNeighborsAlive += previousCells_[i][j].status();
				}
			}
			
			if (previousCells_[y][x].status() && (numNeighborsAlive < 2 || numNeighborsAlive > 3) ) {
				cells_[y][x].statusIs("dead");
				totalAlive_--;
			} else if (!previousCells_[y][x].status() && numNeighborsAlive == 3) {
				cells_[y][x].statusIs("alive");
				totalAlive_++;
			}
		}
	}
	
	if (totalAlive_ == 0) {
		PrintBoard();
		std::cout << "Colony died :(" << std::endl;
		exit(0);
	}*/
}

void Board::PrintBoard() {
	for (int64_t y = MIN; y < MAX; y++) {
		for (int64_t x = MIN; x < MAX; x++) {
			if (aliveCells_.find({x, y}) != aliveCells_.end()) {
				std::cout << "•";
				//std::wcout << L"■";
			} else {
				std::cout << "-";
				//std::wcout << L"□";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << std::endl << std::endl;
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
