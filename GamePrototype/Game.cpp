#include "pch.h"
#include "Game.h"
#include "utils.h"
#include <iostream>
using namespace utils;

Game::Game( const Window& window ) 
	:BaseGame{ window }
	,m_Inv{ InventoryState::close }
	,m_Victory{420,0,60,30}
{
	Initialize();
}

Game::~Game( )
{
	Cleanup(); 
}

void Game::Initialize( )
{
	InitializeAll();
}

void Game::Cleanup( )
{
	DeleteAll();
}

void Game::Update( float elapsedSec )
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	if (m_Inv == InventoryState::close) {
		m_Player->Move(pStates, elapsedSec, m_Walls, m_Chests, m_Doors);
		if (pStates[SDL_SCANCODE_SPACE]) {
			m_Player->Action(m_Chests, m_Doors, m_pInventory, m_Laser1, m_Laser2);
		}
	}
	if (m_Laser1->IsEnabled() == true) {
		if (utils::IsOverlapping(m_Player->GetBounds(), m_Laser1->GetBounds()) == true) {
			Reset();
		}
	}
	if (m_Laser2->IsEnabled() == true) {
		if (utils::IsOverlapping(m_Player->GetBounds(), m_Laser2->GetBounds()) == true) {
			Reset();
		}
	}
	for (int sniper{}; sniper < m_Snipers.size(); ++sniper) {
		if (utils::IsOverlapping(m_Player->GetBounds(), m_Snipers.at(sniper)->GetBounds()) == true) {
			m_Snipers.at(sniper)->Count(elapsedSec);
			m_Snipers.at(sniper)->SetAiming();
		}
		else m_Snipers.at(sniper)->Reset();
		if (m_Snipers.at(sniper)->CheckTime() == true) Reset();
	}
	for (int police{}; police < m_Polices.size(); ++police) {
		m_Polices.at(police)->Move(elapsedSec);
		m_Polices.at(police)->ChangeDirection(elapsedSec);
		m_Polices.at(police)->ChangeVision();
	}
	for (int police{}; police < m_Polices.size(); ++police) {
		if (utils::IsOverlapping(m_Polices.at(police)->GetBoundsVision(), m_Player->GetBounds()) == true) Reset();
	}
	for (int police{}; police < m_Polices.size(); ++police) {
		if (m_Polices.at(police)->IsRotating() == true) {
			if (utils::IsOverlapping(m_Polices.at(police)->GetBounds(), m_Player->GetBounds()) == true) Reset();
		}
	}
	if (utils::IsOverlapping(m_Player->GetBounds(), m_Victory) == true) {
		std::cout << "YOU ESCAPED!";
		Reset();
	}
	// Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
}

void Game::Draw( ) const
{

	ClearBackground();
	if (m_Inv == InventoryState::open) {
		m_pInventory->Draw();
	}
	if (m_Inv == InventoryState::close) {
		//m_pSCamera->Aim(930, 780, m_Player->GetPosition());
		DrawSnipers();
		m_Player->Draw();
		m_Laser1->Draw();
		m_Laser2->Draw();
		DrawWalls();
		DrawChests();
		DrawDoors();
		DrawPolices();
		DrawVictory();
		//DrawSquares();
		//m_pSCamera->Reset();
	}


}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	if (e.keysym.sym == SDLK_i) m_Inv = InventoryState::open;
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	if (e.keysym.sym == SDLK_i) m_Inv = InventoryState::close;
	//if (e.keysym.sym == SDLK_SPACE) {
	//	if (m_Player->HasKey() == false) m_Player->PickUpKey(m_YellowKey);
	//	else m_Player->PutDownKey();
	//}
	//if (e.keysym.sym == SDLK_a && m_Player->HasKey() == true) m_Player->UseKey(m_YellowDoor);

	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	std::cout << "(" << e.x << ", " << e.y << ")\n";
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::InitializeAll()
{
	m_pInventory = new Inventory;
	m_pSCamera = new SCamera{ 120.f , 60.f };
	m_Player = new Villain{ Point2f(12,119) };
	m_Laser1 = new Laser{Point2f(600,540), Point2f(600,490)};
	m_Laser2 = new Laser{ Point2f(100,479), Point2f(60,383)};
	InitializeWalls();
	InitializeChests();
	InitializeDoors();
	InitializeSnipers();
	InitializePolices();
}

