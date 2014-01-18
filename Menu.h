#pragma once
static class Menu
{
	private: 
		static void Menu::StartGame();
	public:
		static void Menu::Initialize();
		static void Menu::NewGame();
		static void Menu::LoadGame();
		static void Menu::Instructions();
		static void Menu::HighScore(int g_1place, int g_2place, int g_3place, int g_playerCredits, int g_playerName, int g_level);
		static void Menu::Credits();
		static void Menu::Options();
};

