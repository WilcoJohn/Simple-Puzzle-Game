#include "puzzle_data.h"

#ifndef ADD_PUZZLE_H
#define ADD_PUZZLE_H

PuzzleData::Movement getUserMovement();
std::ostream& operator<<(std::ostream& out,PuzzleData::Movement movement);

void playPuzzle();
bool startPuzzleGame();

#endif // PUZZLE_CLSS_H