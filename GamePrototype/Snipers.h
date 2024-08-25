#pragma once
class Snipers
{
public:
	Snipers(Point2f pos);
	void Draw();
	void Count(float elapsedSec);
	void Reset();
	void SetAiming();
	bool CheckTime();
	Circlef GetBounds();
	float ReturnTime();
private:
	Circlef m_Bounds;
	float m_ElapsedTime;
	bool m_IsAiming;
};

