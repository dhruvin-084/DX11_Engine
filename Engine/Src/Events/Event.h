#pragma once

#include<string>
#include<functional>

enum class EventType {
	None = 0,
	WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
	AppTick, AppUpdate, AppRender,
	KeyPressed, KeyReleased, KeyChar,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

class Event {
public:
	bool Handled = false;

	virtual EventType GetEventType() = 0;
	virtual const char* GetEventName() = 0;
	virtual std::string ToString() { return GetEventName(); }
};

class EventDispatcher {
public:
	EventDispatcher(Event& event)
		: m_Event(event) {}

	template<typename T>
	bool Dispatch(std::function<bool(T&)> func) {

		if (m_Event.GetEventType() == T::GetStaticType()) {
			m_Event.Handled = func(*(T*)&m_Event);
			return true;
		}
		return false;
	}

private:
	Event& m_Event;
};
