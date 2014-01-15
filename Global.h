#include <iostream>
#include <string>
#include "ConsoleGaming.h"
//this is where the global variables should be
namespace Global
{
	int g_level = 1;
	std::string g_playerName = "";
	bool isSoundOn = true;
	char upKey = 'w';
	char downKey = 's';
	char leftKey = 'a';
	char rightKey = 'd';
	char fireKey = ' ';
	ConsoleColor shipColor = ConsoleColors::White;
}