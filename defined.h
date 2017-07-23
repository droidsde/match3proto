#pragma once

#define		Z_INDEX_CANDY		50
#define		Z_INDEX_BG			20

#define		RAND_MIN_RANGE			1
#define		RAND_MAX_RANGE			20

#define		BOARD_HEIGHT		5
#define		BOARD_WIDTH			7

#define		TYPE_ONE	1
#define		TYPE_TWO	2
#define		TYPE_THREE	3
#define		TYPE_FOUR	4
#define		TYPE_FIVE	5

#define		TOP_LEFT_X	100
#define		TOP_LEFT_Y	100

typedef struct Position
{
	int		m_row;
	int		m_col;

	Position(int row = 0, int col = 0)
	{
		m_row = row;
		m_col = col;
	}

	void operator=(const Position& p)
	{
		m_row = p.m_row;
		m_col = p.m_col;
	}

	bool operator==(const Position& p)
	{
		if ((m_row == p.m_row) && (m_col == p.m_col))
		{
			return true;
		}
		return false;
	}

	bool operator!=(const Position& p)
	{
		if ((m_row != p.m_row) || (m_col == p.m_col))
		{
			return true;
		}
		return false;
	}

}Position;
