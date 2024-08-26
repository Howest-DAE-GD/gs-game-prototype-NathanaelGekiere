#include "pch.h"
#include "Laser.h"
#include "utils.h"

Laser::Laser(Point2f posLaser, Point2f posButton, bool lVertical, bool pVertical, bool timer, float maxTime)
	:m_BoundsLaser{ posLaser.x, posLaser.y,5,30 }
	,m_BoundsButton{ posButton.x, posButton.y,5,10 }
	,m_RadiusButton{ posButton.x - 5, posButton.y + 5,15,20 }
	,m_Enabled{true}
	,m_Pushed{false}
	,m_ElapsedTime{ 0 }
	,m_Timer{timer}
	,m_VerticalButton{ pVertical}
	,m_MaxTime{maxTime}
{
	if (lVertical == false) {
		m_BoundsLaser.width = 30;
		m_BoundsLaser.height = 5;
	}
	if (pVertical == false) {
		m_BoundsButton.width = 10;
		m_BoundsButton.height = 5;
		m_RadiusButton.width = 20;
		m_RadiusButton.height = 15;
	}
}

void Laser::Draw()
{	
	if (m_Enabled == true) {
		utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));
		utils::FillRect(m_BoundsLaser);
	}
	if (m_Pushed == false) {
		utils::SetColor(Color4f(0.f, 0.50f, 0.f, 1.f));
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
	if (m_VerticalButton == true) {
		m_BoundsButton.width = 2.5f;
	}
	if (m_VerticalButton == false) {
		m_BoundsButton.height = 2.5f;
	}
}

void Laser::UpdateTimer(float elapsedSec)
{
	if (m_Timer == true) {
		if (m_Enabled == false) {
			m_ElapsedTime += elapsedSec;
			if (m_ElapsedTime >= m_MaxTime) {
				m_ElapsedTime = 0;
				m_Enabled = true;
				m_Pushed = false;
				if (m_VerticalButton == true) {
					m_BoundsButton.width = 5.f;
				}
				if (m_VerticalButton == false) {
					m_BoundsButton.height = 5.f;
				}
			}
		}
	}
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
