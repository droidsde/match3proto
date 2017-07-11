#pragma once

#include "cocos2d.h"
#include "defined.h"

class Chain {

public:
	Point2D		m_first;
	Point2D		m_last;
	int			m_length;
	bool		m_isVertical;
	TypeOfCandy m_chainOfType;

	Chain();
	/// mặc định là chain theo chiều dọc.
	Chain(Point2D first, Point2D last, int length, bool direction = true);
	~Chain();

	/// thêm 1 phần tử vào chuỗi nếu như cùng kiểu vs chuỗi.
	void		AddOneNodeToChain(Point2D pos);

	/// ktra nếu 1 phần tử cùng kiểu vs chuỗi -> true, ngược lại -> false.
	bool		CheckIfSameTypeChain(TypeOfCandy type);

	/// ktra nếu 1 1 tử có vị trí p thuộc chuỗi -> true, ngược lại -> false.
	bool		CheckIfInChain(Point2D p);

	void operator=(const Chain& c)
	{
		m_first = c.m_first;
		m_last = c.m_last;
		m_length = c.m_length;
		m_isVertical = c.m_isVertical;
		m_chainOfType = c.m_chainOfType;
	}
};