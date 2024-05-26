#include <iostream>
#include "../Header/add_puzzle_func.h"
#include "../Header/puzzle_data.h"
#include "../Header/puzzle.h"



PuzzleData::Movement getUserMovement()
{
	char input{};

	while (true)
	{
		std::cout << "\nEnter a command( w, a, s, d or q): ";
		std::cin >> input;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. try again.\n";
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		switch (input)
		{
		case 'w':
		case 'a':
		case 's':
		case 'd':
		case 'q':
			return static_cast<PuzzleData::Movement>(input);
		default:
			std::cout << "Invalid input. Try again\n";
			continue;
		}
	}
}





std::ostream& operator<<(std::ostream& out, PuzzleData::Movement movement)
{
	using enum PuzzleData::Movement;

	switch (movement)
	{
	case move_up:		
		out << "up";
		break;
	case move_left:		
		out << "left";
		break;
	case move_down:		
		out << "down";
		break;
	case move_right:
		out << "right";
		break;
	case move_max:		
		out << "Bye!";
		break;

	default: 
		out << "Invalid input";
		break;
	}

	return out;
}


bool startPuzzleGame()
{
	char input{};

	while (true)
	{
		std::cout << "Would you like to play a game of 15 Puzzle (y/n)? ";
		std::cin >> input;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. try again.\n";
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		switch (input)
		{
		case 'y':
		case 'Y':
			return true;
		case 'N':
		case 'n':
		case 'q':
		case 'Q':
			return false;
		default:
			continue;
		}

	}
}



void playPuzzle()
{
	while (startPuzzleGame())
	{
		Puzzle p{};

		std::cout << p << "\n";

		while (true)
		{
			PuzzleData::Movement input{ getUserMovement() };

			if (input == 'q')
			{
				std::cout << input << '\n';
				return;
			}

			p.movePuzzle(input);
			std::cout << p;

			if (p.isSovled())
			{
				std::cout << "Congratulations! You won!\n";
				break;
			}
		}

	}

}