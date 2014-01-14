#include <iostream>
#include <vector>
#include <conio.h>
#include <time.h>

#include "ConsoleGaming.h"
#include "Menu.h"
void Menu::Initialize() 
{
	char key;

	system("cls");
	//Displays Options
	std::cout << "Main Menu\n";
	std::cout << "Please make your selection\n";
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
void Menu::NewGame(){ }
void Menu::LoadGame(){ }
void Menu::StartGame(){ }
void Menu::Instructions(){ }
void Menu::HighScore(){ }
void Menu::Credits(){ }