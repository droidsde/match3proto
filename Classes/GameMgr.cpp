#include "GameMgr.h"

#include "GameMgr.h"
#include <ctime>
#include <chrono>
#include "defined.h"
#include "Chain.h"
#include <iostream>
#include <fstream>


GameMgr* GameMgr::m_pInstance = nullptr;

GameMgr * GameMgr::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new GameMgr();
	}
	return m_pInstance;
}

void GameMgr::InitBoard(cocos2d::Layer *layer)
{
	int i = 0, j = 0;
	m_board = new Candy**[BOARD_HEIGHT];
	for (i = 0; i < BOARD_HEIGHT; i++)
	{
		m_board[i] = new Candy*[BOARD_WIDTH];
	}

	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::srand(seed);
	int random = 0;

	for (i = 0; i < BOARD_HEIGHT; i++)
	{
		for (j = 0; j < BOARD_WIDTH; j++)
		{
			random = RAND_MIN_RANGE + std::rand() % (RAND_MAX_RANGE - RAND_MIN_RANGE + 1);
			if (random <= 6) // 1 - 6
			{
				m_board[i][j] = Candy::createCandyWithFileName("candy/bean_green.png");
				m_board[i][j]->m_value = TYPE_ONE;
			}
			else if (random <= 10) // 7 - 10
			{
				m_board[i][j] = Candy::createCandyWithFileName("candy/jelly_pink.png");
				m_board[i][j]->m_value = TYPE_TWO;
			}
			else if (random <= 13) // 11 - 13
			{
				m_board[i][j] = Candy::createCandyWithFileName("candy/lollipop_blue.png");
				m_board[i][j]->m_value = TYPE_THREE;
			}
			else if (random <= 15) // 14 - 15
			{
				m_board[i][j] = Candy::createCandyWithFileName("candy/mmstroke_brown.png");
				m_board[i][j]->m_value = TYPE_FOUR;
			}
			else // 17 - Max_range
			{
				m_board[i][j] = Candy::createCandyWithFileName("candy/swirl_pink.png");
				m_board[i][j]->m_value = TYPE_FIVE;
			}
			m_board[i][j]->m_pos = Position(i, j);
			m_board[i][j]->setPosition(Point(TOP_LEFT_X + j*m_offsetX, TOP_LEFT_Y + i*m_offsetY));
			layer->addChild(m_board[i][j], Z_INDEX_CANDY);
		}
	}

}

void GameMgr::InitBoardManual(const char * fileName)
{
	int i = 0, j = 0;

	std::ifstream in;
	in.open(fileName);
	int HEIGHT = 0, WIDTH = 0, countW = 0, countH = 0;
	j = 0;

	/// find out WIDTH & HEIGHT
	char next;
	while (!in.eof())
	{
		next = in.get();
		switch (next)
		{
		case '\n':
		{
			HEIGHT += 1;
			countW = 0;
		}
		break;
		case (char)32:
		{
		}
		break;
		default:
		{
			countW += 1;
			if (countW > WIDTH)
			{
				WIDTH = countW;
			}
		}
		break;
		}
	}

	m_height = HEIGHT;
	m_width = WIDTH;

	m_board = new Candy**[HEIGHT];
	for (i = 0; i < HEIGHT; i++)
	{
		m_board[i] = new Candy*[WIDTH];
	}

	/// return to beginning of file.
	in.clear();
	in.seekg(0, in.beg);
	for (i = 0; i < HEIGHT; i++)
	{
		j = 0;
		do
		{
			next = in.get();
			//printf("  %c  ", next);
			if (next != (char)32 && next != '\n')	/// ki tu space && '\n'
			{
				int value = -1;
				switch (next)
				{
				case '1':
					value = 1;
					break;
				case '2':
					value = 2;
					break;
				case '3':
					value = 3;
					break;
				case '4':
					value = 4;
					break;
				case '5':
					value = 5;
					break;
				default:
					break;
				}
				m_board[i][j]->m_value = value;
				m_board[i][j]->m_pos = Position(i, j);
				j += 1;
			}
		} while (next != '\n');

	}

	in.close();






}

void GameMgr::PrintBoard()
{
	printf("-----------------\n");
	printf("W = %d, H = %d\n", BOARD_WIDTH, BOARD_HEIGHT);
	int i = 0, j = 0;
	for (i = 0; i < BOARD_HEIGHT; i++)
	{
		for (j = 0; j < BOARD_WIDTH; j++)
		{
			printf(" %2d ", m_board[i][j]->m_value);
		}
		printf("\n");
	}
}

