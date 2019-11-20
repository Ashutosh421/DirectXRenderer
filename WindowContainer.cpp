#include "WindowContainer.h"

LRESULT WindowContainer::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
		case WM_KEYDOWN:
		{
			unsigned char ch = static_cast<unsigned char>(wParam);
			if (this->keyboardClass.IsKeysAutoRepeat()) {
				this->keyboardClass.OnKeyPressed(ch);
			}
			else {
				const bool wasPressed = lParam & 1 << 30;
				if (!wasPressed) {
					this->keyboardClass.OnKeyPressed(ch);
				}
			}
			return 0;
		}
		case WM_KEYUP:
		{
			unsigned char ch = static_cast<unsigned char>(wParam);
			this->keyboardClass.OnKeyReleased(ch);
			return 0;
		}
		case WM_CHAR:
		{
			unsigned char ch = static_cast<unsigned char>(wParam);
			if (this->keyboardClass.IsCharsAutoRepeat()) {
				this->keyboardClass.OnChar(ch);
			} 
			else {
				const bool wasPressed = lParam & 1 << 30;
				if (!wasPressed) {
					this->keyboardClass.OnChar(ch);
				}
			}
			return 0;
		}
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}
