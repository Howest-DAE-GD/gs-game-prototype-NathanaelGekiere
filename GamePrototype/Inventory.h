#pragma once
#include "Key.h"
#include <vector>
#include "Door.h"
class Inventory
{
public:
	Inventory();
	void Draw();
	void StoreKey(Key*& key);
	void UseKey(Door*& door);
private:
	Key* m_YellowKey;
	Key* m_PurpleKey;
	Key* m_BlueKey;
	Key* m_GrayKey;
	Key* m_OrangeKey;
	Key* m_GreenKey;
	Key* m_PinkKey;
	Rectf m_YellowPos;
	Rectf m_PurplePos;
	Rectf m_BluePos;
	Rectf m_GrayPos;
	Rectf m_OrangePos;
	Rectf m_GreenPos;
	Rectf m_PinkPos;
};