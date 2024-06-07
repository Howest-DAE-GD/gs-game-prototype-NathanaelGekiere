#pragma once
#include "Key.h"
#include <vector>
class Door
{
public:
	Door(Rectf bounds, Color4f color, std::string colors);
	void Draw();
	void OpenDoor();
	bool IsDoorOpen();
	Rectf GetBounds() const;
	Rectf GetRadius() const;
	Color4f GetColor();
	std::string GetString();
	std::vector<Point2f> ReturnVector();
private:
	Rectf m_Bounds;
	Rectf m_Radius;
	bool m_IsOpen;
	Color4f m_Color;
	std::string m_Colors;
};

