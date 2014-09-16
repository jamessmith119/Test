#include<Windows.h>
#include "GraphicsEngine.h"
#include "SimpleTriangleMesh.h"

HINSTANCE g_hInst = nullptr;
HWND g_hWnd = nullptr;

//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HRESULT InitWindow(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previousInstance, LPSTR cmdLine, int cmdShow)
{
	if(FAILED( InitWindow( instance, cmdShow )))
	{
        return 0;
	}

	GraphicsEngine graphicsEngine;
	if(FAILED(graphicsEngine.InitializeDevice(g_hWnd)))
	{
		MessageBox(NULL, L"Direct3D Initialization Failed", L"Error", MB_ICONERROR);
		return 0;
	}

	graphicsEngine.GetDefaultGraphicsAdapter();
	
	SimpleTriangleMesh triangle(graphicsEngine.GetGraphicsDevice());
	if(FAILED(triangle.Initialize()))
	{
		MessageBox(NULL, L"Could not create the triangle mesh.", L"Error", MB_ICONERROR);
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
			graphicsEngine.ClearScene();

			triangle.Render(graphicsEngine.GetGraphicsDeviceContext());
			
            graphicsEngine.Render();
        }
    }

	return (int)msg.wParam;
}

//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow)
{
    // Register class
    WNDCLASSEX windowClass;
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = WndProc;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = hInstance;
    windowClass.hIcon = LoadIcon(hInstance, ( LPCTSTR )IDI_APPLICATION);
    windowClass.hCursor = LoadCursor( nullptr, IDC_ARROW );
    windowClass.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
    windowClass.lpszMenuName = nullptr;
    windowClass.lpszClassName = L"MainWindowClass";
    windowClass.hIconSm = LoadIcon(windowClass.hInstance, ( LPCTSTR )IDI_APPLICATION);

    if(!RegisterClassEx(&windowClass))
	{
        return E_FAIL;
	}

    // Create window
    g_hInst = hInstance;
    RECT rc = { 0, 0, 800, 600 };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    g_hWnd = CreateWindow(L"MainWindowClass", L"Main Window", WS_OVERLAPPEDWINDOW,
                           CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, 
						   nullptr, nullptr, hInstance, nullptr);
    if(!g_hWnd)
	{
        return E_FAIL;
	}

    ShowWindow(g_hWnd, nCmdShow);

    return S_OK;
}

//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
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