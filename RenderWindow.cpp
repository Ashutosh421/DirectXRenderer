#include "WindowContainer.h"

bool RenderWindow::Initialize(WindowContainer* pWindowContainer, HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height)
{	
	this->hInstance = hInstance;
	this->window_title = window_title;
	this->window_title_wide = StringConverter::StringToWide(this->window_title);

	this->window_class = window_class;
	this->window_class_wide = StringConverter::StringToWide(this->window_class);

	this->width = width;
	this->height = height;

	this->RegisterWindowClass();

	this->handle = CreateWindowEx(0,
		this->window_class_wide.c_str(),  // Window Class
		this->window_title_wide.c_str(), // Window Title
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, // Windows Style
		0,  // Pos X
		0,  // Pos Y
		this->width, // Width of window
		this->height, // Height of window
		NULL,	// Handle to parent window
		NULL,   // Handle to menu
		this->hInstance, // Handle to HInstance
		pWindowContainer // Parameter to create window
	);

	if (this->handle == NULL) {
		ErrorLogger::Log(GetLastError(), "CreateWindowEx failed to create window: " + this->window_title);
		return false;
	}

	//Show Window to screen and focus
	ShowWindow(this->handle, SW_SHOW);
	SetForegroundWindow(this->handle);
	SetFocus(this->handle);

	return true;
}

bool RenderWindow::ProcessMessages() {

	// Handle to the window message
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	if (PeekMessage(&msg, this->handle, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg); //Translate message to from virtual key messages to character messages
		DispatchMessage(&msg);	//Dispatch message to our Window Proc method
	}

	// Check if the window is closed
	if (msg.message == WM_NULL) {
		if (!IsWindow(this->handle)) {
			this->handle = NULL;
			UnregisterClass(this->window_class_wide.c_str(), this->hInstance);
			return false;
		}
	}

	return true;
}

LRESULT CALLBACK HandleMsgRedirect(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg)
	{
	case WM_CLOSE: {
		DestroyWindow(hwnd);
		return 0;
	}
	default:
		WindowContainer* const pWindow = reinterpret_cast<WindowContainer*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
	}
}

LRESULT CALLBACK HandleMsgSetup(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg)
	{
		case WM_NCCREATE: {
			OutputDebugStringA("The window was created");

			const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
			WindowContainer* pWindow = reinterpret_cast<WindowContainer*>(pCreate->lpCreateParams);
			if (pWindow == nullptr) {
				ErrorLogger::Log("Critical Error: Pointer to window container is null during WN_NCCREATE");
			}

			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
			SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMsgRedirect));

			return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
		}
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

void RenderWindow::RegisterWindowClass() {
	WNDCLASSEX wc; //Our Window Class (This has to be filled before our window can be created) See: https://msdn.microsoft.com/en-us/library/windows/desktop/ms633577(v=vs.85).aspx
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; //Flags [Redraw on width/height change from resize/movement] See: https://msdn.microsoft.com/en-us/library/windows/desktop/ff729176(v=vs.85).aspx
	wc.lpfnWndProc = HandleMsgSetup; //Pointer to Window Proc function for handling messages from this window
	wc.cbClsExtra = 0; //# of extra bytes to allocate following the window-class structure. We are not currently using this.
	wc.cbWndExtra = 0; //# of extra bytes to allocate following the window instance. We are not currently using this.
	wc.hInstance = this->hInstance; //Handle to the instance that contains the Window Procedure
	wc.hIcon = NULL;   //Handle to the class icon. Must be a handle to an icon resource. We are not currently assigning an icon, so this is null.
	wc.hIconSm = NULL; //Handle to small icon for this class. We are not currently assigning an icon, so this is null.
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); //Default Cursor - If we leave this null, we have to explicitly set the cursor's shape each time it enters the window.
	wc.hbrBackground = NULL; //Handle to the class background brush for the window's background color - we will leave this blank for now and later set this to black. For stock brushes, see: https://msdn.microsoft.com/en-us/library/windows/desktop/dd144925(v=vs.85).aspx
	wc.lpszMenuName = NULL; //Pointer to a null terminated character string for the menu. We are not using a menu yet, so this will be NULL.
	wc.lpszClassName = this->window_class_wide.c_str(); //Pointer to null terminated string of our class name for this window.
	wc.cbSize = sizeof(WNDCLASSEX); //Need to fill in the size of our struct for cbSize

	RegisterClassEx(&wc);
}

RenderWindow::~RenderWindow() {
	if (this->handle != NULL) {
		UnregisterClass(this->window_class_wide.c_str(), this->hInstance);
		DestroyWindow(this->handle);
	}
}
