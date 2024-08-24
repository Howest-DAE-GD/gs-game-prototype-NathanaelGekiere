#pragma once
#include <vector>
#include "Door.h"
#include "Chest.h"
#include "Laser.h"
class Inventory;

class Villain
{
public:
	Villain(Point2f position);
	void Draw() const;
	void Move(const Uint8* pStates, float elapsedSec, std::vector<std::vector<Point2f>> walls, std::vector<Chest*> chests, std::vector<Door*> doors);
	void Action(std::vector<Chest*> chests, std::vector<Door*> doors, Inventory*& inv, Laser*& laser1, Laser*& laser2);
	void CheckForWalls(std::vector<std::vector<Point2f>> walls);
	void CheckForChests(std::vector<Chest*> chests);
	void CheckForDoors(std::vector<Door*> doors);
	Rectf GetBounds() const;
	Point2f GetPosition() const;
	//void CheckForDoorU(Door* & door);
	//void CheckForDoorB(Door*& door);
	//void CheckForDoorL(Door*& door);
	//void CheckForDoorR(Door*& door);
private:
	Rectf m_Bounds;
	float m_Velocity;
	enum class Direction {
		none,
		up,
		down,
		left,
		right
	};
	Direction m_Direction;
	//Key* m_Key;
	//enum class TouchingDoor {
	//	yes,
	//	no
	//};
	//TouchingDoor m_TDoor;
};	//

