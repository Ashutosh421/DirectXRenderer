#pragma once
#include "KeyboardEvent.h"
#include <queue>

class KeyboardClass {

public:
	KeyboardClass();
	bool KeyIsPressed(const unsigned char);
	bool KeyBufferIsEmpty();
	bool CharBufferIsEmpty();
	KeyboardEvent ReadKey();
	unsigned char ReadChar();
	void OnKeyPressed(unsigned char);
	void OnKeyReleased(unsigned char);
	void OnChar(const unsigned char);
	void EnableAutoRepeatKeys();
	void DisableAutoRepeatKeys();
	void EnableAutoRepeatChars();
	void DisableAutoRepeatChars();
	bool IsKeysAutoRepeat();
	bool IsCharsAutoRepeat();

private:
	bool autoRepeatKeys = false;
	bool autoRepeatChars = false;
	bool keyStates[256];
	std::queue<KeyboardEvent> keyBuffer;
	std::queue<unsigned char> charBuffer;
};