#include"GraphicsException.h"
#include<sstream>

GraphicsException::GraphicsException(int line, const char* file, HRESULT hr) noexcept
	: Exception(line, file), hr(hr)
{}

const char* GraphicsException::what() const noexcept
{
	std::ostringstream oss;
	oss << "[Error Code] " << std::hex << GetErrorCode() << std::endl
		<< "[Description] " << GetErrorString() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* GraphicsException::GetType() const noexcept
{
	return "Graphics Excetion";
}

std::string GraphicsException::TranslateErrorCode(HRESULT hr) noexcept
{
	char* pMsgBuf = nullptr;
	DWORD nMsgLen = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&pMsgBuf), 0, nullptr
	);
	if (nMsgLen == 0) {
		return "Unidentified error code";
	}
	std::string errorString = pMsgBuf;
	LocalFree(pMsgBuf);
	return errorString;
}

HRESULT GraphicsException::GetErrorCode() const noexcept
{
	return hr;
}

std::string GraphicsException::GetErrorString() const noexcept
{
	return TranslateErrorCode(hr);
}