void GameMgr::PrintBoard(int width, int height)
{
	printf("-----------------\n");
	printf("W = %d, H = %d\n", width, height);
	int i = 0, j = 0;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			printf(" %2d ", m_board[i][j]->m_value);
		}
		printf("\n");
	}
}

void GameMgr::CheckMatchVertical(Candy* currCandy, int width, int height)
{
	/// ktra nếu ptu đang xét đã thuộc 1 chain vertical nào đó rồi thì bỏ qua.
	Position		posOfCandy = currCandy->m_pos;
	for (auto it = m_allChains.begin(); it != m_allChains.end(); it++)
	{
		auto chain = (*it);
		if (chain->m_isVertical && chain->CheckIfInChain(posOfCandy))
		{
			return;
		}
	}

	int		typeOfCandy;
	Chain*	chain = new Chain;
	/// khởi tạo chuỗi ban đầu bằng ptu đang xét.
	chain->m_first = posOfCandy;
	chain->m_last = posOfCandy;
	chain->m_isVertical = true;
	chain->m_length = 1;
	chain->m_typeOfChain = currCandy->m_value;

	const int row = posOfCandy.m_row;
	const int column = posOfCandy.m_col;

	int i = 0;
	/// duyệt từ ptu == candy lên phía trên.
	for (i = row + 1; i < height; i++)
	{
		typeOfCandy = m_board[i][column]->m_value;
		if (chain->CheckIfSameTypeChain(typeOfCandy))
		{
			chain->AddOneNodeToChain(Position(i, column));
		}
		else
		{
			break;
		}
	}

	/// duyệt từ ptu == candy xuống phía dưới.
	for (i = row - 1; i >= 0; i--)
	{
		typeOfCandy = m_board[i][column]->m_value;
		if (chain->CheckIfSameTypeChain(typeOfCandy))
		{
			chain->AddOneNodeToChain(Position(i, column));
		}
		else
		{
			break;
		}
	}

	/// ktra nếu length của chain >=3 thì add vào m_allChains.
	if (chain->m_length >= 3)
	{
		chain->FixChain();
		m_allChains.push_back(chain);
	}
}

void GameMgr::CheckMatchHorizontal(Candy* currCandy, int width, int height)
{
	/// ktra nếu ptu đang xét đã thuộc 1 chain horizontal nào đó rồi thì bỏ qua.
	Position		posOfCandy = currCandy->m_pos;
	for (auto it = m_allChains.begin(); it != m_allChains.end(); it++)
	{
		auto chain = (*it);
		if ((chain->m_isVertical == false) && chain->CheckIfInChain(posOfCandy) == true)
		{
			return;
		}
	}
	int  typeOfCandy;
	Chain*	chain = new Chain;
	/// khởi tạo chuỗi ban đầu bằng ptu đang xét.
	chain->m_first = posOfCandy;
	chain->m_last = posOfCandy;
	chain->m_isVertical = false;
	chain->m_length = 1;
	chain->m_typeOfChain = currCandy->m_value;

	const int row = posOfCandy.m_row;
	const int column = posOfCandy.m_col;

	int i = 0;
	/// duyệt từ ptu == candy sang bên phải
	for (i = column + 1; i < width; i++)
	{
		typeOfCandy = m_board[row][i]->m_value;
		if (chain->CheckIfSameTypeChain(typeOfCandy))
		{
			chain->AddOneNodeToChain(Position(row, i));
		}
		else
		{
			break;
		}
	}

	/// duyệt từ ptu == candy sang bên trái
	for (i = column - 1; i >= 0; i--)
	{
		typeOfCandy = m_board[row][i]->m_value;
		if (chain->CheckIfSameTypeChain(typeOfCandy))
		{
			chain->AddOneNodeToChain(Position(row, i));
		}
		else
		{
			break;
		}
	}

	/// ktra nếu length của chain >=3 thì add vào m_allChains.
	if (chain->m_length >= 3)
	{
		chain->FixChain();
		m_allChains.push_back(chain);
	}
}

void GameMgr::CheckAllMatch3(int width, int height)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			CheckMatchHorizontal(m_board[i][j], width, height);
			CheckMatchVertical(m_board[i][j], width, height);
		}
	}
}

