#pragma once

#include "pch.h"

class Menu
{
public:

	static void updateInput(sf::Event &event);
	static void update(const float &deltaTime, const sf::Vector2i &mousePos);
	static void render(const sf::RenderTarget *target);	
private:

};