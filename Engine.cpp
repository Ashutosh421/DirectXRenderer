#include "Engine.h"

bool Engine::Initialize(HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height) {
	return this->renderWindow.Initialize(this, hInstance, window_title, window_class, width, height);
}

bool Engine::ProcessMessages() {
	return this->renderWindow.ProcessMessages();
}

void Engine::Update() {
	while (!this->keyboardClass.CharBufferIsEmpty()) {
		unsigned char ch = this->keyboardClass.ReadChar();
		std::string msg = "Char: ";
		msg += ch;
		msg += "\n";
		OutputDebugStringA(msg.c_str());
	}

	while (!this->keyboardClass.KeyBufferIsEmpty()) {
		KeyboardEvent keyEvent = this->keyboardClass.ReadKey();
		if (keyEvent.IsValid()) {
			std::string msg = "KeyEvent: ";
			if (keyEvent.IsPress()) {
				msg += "press: ";
			}
			else if (keyEvent.IsRelease()) {
				msg += "release: ";
			}
			msg += keyEvent.GetKeyCode();
			msg += "\n";
			OutputDebugStringA(msg.c_str());
		}	
	}
}