#include "GameWindow.h"

LRESULT CALLBACK WindowMessageProc(HWND, UINT, WPARAM, LPARAM);

HRESULT GameWindow::InitializeWindow(HINSTANCE hInstance, int nCmdShow)
{
    // Register class
    WNDCLASSEX windowClass;
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = WindowMessageProc;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = hInstance;
    windowClass.hIcon = nullptr;
    windowClass.hCursor = LoadCursor( nullptr, IDC_ARROW );
    windowClass.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
    windowClass.lpszMenuName = nullptr;
    windowClass.lpszClassName = L"MainWindowClass";
    windowClass.hIconSm = nullptr;

    if(!RegisterClassEx(&windowClass))
	{
        return E_FAIL;
	}

    // Create window
    gameInstance = hInstance;
    RECT rc = { 0, 0, 800, 600 };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    gameWindow = CreateWindow(L"MainWindowClass", L"Main Window", WS_OVERLAPPEDWINDOW,
                           CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, 
						   nullptr, nullptr, hInstance, nullptr);
    if(!gameWindow)
	{
        return E_FAIL;
	}

    ShowWindow(gameWindow, nCmdShow);

    return S_OK;
}

HWND GameWindow::GetGameWindow()
{
	return gameWindow;
}

HINSTANCE GameWindow::GetApplicationInstance()
{
	return gameInstance;
}

//===================================================================================
// Called every time the application receives a message
//===================================================================================
LRESULT CALLBACK WindowMessageProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch( message )
    {
        case WM_PAINT:
            hdc = BeginPaint( hWnd, &ps );
            EndPaint( hWnd, &ps );
            break;

        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;

        default:
            return DefWindowProc( hWnd, message, wParam, lParam );
    }

    return 0;
}