#pragma once

#include<queue>
#include<bitset>
#include<optional>

#include"Events/Event.h"
#include"Events/KeyboardEvents.h"



class Keyboard {
	friend class Application;
public:
	Keyboard() = default;
	Keyboard(const Keyboard&) = delete;
	Keyboard& operator=(const Keyboard&) = delete;

	// key events
	bool KeyIsPressed(unsigned char keycode) const noexcept;
	bool KeyIsEmpty() const noexcept;
	void FlushKey() noexcept;

	// char events
	std::optional<char> ReadChar() noexcept;
	bool CharIsEmpty() const noexcept;
	void FlushChar() noexcept;

	void Flush() noexcept;

	// autorepeat
	void EnableAutorepeat() noexcept;
	void DisableAutorepeat() noexcept;
	bool AutorepeatIsEnabled() const noexcept;



private:
	void OnKeyPressed(KeyPressedEvent e) noexcept;
	void OnKeyRelesed(KeyReleasedEvent e) noexcept;
	void OnChar(char character) noexcept;
	void CleareState() noexcept;
	
	template<typename T>
	static void TrimBuffer(std::queue<T>& buffer) noexcept;


private:
	static constexpr unsigned int nKeys = 256u;
	static constexpr unsigned int bufferSize = 16u;
	bool autorepeatEnabled = false;
	std::bitset<nKeys> keystates;
	std::queue<KeyEvent> keybuffer;
	std::queue<char> charbuffer;
};

template<typename T>
inline void Keyboard::TrimBuffer(std::queue<T>& buffer) noexcept
{
	while (buffer.size() > bufferSize) {
		buffer.pop();
	}
}
