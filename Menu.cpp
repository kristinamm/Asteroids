#include <iostream>
#include <vector>
#include <conio.h>
#include <time.h>
#include <iomanip>

//#include "configParser.cpp"
#include "ConsoleGaming.h"
#include "Menu.h"
#include "Global.h"

const std::string Logo[9] = {
	//Sorry, but i have to put two backslashes when i want to display only one. It doesn't look as good as i would want in the code
	"                                                              L.Raykov, S.Sinapov, K.Mileva, K.Kartuleva\n",
	"                             _                 _     _                           \n",
	"                   /\\       | |               (_)   | |                         \n",
	"                  /  \\   ___| |_ ___ _ __ ___  _  __| |___                      \n",
	"                 / /\\ \\ / __| __/ _ \\ '__/ _ \\| |/ _` / __|                  \n",
	"                / ____ \\\\__ \\ ||  __/ | | (_) | | (_| \\__ \\                 \n",
	"               /_/    \\_\\\___/\\__\\___|_|  \\___/|_|\\__,_|___/               \n",
	"  \n",
	"  \n",
};

const std::string MainMenu[5] =
{
	"                             1 - Start game                                     \n",
	"                             2 - Instructions                                   \n",
	"                             3 - Hightest score                                 \n",
	"                             4 - Options                                        \n",
	"                             5 - Quit                                           \n",
};
bool ShowIntro = true;


void Menu::ColorGray()
{

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);

}

void Menu::ColorLwhite()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void Menu::ColorCyan()
{	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
}

void Menu::ColorRed()
{	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
}

void Menu::ColorReset()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); 
}
void Menu::Initialize() 
{
	char key;

	system("cls");
	//Displays Options
	std::cout << std::setw(39) << "MAIN MENU"<< std::endl;
	std::cout << std::setw(57) << "Please make your selection"<< std::endl;
	std::cout << "1 - New Game\n";
	std::cout << "2 - Instructions\n";
	std::cout << "3 - Hightest score\n";
	std::cout << "4 - Options\n";
	std::cout << "5 - Quit\n";

	if (ShowIntro)
	{
		Sleep(200);
		Menu::ColorCyan();
		for (int x = 0; x < 10; x++)
		{

			if (x == 9){ std::cout << std::endl; }

			if (x >= 8)
			{
				Menu::ColorGray();
				std::cout << Logo[0];
				Menu::ColorCyan();
			}

			if (x >= 7){ std::cout << Logo[1]; }
			if (x >= 6){ std::cout << Logo[2]; }
			if (x >= 5){ std::cout << Logo[3]; }
			if (x >= 4){ std::cout << Logo[4]; }
			if (x >= 3){ std::cout << Logo[5]; }
			if (x >= 2){ std::cout << Logo[6]; }
			if (x >= 1){ std::cout << Logo[7]; }
			if (x >= 0){ std::cout << Logo[8]; }

			Sleep(100);
			if (x<9){ system("cls"); }
		}
	}
	//Menu::ColorReset();
	Beep(300, 50); Beep(400, 400);


	if (MainMenu != NULL)
	{
		std::cout << MainMenu[0];
		std::cout << MainMenu[1];
		std::cout << MainMenu[2];
		std::cout << MainMenu[3];
		std::cout << MainMenu[4];
	}

	do
	{
		//get choise
		key = _getch();

		switch (key)
		{
		case '1':
			NewGame();
			return;
		case '2':
			Instructions();
			return;
		case '3':
			HighScore();
			return;
		case '4':
			Options();
			return;
		case '5':
			exit(0);
			Menu::Options();
			break;
		} 
	}while (key != '1' || key != '5');
}
void Menu::NewGame()
{
	system("cls");
	std::cout<<"Enter your name: ";
	std::string newPlayerName = "";
	std::cin>>newPlayerName;
	StartGame(newPlayerName);
	return;
}

void Menu::LoadGame(){ }

void Menu::StartGame(std::string newPlayerName)
{
	//write all of the fields from the config file in the global.h file
	//example for upkey
	//ConfigFile config("game.cfg");
	//upKey = config.getValueOfKey<char>("upKey");
	playerName = newPlayerName;
	return;
}

void Menu::Instructions()
{
	system("cls");
	std::cout << std::setw(41) << "Instructions"<< std::endl;
	std::cout << "Hello, player! The destiny of Earth is in your hands!"<<std::endl;
	std::cout << "Your mission is to destroy as many asteroids as you can.\n";
	std::cout << "During the game there are more asteroids, they get faster, and they break up into more pieces.\n";
	std::cout << "Use the";
	ColorRed();
	std::cout << " W A S D ";
	ColorCyan();
	std::cout<<"keys on your keyboard to move." << std::endl;
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
			Menu::Initialize();
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
	std::cout << " 3 - Back\n";
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
			Menu::Initialize();
			return;
		}
	}
	while ( key != '1' || key != '3');
}

void Menu::HighScore ()
{
	//here the data for the highscores should be read from the config file and displayed
	//example for the name of the first player
	//ConfigFile config("game.cfg");
	//std::string firstPlayerName = config.getValueOfKey<std::string>("firstPlayerName");
	//afterwards display them
}

void Menu::Credits(){ }
