
#include <ShaderCompiler/Core/Console.hpp>

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>

bool Console::bIsWindowsConsoleInitialized = false;

bool Console::InitializeWindowsConsole() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);

	if (hOut == INVALID_HANDLE_VALUE || hIn == INVALID_HANDLE_VALUE) {
		return false;
	}

	DWORD dwOutCurr = 0;
	DWORD dwInCurr = 0;

	if (!GetConsoleMode(hOut, &dwOutCurr) || !GetConsoleMode(hIn, &dwInCurr)) {
		return false;
	}

	DWORD dwOutRequested = ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;

	DWORD dwOut = dwOutCurr | dwOutRequested;
	DWORD dwIn = dwInCurr | ENABLE_VIRTUAL_TERMINAL_INPUT;

	if (!SetConsoleMode(hOut, dwOut)) {
		dwOutRequested = ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		dwOut = dwOutCurr | dwOutRequested;

		if (!SetConsoleMode(hOut, dwOut)) {
			return false;
		}
	}

	if (!SetConsoleMode(hIn, dwIn)) {
		return false;
	}

	return true;
}
#endif

void Console::Print(const String& _strMessage, ConsoleColor _ccColor) {
#if defined(_WIN32) || defined(_WIN64)
	if (!bIsWindowsConsoleInitialized) {
		bIsWindowsConsoleInitialized = InitializeWindowsConsole();
	}
#endif

	std::cout << ColorText(_strMessage, _ccColor);
}

void Console::PrintLine(const String& _strMessage, ConsoleColor _ccColor) {
#if defined(_WIN32) || defined(_WIN64)
	if (!bIsWindowsConsoleInitialized) {
		bIsWindowsConsoleInitialized = InitializeWindowsConsole();
	}
#endif

	std::cout << ColorText(_strMessage, _ccColor) << "\r\n";

	std::cout.flush();
}

void Console::PrintDebugMessage(const String& _strMessage, MessageType _mtType) {
#if defined(_WIN32) || defined(_WIN64)
	if (!bIsWindowsConsoleInitialized) {
		bIsWindowsConsoleInitialized = InitializeWindowsConsole();
	}
#endif

	std::cout << GetMessagePrefix(_mtType) << _strMessage << "\r\n";

	std::cout.flush();
}

#undef ERROR
String Console::GetMessagePrefix(MessageType _mtType) {
	String strPrefix;

	switch (_mtType) {
	case LOG: {
		strPrefix = ColorText("LOG", WHITE);
	} break;
	case INFO: {
		strPrefix = ColorText("INFO", BLUE);
	} break;
	case SUCCESS: {
		strPrefix = ColorText("SUCCESS", GREEN);
	} break;
	case FAIL: {
		strPrefix = ColorText("FAIL", RED);
	} break;
	case WARNING: {
		strPrefix = ColorText("WARNING", YELLOW);
	} break;
	case ERROR: {
		strPrefix = ColorText("ERROR", RED);
	} break;
	}

	std::stringstream ssTimeStampedId;

	std::time_t tCurrentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	std::tm* tLocalTime = std::localtime(&tCurrentTime);

	ssTimeStampedId << "[" << strPrefix << "][" << std::this_thread::get_id() << "][" << std::put_time(tLocalTime, "%H:%M:%S") << "] ";

	return ssTimeStampedId.str();
}

String Console::ColorText(const String& _strText, ConsoleColor _ccColor) {
	std::stringstream ssStr;

	ssStr << "\033[" << std::to_string(_ccColor) << "m" << _strText << "\033[0m";

	return ssStr.str();
}
