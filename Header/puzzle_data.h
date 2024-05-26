#ifndef PUZZLE_DATA_H
#define PUZZLE_DATA_H


namespace PuzzleData
{
	inline constexpr std::size_t Row{ 5 };
	inline constexpr std::size_t Col{ 5 };
	inline constexpr std::size_t RepeatEdgeCase{ 4 };

	inline constexpr int lineRefresh{ 25 };

	enum Movement : char
	{
		move_up = 'w',
		move_down = 's',
		move_right = 'd',
		move_left = 'a',
		move_max = 'q',			// move_max = q = quit
	};

}


#endif