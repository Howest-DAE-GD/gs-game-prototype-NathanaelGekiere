#include "pch.h"
#include "Villain.h"
#include "utils.h"
#include <iostream>

Villain::Villain(Point2f position)
	:m_Bounds{ position.x, position.y, 10, 10 }
	,m_Velocity{ 60.f }
	,m_Direction{Direction::none}
{
}

void Villain::Draw() const
{
	utils::SetColor(Color4f{ 1.f, 0.f, 0.f, 1.f });
	//utils::DrawRect(m_Bounds);
	utils::FillEllipse(Point2f(m_Bounds.left + m_Bounds.width / 2, m_Bounds.bottom + m_Bounds.height / 2), m_Bounds.width / 2, m_Bounds.height / 2);
}

void Villain::Move(const Uint8* pStates, float elapsedSec, std::vector<std::vector<Point2f>> walls, std::vector<Chest*> chests, std::vector<Door*> doors)
{
	if (pStates[SDL_SCANCODE_D]) {
		m_Bounds.left += m_Velocity * elapsedSec;
		m_Direction = Direction::right;
		CheckForWalls(walls);
		CheckForChests(chests);
		CheckForDoors(doors);
	}
	if (pStates[SDL_SCANCODE_A]) {
		m_Bounds.left -= m_Velocity * elapsedSec;
		m_Direction = Direction::left;
		CheckForWalls(walls);
		CheckForChests(chests);
		CheckForDoors(doors);
	}
	if (pStates[SDL_SCANCODE_W]) {
		m_Bounds.bottom += m_Velocity * elapsedSec;
		m_Direction = Direction::up;
		CheckForWalls(walls);
		CheckForChests(chests);
		CheckForDoors(doors);
	}
	if (pStates[SDL_SCANCODE_S]) {
		 m_Bounds.bottom -= m_Velocity * elapsedSec;
		 m_Direction = Direction::down;
		 CheckForWalls(walls);
		 CheckForChests(chests);
		 CheckForDoors(doors);
	}
}

void Villain::Action(std::vector<Chest*> chests, std::vector<Door*> doors, Inventory*& inv, Laser*& laser1, Laser*& laser2)
{
	for (int chest{}; chest < chests.size(); ++chest) {
		if (utils::IsOverlapping(chests.at(chest)->GetRadius(), m_Bounds) == true) {
			chests.at(chest)->Open(inv);
		}
	}
	for (int door{}; door < doors.size(); ++door) {
		if (utils::IsOverlapping(doors.at(door)->GetRadius(), m_Bounds) == true) {
			inv->UseKey(doors.at(door));
		}
	}
	if (utils::IsOverlapping(m_Bounds, laser1->GetRadius()) == true) {
		laser1->Disable();
	}
	if (utils::IsOverlapping(m_Bounds, laser2->GetRadius()) == true) {
		laser2->Disable();
	}
}

Rectf Villain::GetBounds() const
{
	return m_Bounds;
}

Point2f Villain::GetPosition() const
{
	return Point2f(m_Bounds.left, m_Bounds.bottom);
}

