//------------------------------------------------------------------------------
// ViroVision.cpp
//------------------------------------------------------------------------------

#define _WIN32_WINNT 0x0500

#include "ViroVision.h"
#include "ViroVisionFilters.h"

using namespace ViroVision;
using namespace ViroVisionFilters;

#include "main.h"

HWND m_hWnd = NULL;
CViroVisionBase *g_pViroVision = NULL;


LRESULT CALLBACK WndMainProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_VIROVISION_NOTIFY:
			g_pViroVision->HandleGraphEvent();
            break;

        case WM_SIZE:
            g_pViroVision->ResizeVideoWindow();
            break;

        case WM_CLOSE:            
            // Hide the main window while the graph is destroyed
            ShowWindow(m_hWnd, SW_HIDE);
            delete g_pViroVision;  // Stop capturing and release interfaces
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    // Pass this message to the video window for notification of system changes
    //if (m_pVideoWindow)
      //  m_pVideoWindow->NotifyOwnerMessage((LONG_PTR) hwnd, message, wParam, lParam);

    return DefWindowProc (hwnd , message, wParam, lParam);
}


int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hInstP, LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg={0};
    WNDCLASS wc;

	::CoInitializeEx(NULL, COINIT_MULTITHREADED);

    // Register the window class
    ZeroMemory(&wc, sizeof wc);
    wc.lpfnWndProc   = WndMainProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASSNAME;
    wc.lpszMenuName  = NULL;
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon         = NULL;
    if(!RegisterClass(&wc))
    {
        exit(1);
    }

    // Create the main window.  The WS_CLIPCHILDREN style is required.
    m_hWnd = CreateWindow(CLASSNAME, APPLICATIONNAME,
                         WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_CLIPCHILDREN,
                         CW_USEDEFAULT, CW_USEDEFAULT,
                         DEFAULT_VIDEO_WIDTH, DEFAULT_VIDEO_HEIGHT,
                         0, 0, hInstance, 0);

    if(m_hWnd)
    {
		g_pViroVision = new CViroVisionBase();
		CViroVisionFilters *pvvFilters = new CViroVisionFilters();
		unsigned int filterParam = 1;

		if (SUCCEEDED(g_pViroVision->FilterVideo(m_hWnd,
			(LRESULT CALLBACK) CViroVisionFilters::MotionDetectionFilter,
				(LPVOID) &filterParam, pvvFilters)))
		{
			ShowWindow(m_hWnd, nCmdShow);
		}
		else
		{
			delete g_pViroVision;
			DestroyWindow(m_hWnd);
		}

        // Main message loop
        while(GetMessage(&msg,NULL,0,0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



