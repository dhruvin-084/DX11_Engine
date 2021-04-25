#pragma once

#include"Event.h"
#include<sstream>

class KeyEvent : public Event {
public:
	inline int GetKeyCode() const { return m_KeyCode; }
protected:
	KeyEvent(int keyCode)
		:m_KeyCode(keyCode) {}

	int m_KeyCode;
};

class KeyPressedEvent : public KeyEvent {
public:
	KeyPressedEvent(int keyCode, int repeatCout)
		: KeyEvent(keyCode), m_RepeatCount(repeatCout) {}

	static EventType GetStaticType() { return EventType::KeyPressed; }
	virtual EventType GetEventType() override { return GetStaticType(); }
	virtual const char* GetEventName() override { return "KeyPressed"; }
	int GetRepeatcount() const { return m_RepeatCount; }
	virtual std::string ToString() override {
		std::stringstream ss;
		ss << "KeyPressedEvent: " << m_KeyCode << "(" << m_RepeatCount << " repeats)";
		return ss.str();
	}

private:
	int m_RepeatCount;

};



class KeyReleasedEvent : public KeyEvent {
public:
	KeyReleasedEvent(int keyCode)
		: KeyEvent(keyCode) {}

	static EventType GetStaticType() { return EventType::KeyReleased; }
	virtual EventType GetEventType() override { return GetStaticType(); }
	virtual const char* GetEventName() override { return "KeyReleased"; }
	virtual std::string ToString() override {
		std::stringstream ss;
		ss << "KeyReleasedEvent: " << m_KeyCode;
		return ss.str();
	}
};

class KeyCharEvent : public KeyEvent {
public:
	KeyCharEvent(int keyCode)
		: KeyEvent(keyCode) {}

	static EventType GetStaticType() { return EventType::KeyChar; }
	virtual EventType GetEventType() override { return GetStaticType(); }
	virtual const char* GetEventName() override { return "KeyChar"; }
	virtual std::string ToString() override {
		std::stringstream ss;
		ss << "KeyTypedEvent: " << m_KeyCode;
		return ss.str();
	}
};