Asteroids
=========


Стефан Борисов Синапов - фак. № 61714

Любомир Петров Райков - фак. № 61735

Кристина Марио Милева - фак. № 61674

Катрин Костадинова Картулева - фак. № 61756

A C++, console-based version of the game asteroids.




Tasks
======
## General

-	Create a repo @ github.com. Send me a mail with a list of all team members and the link to the repo BEFORE 23.12.2013!
-	Choose / Invent your own  naming convention and explicitly write in the README.md file of your project
-	Fix all bugs currently in the game. Implement missing functionality.
-	Add a simple menu that allows the player to:
	*	Start a game
	*	See instructions about the game
	*	Show the highest score the player has achieved in this session
	*	Change settings (controls, graphics, audio) **[BONUS]**
	*	Exit the game
	
	The menu shall be the first thing a player sees and the player MUST have the option to return to the main menu at ANYTIME.
	
-	Add aesthetics to your game. Choose appropriate colours, ASCII art and audio.
-	Actually implement an Audio system using either `cout << '\a';` or the Windows function Beep (google it). **[BONUS]**
-	Implement save / load functionality. Use file streams (google them) **[BONUS]**
-	Do all the above adhering to the naming convention of your choice!


## Asteroids

-	Add asteroids of different sizes and colours
-	Add space ships of different sizes and colours
-	Implement collision detection
-	Give the space ship the ability to shoot down asteroids
-	Add bosses to the game - other space ships that have their own personal arsenal and don't die on first hit.
-	Give the player health / lives, allow him to survive more than a single hit with an asteroid
-	Add power-ups - bonuses that help the player like improving his fire power or speeding him up
-	Add levels to the game - it may be something as simple as increasing the speed at which asteroids come at the player, decreasing the interval during which they spawn or slowing down the player
-	Implement an RPG-like skill system. Have the space-ship gain abilities like moving trough rocks, gaining speed, etc.  **[BONUS]**