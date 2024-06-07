#pragma once
#include "Key.h"
#include "Inventory.h"
#include <vector>

class Chest
{
public:
	Chest(Point2f pos, bool hasKey, int uses, bool used, Color4f keyColor, std::string keyColors);
	Chest(Point2f pos, bool hasKey);
	void Draw();
	void Open(Inventory* inv);
	Rectf GetRadius();
	std::vector<Point2f> ReturnVector();
private:
	Rectf m_Bounds;
	Rectf m_Radius;
	enum class ChestState {
		closed,
		open
	};
	ChestState m_State;
	bool m_HasKey;
	Key* m_Key;
};

