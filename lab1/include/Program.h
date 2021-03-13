#pragma once

#include "Menu.h"

class Program
{
public:
	Program();
	~Program();

	void update();
	void render();
	void run();

private:
	void initWindow();
	void updateDeltaTime();
	void updateSFMLEvents();

	sf::RenderWindow *window;
	sf::Event event;

	sf::Clock dtClock;
	float deltaTime;
};