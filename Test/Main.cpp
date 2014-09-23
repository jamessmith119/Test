#include<Windows.h>
#include "GameWindow.h"
#include "Game.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previousInstance, LPSTR cmdLine, int cmdShow)
{
	//Create a window for the game.
	GameWindow gameWindow;
	if(FAILED(gameWindow.InitializeWindow(instance, cmdShow)))
	{
		MessageBox(NULL, L"Could not create a game window.", L"Error", MB_ICONERROR);
		return 0;
	}

	//Start the game engine.
	Game game(gameWindow.GetGameWindow());
	if(FAILED(game.Initialize()))
	{
		MessageBox(NULL, L"Game Initialization Failed", L"Error", MB_ICONERROR);
		return 0;
	}

	// Main message loop
    MSG msg = {0};
    while( WM_QUIT != msg.message )
    {
        if( PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
			//Run the game logic.
			game.Run();
        }
    }

	//Shut the game down.
	game.Shutdown();

	return 0;
}
