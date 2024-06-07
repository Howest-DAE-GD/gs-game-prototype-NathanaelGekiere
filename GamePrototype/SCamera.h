#pragma once
class SCamera
{
public:
	SCamera(float screenWidth, float screenHeight);
	void Aim(float levelW, float levelH, const Point2f& trackCenter);
	Point2f Reset();
private:
	const float m_ScreenWidth;
	const float m_ScreenHeight;
};

