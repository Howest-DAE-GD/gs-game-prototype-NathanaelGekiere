#include "pch.h"
#include "Key.h"
#include "utils.h"

Key::Key(Rectf bounds, int uses, bool used, Color4f color, std::string colors)
	:m_Bounds{bounds}
	,m_uses{uses}
	,m_used{used}
	,m_Color{color}
	,m_Colors{colors}
{
}

void Key::Draw()
{
		utils::SetColor(m_Color);
		utils::FillRect(Rectf(m_Bounds.left + m_Bounds.width/ 4, m_Bounds.bottom + m_Bounds.height * 3/8, m_Bounds.width * 2/8, m_Bounds.height *2/8));
		utils::FillRect(Rectf(m_Bounds.left + m_Bounds.width * 2 / 4, m_Bounds.bottom + m_Bounds.height * 7 / 16, m_Bounds.width * 5 / 16, m_Bounds.height * 2 / 16));
		utils::FillRect(Rectf(m_Bounds.left + m_Bounds.width * 11/16, m_Bounds.bottom + m_Bounds.height * 3 / 8, m_Bounds.width * 2 / 16, m_Bounds.height * 1 / 16));
		utils::SetColor(Color4f(0.f, 0.f, 0.f, 1.f));
		utils::FillRect(Rectf(m_Bounds.left + m_Bounds.width * 5 / 16, m_Bounds.bottom + m_Bounds.height * 7 / 16, m_Bounds.width * 2 / 16, m_Bounds.height * 2 / 16));
		if (m_used == true) {
			utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));
			utils::DrawLine(Point2f(m_Bounds.left, m_Bounds.bottom), Point2f(m_Bounds.left + m_Bounds.width, m_Bounds.bottom + m_Bounds.height), 3.f);
			utils::DrawLine(Point2f(m_Bounds.left, m_Bounds.bottom + m_Bounds.height), Point2f(m_Bounds.left + m_Bounds.width, m_Bounds.bottom), 3.f);
		}
}

void Key::SetBounds(Rectf bounds)
{
	m_Bounds = bounds;
}

void Key::UseKey()
{
}


Rectf Key::GetBounds() const
{
	return m_Bounds;
}

Color4f Key::GetColor()
{
	return m_Color;
}

std::string Key::GetString()
{
	return m_Colors;
}
