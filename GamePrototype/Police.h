#pragma once
#include <vector>
class Police
{
public:
	Police(Point2f pos, Point2f end, float distance, float velocity, int points, bool rotate, bool cycle, bool linear, std::string direction);
	void Draw();
	void Move(float elapsedSec);
	void ChangeDirection(float elapsedSec);
	void ChangeVision();
	Rectf GetBoundsVision();
	Rectf GetBounds();
	bool IsRotating();
private:
	Rectf m_Bounds;
	Rectf m_Vision;
	Point2f m_StartPos;
	Point2f m_EndPos;
	Point2f m_Pos;
	float m_Distance;
	float m_Velocity;
	float m_ElapsedTime;
	int m_Point;
	int m_Points;
	bool m_Rotate;
	bool m_Cycle;
	bool m_Linear;
	enum class Direction {
		up,
		down,
		left,
		right
	};
	Direction m_Watch;
	Direction m_StartDirection;
};

