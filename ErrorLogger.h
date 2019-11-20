#pragma once
#include <Windows.h>
#include <string>
#include "StringConverter.h"

class ErrorLogger
{
public:
	static void Log(std::string);
	static void Log(HRESULT hr, std::string);
};