void Villain::CheckForWalls(std::vector<std::vector<Point2f>> walls)
{
	utils::HitInfo hit{};
	if (m_Direction == Direction::up) {
		for (int vector{}; vector < walls.size(); ++vector) {
			if (utils::Raycast(walls.at(vector), Point2f(m_Bounds.left + 1, m_Bounds.bottom + m_Bounds.height), Point2f(m_Bounds.left + 1, m_Bounds.bottom), hit) == true ||
				utils::Raycast(walls.at(vector), Point2f(m_Bounds.left + m_Bounds.width-1, m_Bounds.bottom + m_Bounds.height), Point2f(m_Bounds.left + m_Bounds.width-1, m_Bounds.bottom), hit) == true) {
				m_Bounds.bottom = hit.intersectPoint.y - m_Bounds.height;
			}
		}
	}
	if (m_Direction == Direction::down) {
		for (int vector{}; vector < walls.size(); ++vector) {
			if (utils::Raycast(walls.at(vector), Point2f(m_Bounds.left + 1, m_Bounds.bottom + m_Bounds.height), Point2f(m_Bounds.left + 1, m_Bounds.bottom), hit) == true ||
				utils::Raycast(walls.at(vector), Point2f(m_Bounds.left + m_Bounds.width -1, m_Bounds.bottom + m_Bounds.height), Point2f(m_Bounds.left + m_Bounds.width-1, m_Bounds.bottom), hit) == true) {
				m_Bounds.bottom = hit.intersectPoint.y;
			}
		}
	}
	if (m_Direction == Direction::left) {
		for (int vector{}; vector < walls.size(); ++vector) {
			if (utils::Raycast(walls.at(vector), Point2f(m_Bounds.left, m_Bounds.bottom + 1), Point2f(m_Bounds.left + m_Bounds.width, m_Bounds.bottom + 1), hit) == true ||
				utils::Raycast(walls.at(vector), Point2f(m_Bounds.left, m_Bounds.bottom + m_Bounds.height - 1), Point2f(m_Bounds.left + m_Bounds.width, m_Bounds.bottom + m_Bounds.height- 1), hit) == true) {
				m_Bounds.left = hit.intersectPoint.x;
			}
		}
	}
	if (m_Direction == Direction::right) {
		for (int vector{}; vector < walls.size(); ++vector) {
			if (utils::Raycast(walls.at(vector), Point2f(m_Bounds.left, m_Bounds.bottom + 1), Point2f(m_Bounds.left + m_Bounds.width, m_Bounds.bottom + 1), hit) == true ||
				utils::Raycast(walls.at(vector), Point2f(m_Bounds.left, m_Bounds.bottom + m_Bounds.height - 1), Point2f(m_Bounds.left + m_Bounds.width, m_Bounds.bottom + m_Bounds.height - 1), hit) == true) {
				m_Bounds.left = hit.intersectPoint.x - m_Bounds.width;
			}
		}
	}
}

void Villain::CheckForChests(std::vector<Chest*> chests)
{
	utils::HitInfo hit{};
	if (m_Direction == Direction::up) {
		for (int vector{}; vector < chests.size(); ++vector) {
			std::vector<Point2f> chest;
			chest = chests.at(vector)->ReturnVector();
			if (utils::Raycast(chest, Point2f(m_Bounds.left + 1, m_Bounds.bottom + m_Bounds.height), Point2f(m_Bounds.left + 1, m_Bounds.bottom), hit) == true ||
				utils::Raycast(chest, Point2f(m_Bounds.left + m_Bounds.width - 1, m_Bounds.bottom + m_Bounds.height), Point2f(m_Bounds.left + m_Bounds.width - 1, m_Bounds.bottom), hit) == true) {
				m_Bounds.bottom = hit.intersectPoint.y - m_Bounds.height;
			}
		}
	}
	if (m_Direction == Direction::down) {
		for (int vector{}; vector < chests.size(); ++vector) {
			std::vector<Point2f> chest;
			chest = chests.at(vector)->ReturnVector();
			if (utils::Raycast(chest, Point2f(m_Bounds.left + 1, m_Bounds.bottom + m_Bounds.height), Point2f(m_Bounds.left + 1, m_Bounds.bottom), hit) == true ||
				utils::Raycast(chest, Point2f(m_Bounds.left + m_Bounds.width - 1, m_Bounds.bottom + m_Bounds.height), Point2f(m_Bounds.left + m_Bounds.width - 1, m_Bounds.bottom), hit) == true) {
				m_Bounds.bottom = hit.intersectPoint.y;
			}
		}
	}
	if (m_Direction == Direction::left) {
		for (int vector{}; vector < chests.size(); ++vector) {
			std::vector<Point2f> chest;
			chest = chests.at(vector)->ReturnVector();
				if (utils::Raycast(chest, Point2f(m_Bounds.left, m_Bounds.bottom + 1), Point2f(m_Bounds.left + m_Bounds.width, m_Bounds.bottom + 1), hit) == true ||
					utils::Raycast(chest, Point2f(m_Bounds.left, m_Bounds.bottom + m_Bounds.height - 1), Point2f(m_Bounds.left + m_Bounds.width, m_Bounds.bottom + m_Bounds.height - 1), hit) == true) {
					m_Bounds.left = hit.intersectPoint.x;
				}

		}
	}
	
	if (m_Direction == Direction::right) {
		for (int vector{}; vector < chests.size(); ++vector) {
			std::vector<Point2f> chest;
			chest = chests.at(vector)->ReturnVector();
				if (utils::Raycast(chest, Point2f(m_Bounds.left, m_Bounds.bottom + 1), Point2f(m_Bounds.left + m_Bounds.width, m_Bounds.bottom + 1), hit) == true ||
					utils::Raycast(chest, Point2f(m_Bounds.left, m_Bounds.bottom + m_Bounds.height - 1), Point2f(m_Bounds.left + m_Bounds.width, m_Bounds.bottom + m_Bounds.height - 1), hit) == true) {
					m_Bounds.left = hit.intersectPoint.x - m_Bounds.width;
			}
		}
	}
}

