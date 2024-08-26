#include "pch.h"
#include "Police.h"
#include "utils.h"

Police::Police(Point2f pos, Point2f end, float distance, float velocity, int points, float angle, bool rotate, bool cycle, bool linear, std::string direction)
	:m_Bounds{pos.x, pos.y, 30, 30}
	,m_Vision{ pos.x, pos.y, 0,0}
	,m_Warning{pos.x, pos.y, 0,0}
	,m_StartPos{pos}
	,m_EndPos{end}
	,m_Distance{distance}
	,m_Velocity{velocity}
	,m_ElapsedTime{ 0 }
	,m_Angle{angle}
	,m_MaxAngle{angle += points * 90}
	,m_Point{ 0 }
	,m_Points{points}
	,m_Rotate{rotate}
	,m_Cycle{cycle}
	,m_Linear{linear}
	,m_Watch{}
	,m_StartDirection{}
{
	if (direction == "left") m_Watch = Direction::left;
	if (direction == "down") m_Watch = Direction::down;
	if (direction == "right") m_Watch = Direction::right;
	if (direction == "up") m_Watch = Direction::up;
	if (m_Rotate == true) {
		m_StartDirection = m_Watch;
	}
}

void Police::Draw()
{
	utils::SetColor(Color4f{ 0.f, 0.f, 1.f, 1.f });
	//utils::DrawRect(m_Bounds);
	utils::FillEllipse(Point2f((m_Bounds.left + m_Bounds.width / 2) -1,( m_Bounds.bottom + m_Bounds.height / 2) -1), m_Bounds.width / 6, m_Bounds.height / 6);
	if (m_Linear == true) {
		utils::SetColor(Color4f(1.f, 1.f, 0.f, 0.75f));
		utils::FillRect(m_Warning);
	}
	utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));
	utils::FillRect(m_Vision);
	if (m_Rotate == true) {
		utils::DrawRect(m_Bounds);
	}
}

void Police::Move(float elapsedSec)
{
	if (m_Cycle == true) {
		if (m_Watch == Direction::left) {
			m_Bounds.left -= m_Velocity * elapsedSec;
		}
		if (m_Watch == Direction::down) {
			m_Bounds.bottom -= m_Velocity * elapsedSec;
		}
		if (m_Watch == Direction::right) {
			m_Bounds.left += m_Velocity * elapsedSec;
		}
		if (m_Watch == Direction::up) {
			m_Bounds.bottom += m_Velocity * elapsedSec;
		}
	}
	if (m_Linear == true) {
		if (m_Watch == Direction::left) {
			m_Bounds.left -= m_Velocity * elapsedSec;
		}
		if (m_Watch == Direction::down) {
			m_Bounds.bottom -= m_Velocity * elapsedSec;
		}
		if (m_Watch == Direction::right) {
			m_Bounds.left += m_Velocity * elapsedSec;
		}
		if (m_Watch == Direction::up) {
			m_Bounds.bottom += m_Velocity * elapsedSec;
		}
	}
}

void Police::ChangeDirection(float elapsedSec)
{
	if (m_Cycle == true) {
		if (m_Watch == Direction::left) {
			if (m_Bounds.left <= m_EndPos.x) {
				m_Watch = Direction::down;
				m_EndPos.y -= m_Distance;
			}
		}
		else if (m_Watch == Direction::down) {
			if (m_Bounds.bottom <= m_EndPos.y) {
				m_Watch = Direction::right;
				m_EndPos.x += m_Distance;
			}
		}
		else if (m_Watch == Direction::right) {
			if (m_Bounds.left >= m_EndPos.x) {
				m_Watch = Direction::up;
				m_EndPos.y += m_Distance;
			}
		}
		else if (m_Watch == Direction::up) {
			if (m_Bounds.bottom >= m_EndPos.y) {
				m_Watch = Direction::left;
				m_EndPos.x -= m_Distance;
			}
		}
	}
	if (m_Linear == true) {
		if (m_Watch == Direction::left) {
			if (m_Bounds.left <= m_EndPos.x) {
				m_Watch = Direction::right;
				m_EndPos.x += m_Distance;
			}
		}
		else if (m_Watch == Direction::down) {
			if (m_Bounds.bottom <= m_EndPos.y) {
				m_Watch = Direction::up;
				m_EndPos.y += m_Distance;
			}
		}
		else if (m_Watch == Direction::right) {
			if (m_Bounds.left >= m_EndPos.x) {
				m_Watch = Direction::left;
				m_EndPos.x -= m_Distance;
			}
		}
		else if (m_Watch == Direction::up) {
			if (m_Bounds.bottom >= m_EndPos.y) {
				m_Watch = Direction::down;
				m_EndPos.y -= m_Distance;
			}
		}
	}

	if (m_Rotate == true) {
		m_ElapsedTime += elapsedSec;
		if (m_ElapsedTime >= m_Velocity) {
			if (m_Watch == Direction::left) {
					m_Watch = Direction::down;
			}
			else if (m_Watch == Direction::down) {
					m_Watch = Direction::right;
			}
			else if (m_Watch == Direction::right) {
					m_Watch = Direction::up;
			}
			else if (m_Watch == Direction::up) {
					m_Watch = Direction::left;
			}
			m_ElapsedTime = 0;
			m_Point += 1;
			if (m_Point == m_Points) {
				m_Watch = m_StartDirection;
				m_Point = 0;
			}
		}
	}
}

