
#include <ShaderCompiler/Core/Util.hpp>

#include <codecvt>
#include <locale>

namespace Util {
    [[nodiscard]] std::wstring ConvertToWString(const String& _strConvert) {
        return std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().from_bytes(_strConvert);
    }

	[[nodiscard]] String ConvertFromWString(const std::wstring& _strConvert) {
		return std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().to_bytes(_strConvert);
	}
}
