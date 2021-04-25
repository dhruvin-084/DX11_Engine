#include"Keyboard.h"



bool Keyboard::KeyIsPressed(unsigned char keycode) const noexcept
{
	return keystates[keycode];
}

bool Keyboard::KeyIsEmpty() const noexcept
{
	return keybuffer.empty();
}

void Keyboard::FlushKey() noexcept
{
	keybuffer = std::queue<KeyEvent>();
}

std::optional<char> Keyboard::ReadChar() noexcept
{
	if (charbuffer.size() > 0) {
		unsigned char charcode = charbuffer.front();
		charbuffer.pop();
		return charcode;
	}
	return {};
}

bool Keyboard::CharIsEmpty() const noexcept
{
	return charbuffer.empty();
}

void Keyboard::FlushChar() noexcept
{
	charbuffer = std::queue<char>();
}

void Keyboard::Flush() noexcept
{
	FlushKey();
	FlushChar();
}

void Keyboard::EnableAutorepeat() noexcept
{
	autorepeatEnabled = true;
}

void Keyboard::DisableAutorepeat() noexcept
{
	autorepeatEnabled = false;
}

bool Keyboard::AutorepeatIsEnabled() const noexcept
{
	return autorepeatEnabled;
}

void Keyboard::OnKeyPressed(KeyPressedEvent e) noexcept
{
	keystates[e.GetKeyCode()] = true;
	//keybuffer.push(e);
	TrimBuffer(keybuffer);
}

void Keyboard::OnKeyRelesed(KeyReleasedEvent e) noexcept
{
	keystates[e.GetKeyCode()] = false;
	//keybuffer.push(e);
	TrimBuffer(keybuffer);
}

void Keyboard::OnChar(char character) noexcept
{
	charbuffer.push(character);
	TrimBuffer(charbuffer);
}

void Keyboard::CleareState() noexcept
{
	keystates.reset();
}