void Villain::CheckForDoors(std::vector<Door*> doors)
{
	utils::HitInfo hit{};
	if (m_Direction == Direction::up) {
		for (int vector{}; vector < doors.size(); ++vector) {
			if (doors.at(vector)->IsDoorOpen() == false) {
				std::vector<Point2f> door;
				door = doors.at(vector)->ReturnVector();
				if (utils::Raycast(door, Point2f(m_Bounds.left + 1, m_Bounds.bottom + m_Bounds.height), Point2f(m_Bounds.left + 1, m_Bounds.bottom), hit) == true ||
					utils::Raycast(door, Point2f(m_Bounds.left + m_Bounds.width - 1, m_Bounds.bottom + m_Bounds.height), Point2f(m_Bounds.left + m_Bounds.width - 1, m_Bounds.bottom), hit) == true) {
					m_Bounds.bottom = hit.intersectPoint.y - m_Bounds.height;
				}
			}
		}
	}
	if (m_Direction == Direction::down) {
		for (int vector{}; vector < doors.size(); ++vector) {
			if (doors.at(vector)->IsDoorOpen() == false) {
				std::vector<Point2f> door;
				door = doors.at(vector)->ReturnVector();
				if (utils::Raycast(door, Point2f(m_Bounds.left + 1, m_Bounds.bottom + m_Bounds.height), Point2f(m_Bounds.left + 1, m_Bounds.bottom), hit) == true ||
					utils::Raycast(door, Point2f(m_Bounds.left + m_Bounds.width - 1, m_Bounds.bottom + m_Bounds.height), Point2f(m_Bounds.left + m_Bounds.width - 1, m_Bounds.bottom), hit) == true) {
					m_Bounds.bottom = hit.intersectPoint.y;
				}
			}
		}
	}
	if (m_Direction == Direction::left) {
		for (int vector{}; vector < doors.size(); ++vector) {
			if (doors.at(vector)->IsDoorOpen() == false) {
				std::vector<Point2f> door;
				door = doors.at(vector)->ReturnVector();
				if (utils::Raycast(door, Point2f(m_Bounds.left, m_Bounds.bottom + 1), Point2f(m_Bounds.left + m_Bounds.width, m_Bounds.bottom + 1), hit) == true ||
					utils::Raycast(door, Point2f(m_Bounds.left, m_Bounds.bottom + m_Bounds.height - 1), Point2f(m_Bounds.left + m_Bounds.width, m_Bounds.bottom + m_Bounds.height - 1), hit) == true) {
					m_Bounds.left = hit.intersectPoint.x;
				}
			}
		}
	}

	if (m_Direction == Direction::right) {
		for (int vector{}; vector < doors.size(); ++vector) {
			if (doors.at(vector)->IsDoorOpen() == false) {
				std::vector<Point2f> door;
				door = doors.at(vector)->ReturnVector();
				if (utils::Raycast(door, Point2f(m_Bounds.left, m_Bounds.bottom + 1), Point2f(m_Bounds.left + m_Bounds.width, m_Bounds.bottom + 1), hit) == true ||
					utils::Raycast(door, Point2f(m_Bounds.left, m_Bounds.bottom + m_Bounds.height - 1), Point2f(m_Bounds.left + m_Bounds.width, m_Bounds.bottom + m_Bounds.height - 1), hit) == true) {
					m_Bounds.left = hit.intersectPoint.x - m_Bounds.width;
				}
			}
		}
	}
}
