#pragma once
#include "BaseGame.h"
#include <vector>
#include "Villain.h"
#include "Door.h"
#include "SCamera.h"
#include "Inventory.h"
#include "Chest.h"
#include "Laser.h"
#include "Snipers.h"
#include "Police.h"
#include "Texture.h"
class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:
	// DATA MEMBERS
	Villain* m_Player;
	SCamera* m_pSCamera;
	Laser* m_Laser1;
	Laser* m_Laser2;
	Laser* m_Laser3;
	Inventory* m_pInventory;
	enum class InventoryState {
		open, 
		close
	};
	InventoryState m_Inv;
	std::vector<std::vector<Point2f>> m_Walls;
	std::vector<Chest*> m_Chests;
	std::vector<Door*> m_Doors;
	std::vector<Snipers*> m_Snipers;
	std::vector<Police*> m_Polices;
	Rectf m_Victory;
	Texture* m_pSpace;
	bool m_Space;
	TTF_Font* m_pFont;

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;

	void InitializeAll();
	void InitializeWalls();
	void InitializeChests();
	void InitializeDoors();
	void InitializeSnipers();
	void InitializePolices();
	void DrawWalls() const;
	void DrawChests() const;
	void DrawDoors() const;
	void DrawSnipers() const;
	void DrawPolices() const;
	void DrawSquares() const;
	void DrawVictory() const;
	void DeleteAll();
	void Reset();
};