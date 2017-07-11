#pragma once

/// type of candy
enum TypeOfCandy
{
		TYPE_UNKNOW_CANDY = 0,
		TYPE_BEAN_BLUE	=	1,
		TYPE_BEAN_GREEN,
		TYPE_BEAN_ORANGE,
		TYPE_BEAN_PINK,
		TYPE_BEAN_PURPLE,
		TYPE_BEAN_RED,
		TYPE_BEAN_WHITE,
		TYPE_BEAN_YELLOW,

		TYPE_CANE_CANE,
		TYPE_CANE_CORN,
		TYPE_CANE_HUMBUG,
};


// score: 
#define  SCORE_BEAN_BLUE			11
#define  SCORE_BEAN_GREEN			12
#define  SCORE_BEAN_ORANGE		13
#define  SCORE_BEAN_PINK			14
#define  SCORE_BEAN_PURPLE		15
#define  SCORE_BEAN_RED			16
#define  SCORE_BEAN_WHITE			17
#define  SCORE_BEAN_YELLOW		18

// CANDY = 2
#define  SCORE_CANDY_CANE				21
#define  SCORE_CANDY_CORN				22
#define  SCORE_CANDY_HUMBUG			23

#define  Z_INDEX_BG				20
#define  Z_INDEX_CANDY			50

// the chance for random to blue, green, orange
#define  CHANCE_BEAN_BLUE		0.8
#define  CHANCE_BEAN_GREEN		CHANCE_BEAN_BLUE
#define  CHANCE_BEAN_ORANGE		CHANCE_BEAN_BLUE

#define	 BOARD_HEIGHT		5
#define	 BOARD_WIDTH		8

#define	 RAND_MIN_RANGE			1
#define  RAND_MAX_RANGE			39

#define	 EXIST_MATCH_3			1

#define	 DEBUG_MODE			0

typedef struct Point2D
{
	int		m_x;
	int		m_y;

	Point2D(int x = 0, int y = 0)
	{
		m_x = x;
		m_y = y;
	}

	void operator=(const Point2D& p)
	{
		m_x = p.m_x;
		m_y = p.m_y;
	}
}Point2D;

