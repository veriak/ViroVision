//------------------------------------------------------------------------------
// ViroVision.h
//------------------------------------------------------------------------------


//
// Function prototypes
//

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hInstP, LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK WndMainProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

//
// Constants
//
#define DEFAULT_VIDEO_WIDTH     800
#define DEFAULT_VIDEO_HEIGHT    600

#define APPLICATIONNAME TEXT("ViroVision\0")
#define CLASSNAME       TEXT("ViroVisionPreviewer\0")
