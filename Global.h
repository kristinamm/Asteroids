#include <iostream>
#include <string>
#include "ConsoleGaming.h"
//this is where the global variables should be
namespace Global
{
	int g_level = 1;
	std::string g_playerName = "";
	bool isSoundOn = true;
	int shipType = 1;
	const char upKey = 'w';
	const char downKey = 's';
	const char leftKey = 'a';
	const char rightKey = 'd';
	const char fireKey = ' ';
	ConsoleColor shipColor = ConsoleColors::White;
}