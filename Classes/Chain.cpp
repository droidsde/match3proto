#include "Chain.h"

#include "Chain.h"

Chain::Chain()
{
	m_first = Position(0, 0);
	m_last = Position(0, 0);
	m_length = 0;
	m_isVertical = true;
	m_typeOfChain = 0;
}

Chain::Chain(Position first, Position last, int length, bool direction /*= true*/)
{
	m_first = first;
	m_last = last;
	m_length = length;
	m_isVertical = direction;
}

Chain::~Chain()
{
}

void Chain::AddOneNodeToChain(Position pos)
{
	m_length += 1;
	/// thêm vào cuối nếu chỉ số row(col) lớn hơn phần tử cuối của chuỗi,
	/// và cập nhật lại vị trí phần tử cuối.
	if (m_isVertical)
	{
		if (pos.m_col > m_last.m_col)
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
		if (pos.m_row > m_last.m_row)
		{
			m_last = pos;
		}
		else
		{
			m_first = pos;
		}
	}
}

void Chain::FixChain()
{
	if (m_isVertical)
	{
		if (m_first.m_row > m_last.m_row)
		{
			Position temp = m_first;
			m_first = m_last;
			m_last = temp;
		}
	}
	else
	{
		if (m_first.m_col > m_last.m_col)
		{
			Position temp = m_first;
			m_first = m_last;
			m_last = temp;
		}
	}
}

bool Chain::CheckIfSameTypeChain(int typeOfCandy)
{
	if (m_typeOfChain == typeOfCandy)
	{
		return true;
	}
	return false;
}

bool Chain::CheckIfInChain(Position p)
{
	FixChain();
	if (m_isVertical)
	{
		/// so sánh row
		if ((m_first.m_row <= p.m_row) && (p.m_row <= m_last.m_row) && (m_first.m_col == p.m_col))
		{
			return true;
		}
		return false;
	}
	else
	{
		/// so sánh column
		if ((m_first.m_col <= p.m_col) && (p.m_col <= m_last.m_col) && (m_first.m_row == p.m_row))
		{
			return true;
		}
		return false;
	}
}

void Chain::PrintChain()
{
	FixChain();
	if (m_isVertical)
	{
		printf("column = %d\n", m_first.m_col);
		for (int row = m_first.m_row; row <= m_last.m_row; row++)
		{
			printf(" %2d ", row);
		}
		printf("\n");
	}
	else
	{
		printf("row = %d\n", m_first.m_row);
		for (int col = m_first.m_col; col <= m_last.m_col; col++)
		{
			printf(" %2d ", col);
		}
		printf("\n");
	}
}