void GameMgr::CheckMatchVertical(Candy* currCandy, bool isAfterSwap /* false*/)
{
	if (currCandy == nullptr)
	{
		return;
	}
	/// ktra nếu ptu đang xét đã thuộc 1 chain nào đó rồi thì bỏ qua.
	Position		posOfCandy = currCandy->m_pos;
	for (auto it = m_allChains.begin(); it != m_allChains.end(); it++)
	{
		auto chain = (*it);
		if (chain->m_isVertical && chain->CheckIfInChain(posOfCandy))
		{
			return;
		}
	}

	int		typeOfCandy;
	Chain*	chain = new Chain;
	/// khởi tạo chuỗi ban đầu bằng ptu đang xét.
	chain->m_first = posOfCandy;
	chain->m_last = posOfCandy;
	chain->m_isVertical = true;
	chain->m_length = 1;
	chain->m_typeOfChain = currCandy->m_value;
	chain->m_firstPosition = currCandy->getPosition();

	const int row = posOfCandy.m_row;
	const int column = posOfCandy.m_col;

	int i = 0;
	/// duyệt từ ptu == candy lên phía trên.
	for (i = row + 1; i < BOARD_HEIGHT; i++)
	{
		if (m_board[i][column] != nullptr)
		{
			typeOfCandy = m_board[i][column]->m_value;
			if (chain->CheckIfSameTypeChain(typeOfCandy))
			{
				chain->AddOneNodeToChain(Position(i, column));
			}
			else
			{
				break;
			}
		}
	}

	/// duyệt từ ptu == candy xuống phía dưới.
	for (i = row - 1; i >= 0; i--)
	{
		if (m_board[i][column] != nullptr)
		{
			typeOfCandy = m_board[i][column]->m_value;
			if (chain->CheckIfSameTypeChain(typeOfCandy))
			{
				chain->AddOneNodeToChain(Position(i, column));
			}
			else
			{
				break;
			}
		}
	}

	/// ktra nếu length của chain >=3 thì add vào m_allChains.
	if (chain->m_length >= 3)
	{
		chain->FixChain();
		m_allChains.push_back(chain);
		if (isAfterSwap)
		{
			m_chainAfterSwap.push_back(chain);
		}
	}
	else
	{
		delete chain;
	}
}

void GameMgr::CheckMatchHorizontal(Candy* currCandy, bool isAfterSwap /* false */)
{
	if (currCandy == nullptr)
	{
		return;
	}
	/// ktra nếu ptu đang xét đã thuộc 1 chain nào đó rồi thì bỏ qua.
	Position		posOfCandy = currCandy->m_pos;
	for (auto it = m_allChains.begin(); it != m_allChains.end(); it++)
	{
		auto chain = (*it);
		if ((chain->m_isVertical == false) && chain->CheckIfInChain(posOfCandy) == true)
		{
			return;
		}
	}
	int  typeOfCandy;
	Chain*	chain = new Chain;
	/// khởi tạo chuỗi ban đầu bằng ptu đang xét.
	chain->m_first = posOfCandy;
	chain->m_last = posOfCandy;
	chain->m_isVertical = false;
	chain->m_length = 1;
	chain->m_typeOfChain = currCandy->m_value;
	chain->m_firstPosition = currCandy->getPosition();

	const int row = posOfCandy.m_row;
	const int column = posOfCandy.m_col;

	int i = 0;
	/// duyệt từ ptu == candy sang bên phải
	for (i = column + 1; i < BOARD_WIDTH; i++)
	{
		if (m_board[row][i] != nullptr)
		{
			typeOfCandy = m_board[row][i]->m_value;
			if (chain->CheckIfSameTypeChain(typeOfCandy))
			{
				chain->AddOneNodeToChain(Position(row, i));
			}
			else
			{
				break;
			}
		}
	}

	/// duyệt từ ptu == candy sang bên trái
	for (i = column - 1; i >= 0; i--)
	{
		if (m_board[row][i] != nullptr)
		{
			typeOfCandy = m_board[row][i]->m_value;
			if (chain->CheckIfSameTypeChain(typeOfCandy))
			{
				chain->AddOneNodeToChain(Position(row, i));
			}
			else
			{
				break;
			}
		}
	}

	/// ktra nếu length của chain >=3 thì add vào m_allChains.
	if (chain->m_length >= 3)
	{
		chain->FixChain();
		m_allChains.push_back(chain);
		if (isAfterSwap)
		{
			m_chainAfterSwap.push_back(chain);
		}
	}
	else
	{
		delete chain;
	}
}

void GameMgr::CheckAllMatch3()
{
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			CheckMatchHorizontal(m_board[i][j]);
			CheckMatchVertical(m_board[i][j]);
		}
	}
}

