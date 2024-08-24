#include "pch.h"
#include "SCamera.h"

SCamera::SCamera(float screenWidth, float screenHeight)
	:m_ScreenWidth{ screenWidth }
	, m_ScreenHeight{ screenHeight }
{
}

void SCamera::Aim(float levelW, float levelH, const Point2f& trackCenter)
{
	Point2f cameraPos{ trackCenter.x - (m_ScreenWidth / 4) *2, trackCenter.y - (m_ScreenHeight / 4) *3};
	glPushMatrix();
	glScalef(8.f, 8.f, 1.f);
	if (trackCenter.x + m_ScreenWidth / 2 > levelW)
	{
		cameraPos.x = levelW - m_ScreenWidth;
	}
	if (trackCenter.y + m_ScreenHeight * 0.5f > levelH) {
		cameraPos.y = levelH - m_ScreenHeight;
	}
	if (trackCenter.x - m_ScreenWidth / 2 < 0) {
		cameraPos.x = 0;
	}
	if (trackCenter.y - m_ScreenHeight / 2 < 0) {
		cameraPos.y = 0;
	}
	glTranslatef(-cameraPos.x, -cameraPos.y, 0);
}


Point2f SCamera::Reset()
{
	glPopMatrix();
	return Point2f(0, 0);
}