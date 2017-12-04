#include "Utils.h"

Vec2 Utils::GetPositionInWorld(Coord & c)
{
	return Vec2(BOT_LEFT_X + c.m_x * OFFSET_X, BOT_LEFT_Y + c.m_y * OFFSET_Y);
}

Vec2 Utils::GetPositionInWorldMan(Coord & c)
{
	return Vec2(TOP_LEFT_X + c.m_x * OFFSET_X, TOP_LEFT_Y - c.m_y * OFFSET_Y);
}
