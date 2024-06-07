#include "pch.h"
#include "Laser.h"
#include "utils.h"

Laser::Laser()
	:m_BoundsLaser{ 600,540,5,30 }
	,m_BoundsButton{ 600,490,5,10 }
	,m_RadiusButton{ 595,495,15,20 }
	,m_Enabled{true}
	,m_Pushed{false}
{
}

void Laser::Draw()
{	
	if (m_Enabled == true) {
		utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));
		utils::FillRect(m_BoundsLaser);
	}
	if (m_Pushed == false) {
		utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));
		utils::FillRect(m_BoundsButton);
	}
	if (m_Pushed == true) {
		utils::SetColor(Color4f(0.f, 1.f, 0.f, 1.f));
		utils::FillRect(m_BoundsButton);
	}
}

void Laser::Disable()
{
	m_Pushed = true;
	m_Enabled = false;
	m_BoundsButton.width = 2.5f;
}

bool Laser::IsEnabled() const
{
	return m_Enabled;
}

bool Laser::IsPushed() const
{
	return m_Pushed;
}

Rectf Laser::GetRadius() const
{
	return m_RadiusButton;
}

Rectf Laser::GetBounds() const
{
	return m_BoundsLaser;
}
