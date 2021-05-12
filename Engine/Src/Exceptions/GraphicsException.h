#pragma once
#include<Windows.h>

#include"Exception.h"

class GraphicsException : public Exception {
public:
	GraphicsException(int line, const char* file, HRESULT hr) noexcept;
	const char* what() const noexcept override;
	virtual const char* GetType() const noexcept override;
	static std::string TranslateErrorCode(HRESULT hr) noexcept;
	HRESULT GetErrorCode() const noexcept;
	std::string GetErrorString() const noexcept;
private:
	HRESULT hr;
};

#define GFX_THROW_FAILD(expr) {HRESULT hr; if((hr=expr) != S_OK){ throw GraphicsException(__LINE__, __FILE__, hr);}}