void Game::InitializeWalls()
{
	std::vector<Point2f> m_Walls1{
		Point2f{390,0},
		Point2f{390,30},
		Point2f{420,30},
		Point2f{420,0},
		Point2f{390,0}
	};
	std::vector<Point2f> m_Walls2{
		Point2f{390,60},
		Point2f{390,120},
		Point2f{315,120},
		Point2f{315,150},
		Point2f{330,150},
		Point2f{330,180},
		Point2f{90, 180},
		Point2f{90,210},
		Point2f{360,210},
		Point2f{360,300},
		Point2f{390,300},
		Point2f{390,210},
		Point2f{420,210},
		Point2f{420,60},
		Point2f{390,60}
	};
	std::vector<Point2f> m_Walls3{
		Point2f{285,120},
		Point2f{30,120},
		Point2f{30,690},
		Point2f{90,690},
		Point2f{90,750},
		Point2f{810,750},
		Point2f{810,660},
		Point2f{900,660},
		Point2f{900,120},
		Point2f{675,120},
		Point2f{675,150},
		Point2f{840,150},
		Point2f{840,180},
		Point2f{870,180},
		Point2f{870,570},
		Point2f{480,570},
		Point2f{480,690},
		Point2f{600,690},
		Point2f{600,660},
		Point2f{510,660},
		Point2f{510,600},
		Point2f{630,600},
		Point2f{630,690},
		Point2f{660,690},
		Point2f{660,600},
		Point2f{780,600},
		Point2f{780,660},
		Point2f{690,660},
		Point2f{690,690},
		Point2f{780,690},
		Point2f{780,720},
		Point2f{120,720},
		Point2f{120,690},
		Point2f{210,690},
		Point2f{210,660},
		Point2f{120,660},
		Point2f{120,600},
		Point2f{240,600},
		Point2f{240,690},
		Point2f{270,690},
		Point2f{270,600},
		Point2f{390,600},
		Point2f{390,660},
		Point2f{300,660},
		Point2f{300,690},
		Point2f{420,690},
		Point2f{420,570},
		Point2f{120,570},
		Point2f{120,510},
		Point2f{90,510},
		Point2f{90,630},
		Point2f{60,630},
		Point2f{60,480},
		Point2f{210,480},
		Point2f{210,540},
		Point2f{420,540},
		Point2f{420,450},
		Point2f{390,450},
		Point2f{390,360},
		Point2f{360,360},
		Point2f{360,510},
		Point2f{270,510},
		Point2f{270,330},
		Point2f{240,330},
		Point2f{240,450},
		Point2f{210,450},
		Point2f{210,405},
		Point2f{180,405},
		Point2f{180,420},
		Point2f{150,420},
		Point2f{150,450},
		Point2f{120,450},
		Point2f{120,420},
		Point2f{90,420},
		Point2f{90,405},
		Point2f{60,405},
		Point2f{60,375},
		Point2f{90,375},
		Point2f{90,360},
		Point2f{120,360},
		Point2f{120,330},
		Point2f{150,330},
		Point2f{150,360},
		Point2f{180,360},
		Point2f{180,375},
		Point2f{210,375},
		Point2f{210,270},
		Point2f{300,270},
		Point2f{300,450},
		Point2f{330,450},
		Point2f{330,240},
		Point2f{180,240},
		Point2f{180,300},
		Point2f{90,300},
		Point2f{90,240},
		Point2f{60,240},
		Point2f{60,150},
		Point2f{285,150},
		Point2f{285,120}
	};
	std::vector<Point2f> m_Walls4{
		Point2f{120,240},
		Point2f{150,240},
		Point2f{150,270},
		Point2f{120,270},
		Point2f{120,240}
	};
	std::vector<Point2f> m_Walls5{
		Point2f{480,0},
		Point2f{480,150},
		Point2f{600,150},
		Point2f{600,210},
		Point2f{690,210},
		Point2f{690,270},
		Point2f{570,270},
		Point2f{570,360},
		Point2f{600,360},
		Point2f{600,300},
		Point2f{750,300},
		Point2f{750,510},
		Point2f{600,510},
		Point2f{600,480},
		Point2f{720,480},
		Point2f{720,450},
		Point2f{600,450},
		Point2f{600,390},
		Point2f{570,390},
		Point2f{570,510},
		Point2f{480,510},
		Point2f{480,540},
		Point2f{840,540},
		Point2f{840,510},
		Point2f{780,510},
		Point2f{780,300},
		Point2f{840,300},
		Point2f{840,270},
		Point2f{780,270},
		Point2f{780,240},
		Point2f{750,240},
		Point2f{750,180},
		Point2f{630,180},
		Point2f{630,150},
		Point2f{645,150},
		Point2f{645,120},
		Point2f{510,120},
		Point2f{510,0},
		Point2f{480,0}
	};
	std::vector<Point2f> m_Walls6{
		Point2f{420, 240},
		Point2f{480, 240},
		Point2f{480, 300},
		Point2f{420, 300},
		Point2f{420, 240}
	};
	std::vector<Point2f> m_Walls7{
		Point2f{420, 360},
		Point2f{480, 360},
		Point2f{480, 420},
		Point2f{420, 420},
		Point2f{420, 360}
	};
	std::vector<Point2f> m_Walls8{
		Point2f{810, 330},
		Point2f{810, 390},
		Point2f{840, 390},
		Point2f{840, 330},
		Point2f{810, 330}
	};
	std::vector<Point2f> m_Walls9{
		Point2f{810, 420},
		Point2f{810, 480},
		Point2f{840, 480},
		Point2f{840, 420},
		Point2f{810, 420}
	};
	std::vector<Point2f> m_Walls10{
		Point2f{810, 225},
		Point2f{810, 240},
		Point2f{840, 240},
		Point2f{840, 225},
		Point2f{810, 225}
	};
	std::vector<Point2f> m_Walls11{
		Point2f{780, 180},
		Point2f{780, 210},
		Point2f{795, 210},
		Point2f{795, 180},
		Point2f{780, 180}

	};
	std::vector<Point2f> m_Walls12{
		Point2f{480, 180},
		Point2f{480, 210},
		Point2f{510, 210},
		Point2f{510, 450},
		Point2f{480, 450},
		Point2f{480, 480},
		Point2f{540, 480},
		Point2f{540, 210},
		Point2f{570, 210},
		Point2f{570, 180},
		Point2f{480, 180}
	};
	std::vector<Point2f> m_Walls13{
		Point2f{30,90},
		Point2f{135,90},
		Point2f{135,60},
		Point2f{90,60},
		Point2f{90,30},
		Point2f{165,30},
		Point2f{165,120},
		Point2f{30,120},
		Point2f{30,90}
	};
	std::vector<Point2f> m_Walls14{
		Point2f{195,120},
		Point2f{225,120},
		Point2f{225,0},
		Point2f{195,0},
		Point2f{195,120}
	};
	std::vector<Point2f> m_Walls15{
		Point2f{270,45},
		Point2f{270,75},
		Point2f{345,75},
		Point2f{345,45},
		Point2f{270,45}
	};
	std::vector<Point2f> m_Walls16{
		Point2f{30,720},
		Point2f{30,750},
		Point2f{60,750},
		Point2f{60,720},
		Point2f{30,720},
	};
	std::vector<Point2f> m_Walls17{
		Point2f{870,0},
		Point2f{870,60},
		Point2f{930,60},
		Point2f{930,0},
		Point2f{870,0}
	};
	std::vector<Point2f> m_Walls18{
		Point2f{870,720},
		Point2f{870,780},
		Point2f{930,780},
		Point2f{930,720},
		Point2f{870,720}
	};
	std::vector<Point2f> m_Walls19{
		Point2f{0,0},
		Point2f{0,60},
		Point2f{60,60},
		Point2f{60,0},
		Point2f{0,0}
	};
	std::vector<Point2f> m_Walls20{
		Point2f{690,120},
		Point2f{690,90},
		Point2f{630,90},
		Point2f{630,75},
		Point2f{600,75},
		Point2f{600,90},
		Point2f{540,90},
		Point2f{540,75},
		Point2f{555,75},
		Point2f{555,45},
		Point2f{540,45},
		Point2f{540,30},
		Point2f{630,30},
		Point2f{630,45},
		Point2f{660,45},
		Point2f{660,30},
		Point2f{720,30},
		Point2f{720,120},
		Point2f{690,120}
	};
	std::vector<Point2f> m_Walls21{
		Point2f{420,120},
		Point2f{420,150},
		Point2f{480,150},
		Point2f{480,120},
		Point2f{420,120}
	};
	std::vector<Point2f> m_Walls22{
		Point2f{810,750},
		Point2f{840,750},
		Point2f{840,720},
		Point2f{825,720},
		Point2f{825,675},
		Point2f{870,675},
		Point2f{870,690},
		Point2f{900,690},
		Point2f{900,660},
		Point2f{810,660},
		Point2f{810,750}
	};
	std::vector<Point2f> m_Walls23{
		Point2f{150,510},
		Point2f{180,510},
		Point2f{180,540},
		Point2f{150,540},
		Point2f{150,510}
	};
	std::vector<Point2f> m_Walls24{
		Point2f{0,0},
		Point2f{0,780},
		Point2f{930,780},
		Point2f{930,0},
		Point2f{0,0}
	};
	m_Walls.push_back(m_Walls1);
	m_Walls.push_back(m_Walls2);
	m_Walls.push_back(m_Walls3);
	m_Walls.push_back(m_Walls4);
	m_Walls.push_back(m_Walls5);
	m_Walls.push_back(m_Walls6);
	m_Walls.push_back(m_Walls7);
	m_Walls.push_back(m_Walls8);
	m_Walls.push_back(m_Walls9);
	m_Walls.push_back(m_Walls10);
	m_Walls.push_back(m_Walls11);
	m_Walls.push_back(m_Walls12);
	m_Walls.push_back(m_Walls13);
	m_Walls.push_back(m_Walls14);
	m_Walls.push_back(m_Walls15);
	m_Walls.push_back(m_Walls16);
	m_Walls.push_back(m_Walls17);
	m_Walls.push_back(m_Walls18);
	m_Walls.push_back(m_Walls19);
	m_Walls.push_back(m_Walls20);
	m_Walls.push_back(m_Walls21);
	m_Walls.push_back(m_Walls22);
	m_Walls.push_back(m_Walls23);
	m_Walls.push_back(m_Walls24);
}

