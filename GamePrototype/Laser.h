#pragma once
class Laser
{
public:
	Laser();
	void Draw();
	void Disable();
	bool IsEnabled() const;
	bool IsPushed() const;
	Rectf GetRadius() const;
	Rectf GetBounds() const;
private:
	Rectf m_BoundsLaser;
	Rectf m_BoundsButton;
	Rectf m_RadiusButton;
	bool m_Enabled;
	bool m_Pushed;

};

