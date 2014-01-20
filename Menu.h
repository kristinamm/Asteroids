#pragma once
static class Menu
{
	private: 
		static void Menu::StartGame(std::string);
	public:
		static void Menu::Initialize();
		static void Menu::NewGame();
		static void Menu::LoadGame();
		static void Menu::Instructions();
		static void Menu::HighScore();
		static void Menu::Credits();
		static void Menu::Options();
};