void Game::InitializeChests()
{
	m_Chests.push_back(new Chest{ Point2f(510,600), true, 1, false, Color4f(0.23f,0.23f,0.23f,1.f), "Gray"});
	m_Chests.push_back(new Chest{ Point2f(120,600), true, 2, false, Color4f(0.50f,0.f,0.50f,1.f), "Purple"});
	m_Chests.push_back(new Chest{ Point2f(67,607), true, 3, false, Color4f(0.f, 0.f, 1.f, 1.f), "Blue" });
	m_Chests.push_back(new Chest{ Point2f(127,427), false});
	m_Chests.push_back(new Chest{ Point2f(127,332), true, 1, false, Color4f(1.f, 1.f, 0.f, 1.f), "Yellow"});
	m_Chests.push_back(new Chest{ Point2f(668,231), true, 1, false, Color4f(0.f, 1.f, 0.f, 1.f), "Green" });
	m_Chests.push_back(new Chest{ Point2f(170,97), true, 1, false, Color4f(1.f, 0.41f, 0.70f, 1.f), "Pink"});
	m_Chests.push_back(new Chest{ Point2f(603,301), false});
	m_Chests.push_back(new Chest{ Point2f(600,427), false});
	m_Chests.push_back(new Chest{ Point2f(666,427), false});
	m_Chests.push_back(new Chest{ Point2f(666,302), false});
	m_Chests.push_back(new Chest{ Point2f(724,301), true, 1, false, Color4f(1.f, 0.f, 0.f, 1.f), "Red"});
	m_Chests.push_back(new Chest{ Point2f(724,359), false});
}

