#include "pch.h"
#include "Snipers.h"
#include "utils.h"

Snipers::Snipers(Point2f pos)
	:m_Bounds{pos.x, pos.y, 75}
	,m_ElapsedTime{ 0 }
{
}

void Snipers::Draw()
{
	utils::SetColor(Color4f(1.f, 0.98f, 0.80f, 1.f));
	utils::FillEllipse(m_Bounds.center, m_Bounds.radius, m_Bounds.radius);
}

void Snipers::Count(float elapsedSec)
{
	m_ElapsedTime += elapsedSec;
}

void Snipers::Reset()
{
	m_ElapsedTime = 0;
}

bool Snipers::CheckTime()
{
	if (m_ElapsedTime >= 2.1f) return true;
	else return false;
}

Circlef Snipers::GetBounds()
{
	return m_Bounds;
}

float Snipers::ReturnTime()
{
	return m_ElapsedTime;
}
