#ifndef __GAMEHEADER__
#define __GAMEHEADER__

#include <vector>
#include "GameFiles.h"
#include "GraphicsEngine.h"
#include "Camera.h"

class Game
{
	private:
		void InitializeWindow();

	protected:
		HWND mainGameWindow;
		GraphicsEngine graphicsEngine;
		Camera camera;

		std::vector<BaseObject> gameObjects;

	public:

		//===================================================================================
		// Create a new instance of Game.
		//===================================================================================
		Game(HWND);

		//===================================================================================
		// Initializes the game. 
		// Creates the game systems (graphics, sound, input, etc.) and the game content.
		//===================================================================================
		HRESULT Initialize();

		//===================================================================================
		// Runs the game. This is the main game loop.
		//===================================================================================
		void Run();

		//===================================================================================
		// Shuts down the game and all of its supporting systems.
		void Shutdown();
		//===================================================================================

		//===================================================================================
		// Gets the current game window.
		//===================================================================================
		HWND GetGameWindow();
};

#endif