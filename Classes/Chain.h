#pragma once

#include "defined.h"
#include "Candy.h"


class Chain {

public:
	Position		m_first;
	Vec2			m_firstPosition;
	Position		m_last;
	int				m_length;
	bool			m_isVertical;
	int				m_typeOfChain;
	Chain();
	/// mặc định là chain theo chiều dọc.
	Chain(Position first, Position last, int length, bool direction = true);
	~Chain();

	/// thêm 1 phần tử vào chuỗi nếu như cùng kiểu vs chuỗi.
	void		AddOneNodeToChain(Position pos);

	/// đảm bảo ptu đầu chain luôn có tọa độ nhỏ hơn pt cuối chain.
	void		FixChain();

	bool		CheckIfSameTypeChain(int  typeOfCandy);

	/// ktra nếu 1 1 tử có vị trí p thuộc chuỗi -> true, ngược lại -> false.
	bool		CheckIfInChain(Position p);

	void		PrintChain();

	void operator=(const Chain& c)
	{
		m_first = c.m_first;
		m_last = c.m_last;
		m_length = c.m_length;
		m_isVertical = c.m_isVertical;
	}
};