void Game::InitializeDoors()
{
	m_Doors.push_back(new Door{ Rectf(600,660,30,30), Color4f(0.23f,0.23f,0.23f,1.f), "Gray"});
	m_Doors.push_back(new Door{ Rectf(420,570,60,30), Color4f(0.50f,0.f,0.50f,1.f), "Purple" });
	m_Doors.push_back(new Door{ Rectf(420,510,60,30), Color4f(0.50f,0.f,0.50f,1.f), "Purple" });
	m_Doors.push_back(new Door{ Rectf(720,450,30,30), Color4f(1.f, 0.f, 0.f, 1.f), "Red" });
	m_Doors.push_back(new Door{ Rectf(285,120,30,30), Color4f(0.f, 0.f, 1.f, 1.f), "Blue"});
	m_Doors.push_back(new Door{ Rectf(645,120,30,30), Color4f(0.f, 1.f, 0.f, 1.f), "Green"});
	m_Doors.push_back(new Door{ Rectf(900,120,30,30), Color4f(0.f, 1.f, 0.f, 1.f), "Green"});
	m_Doors.push_back(new Door{ Rectf(570,360,30,30), Color4f(1.f,1.f,0.f,1.f), "Yellow" });
	m_Doors.push_back(new Door{ Rectf(390,30,30,30), Color4f(1.f, 0.41f, 0.70f, 1.f), "Pink" });
}

