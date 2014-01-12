#include <iostream>
#include <vector>
#include <conio.h>
#include <time.h>

#include "ConsoleGaming.h"

using namespace std;

HANDLE consoleHandle;

typedef vector<GameObject>::iterator randomAccess_iterator;
typedef vector<GameObject>::const_iterator const_iterator;

// Window constants
const int WINDOW_WIDTH = 70;
const int WINDOW_HEIGHT = 27;
// Asteroid variables
const char AsteroidSymbol = '#';
int asteroidSpeed = 1;
// Ship variables
int shipSpeed = 1;

// Game variables
unsigned long sleepDuration = 200;

int maximumRocketsCount = 3;

vector<GameObject> ship;
vector<GameObject> asteroids;
vector<GameObject> rockets;

unsigned int frameCounter = 0;
unsigned int asteroidSpawnInterval = 10;

void Fire()
{
	//the element of the ship which is in the middle
	GameObject mainShipElement = ship[3]; 
	if(rockets.size() < maximumRocketsCount)
	{
		int firedRocketX = mainShipElement.Coordinates.X + 1;
		int firedRocketY = mainShipElement.Coordinates.Y;
		GameObject firedRocket = GameObject(firedRocketX, firedRocketY,'-');
		rockets.push_back(firedRocket);
	}
}

void DetectColisions()
{
}

void Update()
{
	COORD direction = { 0, 0 };
	if (kbhit())
	{
		char key = getch();
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
	for (randomAccess_iterator rocket = rockets.begin(); rocket != rockets.end(); ++rocket)
	{
		if(rocket->Coordinates.X > WINDOW_WIDTH)
		{
			rocket = rockets.erase(rocket);
		}
		rocket->Coordinates.X += asteroidSpeed;
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
					newAsteroid.Color = ConsoleColors::Red;
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

int main()
{
	consoleHandle = GetStdHandle( STD_OUTPUT_HANDLE );

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
		DetectColisions();
		Draw();
		Sleep(sleepDuration);
	}

	return 0;
}