void	GameMgr::CheckMatch3AfterSwap()
{
	CheckMatchHorizontal(m_firstObj, true);
	CheckMatchVertical(m_firstObj, true);

	CheckMatchHorizontal(m_secondObj, true);
	CheckMatchVertical(m_secondObj, true);
}

void GameMgr::PrintAllMatch3()
{
	if (m_allChains.size() > 0)
	{
		auto it = m_allChains.begin();
		for (; it != m_allChains.end(); it++)
		{
			(*it)->PrintChain();
		}
	}
	else
	{
		printf("The board have no match-3 !\n");
	}
}

void GameMgr::RemoveAllMatch3(cocos2d::Layer *layer)
{
	if (m_allChains.size() > 0)
	{
		auto it = m_allChains.begin();
		for (; it != m_allChains.end(); it++)
		{
			auto chain = (*it);

			if (chain->m_isVertical)
			{
				const int col = chain->m_first.m_col;
				for (int row = chain->m_first.m_row; row <= chain->m_last.m_row; row++)
				{
					m_board[row][col]->DisAppear();
					layer->removeChild(m_board[row][col]);
					m_board[row][col] = nullptr;
				}
			}
			else
			{
				const int row = chain->m_first.m_row;
				for (int col = chain->m_first.m_col; col <= chain->m_last.m_col; col++)
				{
					m_board[row][col]->DisAppear();
					layer->removeChild(m_board[row][col]);
					m_board[row][col] = nullptr;
				}
			}
			chain = nullptr;
		}
		m_allChains.clear();
	}
}

void	GameMgr::ReFillBoard(cocos2d::Layer *layer)
{
	if (m_allChains.size() > 0)
	{
		CCLOG("Re fill board !");
		auto seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::srand(seed);
		int random = 0;
		auto it = m_allChains.begin();
		for (; it != m_allChains.end(); it++)
		{
			auto chain = (*it);
			const int posX = chain->m_firstPosition.x;
			const int posY = chain->m_firstPosition.y;
			if (chain->m_isVertical)
			{
				const int col = chain->m_first.m_col;
				int i = 1;
				for (int row = chain->m_first.m_row; row <= chain->m_last.m_row; row++)
				{
					random = RAND_MIN_RANGE + std::rand() % (RAND_MAX_RANGE - RAND_MIN_RANGE + 1);
					if (random <= 6) // 1 - 6
					{
						m_board[row][col] = Candy::createCandyWithFileName("candy/bean_blue.png");
						m_board[row][col]->m_value = TYPE_ONE;
					}
					else if (random <= 10) // 7 - 10
					{
						m_board[row][col] = Candy::createCandyWithFileName("candy/bean_green.png");
						m_board[row][col]->m_value = TYPE_TWO;
					}
					else if (random <= 13) // 11 - 13
					{
						m_board[row][col] = Candy::createCandyWithFileName("candy/bean_orange.png");
						m_board[row][col]->m_value = TYPE_THREE;
					}
					else if (random <= 15) // 14 - 15
					{
						m_board[row][col] = Candy::createCandyWithFileName("candy/bean_pink.png");
						m_board[row][col]->m_value = TYPE_FOUR;
					}
					else // 17 - Max_range
					{
						m_board[row][col] = Candy::createCandyWithFileName("candy/bean_yellow.png");
						m_board[row][col]->m_value = TYPE_FIVE;
					}
					layer->addChild(m_board[row][col], Z_INDEX_CANDY);
					m_board[row][col]->setPosition(Vec2(posX, posY + i*m_offsetY));
					i += 1;
					m_board[row][col]->m_pos = Position(row, col);
				}
			}
			else
			{
				const int row = chain->m_first.m_row;
				int j = 1;
				for (int col = chain->m_first.m_col; col <= chain->m_last.m_col; col++)
				{
					random = RAND_MIN_RANGE + std::rand() % (RAND_MAX_RANGE - RAND_MIN_RANGE + 1);
					if (random <= 6) // 1 - 6
					{
						m_board[row][col] = Candy::createCandyWithFileName("candy/bean_blue.png");
						m_board[row][col]->m_value = TYPE_ONE;
					}
					else if (random <= 10) // 7 - 10
					{
						m_board[row][col] = Candy::createCandyWithFileName("candy/bean_green.png");
						m_board[row][col]->m_value = TYPE_TWO;
					}
					else if (random <= 13) // 11 - 13
					{
						m_board[row][col] = Candy::createCandyWithFileName("candy/bean_orange.png");
						m_board[row][col]->m_value = TYPE_THREE;
					}
					else if (random <= 15) // 14 - 15
					{
						m_board[row][col] = Candy::createCandyWithFileName("candy/bean_pink.png");
						m_board[row][col]->m_value = TYPE_FOUR;
					}
					else // 17 - Max_range
					{
						m_board[row][col] = Candy::createCandyWithFileName("candy/bean_yellow.png");
						m_board[row][col]->m_value = TYPE_FIVE;
					}
					layer->addChild(m_board[row][col], Z_INDEX_CANDY);
					m_board[row][col]->setPosition(Vec2(posX + j*m_offsetX, posY));
					j += 1;
					m_board[row][col]->m_pos = Position(row, col);
				}
			}
		}
	}

}

