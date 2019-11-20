#include <Windows.h>
#include "Engine.h"

#pragma region LinkingLibraries
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "DirectXTK.lib")
#pragma endregion

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {

	Engine engine;
	engine.Initialize(hInstance, "My Window", "My Window Class", 800, 600);

	while (engine.ProcessMessages())
	{
		engine.Update();
	}

	return 0;
}

	