#include "Chain.h"


Chain::Chain()
{
	m_first = Point2D(0, 0);
	m_last = Point2D(0, 0);
	m_length = 0;
	m_isVertical = true;
	m_chainOfType = TypeOfCandy::TYPE_UNKNOW_CANDY;
}

Chain::Chain(Point2D first, Point2D last, int length, bool direction /*= true*/)
{
	m_first = first;
	m_last = last;
	m_length = length;
	m_isVertical = direction;
}

Chain::~Chain()
{

}

void Chain::AddOneNodeToChain(Point2D pos)
{
	m_length += 1;
	/// thêm vào cuối nếu chỉ số row(col) lớn hơn phần tử cuối của chuỗi,
	/// và cập nhật lại vị trí phần tử cuối.
	if (m_isVertical)
	{
		if (pos.m_y > m_last.m_y)
		{
			m_last = pos;
		}
		else
		{
			m_first = pos;
		}
	}
	/// thêm vào đầu chuỗi nếu chỉ số row(col) nhỏ hơn phần tử đầu của chuỗi,
	/// và cập nhật lại vị trí phần tử đầu.
	else
	{
		if (pos.m_x > m_last.m_x)
		{
			m_last = pos;
		}
		else
		{
			m_first = pos;
		}
	}
}

bool Chain::CheckIfSameTypeChain(TypeOfCandy type)
{
	if (m_chainOfType == type)
	{
		//CCLOG("== type");
		return true;
	}
	//CCLOG("!= type");
	return false;
}

bool Chain::CheckIfInChain(Point2D p)
{
	if (m_isVertical)
	{
		/// so sánh row
		if (m_first.m_x < m_last.m_x)
		{
			if ((m_first.m_x <= p.m_x) && (p.m_x <= m_last.m_x))
			{
				return true;
			}
			return false;
		}
		else
		{
			if ((m_first.m_x >= p.m_x) && (p.m_x >= m_last.m_x))
			{
				return true;
			}
			return false;
		}
	}
	else
	{
		/// so sánh column
		if (m_first.m_y < m_last.m_y)
		{
			if ((m_first.m_y <= p.m_y) && (p.m_y <= m_last.m_y))
			{
				return true;
			}
			return false;
		}
		else
		{
			if ((m_first.m_y >= p.m_y) && (p.m_y >= m_last.m_y))
			{
				return true;
			}
			return false;
		}
	}
}

