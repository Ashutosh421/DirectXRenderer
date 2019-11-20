#pragma once

class KeyboardEvent {

public:
	enum EventType
	{
		Press,
		Release,
		Invalid
	};

	KeyboardEvent();
	KeyboardEvent(EventType, const unsigned char);

	bool IsPress() const;
	bool IsRelease() const;
	bool IsValid() const;
	unsigned char GetKeyCode() const;

private:
	EventType type;
	unsigned char key;
};