#include <array>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>
#include "puzzle_data.h"

#ifndef PUZZLE_CLSS_H
#define PUZZLE_CLSS_H



class Puzzle
{
private:
	const std::size_t m_row{ PuzzleData::Row };
	const std::size_t m_col{ PuzzleData::Col };

	std::array<std::size_t, PuzzleData::Row> m_InvalidMoveUp{};	
	std::array<std::size_t, PuzzleData::Row> m_InvalidMoveDown{};	
	std::array<std::size_t, PuzzleData::Col> m_InvalidMoveLeft{};	
	std::array<std::size_t, PuzzleData::Col> m_InvalidMoveRight{};	


	std::array<int, PuzzleData::Row * PuzzleData::Col> m_puzzle{};


	std::size_t findZeroSpace() const;
public:
	// constructor
	Puzzle();

	/// <summary>
	/// Reset the state of the game.
	/// </summary>
	void reset();


	/// <summary>
	/// Return the value of an arrau member at a specific index
	/// 
	/// <param name="row">row index</param>
	/// <param name="col">column index</param>
	/// <returns>return int& for changing values and int for const non-chaning vals</returns>
	int& operator()(std::size_t row, std::size_t col);
	int& operator()(std::size_t idx);
	int operator()(std::size_t row, std::size_t col) const;
	int operator()(std::size_t idx) const;


	/// <summary>
	/// Check if current state of puzzle is ordered
	/// from 0 to row * col - 1
	/// return true if is ordered
	/// return false otherwise
	/// </summary>
	/// <returns>bool</returns>
	bool isSovled() const;

	void movePuzzle(PuzzleData::Movement movement);

	friend std::ostream& operator<<(std::ostream& out, const Puzzle& puzzle);
	~Puzzle() = default;	// use default destructor
};



#endif // PUZZLE_CLSS_H

