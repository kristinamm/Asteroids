#include <iostream>
#include <vector>
#include <conio.h>
#include <time.h>
#include <iomanip>

#include "configParser.cpp"
#include "ConsoleGaming.h"
#include "Menu.h"
#include "Global.h"

void Menu::Initialize() 
{
	char key;

	system("cls");
	//Displays Options
	std::cout << std::setw(39) << "MAIN MENU"<< std::endl;
	std::cout << std::setw(57) << "Please make your selection"<< std::endl;
	std::cout << "1 - Start game\n";
	std::cout << "2 - Instructions\n";
	std::cout << "3 - Hightest score\n";
	std::cout << "4 - Options\n";
	std::cout << "5 - Quit\n";

	do
	{

		//get choise
		key = _getch();

		switch (key)
		{
		case '1':
			// "Start game";
			return;
		case '2':
			std::cout << "Instructions";
			return;
		case '3':
			std::cout << "Highest score";
			break;
		case '4':
			std::cout << "Settings";
			break;
		case '5':
			//exit
			return;
			break;
		}
	} while (key != '1' || key != '5');
}
void Menu::NewGame()
{
 // Player enters his name
}

void Menu::LoadGame(){ }

void Menu::StartGame()
{
	//write all of the fields from the config file in the global.h file
	//example for upkey
	ConfigFile config("game.cfg");
	Global::upKey = config.getValueOfKey<char>("upKey");
}

void Menu::Instructions()
{
	system("cls");
	std::cout << std::setw(41) << "Instructions"<< std::endl;
	std::cout << "Hello, player! The destiny of Earth is in your hands!"<<std::endl;
	std::cout << "Your mission is to destroy as many asteroids as you can.\n";
	std::cout << "During the game there are more asteroids, they get faster, and they break up into more pieces.\n";
	std::cout << "Use the W A S D keys on your keyboard to move."<<std::endl;
	std::cout << "With A you move left, with D - right, with S - up and with W - down. Or change the keys from settings.\n";
	std::cout << "Use the space key  to fire."<<std::endl;
	std::cout << "Hit P for pause." << std::endl;

	std::cout << "Clear all the asteroids and save the day!" << std::endl;
	std::cout <<std::endl;
	std::cout << "Please press\n";
	std::cout << "1 - Main Menu "<< std::endl;
	std::cout << "2 - Quit" << std::endl;
	char key;
	do
	{
		key = _getch();
		switch (key)
		{
		case '1':
			Menu();
			break;
		case '2':
			//	exitGame = true;
			return;
		}
	} while (key != '1' || key != '2');
}

void Menu::Options() 
{
	std::cout << std::setw (38) << "Options"<< std::endl;
	std::cout << std::setw (57) << "Please make your selection"<< std::endl;
	std::cout << " 1 - Play sounds\n";
	std::cout << " 2 - Stop sounds\n";
	std::cout << " 3 - Exit\n";
	char key;
	do
	{
		key = _getch();

		switch (key)
		{
		case '1':
		//	SoundsOn ();
			return;
		case '2':
	//		SoundsOff;
			return;
		case '3':
	//		exitGame = true;
			return;
			break;
		}
	}
	while ( key != '1' || key != '3');
}

void Menu::HighScore ()
{
	//here the data for the highscores should be read from the config file and displayed
	//example for the name of the first player
	ConfigFile config("game.cfg");
	std::string firstPlayerName = config.getValueOfKey<std::string>("firstPlayerName");
	//afterwards display them
}

void Menu::Credits(){ }
