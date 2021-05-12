#pragma once

#include"Exception.h"
#include<Windows.h>

class WindowException : public Exception {
public:
	WindowException(int line, const char* file, HRESULT hr) noexcept;
	const char* what() const noexcept override;
	virtual const char* GetType() const noexcept override;
	static std::string TranslateErrorCode(HRESULT hr) noexcept;
	HRESULT GetErrorCode() const noexcept;
	std::string GetErrorString() const noexcept;



private:
	HRESULT hr;
};

// excetption helper macro;
#define WND_EXCEPT(hr) WindowException(__LINE__, __FILE__, hr)
#define WND_LAST_EXCEPT() WindowException(__LINE__, __FILE__, GetLastError())