void	GameMgr::TestReFillBoard(cocos2d::Layer *layer)
{
	int i = 0, j = 0;
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::srand(seed);
	int random = 0;

	for (i = 0; i < BOARD_HEIGHT; i++)
	{
		for (j = 0; j < BOARD_WIDTH; j++)
		{
			if (m_board[i][j] == nullptr)
			{
				random = RAND_MIN_RANGE + std::rand() % (RAND_MAX_RANGE - RAND_MIN_RANGE + 1);
				if (random <= 6) // 1 - 6
				{
					m_board[i][j] = Candy::createCandyWithFileName("candy/bean_blue.png");
					m_board[i][j]->m_value = TYPE_ONE;
				}
				else if (random <= 10) // 7 - 10
				{
					m_board[i][j] = Candy::createCandyWithFileName("candy/bean_green.png");
					m_board[i][j]->m_value = TYPE_TWO;
				}
				else if (random <= 13) // 11 - 13
				{
					m_board[i][j] = Candy::createCandyWithFileName("candy/bean_orange.png");
					m_board[i][j]->m_value = TYPE_THREE;
				}
				else if (random <= 15) // 14 - 15
				{
					m_board[i][j] = Candy::createCandyWithFileName("candy/bean_pink.png");
					m_board[i][j]->m_value = TYPE_FOUR;
				}
				else // 17 - Max_range
				{
					m_board[i][j] = Candy::createCandyWithFileName("candy/bean_yellow.png");
					m_board[i][j]->m_value = TYPE_FIVE;
				}
				m_board[i][j]->m_pos = Position(i, j);
				m_board[i][j]->setPosition(Point(TOP_LEFT_X + j*m_offsetX, TOP_LEFT_Y + i*m_offsetY));
				m_board[i][j]->Appear();
				layer->addChild(m_board[i][j], Z_INDEX_CANDY);
			}
		}
	}
}

void	GameMgr::RemoveAllChain()
{
	m_allChains.clear();
}

void	GameMgr::CheckAllSprite(Vec2 &p)
{
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			if (m_board[i][j] && m_board[i][j]->IsSelected(p))
			{
				if (m_firstObj == nullptr)
				{
					m_firstObj = m_board[i][j];
					CCLOG("m_first dc chon !, pos: %f, %f", m_firstObj->getPositionX(), m_firstObj->getPositionY());
				}
				else
				{
					if (m_firstObj != m_board[i][j])
					{
						m_secondObj = m_board[i][j];
						CCLOG("m_second dc chon !, pos: %f, %f", m_secondObj->getPositionX(), m_secondObj->getPositionY());
					}
				}
				return;
			}
		}
	}
}

bool		GameMgr::IsSwappable()
{
	auto m_index1st = m_firstObj->m_pos;
	auto m_index2nd = m_secondObj->m_pos;
	/// same row
	if (m_index1st.m_row == m_index2nd.m_row)
	{
		if (m_index1st.m_col == (m_index2nd.m_col + 1) || (m_index1st.m_col + 1) == m_index2nd.m_col)
		{
			return true;
		}
	}
	///same column
	else if (m_index1st.m_col == m_index2nd.m_col)
	{
		if (m_index1st.m_row == (m_index2nd.m_row + 1) || (m_index1st.m_row + 1) == m_index2nd.m_row)
		{
			return true;
		}
	}
	return false;

}

bool	GameMgr::IsPossibleSwap()
{
	if (m_firstObj && m_secondObj)
	{
		return true;
	}
	return false;
}

