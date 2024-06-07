#include "pch.h"
#include "Inventory.h"
#include "utils.h"
using namespace utils;

Inventory::Inventory()
:m_YellowKey{nullptr}
,m_PurpleKey{ nullptr }
,m_BlueKey{ nullptr }
,m_GrayKey{ nullptr }
,m_RedKey{ nullptr }
,m_GreenKey{ nullptr }
,m_PinkKey{ nullptr }
,m_YellowPos{25,340,100,100}
,m_PurplePos{155,340,100,100 }
,m_BluePos{285,340,100,100 }
,m_GrayPos{415,340,100,100 }
,m_RedPos{545,340,100,100 }
,m_GreenPos{675,340,100,100 }
,m_PinkPos{805,340,100,100 }
{
}

void Inventory::Draw()
{	
	SetColor(Color4f(0.f, 0.f, 0.f, 1.f));
	FillRect(0, 300, 930, 200);
	SetColor(Color4f(0.f, 0.f, 1.f, 1.f));
	DrawRect(m_YellowPos);
	DrawRect(m_PurplePos);
	DrawRect(m_BluePos);
	DrawRect(m_GrayPos);
	DrawRect(m_RedPos);
	DrawRect(m_GreenPos);
	DrawRect(m_PinkPos);
	if (m_YellowKey != nullptr) m_YellowKey->Draw();
	if (m_GrayKey != nullptr) m_GrayKey->Draw();
	if (m_PurpleKey != nullptr) m_PurpleKey->Draw();
	if (m_BlueKey != nullptr) m_BlueKey->Draw();
	if (m_RedKey != nullptr) m_RedKey->Draw();
	if (m_GreenKey != nullptr) m_GreenKey->Draw();
	if (m_PinkKey != nullptr) m_PinkKey->Draw();
}

void Inventory::StoreKey(Key*& key)
{
	if (key->GetString() == "Yellow") {
		m_YellowKey = key;
		m_YellowKey->SetBounds(m_YellowPos);
	}
	if (key->GetString() == "Gray") {
		m_GrayKey = key;
		m_GrayKey->SetBounds(m_GrayPos);
	}
	if (key->GetString() == "Purple") {
		m_PurpleKey = key;
		m_PurpleKey->SetBounds(m_PurplePos);
	}
	if (key->GetString() == "Blue") {
		m_BlueKey = key;
		m_BlueKey->SetBounds(m_BluePos);
	}
	if (key->GetString() == "Red") {
		m_RedKey = key;
		m_RedKey->SetBounds(m_RedPos);
	}
	if (key->GetString() == "Green") {
		m_GreenKey = key;
		m_GreenKey->SetBounds(m_GreenPos);
	}
	if (key->GetString() == "Pink") {
		m_PinkKey = key;
		m_PinkKey->SetBounds(m_PinkPos);
	}
}

void Inventory::UseKey(Door*& door)
{
	if (m_YellowKey != nullptr) {
		if (door->GetString() == m_YellowKey->GetString()) {
			door->OpenDoor();
		}
	}
	if (m_GrayKey != nullptr) {
		if (door->GetString() == m_GrayKey->GetString()) {
			door->OpenDoor();
		}
	}
	if (m_PurpleKey != nullptr) {
		if (door->GetString() == m_PurpleKey->GetString()) {
			door->OpenDoor();
		}
	}
	if (m_BlueKey != nullptr) {
		if (door->GetString() == m_BlueKey->GetString()) {
			door->OpenDoor();
		}
	}
	if (m_RedKey != nullptr) {
		if (door->GetString() == m_RedKey->GetString()) {
			door->OpenDoor();
		}
	}
	if (m_GreenKey != nullptr) {
		if (door->GetString() == m_GreenKey->GetString()) {
			door->OpenDoor();
		}
	}
	if (m_PinkKey != nullptr) {
		if (door->GetString() == m_PinkKey->GetString()) {
			door->OpenDoor();
		}
	}
}