void Police::ChangeVision()
{
	if (m_Cycle == true) {
		if (m_Watch == Direction::left) {
			m_Vision.width = 10;
			m_Vision.height = 30;
			m_Vision.left = m_Bounds.left;
			m_Vision.bottom = m_Bounds.bottom;
		}
		if (m_Watch == Direction::down) {
			m_Vision.width = 30;
			m_Vision.height = 10;
			m_Vision.left = m_Bounds.left;
			m_Vision.bottom = m_Bounds.bottom;
		}
		if (m_Watch == Direction::right) {
			m_Vision.width = 10;
			m_Vision.height = 30;
			m_Vision.left = m_Bounds.left +20;
			m_Vision.bottom = m_Bounds.bottom;
		}
		if (m_Watch == Direction::up) {
			m_Vision.width = 30;
			m_Vision.height = 10;
			m_Vision.left = m_Bounds.left;
			m_Vision.bottom = m_Bounds.bottom + 20;
		}
	}
	if (m_Linear == true) {
		if (m_Watch == Direction::left) {
			m_Vision.width = 10;
			m_Vision.height = 30;
			m_Vision.left = m_Bounds.left;
			m_Vision.bottom = m_Bounds.bottom;
			m_Warning.width = 10;
			m_Warning.height = 30;
			m_Warning.left = m_Bounds.left-10;
			m_Warning.bottom = m_Bounds.bottom;
		}
		if (m_Watch == Direction::down) {
			m_Vision.width = 30;
			m_Vision.height = 10;
			m_Vision.left = m_Bounds.left;
			m_Vision.bottom = m_Bounds.bottom;
			m_Warning.width = 30;
			m_Warning.height = 10;
			m_Warning.left = m_Bounds.left;
			m_Warning.bottom = m_Bounds.bottom-10;
		}
		if (m_Watch == Direction::right) {
			m_Vision.width = 10;
			m_Vision.height = 30;
			m_Vision.left = m_Bounds.left + 20;
			m_Vision.bottom = m_Bounds.bottom;
			m_Warning.width = 10;
			m_Warning.height = 30;
			m_Warning.left = m_Bounds.left +30;
			m_Warning.bottom = m_Bounds.bottom;
		}
		if (m_Watch == Direction::up) {
			m_Vision.width = 30;
			m_Vision.height = 10;
			m_Vision.left = m_Bounds.left;
			m_Vision.bottom = m_Bounds.bottom + 20;
			m_Warning.width = 30;
			m_Warning.height = 10;
			m_Warning.left = m_Bounds.left;
			m_Warning.bottom = m_Bounds.bottom +30;
		}
	}
	if (m_Rotate == true) {
		if (m_Watch == Direction::left) {
			m_Vision.width = 55;
			m_Vision.height = 30;
			m_Vision.left = m_Bounds.left-55;
			m_Vision.bottom = m_Bounds.bottom;
		}
		if (m_Watch == Direction::down) {
			m_Vision.width = 30;
			m_Vision.height = 55;
			m_Vision.left = m_Bounds.left;
			m_Vision.bottom = m_Bounds.bottom - 55;
		}
		if (m_Watch == Direction::right) {
			m_Vision.width = 55;
			m_Vision.height = 30;
			m_Vision.left = m_Bounds.left + 30;
			m_Vision.bottom = m_Bounds.bottom;
		}
		if (m_Watch == Direction::up) {
			m_Vision.width = 30;
			m_Vision.height = 55;
			m_Vision.left = m_Bounds.left;
			m_Vision.bottom = m_Bounds.bottom + 30;
		}
	}
}

Rectf Police::GetBoundsVision()
{
	return m_Vision;
}

Rectf Police::GetBounds()
{
	return m_Bounds;
}

bool Police::IsRotating()
{
	return m_Rotate;
}
