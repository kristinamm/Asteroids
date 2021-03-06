#include <iostream>
#include <vector>
#include <conio.h>
#include <time.h>
#include <iomanip>
#include <algorithm>

#include "ConsoleGaming.h"
#include "Menu.h"
#include "Global.h"

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
//Boss variables
bool isBossAlive = false;
string bossDirection = "UP";
int bossHealth = 60;
unsigned int bossShootSpawnInterval = 7;
int bossFrames;
int score = 0;
int levelPassPoints = 100;
int currentLevel = 1;
int maximumAsteroidSize = 4;

// Game variables
unsigned long sleepDuration = 200;

bool endGame = false;
bool exitGame = false;
int maximumRocketsCount = 12;

vector<GameObject> ship;
vector<GameObject> asteroids;
vector<GameObject> rockets;
vector<GameObject> bosses;
vector<int> d(342342);

unsigned int frameCounter = 0;
unsigned int asteroidSpawnInterval = 10;

void InitializeShip()
{
	int shipY = WINDOW_HEIGHT / 2;
	int shipX = 2;
	char shipSymbol = '~';

#pragma region ship_Types
	int const charRows = 50;
	int const charCols = 50;
	char shipType1[charRows][charCols] = {
		{ '|', '-', '\\' },
		{ '=', ' ', '[', '_', '|', 'H', ')', '-', '-', '.', '_', '_', '_', '_', '_' },
		{ '=', ' ', '[', '+', '-', '-', ',', ' ', ',', '-', '-', '-', '-', '-', '-', '-', '\'' },
		{ '[', '|', ' ', '_', ' ', '/' }
	};
	char shipType2[charRows][charCols] = {
		{ ' ', '(', '}' },
		{ '<', '/', '\\' },
		{ ' ', '|', '\\', '\'', '-', '.', '_' },
		{ '/', ' ', '|', ' ', ' ', ' ', ' ', '`' },
		{ '`', ' ', ' ', '`', }
	};
	char shipType3[charRows][charCols] = {

		{ '^', },
		{ '<', ' ', '#', '=', '-', '>', },
		{ 'v', }

	};
#pragma endregion contains types of different ships

	switch (shipType)
	{
	case 1:
		ship.push_back(GameObject(shipX - 2, shipY - 1, shipSymbol));
		ship.push_back(GameObject(shipX - 1, shipY - 1, shipSymbol));
		ship.push_back(GameObject(shipX + 1, shipY - 1, shipSymbol));
		ship.push_back(GameObject(shipX, shipY, shipSymbol));
		ship.push_back(GameObject(shipX - 1, shipY + 1, shipSymbol));
		ship.push_back(GameObject(shipX - 2, shipY + 1, shipSymbol));
		ship.push_back(GameObject(shipX + 1, shipY + 1, shipSymbol));
		break;
	case 2:
		for (int rows = 0; rows < charRows; rows++)
		{
			for (int cols = 0; cols < charCols; cols++)
			{
				if (shipType1[rows][cols] != NULL)
				{
					ship.push_back(GameObject(cols + 2, rows + WINDOW_HEIGHT / 2, shipType1[rows][cols]));
				}
			}
		}
		break;
	case 3:
		for (int rows = 0; rows < charRows; rows++)
		{
			for (int cols = 0; cols < charCols; cols++)
			{
				if (shipType2[rows][cols] != NULL)
				{
					ship.push_back(GameObject(cols + 2, rows + WINDOW_HEIGHT / 2, shipType2[rows][cols]));
				}
			}
		}
		break;
	case 4:
		for (int rows = 0; rows < charRows; rows++)
		{
			for (int cols = 0; cols < charCols; cols++)
			{
				if (shipType3[rows][cols] != NULL)
				{
					ship.push_back(GameObject(cols + 2, rows + WINDOW_HEIGHT / 2, shipType3[rows][cols]));
				}
			}
		}
		break;
	}
}