void Game::InitializeSnipers()
{
	m_Snipers.push_back(new Snipers{ Point2f(900, 30) });
	m_Snipers.push_back(new Snipers{ Point2f(900, 750) });
	m_Snipers.push_back(new Snipers{ Point2f(30, 30) });
}

void Game::InitializePolices()
{
	m_Polices.push_back(new Police{ Point2f(180,540), Point2f(120,540), 60.f, 15.f,0, false, true, false, "left" });
	m_Polices.push_back(new Police{ Point2f(120,540), Point2f(120,480), 60.f, 15.f,0, false, true, false, "down" });
	m_Polices.push_back(new Police{ Point2f(120,480), Point2f(180,480), 60.f, 15.f,0, false, true,false, "right" });
	m_Polices.push_back(new Police{ Point2f(180,480), Point2f(180,540), 60.f, 15.f,0, false, true,false, "up" });
	m_Polices.push_back(new Police{ Point2f(105,360), Point2f(135,360), 30.f,15.f,0, false, true,false, "right" });
	m_Polices.push_back(new Police{ Point2f(150,270), Point2f(90,270), 60.f, 15.f,0, false, true,false, "left" });
	m_Polices.push_back(new Police{ Point2f(90,270), Point2f(90,210), 60.f, 15.f,0, false, true,false, "down" });
	m_Polices.push_back(new Police{ Point2f(90,210), Point2f(150,210), 60.f, 15.f,0, false, true,false, "right" });
	m_Polices.push_back(new Police{ Point2f(150,210), Point2f(150,270), 60.f, 15.f,0, false, true,false, "up" });
	m_Polices.push_back(new Police{ Point2f(615,330), Point2f(675,330), 60.f, 30.f,0, false, true,false, "right" });
	m_Polices.push_back(new Police{ Point2f(390,210),  Point2f(390,420), 180.f, 45.f,0, false, false,true, "up" });
	m_Polices.push_back(new Police{ Point2f(480,420), Point2f(480,210), 180.f, 45.f,0, false, false,true, "down" });
	m_Polices.push_back(new Police{ Point2f(345,75), Point2f(240,75), 105.f, 45.f,0, false, false,true, "left" });
	m_Polices.push_back(new Police{ Point2f(240,15), Point2f(345,15), 105.f, 45.f,0, false, false,true, "right" });
	m_Polices.push_back(new Police{ Point2f(660,90), Point2f(510,90), 150.f, 30.f,0, false, false,true, "left" });
	m_Polices.push_back(new Police{ Point2f(510,0), Point2f(690,0), 180.f, 30.f,0, false, false,true, "right" });
	m_Polices.push_back(new Police{ Point2f(240,300), Point2f(0,0), 0.f, 2.f,3, true, false,false, "left" });
	m_Polices.push_back(new Police{ Point2f(300,450), Point2f(0,0), 0.f, 2.f,3, true, false,false, "right" });
	m_Polices.push_back(new Police{ Point2f(810,150), Point2f(0,0), 0.f, 2.f,2, true, false,false, "up" });
	m_Polices.push_back(new Police{ Point2f(840,180), Point2f(0,0), 0.f, 2.f,2, true, false,false, "up" });
	m_Polices.push_back(new Police{ Point2f(60,690), Point2f(0,0), 0.f, 2.f,2, true, false,false, "up" });
	m_Polices.push_back(new Police{ Point2f(600,210), Point2f(630,210), 30.f, 15.f,0, false, true,false, "right" });
	m_Polices.push_back(new Police{ Point2f(780,300),  Point2f(780,480), 180.f, 45.f,0, false, false,true, "up" });
	m_Polices.push_back(new Police{ Point2f(840,480), Point2f(840,300), 180.f, 45.f,0, false, false,true, "down" });
}

