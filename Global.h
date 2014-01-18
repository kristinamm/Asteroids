#include <iostream>
#include <string>
#include "ConsoleGaming.h"
//this is where the global variables should be
namespace Global
{
	/* points of the player */
	int playerScore = 0;
	/* 
	1-st, 2-nd and 3-rd place points */

	std::string playerName = "";
	bool isSoundOn = true;
	int shipType = 1;
	char upKey = 'w';
	char downKey = 's';
	char leftKey = 'a';
	char rightKey = 'd';
	char fireKey = ' ';
	int firstPlayerPoints;
	int secondPlayerPoints;
	int thirdPlayerPoints;
	ConsoleColor shipColor = ConsoleColors::White;
}
