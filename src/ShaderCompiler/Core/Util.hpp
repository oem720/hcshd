#pragma once

#include <ShaderCompiler/Core/Common.hpp>

namespace Util {
	[[nodiscard]] std::wstring ConvertToWString(const String& _strConvert);

	[[nodiscard]] String ConvertFromWString(const std::wstring& _strConvert);
}