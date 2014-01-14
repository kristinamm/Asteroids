#include <iostream>
#include <vector>
#include <conio.h>
#include <time.h>

#include "ConsoleGaming.h"
#include "Menu.h"

using namespace std;

HANDLE consoleHandle;

typedef vector<GameObject>::iterator randomAccess_iterator;
typedef vector<GameObject>::const_iterator const_iterator;

// Window constants
const int WINDOW_WIDTH = 70;
const int WINDOW_HEIGHT = 25;
// Asteroid variables
const char AsteroidSymbol = '#';
int asteroidSpeed = 1;
// Ship variables
int shipSpeed = 1;

// Game variables
unsigned long sleepDuration = 200;

bool endGame = false;
bool exitGame = false;
int maximumRocketsCount = 12;

vector<GameObject> ship;
vector<GameObject> asteroids;
vector<GameObject> rockets;

unsigned int frameCounter = 0;
unsigned int asteroidSpawnInterval = 10;



void Fire()
{
	//the element of the ship which is in the middle
	GameObject mainShipElement = ship[3];
	if (rockets.size() < maximumRocketsCount)
	{
		//fire 4 rockets at once
		int firedRocketX = mainShipElement.Coordinates.X + 1;
		int firedRocketY = mainShipElement.Coordinates.Y;
		GameObject firedRocket = GameObject(firedRocketX, firedRocketY, '-');
		rockets.push_back(firedRocket);
		firedRocketX = mainShipElement.Coordinates.X + 2;
		firedRocketY = mainShipElement.Coordinates.Y;
		firedRocket = GameObject(firedRocketX, firedRocketY, '-');
		rockets.push_back(firedRocket);
		firedRocketX = mainShipElement.Coordinates.X + 2;
		firedRocketY = mainShipElement.Coordinates.Y - 1;
		firedRocket = GameObject(firedRocketX, firedRocketY, '-');
		rockets.push_back(firedRocket);
		firedRocketX = mainShipElement.Coordinates.X + 2;
		firedRocketY = mainShipElement.Coordinates.Y + 1;
		firedRocket = GameObject(firedRocketX, firedRocketY, '-');
		rockets.push_back(firedRocket);
	}
}

void EndGame()
{
	endGame = true;
}

void DetectCollisions()
{
	//detect ship collisions
	for (randomAccess_iterator asteroid = asteroids.begin(); asteroid != asteroids.end(); ++asteroid)
	{
		for (randomAccess_iterator shipBody = ship.begin(); shipBody != ship.end(); ++shipBody)
		{
			bool isXEqual = shipBody->Coordinates.X == asteroid->Coordinates.X;
			bool isYEqual = shipBody->Coordinates.Y == asteroid->Coordinates.Y;
			if (isXEqual == true && isYEqual == true)
			{
				EndGame();
			}
		}
	}
	//detect rocket collisions

	//there are issues with different parity of fired rocket x and asteroid x,
	//so it must be iterated in reverse
	//TODO: replace with std::vector<GameObject>::reverse_iterator
	for (unsigned i = asteroids.size(); i-- > 0;)
	{
		for (randomAccess_iterator rocket = rockets.begin(); rocket != rockets.end();)
		{
			//also needed for parity issues
			bool isXEqual = rocket->Coordinates.X == asteroids[i].Coordinates.X ||
				rocket->Coordinates.X + 1 == asteroids[i].Coordinates.X;
			bool isYEqual = rocket->Coordinates.Y == asteroids[i].Coordinates.Y;
			if (isXEqual == true && isYEqual == true)
			{
				asteroids.erase(asteroids.begin() + i);
				rocket = rockets.erase(rocket);
			}
			else
			{
				++rocket;
			}
		}
	}
}

void Update()
{
	COORD direction = { 0, 0 };
	if (_kbhit())
	{
		char key = _getch();
		switch (key)
		{
		case 'a':
			direction.X = -shipSpeed;
			direction.Y = 0;
			break;
		case 'w':
			direction.X = 0;
			direction.Y = -shipSpeed;
			break;
		case 'd':
			direction.X = shipSpeed;
			direction.Y = 0;
			break;
		case 's':
			direction.X = 0;
			direction.Y = shipSpeed;
			break;
		case ' ':
			Fire();
			break;
		};
	}
	for (randomAccess_iterator shipBody = ship.begin(); shipBody != ship.end(); ++shipBody)
	{
		shipBody->Coordinates.X += direction.X;
		shipBody->Coordinates.Y += direction.Y;
	}
	//update rockets position and remove ones that go out of the screen
	for (randomAccess_iterator rocket = rockets.begin(); rocket != rockets.end();)
	{
		rocket->Coordinates.X += asteroidSpeed;
		if (rocket->Coordinates.X > WINDOW_WIDTH)
		{
			rocket = rockets.erase(rocket);
		}
		else
		{
			++rocket;
		}
	}
	// Update the position of all asteroids. Remove any asteroid that goes outside the window


	for (randomAccess_iterator asteroid = asteroids.begin(); asteroid != asteroids.end();)
	{
		asteroid->Coordinates.X -= asteroidSpeed;
		if (asteroid->Coordinates.X <= 0)
		{
			asteroid = asteroids.erase(asteroid);
		}
		else
		{
			++asteroid;
		}
	}

	if (frameCounter % asteroidSpawnInterval == 0)
	{
		// Spawn a new asteroid at every x frames

		//in the console there are more columns than rows
		//so the asteroids should be wider than they are tall
		int asteroidWidth = rand() % 4 + 1; //from 1 to 4
		int asteroidHeight = rand() % 3 + 1; //from 1 to 3

		int y = rand() % WINDOW_HEIGHT;

		for (int i = 0; i < asteroidWidth; i++)
		{
			for (int j = 0; j < asteroidHeight; j++)
			{
				if (y + j < WINDOW_HEIGHT)
				{
					GameObject newAsteroid = GameObject(WINDOW_WIDTH - 1 - i, y + j, AsteroidSymbol);
					newAsteroid.Color = ConsoleColors::Red; //TODO: add random color asteroids
					asteroids.push_back(newAsteroid);
				}
				else
				{
					asteroids.push_back(GameObject(WINDOW_WIDTH - 1 - i, y, AsteroidSymbol));
				}
			}
		}
	}
	++frameCounter;
}