void Game::DrawWalls() const
{
	SetColor(Color4f(0.f, 0.f, 0.f, 1.f));
	FillRect(390, 0, 30, 30);
	FillRect(390, 60, 30, 150);
	FillRect(360, 120, 30, 180);
	FillRect(330, 120, 30, 90);
	FillRect(315, 120, 15, 30);
	FillRect(90, 180, 240, 30);
	FillRect(120, 240, 30, 30);
	FillRect(30, 120, 255, 30);
	FillRect(30, 150, 30, 480);
	FillRect(60, 240, 30, 135);
	FillRect(60, 405, 30, 75);
	FillRect(90, 300, 30, 60);
	FillRect(120, 300, 30, 30);
	FillRect(150, 300, 30, 60);
	FillRect(180, 240, 30, 135);
	FillRect(210, 240, 90, 30);
	FillRect(300, 240, 30, 210);
	FillRect(90, 420, 30, 60);
	FillRect(120, 450, 30, 30);
	FillRect(150, 420, 30, 60);
	FillRect(180, 405, 30, 75);
	FillRect(210, 450, 30, 90);
	FillRect(240, 330, 30, 210);
	FillRect(30, 630, 60, 30);
	FillRect(90, 510, 30, 240);
	FillRect(120, 570, 300, 30);
	FillRect(120, 720, 690, 30);
	FillRect(780, 570, 30, 150);
	FillRect(480, 570, 330, 30);
	FillRect(120, 660, 90, 30);
	FillRect(240, 600, 30, 90);
	FillRect(300, 660, 90, 30);
	FillRect(390, 600, 30, 90);
	FillRect(480, 600, 30, 90);
	FillRect(510, 660, 90, 30);
	FillRect(630, 600, 30, 90);
	FillRect(690, 660, 90, 30);
	FillRect(810, 570, 90, 90);
	FillRect(870, 120, 30, 450);
	FillRect(30, 660, 60, 30);
	FillRect(480, 0, 30, 120);
	FillRect(480, 120, 165, 30);
	FillRect(675, 120, 225, 30);
	FillRect(270, 510, 150, 30);
	FillRect(360, 360, 30, 150);
	FillRect(390, 450, 30, 60);
	FillRect(420, 240, 60, 60);
	FillRect(420, 360, 60, 60);
	FillRect(480, 510, 360, 30);
	FillRect(480, 450, 60, 30);
	FillRect(480, 180, 90, 30);
	FillRect(510, 210, 30, 240);
	FillRect(600, 150, 30, 60);
	FillRect(630, 180, 60, 30);
	FillRect(810, 420, 30, 60);
	FillRect(810, 330, 30, 60);
	FillRect(750, 300, 30, 210);
	FillRect(570, 270, 270, 30);
	FillRect(690, 180, 60, 90);
	FillRect(570, 300, 30, 60);
	FillRect(570, 390, 30, 120);
	FillRect(600, 450, 120, 30);
	FillRect(840, 150, 30, 30);
	FillRect(750, 240, 30, 30);
	FillRect(780, 180, 15, 30);
	FillRect(810, 228, 30, 15);
	FillRect(420, 120, 60, 30);
	FillRect(150, 510, 30, 30);
	DrawRect(0.f, 0.f, 930.f, 780.f);
	SetColor(Color4f(0.f, 0.39f, 0.f, 1.f));
	FillRect(30, 90, 135, 30);
	FillRect(195, 0, 30, 120);
	FillRect(135, 30, 30, 60);
	FillRect(90, 30, 45, 30);
	FillRect(270, 45, 75, 30);
	FillRect(555, 45, 165, 30);
	FillRect(690, 75, 30, 45);
	FillRect(540, 75, 60, 15);
	FillRect(540, 30, 90, 15);
	FillRect(630, 75, 60, 15);
	FillRect(660, 30, 60, 15);
	FillRect(810, 720, 30, 30);
	FillRect(870, 660, 30, 30);
	FillRect(810, 675, 15, 45);
	FillRect(810, 660, 60, 15);
	SetColor(Color4f(0.34f, 0.22f, 0.15f, 1.f));
	FillRect(0, 0, 60, 60);
	FillRect(30, 720, 30, 30);
	FillRect(870, 0, 60, 60);
	FillRect(870, 720, 60, 60);
}