ConsoleColor randomColor()
{
	int randomNumber = rand() % 5 + 1;
	switch (randomNumber)
	{
	case 1:
		return ConsoleColors::Blue;
		break;
	case 2:
		return ConsoleColors::Cyan;
		break;
	case 3:
		return ConsoleColors::Green;
		break;
	case 4:
		return ConsoleColors::Purple;
		break;
	case 5:
		return ConsoleColors::Red;
		break;
	case 6:
		return ConsoleColors::Yellow;
		break;
	}
	return ConsoleColors::White;
}


void InitializeBoss()
{
	int const bossHeight = 10;
	int const bossWidth = 18;
	int bossY = (WINDOW_HEIGHT / 2) - (bossHeight / 2);
	int bossX = WINDOW_WIDTH - bossWidth - 2;

	char bossMatrix[bossHeight][bossWidth] = {
		{ ' ', ' ', ' ', ' ', ' ', ' ', '/', '-', '-', '-', '-', '\\', ' ', ' ', ' ', ' ', ' ', ' ' },
		{ ' ', ' ', ' ', ' ', ' ', '/', ' ', ' ', ' ', ' ', ' ', ' ', '\\', ' ', ' ', ' ', ' ', ' ' },
		{ '<', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '>' },
		{ '<', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '>' },
		{ ' ', ' ', ' ', ' ', ' ', '\\', ' ', ' ', ' ', ' ', ' ', ' ', '/', ' ', ' ', ' ', ' ', ' ' },
		{ ' ', ' ', ' ', ' ', ' ', ' ', '\\', '-', '-', '-', '-', '/', ' ', ' ', ' ', ' ', ' ', ' ' }
	};

	for (int rows = 0; rows < bossHeight; rows++)
	{
		for (int cols = 0; cols < bossWidth; cols++)
		{
			if (bossMatrix[rows][cols] != NULL && bossMatrix[rows][cols] != ' ')
			{
				bosses.push_back(GameObject(cols + bossX, rows + bossY, bossMatrix[rows][cols]));
			}
		}
	}
}