void		GameMgr::Swap()
{
	/// swap position
	auto pos1st = m_firstObj->getPosition();
	auto pos2nd = m_secondObj->getPosition();
	m_oldPos1 = pos1st;
	m_oldPos2 = pos2nd;
	CCLOG("-----------Swap----------");
	CCLOG("before 1st position: %f, %f", pos1st.x, pos1st.y);
	CCLOG("before 2nd position: %f, %f", pos2nd.x, pos2nd.y);


	auto actionMove1st = MoveTo::create(0.4f, pos2nd);
	auto seq1st = Sequence::create(actionMove1st, nullptr);
	m_firstObj->runAction(seq1st);
	pos1st = m_firstObj->getPosition();

	auto actionMove2nd = MoveTo::create(0.4f, pos1st);
	auto seq2nd = Sequence::create(actionMove2nd, nullptr);
	m_secondObj->runAction(seq2nd);
	pos2nd = m_secondObj->getPosition();

	/// store (row, col) of two obj have changed.
	m_index1stOld = m_firstObj->m_pos;
	m_index2ndOld = m_secondObj->m_pos;

	/// swap value of candy.
	int		tempValue = m_firstObj->m_value;
	m_firstObj->m_value = m_secondObj->m_value;
	m_secondObj->m_value = tempValue;

	pos1st = m_firstObj->getPosition();
	pos2nd = m_secondObj->getPosition();
	CCLOG("after 1st position: %f, %f", m_firstObj->getPosition().x, m_firstObj->getPosition().y);
	CCLOG("after 2nd position: %f, %f", m_secondObj->getPosition().x, m_secondObj->getPosition().y);

	CCLOG("-----------End Swap----------");
}

void	GameMgr::UndoSwap()
{
	CCLOG("-----------Undo Swap----------");

	/// dua vao 2 vi tri vua thay doi (row, col)
	/// tim ra 2 con tro, swap lai vi tri + value.
	/// swap position
	m_firstObj = m_board[m_index1stOld.m_row][m_index1stOld.m_col];
	m_secondObj = m_board[m_index2ndOld.m_row][m_index2ndOld.m_col];

	CCLOG("old 1st position: %f, %f", m_oldPos1.x, m_oldPos1.y);
	CCLOG("old 2nd position: %f, %f", m_oldPos2.x, m_oldPos2.y);

	CCLOG("----old 1st position: %f, %f", m_firstObj->getPositionX(), m_firstObj->getPositionY());
	CCLOG("----old 2nd position: %f, %f", m_secondObj->getPositionX(), m_secondObj->getPositionY());

	auto pos1st = m_firstObj->getPosition();
	auto pos2nd = m_secondObj->getPosition();

	auto actionMove1st = MoveTo::create(0.4f, pos1st);
	auto seq1st = Sequence::create(actionMove1st, nullptr);
	m_firstObj->runAction(seq1st);

	auto actionMove2nd = MoveTo::create(0.4f, pos2nd);
	auto seq2nd = Sequence::create(actionMove2nd, nullptr);
	m_secondObj->runAction(seq2nd);

	///// swap value of candy.
	int		tempValue = m_firstObj->m_value;
	m_firstObj->m_value = m_secondObj->m_value;
	m_secondObj->m_value = tempValue;

	CCLOG("after 1st position: %f, %f", m_firstObj->getPositionX(), m_firstObj->getPositionY());
	CCLOG("after 2nd position: %f, %f", m_secondObj->getPositionX(), m_secondObj->getPositionY());

	CCLOG("-----------End Undo Swap----------");
}

void	GameMgr::ResetAfterSwap()
{
	m_firstObj = nullptr;
	m_secondObj = nullptr;
	CCLOG("m_firstObj ------>>> NULL");
	CCLOG("m_secondObj ------>>> NULL");
}

void	GameMgr::ClearChainAfterSwap()
{
	m_chainAfterSwap.clear();
}

void	GameMgr::UpScore()
{
	//CCLOG("Score up !");
}

int GameMgr::GetWidth()
{
	return m_width;
}

int GameMgr::GetHeight()
{
	return m_height;
}

int		GameMgr::GetOffsetX()
{
	return m_offsetX;
}

int		GameMgr::GetOffsetY()
{
	return m_offsetY;
}

void	GameMgr::SetOffsetX(int offset)
{
	m_offsetX = offset;
}

void	GameMgr::SetOffsetY(int offset)
{
	m_offsetY = offset;
}

int		GameMgr::GetNumOfAllChains()
{
	return m_allChains.size();
}

int		GameMgr::GetNumOfChainAfterSwap()
{
	return m_chainAfterSwap.size();
}