void Game::DrawChests() const
{
	for (int chest{}; chest < m_Chests.size(); ++chest) {
		m_Chests.at(chest)->Draw();
	}
}

void Game::DrawDoors() const
{
	for (int door{}; door < m_Doors.size(); ++door) {
		m_Doors.at(door)->Draw();
	}
}

void Game::DrawSnipers() const
{
	for (int sniper{}; sniper < m_Snipers.size(); ++sniper) {
		m_Snipers.at(sniper)->Draw();
	}
}

void Game::DrawPolices() const
{
	for (int police{}; police < m_Polices.size(); ++police) {
		m_Polices.at(police)->Draw();
	}
}

void Game::DrawSquares() const
{
	utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));
	for (int i{}; i < 31; ++i) {
		utils::DrawLine(Point2f(30 * i, 0), Point2f(30 * i, 780), 1.f);
	}
	for (int i{}; i < 26; ++i) {
		utils::DrawLine(Point2f(0, 30 * i), Point2f(1080, 30 * i), 1.f);
	}
	for (int vectors{}; vectors < m_Walls.size(); ++vectors) {
		for (int point{}; point < m_Walls.at(vectors).size() - 1; ++point) {
			DrawLine(m_Walls.at(vectors).at(point), m_Walls.at(vectors).at(point + 1));
		}
	}
}

void Game::DrawVictory() const
{
	utils::SetColor(Color4f(1.f, 1.f, 0.f, 1.f));
	DrawRect(m_Victory);
}

void Game::DeleteAll()
{
	for (int i{}; i < m_Chests.size(); ++i)
	{
		delete m_Chests.at(i);
	}
	m_Chests.clear();
	for (int i{}; i < m_Doors.size(); ++i)
	{
		delete m_Doors.at(i);
	}
	m_Doors.clear();
	for (int i{}; i < m_Snipers.size(); ++i)
	{
		delete m_Snipers.at(i);
	}
	m_Snipers.clear();
	for (int i{}; i < m_Polices.size(); ++i)
	{
		delete m_Polices.at(i);
	}
	m_Polices.clear();
	delete m_Player;
	m_Player = nullptr;
	delete m_pSCamera;
	m_pSCamera = nullptr;
	delete m_pInventory;
	m_pInventory = nullptr;
	delete m_Laser1;
	m_Laser1 = nullptr;
	delete m_Laser2;
	m_Laser2 = nullptr;
}

void Game::Reset()
{
	DeleteAll();
	InitializeAll();
}
