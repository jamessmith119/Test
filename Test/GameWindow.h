#ifndef __GAMEWINDOWHEADER__
#define __GAMEWINDOWHEADER__

#include<Windows.h>

class GameWindow
{
	private:
		HWND gameWindow;
		HINSTANCE gameInstance;
	
	public:
		//===================================================================================
		// Register window class and create the game window.
		//===================================================================================
		HRESULT InitializeWindow(HINSTANCE, int);
		
		//===================================================================================
		// Gets the current game window.
		//===================================================================================
		HWND GetGameWindow();

		//===================================================================================
		// Gets the current application instance assigned to this window.
		//===================================================================================
		HINSTANCE GetApplicationInstance();		
};

#endif