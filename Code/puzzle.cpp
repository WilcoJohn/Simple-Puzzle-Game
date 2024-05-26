#include <iostream>
#include <algorithm>    // for shuffle
#include <iterator>     // for int types
#include <random>
#include <array>
#include <cassert>

#include "../Header/puzzle.h"
#include "../Header/puzzle_data.h"


// Constructor
Puzzle::Puzzle()
{

	constexpr std::size_t data_points{ PuzzleData::Row * PuzzleData::Col };

	for (std::size_t idx{ 0 }; idx < data_points; ++idx)
		m_puzzle[idx] = static_cast<int>(idx);													// set up array with 0 ... (m_row * m_col) - 1

	std::shuffle(m_puzzle.begin(), m_puzzle.end(), std::mt19937(std::random_device{}()));		// shuffle random array

	//update storage values for invalid move lists
	for (std::size_t idx{ 0 }; idx < m_col; ++idx) m_InvalidMoveDown[idx] = idx;
	for (std::size_t idx{ 0 }; idx < m_col; ++idx) m_InvalidMoveUp[idx] = idx + m_row * (m_col - 1);
	
	for (std::size_t idx{ 0 }; idx < m_row; ++idx) m_InvalidMoveRight[idx] = 0 + idx*m_col;	// linear interpolation
	for (std::size_t idx{ 0 }; idx < m_row; ++idx) m_InvalidMoveLeft[idx] = (m_col-1) + idx*m_row;

	
}





std::size_t Puzzle::findZeroSpace() const
{

	auto zeroSpace{ std::find(m_puzzle.begin(), m_puzzle.end(), 0) };							// get value pointer for 0
	return static_cast<std::size_t>(zeroSpace - m_puzzle.begin());						// convert zero value to index
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	SET UP ARRAY ACCESSING USING PARENTHESIS OPERATOTR '(uint, uint)' or '(uint)'
*/


int& Puzzle::operator()(std::size_t row, std::size_t col)							
{
	assert(row <= m_row && "Array row index is out of range");
	assert(col <= m_col && "Array col index is out of range");

	return m_puzzle[row * m_col + col];
}


int Puzzle::operator()(std::size_t row, std::size_t col) const
{
	assert(row <= m_row && "Array row index is out of range");
	assert(col <= m_col && "Array col index is out of range");

	return m_puzzle[row * m_col + col];
}



int& Puzzle::operator()(std::size_t idx)
{
	assert(idx < (m_row*m_col) && "Array index is out of range");

	return m_puzzle[idx];
}


int Puzzle::operator()(std::size_t idx) const
{
	assert(idx < (m_row * m_col) && "Array index is out of range");

	return m_puzzle[idx];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



// Add how the output works when using std::cout for puzzle
std::ostream& operator<<(std::ostream& out, const Puzzle& puzzle)
{
	int idxCorrect{ 0 };
	for (int i{ 0 }; i < PuzzleData::lineRefresh; ++i) std::cout << '\n';	// refresh board
	for (std::size_t id_row{ 0 }; id_row < puzzle.m_row; ++id_row)
	{
		for (std::size_t id_col{ 0 }; id_col < puzzle.m_col; ++id_col)
		{	
			if (puzzle(id_row, id_col))
				if (puzzle(id_row, id_col) == idxCorrect++)
				{
					out << "\033[32m" << puzzle(id_row, id_col) << "\033[0m\t";
					//out << puzzle(id_row, id_col) << "\t";
				}
				else
					out << puzzle(id_row, id_col) << "\t";
			else
			{
				out << " \t";
				++idxCorrect;
			}
		}
		out << '\n';
	}
	return out;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void Puzzle::reset()
{
	std::shuffle(m_puzzle.begin(), m_puzzle.end(), std::mt19937(std::random_device{}()));
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





bool Puzzle::isSovled() const
{
	for (std::size_t idx{ 0 }; idx < m_puzzle.size(); ++idx)
		if (m_puzzle[idx] != static_cast<int>(idx)) return false;
	
	return true;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Puzzle::movePuzzle(PuzzleData::Movement movement)
{
	using enum PuzzleData::Movement;

	bool invalidMove{ false };
	int colModifier{ 0 };
	int rowModifier{ 0 };

	switch (movement)
	{
	case move_up:		
		
		invalidMove = std::binary_search(m_InvalidMoveUp.begin(), m_InvalidMoveUp.end(), findZeroSpace());
		rowModifier = (invalidMove) ? 0 : 1;
		break;

	case move_left:		
		invalidMove = std::binary_search(m_InvalidMoveLeft.begin(), m_InvalidMoveLeft.end(), findZeroSpace());
		colModifier = (invalidMove) ? 0 : 1;
		break;
	case move_down:		
		invalidMove = std::binary_search(m_InvalidMoveDown.begin(), m_InvalidMoveDown.end(), findZeroSpace());
		rowModifier = (invalidMove) ? 0 : -1;
		break;
	case move_right:
		invalidMove = std::binary_search(m_InvalidMoveRight.begin(), m_InvalidMoveRight.end(), findZeroSpace());
		colModifier = (invalidMove) ? 0 : -1;
		break;

	case move_max:
		std::cout << "Bye bye!\n";
		return;

	default:
		std::cerr << "Invalid movement input!\n";
		return;
	}

	auto zeroSpace{ findZeroSpace() }; // acoid singleton usage

	int zeroRow{ static_cast<int>(zeroSpace) / static_cast<int>(m_col) + rowModifier };
	int zeroCol{ static_cast<int>(zeroSpace) % static_cast<int>(m_col) + colModifier };


	std::swap(m_puzzle[zeroSpace], this->operator()(static_cast<std::size_t>(zeroRow), static_cast<std::size_t>(zeroCol)));
}