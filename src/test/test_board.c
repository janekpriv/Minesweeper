#include "../include/board.h"
#include "test_framework.h"

void test_init_board()
{
	Board	board;

	board = init_board(1);
	ASSERT_EQ(9, board.rows);
	ASSERT_EQ(9, board.cols);
	ASSERT_EQ(10, board.num_mines);
}

void test_mine_board()
{
	Board	board;
	int		mine_count;

	board = init_board(1);
	mine_board(&board, 0, 0);
	mine_count = 0;
	for (int i = 0; i < board.rows; i++)
	{
		for (int j = 0; j < board.cols; j++)
		{
			if (board.minefield[i][j] == -1)
			{
				mine_count++;
			}
		}
	}
	ASSERT_EQ(board.num_mines, mine_count);
}

void test_place_flag()
{
	Board	board;
	int		status;

	board = init_board(1);
	status = place_flag(&board, 0, 0);
	ASSERT_EQ(STATUS_OK, status);
	ASSERT_EQ(2, board.player_view[0][0]);
	status = place_flag(&board, 0, 0);
	ASSERT_EQ(STATUS_OK, status);
	ASSERT_EQ(0, board.player_view[0][0]);
}

void test_reveal_field_safe()
{
	Board	board;
	int		status;

	board = init_board(1);
	mine_board(&board, 0, 0);
	status = reveal_field(&board, 1, 1);
	ASSERT_EQ(STATUS_OK, status);
	ASSERT_EQ(1, board.player_view[1][1]);
}

void test_reveal_field_mine()
{
	Board	board;
	int		status;

	board = init_board(1);
	mine_board(&board, 0, 0);
	for (int i = 0; i < board.rows; i++)
	{
		for (int j = 0; j < board.cols; j++)
		{
			if (board.minefield[i][j] == -1)
			{
				status = reveal_field(&board, i, j);
				ASSERT_EQ(STATUS_LOSS, status);
				return ;
			}
		}
	}
}

void test_calculate_points()
{
	Board board = init_board(1);
	board.player_view[0][0] = 1;
	board.player_view[0][1] = 1;

	int points = calculate_points(&board);
	ASSERT_EQ(2 * board.difficulty, points);
}

int main(){
	test_init_board();
	test_mine_board();
	test_place_flag();
	test_reveal_field_safe();
	test_reveal_field_mine();
	test_calculate_points();
	return 0;
}