void Fire()
{
	if (rockets.size() < maximumRocketsCount)
	{
		if (shipType == 1)
		{
			//the element of the ship which is in the middle
			GameObject mainShipElement = ship[3];
			//fire 4 rockets at once
			int firedRocketX = mainShipElement.Coordinates.X;
			int firedRocketY = mainShipElement.Coordinates.Y;
			GameObject firedRocket = GameObject(firedRocketX, firedRocketY, '-');
			rockets.push_back(firedRocket);
			firedRocketX = mainShipElement.Coordinates.X + 1;
			firedRocketY = mainShipElement.Coordinates.Y;
			firedRocket = GameObject(firedRocketX, firedRocketY, '-');
			rockets.push_back(firedRocket);
			firedRocketX = mainShipElement.Coordinates.X + 1;
			firedRocketY = mainShipElement.Coordinates.Y - 1;
			firedRocket = GameObject(firedRocketX, firedRocketY, '-');
			rockets.push_back(firedRocket);
			firedRocketX = mainShipElement.Coordinates.X + 1;
			firedRocketY = mainShipElement.Coordinates.Y + 1;
			firedRocket = GameObject(firedRocketX, firedRocketY, '-');
			rockets.push_back(firedRocket);
		}
		else if (shipType == 2)
		{
			//the element of the ship which is in the middle
			GameObject mainShipElement = ship[33];
			//fire 2 rockets at once
			int firedRocketX = mainShipElement.Coordinates.X + 1;
			int firedRocketY = mainShipElement.Coordinates.Y;
			GameObject firedRocket = GameObject(firedRocketX, firedRocketY, '-');
			rockets.push_back(firedRocket);
			firedRocketX = mainShipElement.Coordinates.X + 1;
			firedRocketY = mainShipElement.Coordinates.Y - 1;
			firedRocket = GameObject(firedRocketX, firedRocketY, '_');
			rockets.push_back(firedRocket);
		}
		else if (shipType == 4)
		{
			//the element of the ship which is in the middle
			GameObject mainShipElement = ship[5];
			//fire 2 rockets at once
			int firedRocketX = mainShipElement.Coordinates.X + 1;
			int firedRocketY = mainShipElement.Coordinates.Y;
			GameObject firedRocket = GameObject(firedRocketX, firedRocketY, '-');
			rockets.push_back(firedRocket);
		}
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
	for (randomAccess_iterator boss = bosses.begin(); boss != bosses.end(); ++boss)
	{
		for (randomAccess_iterator shipBody = ship.begin(); shipBody != ship.end(); ++shipBody)
		{
			bool isXEqual = shipBody->Coordinates.X == boss->Coordinates.X;
			bool isYEqual = shipBody->Coordinates.Y == boss->Coordinates.Y;
			if (isXEqual == true && isYEqual == true)
			{
				EndGame();
			}
		}
	}

	//detect rocket collisions

	//there are issues with different parity of fired rocket x and asteroid x,
	//so it must be iterated in reverse
	for (int i = asteroids.size() - 1; i >= 0; i--)
	{
		bool deleteAsteroid = false;
		for (randomAccess_iterator rocket = rockets.begin(); rocket != rockets.end();)
		{
			//also needed for parity issues
			bool isXEqual = rocket->Coordinates.X == asteroids[i].Coordinates.X ||
				rocket->Coordinates.X + 1 == asteroids[i].Coordinates.X;
			bool isYEqual = rocket->Coordinates.Y == asteroids[i].Coordinates.Y;
			if (isXEqual == true && isYEqual == true)
			{
				deleteAsteroid = true;
				rocket = rockets.erase(rocket);
			}
			else
			{
				++rocket;
			}
		}
		if (deleteAsteroid == true)
		{
			i = std::distance(asteroids.begin(), asteroids.erase(asteroids.begin() + i));
		}
	}

	//detect if boss is hit
	if (isBossAlive)
	{
		for (int i = bosses.size() - 1; i >= 0; i--)
		{
			bool isBossHitted = false;
			for (randomAccess_iterator rocket = rockets.begin(); rocket != rockets.end();)
			{
				bool isXEqual = rocket->Coordinates.X == bosses[i].Coordinates.X;
				bool isYEqual = rocket->Coordinates.Y == bosses[i].Coordinates.Y;
				if (isXEqual == true && isYEqual == true)
				{
					isBossHitted = true;
					rocket = rockets.erase(rocket);
				}
				else
				{
					++rocket;
				}
			}
			if (isBossHitted)
			{
				i = std::distance(bosses.begin(), bosses.erase(bosses.begin() + i));
				bossHealth -= 5;
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
		//switch from switch and case to if and else if
		if (key == leftKey)
		{
			direction.X = -shipSpeed;
			direction.Y = 0;
		}
		else if (key == upKey)
		{
			direction.X = 0;
			direction.Y = -shipSpeed;
		}
		else if (key == rightKey)
		{
			direction.X = shipSpeed;
			direction.Y = 0;
		}
		else if (key == downKey)
		{
			direction.X = 0;
			direction.Y = shipSpeed;
		}
		else if (key == fireKey)
		{
			Fire();
			//if (Global::isSoundOn)
			//{

			//	//PlaySound(TEXT("shoot.mp3"),NULL, SND_FILENAME | SND_ASYNC);
			//	//PlaySound(NULL, 0, 0);
			//}
		}
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
	if (frameCounter % levelPassPoints == 0 && frameCounter != 0 && !isBossAlive)
	{
		asteroids.clear();
		rockets.clear();
		InitializeBoss();
		isBossAlive = true;
	}
	if (bossHealth <= 0 && isBossAlive)
	{
		isBossAlive = false;
		bossHealth = 60 + 10*currentLevel;
		bosses.clear();
		frameCounter = 0;
		if (asteroidSpawnInterval != 0 && sleepDuration != 0)
		{
			levelPassPoints += 50;
			sleepDuration -= 15;
			currentLevel += 1;
			maximumAsteroidSize += 1;
		}
		if (currentLevel & 1 == 0)
		{
			asteroidSpawnInterval -= 1;
		}
	}

	if (!isBossAlive)
	{
		if (frameCounter % asteroidSpawnInterval == 0)
		{
			// Spawn a new asteroid at every x frames

			//in the console there are more columns than rows
			//so the asteroids should be wider than they are tall
			int asteroidWidth = rand() % maximumAsteroidSize + 2; //from 1 to 4
			int asteroidHeight = rand() % maximumAsteroidSize + 1; //from 1 to 3

			int y = rand() % (WINDOW_HEIGHT - 3) + 3;

			ConsoleColor asteroidColor = randomColor();

			for (int i = 0; i < asteroidWidth; i++)
			{
				for (int j = 0; j < asteroidHeight; j++)
				{
					GameObject newAsteroid = GameObject(0, 0, AsteroidSymbol);
					if (y + j < WINDOW_HEIGHT)
					{
						newAsteroid = GameObject(WINDOW_WIDTH - 1 - i, y + j, AsteroidSymbol);
						newAsteroid.Color = asteroidColor;
						asteroids.push_back(newAsteroid);
					}
					else
					{
						newAsteroid = GameObject(WINDOW_WIDTH - 1 - i, y, AsteroidSymbol);
						asteroids.push_back(newAsteroid);
					}
					std::find(asteroids.begin(), asteroids.end(), newAsteroid)->Color = randomColor();
				}
			}
		}
	}
	//movements of the boss
	if (isBossAlive)
	{
		for (randomAccess_iterator boss = bosses.begin(); boss != bosses.end();)
		{
			if (bossDirection == "UP")
			{
				if (boss->Coordinates.Y <= 3)
				{
					bossDirection = "Down";
				}
				else
				{
					boss->Coordinates.Y -= asteroidSpeed;
					++boss;
				}
			}
			else
			{
				if (boss->Coordinates.Y >= WINDOW_HEIGHT - 5 && boss == bosses.end() - 1)
				{
					bossDirection = "UP";
					boss->Coordinates.Y += asteroidSpeed + 1;
				}
				else
				{
					boss->Coordinates.Y += asteroidSpeed;
					++boss;
				}
			}
		}

		//boss shooting 
		if (frameCounter % bossShootSpawnInterval == 0)
		{
			//the element of the ship which is in the middle
			GameObject mainBossElement = bosses[8];
			//fire 2 rockets at once
			int firedRocketX = mainBossElement.Coordinates.X - 1;
			int firedRocketY = mainBossElement.Coordinates.Y;
			GameObject firedRocket = GameObject(firedRocketX, firedRocketY, '*');
			asteroids.push_back(firedRocket);

			firedRocketX = mainBossElement.Coordinates.X;
			firedRocketY = mainBossElement.Coordinates.Y;
			GameObject firedRocket2 = GameObject(firedRocketX, firedRocketY, '*');
			asteroids.push_back(firedRocket2);

			firedRocketX = mainBossElement.Coordinates.X + 1;
			firedRocketY = mainBossElement.Coordinates.Y;
			GameObject firedRocket3 = GameObject(firedRocketX, firedRocketY, '*');
			asteroids.push_back(firedRocket3);
		}
	}
	++frameCounter;
	score += frameCounter;
}

inline bool operator==(const GameObject& go1, const GameObject& go2)
{
	if (go1.Coordinates.X == go2.Coordinates.X && go1.Coordinates.Y == go2.Coordinates.Y)
	{
		return true;
	}
	return false;
}

void Draw()
{
	ClearScreen(consoleHandle);

	//highscore
	if (!isBossAlive)
	{
		std::cout << setw(20) << "Level: " << currentLevel;
		std::cout << setw(40) << "Score: " << score << endl;
	}
	if (isBossAlive)
	{
		std::cout << setw(20) << "Level: " << currentLevel;
		std::cout << setw(20) << "Score: " << score;
		std::cout << setw(20) << "Health: " << bossHealth << endl;
	}
	for (int i = 0; i < WINDOW_WIDTH; i++)
	{
		cout << "-";
	}

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
	if (isBossAlive)
	{
		for (randomAccess_iterator boss = bosses.begin(); boss != bosses.end(); ++boss)
		{
			boss->Draw(consoleHandle);
		}
	}
}

int main()
{

	Menu::Initialize();

	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	srand(time(NULL));

	//add the ship
	InitializeShip();



	//game loop
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
	std::cout << "Game Over, your score is: " << score<< endl;
	//TODO: add highscores in externel file
	return 0;
}
