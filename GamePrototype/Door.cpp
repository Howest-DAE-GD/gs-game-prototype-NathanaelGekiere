#include "pch.h"
#include "Door.h"
#include "utils.h"

Door::Door(Rectf bounds, Color4f color, std::string colors)
	:m_Bounds{bounds.left, bounds.bottom, bounds.width, bounds.height}
	,m_Radius{bounds.left - 5, bounds.bottom - 5, bounds.width + 10, bounds.height + 10}
	,m_IsOpen{false}
	,m_Color{color}
	,m_Colors{colors}
{
}

void Door::Draw()
{
	if (m_IsOpen == false) {
		utils::SetColor(m_Color);
		utils::FillRect(m_Bounds);
	}
}

void Door::OpenDoor()
{
	m_IsOpen = true;
}

bool Door::IsDoorOpen()
{
	return m_IsOpen;
}

Rectf Door::GetBounds() const
{
	return m_Bounds;
}

Rectf Door::GetRadius() const
{
	return m_Radius;
}

Color4f Door::GetColor()
{
	return m_Color;
}

std::string Door::GetString()
{
	return m_Colors;
}

std::vector<Point2f> Door::ReturnVector()
{
	return std::vector<Point2f>{Point2f{ m_Bounds.left, m_Bounds.bottom },
		Point2f{ m_Bounds.left, m_Bounds.bottom + m_Bounds.height },
		Point2f{ m_Bounds.left + m_Bounds.width, m_Bounds.bottom + m_Bounds.height },
		Point2f{ m_Bounds.left + m_Bounds.width, m_Bounds.bottom },
		Point2f{ m_Bounds.left, m_Bounds.bottom }};
}
