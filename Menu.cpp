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
	std::cout << setw (39) << "MAIN MENU"<< std::endl;
	std::cout << setw (57) << "Please make your selection"<< std::endl;
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
}

void Menu::Instructions()
{

	//ClearScreen(consoleHandle);
	system("cls");
	/*
	#define BLUE 1
	#define GREEN 2
	#define RED 3
	#define YELLOW 4
	#define WHITE 5
	HANDLE screen;
	int textcolor = YELLOW;
	int backgroundcolor = BLACK;
	screen = GetStdHandle(STD_OUTPUT_HANDLE);
	
	void TextColor(int fontcolor,int backgroundcolor,HANDLE screen)
	{
	
	int color_attribute;
	color_attribute = backgroundcolor;
	color_attribute = _rotl(color_attribute,4) | fontcolor;
	SetConsoleTextAttribute(screen,color_attribute);
	
	}
	*/

	std::cout << setw(41) << "Instructions"<< std::endl;
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
	std::cout << setw (38) << "Options"<< std::endl;
	std::cout << setw (57) << "Please make your selection"<< std::endl;
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

void Menu::HighScore ( stuct g_1place, struct g_2place, struct g_3place, int g_playerCredits, char g_playerName, int g_level)
{
	if (g_playerCredits >= g_3place.points)
	{
		g_3place.points = g_playerCredits;
		g_3place.name = g_playerName;
		g_3place.level = g_level;
		
	}
	if (g_playerCredits >= g_2place.points)
	{
		g_2place.points = g_playerCredits;
		g_2place.name = g_playerName;
		g_2place.level = g_level;
	
	}
	if (g_playerCredits >= g_1place.points)
	{
		g_1place.points = g_playerCredits;
		g_1place.name = g_playerName;
		g_1place.level = g_level;
	
	}
	
	std::cout << "1-st place " << g_1place.name << " scores " << g_1place.points << " level " << g_1place.level << std::endl;
	std::cout << "2-nd place " << g_2place.name << " scores " << g_2place.points << " level " << g_2place.level << std::endl;
	std::cout << "3-rd place " << g_3place.name << " scores " << g_3place.points << " level " << g_3place.level << std::endl;
}

void Menu::Credits(){ }