void Draw()
{
	ClearScreen(consoleHandle);

	for (const_iterator shipBody = ship.cbegin(); shipBody != ship.cend(); ++shipBody)
	{
		shipBody->Draw(consoleHandle);
	}

	for (const_iterator asteroid = asteroids.cbegin(); asteroid != asteroids.cend(); ++asteroid)
	{
		asteroid->Draw(consoleHandle);
	}
	for (randomAccess_iterator rocket = rockets.begin(); rocket != rockets.end(); ++rocket)
	{
		rocket->Draw(consoleHandle);
	}
}

void InstructionsMenu()
{
	//ClearScreen(consoleHandle);
	system("cls");
	cout << "Hello, player! The destiny of Earth is in your hands!"<<endl;
	cout << "Use the W A S D keys on your keyboard to move."<<endl;
	cout << "With A you move left, with D - right, with S - up and with W - down. Use the space key  to fire."<<endl;
	cout << "Hit P for pause. During the game there are more asteroids, they get faster, and they break up into more pieces." << endl;

	cout << "Clear all the asteroids and save the day!" << endl;
	cout << "Please press\n";
	cout << "1 - Main Menu "<< endl;
	cout << "2 - Quit" << endl;
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
			exitGame = true;
			return;
		}
	} while (key != '1' || key != '2');
}
<<<<<<< HEAD
=======

void Menu ()
{
	system("cls");
	cout << "MAIN MENU\n";
	cout << "Please make your selection\n";
	cout << " 1 - Start game\n";
	cout << " 2 - Instructions\n";
	cout << " 3 - Highest score\n";
	cout << " 4 - Options\n";
	cout << " 5 - Quit\n";
	do
	{
	key = _getch();

		switch (key)
		{
		case '1':
			main ();
			return;
		case '2':
			cout << "Instructions";
			InstructionsMenu();
			return;
		case '3':
			cout << "Highest score";
			break;
		case '4':
			cout << "Settings";
			break;
		case '5':
			exitGame = true;
			return;
			break;
		}	
	}
	 while (key != '1' || key != '5');
	
}

/*void Options ()
{
	cout << "Please make your selection\n";
	cout << " 1 - Play sounds\n";
	cout << " 2 - Stop sounds\n";
	cout << " 3 - Exit\n";
	
	do
	{
	
	key = _getch();

		switch (key)
		{
		case '1':
			SoundsOn ();
			return;
		case '2':
			SoundsOff;
			return;
		case '3':
			exitGame = true;
			return;
			break;
		}
	}
	while ( key != '1' || key != '3');
}
	*/
>>>>>>> 6e7282a1bc665530822ee887927de69e0924c372

int main()
{

	Menu::Initialize();

	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	srand(time(NULL));

	int shipY = WINDOW_HEIGHT / 2;
	int shipX = 2;
	char shipSymbol = '*';
	ship.push_back(GameObject(shipX - 2, shipY - 1, shipSymbol));
	ship.push_back(GameObject(shipX - 1, shipY - 1, shipSymbol));
	ship.push_back(GameObject(shipX + 1, shipY - 1, shipSymbol));
	ship.push_back(GameObject(shipX, shipY, shipSymbol));
	ship.push_back(GameObject(shipX - 1, shipY + 1, shipSymbol));
	ship.push_back(GameObject(shipX - 2, shipY + 1, shipSymbol));
	ship.push_back(GameObject(shipX + 1, shipY + 1, shipSymbol));

	while (true)
	{
		Update();
		DetectCollisions();

		if (endGame == true)
		{
			break;
		}
		if (exitGame)
		{
			ClearScreen(consoleHandle);
			return 0;
		}

		Draw();
		Sleep(sleepDuration);
	}

	ClearScreen(consoleHandle);
	std::cout << "Game Over, your score is: " << frameCounter << endl;
	//TODO: add highscores in externel file
	return 0;
}
