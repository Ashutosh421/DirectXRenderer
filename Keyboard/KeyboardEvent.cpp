#include "KeyboardEvent.h"

KeyboardEvent::KeyboardEvent() :type(EventType::Invalid), key(0) {}

KeyboardEvent::KeyboardEvent(EventType eType, const unsigned char key) {
	this->type = eType;
	this->key = key;
}

bool KeyboardEvent::IsPress() const {
	return this->type == EventType::Press;
}

bool KeyboardEvent::IsRelease() const {
	return this->type == EventType::Release;
}

bool KeyboardEvent::IsValid() const {
	return this->type != EventType::Invalid;
}

unsigned char KeyboardEvent::GetKeyCode() const {
	return this->key;
}