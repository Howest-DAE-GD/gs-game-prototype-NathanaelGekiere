#pragma once
class Laser
{
public:
	Laser(Point2f posLaser, Point2f posButton, bool lVertical, bool pVertical, bool timer, float maxTime);
	void Draw();
	void Disable();
	void UpdateTimer(float elapsedSec);
	bool IsEnabled() const;
	bool IsPushed() const;
	Rectf GetRadius() const;
	Rectf GetBounds() const;
private:
	Rectf m_BoundsLaser;
	Rectf m_BoundsButton;
	Rectf m_RadiusButton;
	float m_ElapsedTime;
	float m_MaxTime;
	bool m_Enabled;
	bool m_Pushed;
	bool m_Timer;
	bool m_VerticalButton;
};

