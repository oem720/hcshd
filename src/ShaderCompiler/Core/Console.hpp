#pragma once

#include <ShaderCompiler/Core/Common.hpp>

enum ConsoleColor : uint8 {
	WHITE = 37,
	BLACK = 30,
	RED = 31,
	GREEN = 32,
	YELLOW = 33,
	BLUE = 34,
	MAGENTA = 35
};

#undef ERROR
enum MessageType : uint8 {
	LOG,
	INFO,
	SUCCESS,
	FAIL,
	WARNING,
	ERROR
};

class Console {
private:
#if defined(_WIN32) || defined(_WIN64)
	static bool bIsWindowsConsoleInitialized;

	static bool InitializeWindowsConsole();
#endif

	static String GetMessagePrefix(MessageType _mtType);

	static String ColorText(const String& _strText, ConsoleColor _ccColor);

	static void PrintDebugMessage(const String& _strMessage, MessageType _mtType);

public:
	static void Print(const String& _strMessage, ConsoleColor _ccColor = WHITE);

	static void PrintLine(const String & _strMessage, ConsoleColor _ccColor = WHITE);

	static void DebugLog(const String& _strMessage) { PrintDebugMessage(_strMessage, LOG); }

	static void DebugInfo(const String& _strMessage) { PrintDebugMessage(_strMessage, INFO); }

	static void DebugSuccess(const String& _strMessage) { PrintDebugMessage(_strMessage, SUCCESS); }

	static void DebugFail(const String& _strMessage) { PrintDebugMessage(_strMessage, FAIL); }

	static void DebugWarn(const String& _strMessage) { PrintDebugMessage(_strMessage, WARNING); }

	static void DebugError(const String& _strMessage) { PrintDebugMessage(_strMessage, ERROR); }
};