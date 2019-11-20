#include "KeyboardClass.h"

KeyboardClass::KeyboardClass() {
	for (size_t i = 0; i < 256; i++)
	{
		this->keyStates[i] = false;
 	}
}

bool KeyboardClass::KeyIsPressed(const unsigned char key) {
	return this->keyStates[key];
}

bool KeyboardClass::KeyBufferIsEmpty() {
	return this->keyBuffer.empty();
}

bool KeyboardClass::CharBufferIsEmpty() {
	return this->charBuffer.empty();
}

KeyboardEvent KeyboardClass::ReadKey() {
	if (this->keyBuffer.empty()) {
		return KeyboardEvent();
	}
	else {
		KeyboardEvent e = this->keyBuffer.front();
		this->keyBuffer.pop();
		return e;
	}
}

unsigned char KeyboardClass::ReadChar() {
	if (this->charBuffer.empty()) {
		return 0u;
	}
	else {
		unsigned char key = this->charBuffer.front();
		this->charBuffer.pop();
		return key;
	}
}

void KeyboardClass::OnKeyPressed(unsigned char key) {
	this->keyStates[key] = true;
	this->keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Press, key));
}

void KeyboardClass::OnKeyReleased(unsigned char key) {
	this->keyStates[key] = false;
	this->keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Release, key));
}

void KeyboardClass::OnChar(const unsigned char key) {
	this->charBuffer.push(key);
}

void KeyboardClass::EnableAutoRepeatKeys()
{
	this->autoRepeatKeys = true;
}

void KeyboardClass::DisableAutoRepeatKeys()
{
	this->autoRepeatKeys = false;
}

void KeyboardClass::EnableAutoRepeatChars()
{
	this->autoRepeatChars = true;
}

void KeyboardClass::DisableAutoRepeatChars()
{
	this->autoRepeatChars = false;
}

bool KeyboardClass::IsKeysAutoRepeat()
{
	return this->autoRepeatKeys;
}

bool KeyboardClass::IsCharsAutoRepeat()
{
	return this->autoRepeatChars;
}


