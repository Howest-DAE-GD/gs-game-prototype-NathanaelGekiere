#include "pch.h"
#include "Chest.h"
#include "utils.h"


Chest::Chest(Point2f pos, bool hasKey, int uses, bool used, Color4f keyColor, std::string keyColors)
	: m_Bounds{ Rectf(pos.x, pos.y, 20, 20) }
	, m_Radius{ Rectf(pos.x - 5, pos.y - 5, 30, 30) }
	, m_State{ ChestState::closed }
	, m_HasKey(hasKey)
	, m_Key{}
{
	if (hasKey == true) {
		m_Key = new Key{ m_Bounds, uses, used, keyColor, keyColors };
	}
	if (hasKey == false) {
		m_Key = nullptr;
	}
}

Chest::Chest(Point2f pos, bool hasKey)
: m_Bounds{ Rectf(pos.x, pos.y, 20, 20) }
, m_Radius{ Rectf(pos.x - 5, pos.y - 5, 30, 30) }
, m_State{ ChestState::closed }
, m_HasKey(hasKey)
, m_Key{}
{
	if (hasKey == false) {
		m_Key = nullptr;
	}
}


void Chest::Draw()
{
	if (m_State == ChestState::closed) {
		utils::SetColor(Color4f(0.34f, 0.16f, 0.f, 1.f));
		utils::FillRect(m_Bounds);
	}
	if (m_State == ChestState::open) {
		utils::SetColor(Color4f(0.34f, 0.16f, 0.f, 1.f));
		utils::DrawRect(Rectf(m_Bounds.left + 2, m_Bounds.bottom + 2, m_Bounds.width - 4, m_Bounds.height - 4));
	}
}

void Chest::Open(Inventory* inv)
{
	m_State = ChestState::open;
	if (m_HasKey == true) {
		inv->StoreKey(m_Key);
	}
}

Rectf Chest::GetRadius()
{
	return m_Radius;
}

std::vector<Point2f> Chest::ReturnVector()
{
	return std::vector<Point2f>{Point2f{ m_Bounds.left, m_Bounds.bottom },
		Point2f{ m_Bounds.left, m_Bounds.bottom + m_Bounds.height },
		Point2f{  m_Bounds.left + m_Bounds.width, m_Bounds.bottom + m_Bounds.height},
		Point2f{ m_Bounds.left + m_Bounds.width, m_Bounds.bottom },
		Point2f{ m_Bounds.left, m_Bounds.bottom  }};
}

